---
title: Contador de pulsos externos
summary: Nesses três exemplos vamos explorar gradativamente como fazer um contador de eventos externos no Franzininho DIY
authors:
    - Eduardo Dueñas
date: 05/05/2020
some_url: [Quem sou eu](https://github.com/EduardoDuenas)
---

#**Contador de pulsos externos**
 
##**Introdução**    
Nesses três exemplos vamos explorar gradativamente como fazer um contador de eventos externos no Franzininho DIY. Vamos explorar as formas mais simples e as mais complexas de contar eventos e as vantagens de cada uma. Nesses exemplos vamos aprender a usar o timer e a fazer debounce, necessário para lermos apenas eventos válidos e não ler o mesmo evento mais de uma vez.
 
Boa prática!
 
##**Recursos necessários**
 
- Franzininho DIY (com Micronúcleos)
- 4 leds de 3mm
- 4 resistores de 200Ω
- 1 chave tactil
- 1 resistor de 10kΩ
- 7 jumpers macho-fêmea
- 7 jumpers macho-macho
 
##**Contadores**
 
Temos três exemplos de contadores da versão 1 a 3, e aumentando a complexidade do código e dos recursos utilizados.
 
###**Contador_v1**
 
Nesse exemplo vamos utilizar loops para fazer a verificação de eventos. Essa forma de se fazer a contagem, apesar de ser mais simples de se entender e criar, é pouco eficiente, tanto a nível de processamento, quanto ao de energia.
 
O programa é um código em linguagem C e faz uso dos nomes dos registradores definidos na biblioteca "avr/io.h". Para melhor entendimento recomendo ler os comentários do código e o datasheet do ATtiny85.
 
####**Código**
```c
/**
 * 
 * @file main.c
 * @author Eduardo Dueñas
 * @brief Exemplo de contador de eventos
 * @version 1.0
 * @date 06/04/2021
 * 
 */
 
#include <avr/io.h>
 
#define F_CPU 16500000L
    
#define setBit(valor,bit) (valor |= (1<<bit))
#define clearBit(valor,bit) (valor &= ~(1<<bit))
#define toogleBit(valor,bit) (valor ^= (1<<bit))
#define testBit(valor,bit)    (valor & (1<<bit))
 
 
//debounce do push button para desconsiderarmos ruído e bouncing do botão
char debounce(int pino){
    unsigned int i;
    for(i=0;i<20000;i++){            //testa o pino várias vezes para evitar leituras erradas
        if(!(testBit(PINB,pino))){   //testa se o pino deixou de ser 1
            return 0;           //se sim, retorna falso
        }
    }
    return 1;                    //retorna verdadeiro
}
 
 
 
 
int main(void){
    //Configuração de PORTB
    clearBit(DDRB,PB0);     //Configura PB0 como entrada
    setBit(DDRB,PB1);       //Configura PB1 como saida
    setBit(DDRB,PB2);       //Configura PB2 como saida
    setBit(DDRB,PB3);       //Configura PB3 como saida
    setBit(DDRB,PB4);       //Configura PB4 como saida
    
    PORTB &= 0xE1;          //manda 0 para PB[4:1]
    
    unsigned char count = 0;
 
    for(;;){                   //loop infinito
 
        if(testBit(PINB,PB0)){                 //testa de PB0 é 1
            if(debounce(PB0)){                  //verifica se realmente foi um aperto de botão
                count++;                        //se sim, incrementa o contador
                while (testBit(PINB,PB0)){}    //espera o botão parar de ser pressionado
                
            }            
        }
        count = count % 0x10;                   //limpa o overflow docontador
        PORTB = ((PORTB & 0xE1) | (count<<1));       //manda o contador para PB[4:1]
    }              
}
```
 
####**Montagem**
 
![][Circuito v1]
 
Como mostrado na imagem, os leds são ligados nas saídas PortB[4:1] e o botão no PortB[0].
 
####**Compilação e upload**
 
Para compilar o programa, assim como nos programas anteriores, acesse a pasta do exemplo e em seguida o comando `make`:
```
exemplos-avr-libc/exemplos/contador$ make
```
Como já temos o makerfile configurado na pasta, será feita compilação e deve aparecer a seguinte mensagem:
 
```
../../micronucleus/2.0a4/launcher  -cdigispark --timeout 60 -Uflash:w:main.hex:i
Running Digispark Uploader...
Plug in device now... (will timeout in 60 seconds)
> Please plug in the device (will time out in 60 seconds) ...
```
Conecte a placa em uma entrada USB ou, caso a Franzininho já esteja conectada, aperte o botão de reset para iniciar o upload.
 
####**Resultado**
 
Os leds devem mostrar a contagem de apertos do botão de forma binária resetando em 0x10 ou quando resetada a placa.
 
####**Análise**
 
Esse código é de simples compreensão usando apenas um for para checar continuamente se o botão foi apertado, chamando uma função debounce caso a leitura seja 1, incrementando o contador se for confirmado que a leitura é válida, esperando  o botão ser solto e mandando o valor para as saídas. 
 
De forma geral esse código funciona, mas há muito desperdício de processamento, pois há muitos momentos que o processador não está fazendo nada, apenas esperando algo acontecer ou um certo tempo passar, nesse tempo ele poderia estar fazendo outra tarefas ou ficar em modo econômico de energia, que veremos nos próximos exemplos.
 
###**Contador_v2**
 
Nesse exemplo vamos começar a usar interrupções para ler os pulsos. Vamos ver quais são as vantagens desse método e o que pode ser melhorado.
 
O programa é um código em linguagem C e faz uso dos nomes dos registradores definidos na biblioteca "avr/io.h" e a biblioteca "avr/interrupt.h". Para melhor entendimento recomendo ler os comentários do código e o datasheet do ATtiny85.
 
####**Código**
```c
/**
 * 
 * @file main.c
 * @author Eduardo Dueñas
 * @brief Exemplo de contador de eventos com tratamento por interrupção
 * @version 1.0
 * @date 19/04/2021
 * 
 * O programa é um desenvolvimento em cima do contador uma com alterações na leitura do pulso para leitura por interrupção,
 * possibilitando o uso do microcontrolador para outras funções junto do contador 
 * 
 */
 
#include <avr/io.h>
#include <avr/interrupt.h>
 
#define F_CPU 16500000L
 
    
#define setBit(valor,bit) (valor |= (1<<bit))
#define clearBit(valor,bit) (valor &= ~(1<<bit))
#define toogleBit(valor,bit) (valor ^= (1<<bit))
#define testBit(valor,bit)    (valor & (1<<bit))
 
volatile unsigned char count = 0;
 
ISR(INT0_vect){
    cli();                  //Desabilita interrupções globais durante o tratamento da interrupção
    if(debounce(PB2)){      //Se o botão foi realmente apertado incrementa cont e manda para os leds
        count++;
        count %= 0x10;
        PORTB = ((PORTB & 0xE7) | ((count>>2)<<3));
        PORTB = ((PORTB & 0xFC) | (count&0x03));
    }
    sei();                  // Reabilita interrupções globais
}
 
 
//debounce do push button para desconsiderarmos ruído e bouncing do botão
char debounce(int pino){
    unsigned int i;
    for(i=0;i<20000;i++){              //testa o pino varias vezer para evitar leituras erradas
        if(!(testBit(PINB,pino))){   //testa se o pino deixou de ser 1
            return 0;           //se sim, retorna falso
        }
    }
    return 1;                    //retorna verdadeiro
}
 
int main(void){
    //Configuração de PORTB
    clearBit(DDRB,PB2);     //Configura PB2 como entrada
    setBit(DDRB,PB0);       //Configura PB0 como saida
    setBit(DDRB,PB1);       //Configura PB1 como saida
    setBit(DDRB,PB3);       //Configura PB3 como saida
    setBit(DDRB,PB4);       //Configura PB4 como saida
 
    PORTB &= 0xE4;          //manda 0 para PB[4:3] e PB[1:0]
 
    //Configuração de Interrupção externa
    GIMSK |= (1<<INT0);     //Habilita interrupções externas no INT0
    MCUCR |= 0x03;          //Seta interrupções para borda de subida
    sei();                  //Habilita interrupções globais
 
 
    for(;;){                   //loop infinito
        //aqui você pode colocar outra aplicação para rodar simultaneamente ao contador
    }              
}
```
 
####**Montagem**
 
![][Circuito v2]
 
Como mostrado na imagem, os leds são ligados nas saídas PortB[4:3] e [1:0] e o botão na entrada PortB[2].
 
####**Compilação e upload**
 
Para compilar o programa, assim como nos programas anteriores, acesse a pasta do exemplo e em seguida o comando `make`:
```
exemplos-avr-libc/exemplos/contador_v2$ make
```
Como ja temos o makerfile configurado na pasta, será feita compilação e deve aparecer a seguinte mensagem:
 
```
../../micronucleus/2.0a4/launcher  -cdigispark --timeout 60 -Uflash:w:main.hex:i
Running Digispark Uploader...
Plug in device now... (will timeout in 60 seconds)
> Please plug in the device (will time out in 60 seconds) ...
```
Conecte a placa em uma entrada USB ou, caso a Franzininho já esteja conectada, aperte o botão de reset para iniciar o upload.
 
####**Resultado**
 
Assim como no último exemplo, os leds devem mostrar a contagem de eventos, mostrando em binário até 15.
 
####**Análise**
 
Esse exemplo tem um código um pouco mais complexo, podendo fazer diferentes tarefas ao mesmo tempo com o uso de interrupções.
 
Interrupções são, de forma simples, instruções de alta prioridade, que fazem o processador parar o que está fazendo, guardar o estado atual, executar as instruções da interrupção e voltar para o estado anterior, continuando normalmente com o programa. Elas são extremamente uteis para tarefas que precisam de uma precisão de tempo alta ou eventos assíncronos.
 
Porém, apesar do exemplo dois fazer uso de interrupções, ele passa muito tempo nela, o que atrasa o andamento de um possível outro programa que estaria rodando na main. Porém, grande parte do tempo que é gasto na interrupção está atrelado ao debounce, que consiste basicamente de checagens em certos períodos de tempo. Podemos então otimizar o uso do processador saindo da interrupção entre as checagens, uma vez que ele está apenas esperando para fazer o próximo teste. Veremos isso e o modo de economia de energia no contador_v3.
 
###**Contador_v3**
 
Nesse exemplo vamos otimizar o processamento no código utilizando interrupções para as esperas do debounce, também veremos uma alternativa para diminuir o consumo de energia em momentos em que o processador está esperando algum evento, caso você não precise de outra rotina.
 
Esse programa é um código em linguagem C e faz uso dos nomes dos registradores definidos na biblioteca "avr/io.h" e a biblioteca "avr/interrupt.h". Para melhor entendimento recomendo ler os comentários do código e o datasheet do ATtiny85.
 
####**Código**
```c
/**
 * 
 * @file main.c
 * @author Eduardo Dueñas
 * @brief Exemplo de contador de eventos com tratamento por interrupção
 * @version 1.0
 * @date 20/04/2021
 * 
 * O programa é um desenvolvimento em cima do contador_v2 uma com alterações no loop infinito que 
 * havia ficado em aberto para outras aplicações para o modo sleep para diminuir o gasto de energia e
 * alterar o debounce para interrupção, aumentando a eficiência do código. O código pode ser usado com 
 * outras aplicações no lugar do sleep.
 * 
 */
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
 
#define F_CPU 16500000L
 
    
#define setBit(valor,bit) (valor |= (1<<bit))
#define clearBit(valor,bit) (valor &= ~(1<<bit))
#define toogleBit(valor,bit) (valor ^= (1<<bit))
#define testBit(valor,bit)    (valor & (1<<bit))
 
volatile unsigned char count = 0;
volatile unsigned char test = 0;
unsigned int pin = 0;
 
 
//Debounce do push button para desconsiderarmos ruido e bouncing do botão
char debounce(int pino){
    pin=pino;
    //Coloca um timer para cada 1000 ciclos de clk para testar o push buttom
    TCNT0=131;                  //256-(1000/8)=131
    setBit(TIMSK,TOIE0);        //Habilita interrupções por timer overflow
    test=0;
}
 
 
ISR(INT0_vect){             //Tratamento de interrupções de pulso externo
    clearBit(GIMSK,INT0);    //Desabilita interrupções do INT0 durante o tratamento da interrupção
    debounce(PB2);
}
 
 
ISR(TIMER0_OVF_vect){       //Tratamento de interrupções de timer overflow
    if(testBit(PINB,pin)){
        test++;
        if(test>=20){
            count++;
            count %= 0x10;
            PORTB = ((PORTB & 0xE7) | ((count>>2)<<3));
            PORTB = ((PORTB & 0xFC) | (count&0x03));
            clearBit(TIMSK,TOIE0);  //Desabilita interrupções por timer overflow
            setBit(GIMSK,INT0);     //Reabilita interrupções externas no INT0
        }
    }
    else{
        clearBit(TIMSK,TOIE0);  //Desabilita interrupções por timer overflow
        setBit(GIMSK,INT0);     //Reabilita interrupções externas no INT0
    }
 
}
 
 
 
int main(void){
    //Configuração de PORTB
    clearBit(DDRB,PB2);     //Configura PB2 como entrada
    setBit(DDRB,PB0);       //Configura PB0 como saida
    setBit(DDRB,PB1);       //Configura PB1 como saida
    setBit(DDRB,PB3);       //Configura PB3 como saida
    setBit(DDRB,PB4);       //Configura PB4 como saida
 
    PORTB &= 0xE4;          //Manda 0 para PB[4:3] e PB[1:0]
 
    //Configuração do timer
    TCCR0A=0x00;                //Modo Normal
    TCCR0B=0x00;
    TCCR0B |= 0x02;             //Prescaler de 8
 
 
    //Configuração do modo sleep
    clearBit(MCUCR,SM0);        //Configura sleep mode como idle
    clearBit(MCUCR,SM1);
 
    //Configuração de Interrupção externa
    setBit(GIMSK,INT0);     //Habilita interrupções externas no INT0
    MCUCR |= 0x03;          //Seta interrupções para borda de subida
    sei();                  //Habilita interrupções globais
 
 
    for(;;){                   //Loop infinito
        //Aqui você pode colocar outra aplicação para rodar simultaneamente ao contador no lugar do sleep
        sleep_mode();   //entra no sleep mode
    }              
}
```
 
####**Montagem**
 
![][Circuito v3]
 
Como mostrado na imagem, os leds são ligados nas saídas PortB[4:3] e [1:0] e o botão na entrada PortB[2], assim como no exemplo dois.
 
####**Compilação e upload**
 
Para compilar o programa, assim como nos programas anteriores, acesse a pasta do exemplo e em seguida o comando `make`:
```
exemplos-avr-libc/exemplos/contador_v3$ make
```
Como ja temos o makerfile configurado na pasta, será feita compilação e deve aparecer a seguinte mensagem:
 
```
../../micronucleus/2.0a4/launcher  -cdigispark --timeout 60 -Uflash:w:main.hex:i
Running Digispark Uploader...
Plug in device now... (will timeout in 60 seconds)
> Please plug in the device (will time out in 60 seconds) ...
```
Conecte a placa em uma entrada USB ou, caso a Franzininho já esteja conectada, aperte o botão de reset para iniciar o upload.
 
####**Resultado**
 
Assim como nos exemplos anteriores, os leds do circuito devem mostrar a contagem de pulsos até 15 em binário.
 
####**Análise**
 
Neste código adicionamos um pouco mais de complexidade, aumentando o uso de interrupções, além do uso do timer e do modo Sleep. 
 
O modo Sleep é um mode de operação no qual, de forma básica, se desliga alguns módulos do microcontrolador até que alguma interrupção ocorra, o que pode diminuir o consumo de energia de forma drástica. No caso do código do exemplo, utilizamos o modo Idle que no ATtiny85 desliga os CLKs da CPU e FLASH, podendo se desligar opcionalmente o CLK do ADC.
 
O uso de interrupções do timer para o debounce diminui consideravelmente o tempo que o processador consome em execução do tratamento do evento, o que melhora o processamento das rotinas paralelas, ou no caso, permite que o processador fique mais tempo no modo Sleep, diminuindo o consumo de energia ou em caso de alimentação por baterias, aumenta a vida útil da da fonte.
 
 
 
 
[Circuito v1]: https://github.com/Franzininho/exemplos-avr-libc/blob/main/exemplos/contador/Exemplo_Contador_Circuito.png "Circuito do contador_v1"
 
[Circuito v2]: https://github.com/Franzininho/exemplos-avr-libc/blob/main/exemplos/contador_v2/Exemplo_Contador_Circuito_v2.png "Circuito do contador_v2"
 
[Circuito v3]: https://github.com/Franzininho/exemplos-avr-libc/blob/main/exemplos/contador_v3/Exemplo_Contador_Circuito_v3.png "Circuito do contador_v3"
 


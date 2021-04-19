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


//debounce do push button para desconciderarmos ruido e bouncing do botão
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
    clearBit(DDRB,PB2);     //Configura PB2 como saida
    setBit(DDRB,PB0);       //Configura PB0 como entrada
    setBit(DDRB,PB1);       //Configura PB1 como entrada
    setBit(DDRB,PB3);       //Configura PB3 como entrada
    setBit(DDRB,PB4);       //Configura PB4 como entrada

    PORTB &= 0xE4;          //manda 0 para PB[4:3] e PB[1:0]

    //Configuração de Interrupção externa
    GIMSK |= (1<<INT0);     //Habilita interrupções externas no INT0
    MCUCR |= 0x03;          //Seta interrupções para borda de subida
    sei();                  //Habilita interrupções globais


    for(;;){                   //loop infinito
        //aqui você pode colocar outra aplicação para rodar simultaniamenta ao contador
    }              
}
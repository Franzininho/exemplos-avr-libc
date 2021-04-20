/**
 * 
 * @file main.c
 * @author Eduardo Dueñas
 * @brief Exemplo de contador de eventos com tratamento por interrupção
 * @version 1.0
 * @date 20/04/2021
 * 
 * O programa é um desenvolvimento em cima do contador_v2 uma com alterações no loop infinito que 
 * havia ficdo em aberto para outras aplicações para o modo sleep para diminuira o gasto de energia e
 * alterar o debouce para interrupção, aumentando a eficiência do código. O código pode ser usado com 
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


//Debounce do push button para desconciderarmos ruido e bouncing do botão
char debounce(int pino){
    pin=pino;
    //Coloca um timer para cada 1000 ciclos de clk para testar o push buttom
    TCNT0=131;                  //256-(1000/8)=131
    setBit(TIMSK,TOIE0);        //Habilita interrupções por timer overflow
    test=0;
}


ISR(INT0_vect){             //Tratamento de interrupções de pulso externo
    clearBit(GIMSK,INT0);    //Desabilita interrupções do INT0 durante o tratamento da interrupção
    debounce(PB2);/*
    if(debounce(PB2)){      //Se o botão foi realmente apertado incrementa cont e manda para os leds
        count++;
        count %= 0x10;
        PORTB = ((PORTB & 0xE7) | ((count>>2)<<3));
        PORTB = ((PORTB & 0xFC) | (count&0x03));
    }
    sei();                  // Reabilita interrupções globais
    */
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
    clearBit(DDRB,PB2);     //Configura PB2 como saida
    setBit(DDRB,PB0);       //Configura PB0 como entrada
    setBit(DDRB,PB1);       //Configura PB1 como entrada
    setBit(DDRB,PB3);       //Configura PB3 como entrada
    setBit(DDRB,PB4);       //Configura PB4 como entrada

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
        //Aqui você pode colocar outra aplicação para rodar simultaniamenta ao contador no lugar do sleep
        sleep_mode();   //entra no sleep mode
    }              
}
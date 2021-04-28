/**
 * 
 * @file main.c
 * @author Eduardo Dueñas
 * @brief Exemplo de contador de eventos com tratamento por interrupção
 * @version 1.0
 * @date 27/04/2021
 * 
 * O programa é uma aplicação do PWM para aumentar e diminuir a luminosidade do led por frequência
 * 
 */

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16500000L

   
#define setBit(valor,bit) (valor |= (1<<bit))
#define clearBit(valor,bit) (valor &= ~(1<<bit))
#define toogleBit(valor,bit) (valor ^= (1<<bit))
#define testBit(valor,bit)    (valor & (1<<bit))



int main(void){
    //Configuração de PORTB
    setBit(DDRB,PB0);     //Configura PB0 como saida

    //Configuração do timer
    TCCR0A=0x83;                //Modo Fast PWM em mode não invertido do OC0A
    TCCR0B=0x01;                //Sem prescaler e com TOP em 0xFF


    for(;;){                   //Loop infinito
        unsigned int i,j;
        for(i=0;i<0xFF;i++){
            _delay_ms(4);
            OCR0A=i;
        }
        for(i=0;i<0xFF;i++){
            _delay_ms(4);
            OCR0A=0xFF-i;
        }
    }              
}
/**
 * 
 * @file main.c
 * @author Eduardo Dueñas
 * @brief Exemplo de contador de eventos com tratamento por interrupção
 * @version 1.0
 * @date 27/04/2021
 * 
 * O programa é um desenvolvimento em cima do contador_v2 uma com alterações no loop infinito que 
 * havia ficdo em aberto para outras aplicações para o modo sleep para diminuira o gasto de energia e
 * alterar o debouce para interrupção, aumentando a eficiência do código. O código pode ser usado com 
 * outras aplicações no lugar do sleep.
 * 
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16500000L

#define DELAY   30000

 	
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
        int i,j;
        for(i=0;i<0xFF;i++){
            for (j=0;j<DELAY;j++){}
            OCR0A=i;
        }
        //toogleBit(TCCR0A,6);
        for(i=0xFF;i>0;i--){
            for (j=0;j<DELAY;j++){}
            OCR0A=i;
        }
    }              
}
/**
 * 
 * @file main.c
 * @author Eduardo Dueñas
 * @brief Exemplo de contador de eventos
 * @version 0.1
 * @date 06/04/2021
 * 
 */

#include <avr/io.h>
#include <util/delay.h> 

#define F_CPU 16500000L

 	
#define setBit(valor,bit) (valor |= (1<<bit))
#define clearBit(valor,bit) (valor &= ~(1<<bit))
#define toogleBit(valor,bit) (valor ^= (1<<bit))
#define testBit(valor,bit)    (valor & (1<<bit))


//debounce do push button para desconciderarmos ruido e bouncing do botão
char debounce(int pino){
    unsigned char i;
    for(i=0;i<30;i++){
        if(testBit(PORTB,pino)){
            return false;
        }
    }
    return true;
}




int main(void){

    setBit(DDRB,PB0);
    setBit(DDRB,PB1);
    setBit(DDRB,PB2);
    setBit(DDRB,PB3);
    clearBit(DDRB,PB4);
    clearBit(DDRB,PB5);

    PORTB &= 0xF0;
    
    unsigned char count = 0;

    for(;;){
        if(testBit(PORTB,PB5)){ 
            if(debounce(int PB5)){
                count = 0;
            }            
        }
        if(testBit(PORTB,PB4)){ 
            if(debounce(int PB4)){
                count++;
            }            
        }
        count = count % 0x0F;
        PORTB = ((PORTB & 0xF0) | count);
    }              
}
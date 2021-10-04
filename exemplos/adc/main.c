/**
 * 
 * @file main.c
 * @author Gustavo Aguilar
 * @brief Exibe como usar o conversor analogico-digital com interrupcao
 * @version 0.1
 * @date 2021-10-01
 * 
 * @copyright Franzininho 
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */

#include <avr/io.h>
#include <avr/interrupt.h>

//Limiar para ligar ou desligar o LED
#define LIMIAR 50

ISR(ADC_vect){
    // ADC contem o valor resultante da conversao
    if(ADC >= LIMIAR){
        PORTB |= (1 << PB1); // Liga o LED
    }else{
        PORTB &= ~(1 << PB1); // Desliga o LED
    }

    ADCSRA |= (1 << ADSC); // Aciona a proxima conversao
}

void init_mcu(){
    DDRB |= (1 << PB1);  // PB1 (LED) como saida

    ADCSRA = (1 << ADEN) | (1 << ADIE); // Habilita o conversor e sua interrupcao
    ADMUX = 0x02; // Seleciona o canal 2 (A2)
    
    ADCSRA |= (1 << ADSC); // Aciona uma conversao

    sei(); // Habilita as interrupcoes
}

int main(void){
    init_mcu();

    while(1){} // Nao faz nada

    return 0;
}

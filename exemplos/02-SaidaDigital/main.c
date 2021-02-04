/**
 * @file main.c
 * @author Fábio Souza
 * @brief Exemplo para explorar as saídas digitais e o uso de macros
 * @version 0.1
 * @date 2021-02-03
 * 
 * @copyright 
 * This example code is in the Public Domain (or CC0 licensed, at your option.)
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 * 
 */

#include <avr/io.h>
#include <util/delay.h> 

#define F_CPU 16500000L

 	
#define setBit(valor,bit) (valor |= (1<<bit))
#define toogleBit(valor,bit) (valor ^= (1<<bit))

/**
 * @brief Função main
 * 
 * @return int 
 */
int main(void) 
{
 
  setBit(DDRB,PB1); 	// Configura Pino PB1 como saída (Pino do LED)
  
  /**
   * @brief loop infinito
   * 
   */
  while (1)
  {
    toogleBit(PORTB,PB1);
    _delay_ms(250);      	// delay 250 ms
  }                                                
  return (0);                           
}

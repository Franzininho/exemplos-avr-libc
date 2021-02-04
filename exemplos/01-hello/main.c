/**
 * @file main.c
 * @author Fábio Souza
 * @brief Exemplo para blink LED na placa Franzinino 
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

/**
 * @brief Função main
 * 
 * @return int 
 */
int main(void) 
{
 
  DDRB |= (1 << PB1);   	// Configura Pino PB1 como saída (Pino do LED)
  
  /**
   * @brief loop infinito
   * 
   */
  while (1)
  {
    PORTB |= (1 << PB1);   	// Liga LED
    _delay_ms(500);      	// delay 500 ms

    PORTB &= ~(1 << PB1);  	// desliga LED
    _delay_ms(500);      	// delay 500 ms
  }                                                
  return (0);                           
}

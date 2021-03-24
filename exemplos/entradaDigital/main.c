/**
 * 
 * @file main.c
 * @author Fábio Souza
 * @brief Exemplo para leitura de botão e acionamento de LED
 * @version 0.1
 * @date 2021-02-03
 * 
 * @copyright Franzininho 
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
#define clearBit(valor,bit) (valor &= ~(1<<bit))
#define toogleBit(valor,bit) (valor ^= (1<<bit))
#define testBit(valor,bit)    (valor & (1<<bit))

/**
 * @brief Função main
 * 
 * @return int 
 */
int main(void) 
{
 
  setBit(DDRB,PB1); 	// Configura Pino PB1 como saída (Pino do LED)
  clearBit(DDRB,PB0); //configura pino PB0 como entrada (pino do Botão)
  setBit(PORTB,PB0);  //habilita pull up para a entrada PB0 - garante nivel 
                      // lógico 1 quando botão não estiver pressionado
  
  /**
   * @brief loop infinito
   * 
   */
  while (1)
  {
    if(!testBit(PINB,PB0)) //faz a leitura do botão - Se pressionado
    {
      setBit(PORTB,PB1);   //liga LED
    }
    else                   //se não
    {
      clearBit(PORTB,PB1); //apaga LED
    }
  }                                                
  return (0);                           
}

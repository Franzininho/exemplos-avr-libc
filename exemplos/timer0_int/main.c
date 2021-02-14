/**
 * 
 * @file main.c
 * @author Fábio Souza
 * @brief Exibe como usar a interrupção do timer 0 para temporização
 * @version 0.1
 * @date 2021-02-13
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
#include <avr/interrupt.h>

#define F_CPU 16500000L

 	
#define setBit(valor,bit) (valor |= (1<<bit))
#define clearBit(valor,bit) (valor &= ~(1<<bit))
#define toogleBit(valor,bit) (valor ^= (1<<bit))
#define testBit(valor,bit)    (valor & (1<<bit))

unsigned char tempo = 0;  //contador auxiliar


ISR (TIMER0_OVF_vect) //vetor de interrupção para o timer 0
{
  tempo++;                     //incrementa contador auxiliar
  if(tempo >=63)               //se passaram-se 63 x 15,89 ms = 1 s
  {
    toogleBit(PORTB,PB1);      //inverte LED
    tempo = 0;                 //reinicia contador
  }
}

/**
 * @brief Função main
 * 
 * @return int 
 */
int main(void) 
{
  
  setBit(DDRB,PB1); 	// Configura Pino PB1 como saída (Pino do LED)

  //configuração do timer0 para overflow a aproximadamente 15,89 ms
  //t = (1/16.5Mhz) x 1024 x 256 = 15,89 ms
  TCCR0A=0x00;                      //Modo Normal
  TCCR0B=0x00;
  TCCR0B |= (1<<CS00)|(1<<CS02);   //prescaler de 1024
  TCNT0=0;                         //inicia timer com 0
  setBit(TIMSK,TOIE0);             //habilita interrupção do timer0 
  sei();                           //habilita interrupção global
  
  /**
   * @brief loop infinito
   * 
   */
  while (1)
  {
      //não faz nada no loop 
  }                                                
  return (0);                           
}

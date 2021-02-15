/*
 * Timer.c
 *
 * Created: 06/02/2021 07:37:19
 *  Author: evandro teixeira
 */ 
/* 
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stddef.h>
#include "Timer.h"



/** 
 * @brief 
 */
void (*timer_irq)(void);

/**
 * @brief 
 */ 
ISR (TIMER0_OVF_vect)      //Interrupt vector for Timer0
{
  if(timer_irq != NULL)
  {
    timer_irq();
  }
}

/**
 * @brief
 * @param 
 */
void Timer_Init(uint8_t prescaler)
{
  TCCR0A = 0x00;   //Normal mode
  TCCR0B = 0x00;
  TCCR0B |= prescaler;
  sei();				//enabling global interrupt
  TCNT0 = 0;
  TIMSK |= (1<<TOIE0); //enabling timer0 interrupt
}

/**
 * @brief
 * @param (*task)(void)
 */
void Timer_SetCallback(void (*task)(void))
{
  if(task != NULL)
  {
    timer_irq = task;
  }
}
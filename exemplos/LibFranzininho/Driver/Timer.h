/*
 * Timer.h
 *
 * Created: 06/02/2021 07:37:36
 *  Author: evandro teixeira
 */ 
#include <stdbool.h>
#include <stdint.h>

/**  
 * @brief
 */
//enum 
//{
  //Timer_No_Prescaler = 1,
  //Timer_Prescaler_8
  //No_Prescaler = 1,/* Timer Frequency = Frequency CPU / 1    */
  //Prescaler_8,     /* Timer Frequency = Frequency CPU / 8    */
  //Prescaler_64,    /* Timer Frequency = Frequency CPU / 64   */
  //Prescaler_256,   /* Timer Frequency = Frequency CPU / 256  */
  //Prescaler_1024,  /* Timer Frequency = Frequency CPU / 1024 */
  //Prescaler_MAX    /* Not User */
//};

#define TIMER_NO_PRESCALER		1
#define TIMER_PRESCALER_8		2
#define TIMER_PRESCALER_64		3
#define TIMER_PRESCALER_256		4
#define TIMER_PRESCALER_1024	5
#define TIMER_PRESCALER_MAX		6

void Timer_Init(uint8_t prescaler);
void Timer_SetCallback(void (*task)(void));
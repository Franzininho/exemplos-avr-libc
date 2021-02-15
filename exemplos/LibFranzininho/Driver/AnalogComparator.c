/*
 * AnalogComparator.c
 *
 * Created: 10/02/2021 02:31:03
 *  Author: evandro teixeira
 */ 
#include <avr/io.h>
#include "AnalogComparator.h"
#include "../../LibFranzininho/Franzininho.h"

uint8_t AnalogComparator_GetChannelADC(uint8_t x);

/** */
//#define ADC_INPUT_CHANNEL(x)        \
//{                                   \ 
//	switch(x)                       \
//	{                               \
//		case AC1: return 0; break;  \
//		case AC2: return 1; break;  \
//		case AC3: return 2; break;  \
//		case AC4: return 3; break;  \
//		default return 0xFF; break; \
//	}                               \
//}

/**
 * @brief In ATtiny85 the analog comparator peripheral uses AIN0 (PB0) pin as 
 *        positive input and negative input can be chosen from any one of 
 *        following pins: AIN1 (PB1) and ADC input channels – ADC0, ADC1, ADC2, ADC3.
 * @param pin 
 */ 
void AnalogComparator_Init(uint8_t pin)
{
  switch(pin)
  {
    case AC0:
      ADCSRA = 0x00;  // Using AIN0 and AIN1 as comparator inputs
      ADCSRB = 0x00;
    break;
    case AC1:
    case AC2:
    case AC3:
    case AC4:
      ADCSRA = 0x00;
      ADCSRB |= (1 << ACME);           // Enabling ADC multiplexer 
      ADMUX =  AnalogComparator_GetChannelADC(pin);  // Using ADC(pin) channel as inverting input for comparator
      ACSR = 0x00;
    break;
    default:
    break;
  }
}

/**
 * @brief 
 * @return 
 */
bool AnalogComparator_Read(void)
{
  return (bool)(ACSR & (1 << ACO));  // Reading ACO comparator output bit
}

/** 
 *
 */
uint8_t AnalogComparator_GetChannelADC(uint8_t x)
{	
	switch(x)                       
	{                               
		case AC1: return 0; break;  
		case AC2: return 1; break;  
		case AC3: return 2; break;  
		case AC4: return 3; break;  
		default: return 0xFF; break; 
	}                               
}
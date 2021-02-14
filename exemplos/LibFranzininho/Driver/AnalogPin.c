/*
 * AnalogPin.c
 *
 * Created: 06/02/2021 07:36:07
 *  Author: evandro teixeira
 */ 
#include <avr/io.h>
#include "AnalogPin.h"
#include "../../LibFranzininho/Franzininho.h"

#define NUMBER_OF_ANALOG_CH			0x03 // Number of Analog channels
#define MASK_NUMBER_OF_ANALOG_CH    0xFC // Mask number of Analog channels

/** 
 * @brief
 */
void AnalogPin_Init(void)
{
	ADMUX  |= (1 << REFS0);	/* reference voltage on AVCC */
	ADCSRA |= (1 << ADPS2); /* ADC clock prescaler /16 */
	ADCSRA |= (1 << ADEN);  /* enable ADC */
}

/** 
 * @brief
 * @param pin
 * @return 
 */
uint16_t AnalogPin_Read(uint8_t pin)
{
	pin &= NUMBER_OF_ANALOG_CH; 
	ADMUX = (ADMUX & MASK_NUMBER_OF_ANALOG_CH)|pin;
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	return (ADC);
}
/*
 * DigitalPin.c
 *
 * Created: 06/02/2021 05:22:35
 *  Author: evandro teixeira
 */ 
#include <avr/io.h>
#include "DigitalPin.h"
#include "../../LibFranzininho/Franzininho.h"

/** 
 * @brief 
 * @param pin
 * @param dir
 */
void DigitalPin_Init(uint8_t pin, uint8_t dir)
{
	if(dir == OUTPUT)
	{
		DDRB |= (1<<pin);
	}
	else
	{
		DDRB &= ~(1<<pin);
	}
}

/** 
 * @brief 
 * @param pin
 * @param value
 */
void DigitalPin_Write(uint8_t pin, uint8_t value)
{
	if(value == HIGH)
	{
		PORTB |= (1<<pin);
	}
	else
	{
		PORTB &= ~(1<<pin);		
	}
}

/** 
 * @brief 
 * @param pin
 */
void DigitalPin_Toggle(uint8_t pin)
{
	PORTB ^= (1<<pin);
}

/** 
 * @brief 
 * @param pin
 * @return 
 */
uint8_t DigitalPin_Read(uint8_t pin)
{
	return (uint8_t)(PINB & (1 << pin)); 
}
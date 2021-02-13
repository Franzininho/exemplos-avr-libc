/*
 * ci74hc595.c
 *
 * Created: 06/02/2021 06:04:04
 *  Author: evandro teixeira
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "ci74hc595.h"
#include "../../LibFranzininho/Franzininho.h"

#define CI74HC595_BYTE			8
#define CI74HC595_TIME_DELAY	10

/**  @brief */
typedef struct
{
	uint8_t CLK;
	uint8_t LATCH;
	uint8_t DATA;
	bool StsInit;
}ci74hc595_pin_t;

enum
{
	CI74HC595_8_Bit = 1,
	CI74HC595_16_Bit,
	CI74HC595_MAX
};

/** @brief */
static ci74hc595_pin_t ci74hc595_Pin = {0};
static void ci74hc595_Transmits_Data(uint16_t value, uint8_t num_byte);
static void ci74hc595_Delay(uint8_t t);

/** 
 * @brief
 * @param clk
 * @param latch
 * @param data
 */
void ci74hc595_Init(uint8_t clk, uint8_t latch, uint8_t data)
{
	ci74hc595_Pin.CLK = clk;
	ci74hc595_Pin.LATCH = latch;
	ci74hc595_Pin.DATA = data;
	ci74hc595_Pin.StsInit = true;
	DigitalPin_Init(ci74hc595_Pin.CLK,OUTPUT);
	DigitalPin_Init(ci74hc595_Pin.LATCH,OUTPUT);
	DigitalPin_Init(ci74hc595_Pin.DATA,OUTPUT);
}

/** 
 * @brief
 * @param data
 */
void ci74hc595_Transmits_8_Bits(uint8_t data)
{
	ci74hc595_Transmits_Data((uint16_t)data, CI74HC595_8_Bit);
}

/** 
 * @brief
 * @param data
 */
void ci74hc595_Transmits_16_Bits(uint16_t data)
{
	ci74hc595_Transmits_Data(data, CI74HC595_16_Bit);
}

/** 
 * @brief
 * @param value
 * @param num_byte
 */
static void ci74hc595_Transmits_Data(uint16_t value, uint8_t num_byte)
{
	uint8_t i = 0;

	if((ci74hc595_Pin.StsInit == true) && ((num_byte == CI74HC595_8_Bit || num_byte == CI74HC595_16_Bit)))
	{
		for(i=0;i<(CI74HC595_BYTE*num_byte);i++)
		{
			if(value & 1)
			{
				DigitalPin_Write(ci74hc595_Pin.DATA,HIGH);
			}
			else
			{
				DigitalPin_Write(ci74hc595_Pin.DATA,LOW);
			}

			DigitalPin_Write(ci74hc595_Pin.CLK,LOW);
			ci74hc595_Delay(CI74HC595_TIME_DELAY);
			DigitalPin_Write(ci74hc595_Pin.CLK,HIGH);
			value >>= 1;
		}

		DigitalPin_Write(ci74hc595_Pin.LATCH,LOW);
		ci74hc595_Delay(CI74HC595_TIME_DELAY);
		DigitalPin_Write(ci74hc595_Pin.LATCH,HIGH);
		DigitalPin_Write(ci74hc595_Pin.LATCH,LOW);
	}
}

/** 
 * @brief
 * @param t
 */
static void ci74hc595_Delay(uint8_t t)
{
	_delay_us(t);
}
/*
 * Lm35.c
 *
 * Created: 06/02/2021 20:04:15
 *  Author: evandro teixeira
 */ 
#include "lm35.h"
#include "../../LibFranzininho/Franzininho.h"

/** 
 * @brief
 */
void lm35_Init(void)
{
	AnalogPin_Init();
}

/** 
 * @brief
 * @param pinAd
 * @return 
 */
float lm35_ReadTemperature(uint8_t pinAd)
{
	return (float)((float)(AnalogPin_Read(pinAd))*5.00F/(1023.00F))/0.01F;
}
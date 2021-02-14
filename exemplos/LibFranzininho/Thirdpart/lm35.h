/*
 * Lm35.h
 *
 * Created: 06/02/2021 20:04:29
 *  Author: evandro teixeira
 */ 
#include <stdint.h>

void lm35_Init(void);
float lm35_ReadTemperature(uint8_t pinAd);
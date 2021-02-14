/*
 * AnalogComparator.h
 *
 * Created: 10/02/2021 02:31:24
 *  Author: evandro teixeira
 */ 
#include <stdint.h>
#include <stdbool.h>

void AnalogComparator_Init(uint8_t pin);
bool AnalogComparator_Read(void);
/*
 * DigitalPin.h
 *
 * Created: 06/02/2021 05:23:02
 *  Author: evandro teixeira
 */ 


void DigitalPin_Init(uint8_t pin, uint8_t dir);
void DigitalPin_Write(uint8_t pin, uint8_t value);
void DigitalPin_Toggle(uint8_t pin);
uint8_t DigitalPin_Read(uint8_t pin);
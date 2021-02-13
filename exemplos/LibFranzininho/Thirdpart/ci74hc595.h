/*
 * ci74hc595.h
 *
 * Created: 06/02/2021 06:04:26
 *  Author: evandro teixeira 
 */ 


void ci74hc595_Init(uint8_t clk, uint8_t latch, uint8_t data);
void ci74hc595_Transmits_8_Bits(uint8_t data);
void ci74hc595_Transmits_16_Bits(uint16_t data);

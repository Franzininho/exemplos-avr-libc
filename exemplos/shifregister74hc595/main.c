/*
 * Franzininho.c
 *
 * Created: 06/02/2021 04:39:55
 * Author : evandro teixeira
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "LibFranzininho/Franzininho.h"


#define CLK P0
#define DATA P2
#define LATCH P3

uint8_t data = 0;

int main(void)
{
	DigitalPin_Init(LED_BOARD,OUTPUT);
	ci74hc595_Init(CLK,LATCH,DATA);
	
    while (1) 
    {
		
		DigitalPin_Toggle(LED_BOARD);
		ci74hc595_Transmits_8_Bits(data++);
		_delay_ms(500);      	
    }
}


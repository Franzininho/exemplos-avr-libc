#include <avr/io.h>
#include <util/delay.h> 

#define F_CPU 16500000L

int main(void) 
{
 
  DDRB |= (1 << PB1);   	// Configura Pino PB1 como saída (Pino do LED)
  
  // loop oinfinito
  while (1)
 {
    PORTB |= (1 << PB1);   	// Liga LED
    _delay_ms(500);      	// delay 500 ms

    PORTB &= ~(1 << PB1);  	// desliga LED
    _delay_ms(500);      	// delay 500 ms
  }                                                
  return (0);                           
}

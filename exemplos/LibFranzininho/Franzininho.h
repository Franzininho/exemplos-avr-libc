/*
 * Franzininho.h
 *
 * Created: 06/02/2021 05:14:03
 *  Author: evandro teixeira
 */ 
#include <stdbool.h>
#include "Driver/DigitalPin.h"
#include "Thirdpart/ci74hc595.h"

/** */
#define  P0 0
#define  P1 1
#define  P2 2
#define  P3 3
#define  P4 4
#define  P5 5

/** */
#define LED_BOARD P1 

/** */
enum
{
	INPUT = 0,
	OUTPUT = 1
};

/** */
enum
{
	LOW = 0,
	HIGH = 1
};
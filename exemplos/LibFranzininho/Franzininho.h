/*
 * Franzininho.h
 *
 * Created: 06/02/2021 05:14:03
 *  Author: evandro teixeira
 */ 
#include <stdbool.h>
#include <stdint.h>
/** */
#include "Driver/DigitalPin.h"
#include "Driver/AnalogPin.h"
#include "Driver/Pwm.h"
#include "Driver/I2c.h"
#include "Driver/Timer.h"
#include "Driver/SoftwarePwm.h"

/** */
#include "Thirdpart/ci74hc595.h"
#include "Thirdpart/lm35.h"

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
#define A0	0	// Pin PD5 ~ ADC0 channel
#define A1	1	// Pin PD2 ~ ADC1 channel
#define A2	2	// Pin PD4 ~ ADC2 channel
#define A3	3	// Pin PD3 ~ ADC3 channel

/** */
#define AC0 PB1 // AIN1
#define AC1 PB5 // ADC0
#define AC2 PB2 // ADC1
#define AC3 PB4 // ADC2
#define AC4 PB3 // ADC3

/** 
 * @brief The temperature measurement is based on an on-chip temperature 
 * sensor that is coupled to a single ended ADC4 channel
 */
#define TEMPERATURE_SENSOR	0x0F

/** */
enum
{
	INPUT = 0,
	OUTPUT
};

/** */
enum
{
	LOW = 0,
	HIGH
};
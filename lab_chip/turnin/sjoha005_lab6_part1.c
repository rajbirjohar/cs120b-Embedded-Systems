/*	Author: sjoha005
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *  LINK: https://youtu.be/_0NU7ucCW3E
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum LEDStates
{
    LEDStart,
    LED1State,
    LED2State,
    LED3State
} LEDState;

void Tick()
{
    switch (LEDState)
    {
    case LEDStart:
        LEDState = LED1State;
        break;

    case LED1State:
        LEDState = LED2State;
        break;

    case LED2State:
        LEDState = LED3State;
        break;

    case LED3State:
        LEDState = LED1State;
        break;
    }

    switch (LEDState)
    {
    case LED1State:
        PORTB = 0x01;
        break;

    case LED2State:
        PORTB = 0x02;
        break;

    case LED3State:
        PORTB = 0x04;
        break;

    default:
        break;
    }
}

int main(void)
{
    DDRB = 0xFF;
    PORTB = 0x00;

    TimerSet(100);
    TimerOn();
    LEDState = LEDStart;

    while (1)
    {
        Tick();
        while (!TimerFlag)
            ;
        TimerFlag = 0;
    }

    return 1;
}


/*	Author: sjoha005
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
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
    LED3State,
    MiddleState,
    PressedState,
    RestartState
} LEDState;

unsigned char button = 0x00;

void Tick()
{
    switch (LEDState)
    {
    case LEDStart:
        LEDState = LED1State;
        break;

    case LED1State:
        if (button)
        {
            LEDState = PressedState;
        }
        else
        {
            LEDState = LED2State;
        }
        break;

    case LED2State:
        if (button)
        {
            LEDState = PressedState;
        }
        else
        {
            LEDState = LED3State;
        }
        break;

    case LED3State:
        if (button)
        {
            LEDState = PressedState;
        }
        else
        {
            LEDState = MiddleState;
        }
        break;

    case MiddleState:
        if (button)
        {
            LEDState = PressedState;
        }
        else
        {
            LEDState = LED1State;
        }
        break;

    case PressedState:
        if (button)
        {
            LEDState = PressedState;
        }
        else
        {
            LEDState = RestartState;
        }
        break;

    case RestartState:
        if (!button)
        {
            LEDState = RestartState;
        }
        else
        {
            LEDState = LED1State;
        }
        break;
    }

    switch (LEDState)
    {
    case LED1State:
        PORTB = 0x01;
        break;

    case LED2State:
    case MiddleState:
        PORTB = 0x02;
        break;

    case LED3State:
        PORTB = 0x04;
        break;

    case PressedState:
    case RestartState:
        break;

    default:
        break;
    }
}

int main(void)
{
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRB = 0xFF;
    PORTB = 0x00;

    TimerSet(30);
    TimerOn();
    LEDState = LEDStart;

    while (1)
    {
        button = ~PINA & 0x01;
        Tick();
        while (!TimerFlag)
            ;
        TimerFlag = 0;
    }

    return 1;
}
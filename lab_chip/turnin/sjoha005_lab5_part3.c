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
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum lightsStates
{
    LightsOn,
    StartState,
    WaitState,
    HalfState,
    WaitState1,
    EndState,
    WaitState2
} lightsState;

void Tick()
{
    switch (lightsState)
    {
    case LightsOn:
        lightsState = StartState;
        break;

    case StartState:
        if (~PINA & 0x01)
        {
            lightsState = WaitState;
        }
        else
        {
            lightsState = StartState;
        }
        break;

    case WaitState:
        if (!(~PINA & 0x01))
        {
            lightsState = HalfState;
        }
        else
        {
            lightsState = WaitState;
        }
        break;

    case HalfState:
        if (~PINA & 0x01)
        {
            lightsState = WaitState1;
        }
        else
        {
            lightsState = HalfState;
        }
        break;

    case WaitState1:
        if (!(~PINA & 0x01))
        {
            lightsState = EndState;
        }
        else
        {
            lightsState = WaitState1;
        }
        break;

    case EndState:
        if (~PINA & 0x01)
        {
            lightsState = WaitState2;
        }
        else
        {
            lightsState = EndState;
        }
        break;

    case WaitState2:
        if (!(~PINA & 0x01))
        {
            lightsState = StartState;
        }
        else
        {
            lightsState = WaitState2;
        }
        break;
    }

    switch (lightsState)
    {
    case StartState:
        PORTB = 0x30;
        break;

    case WaitState:
        PORTB = 0x03;
        break;

    case HalfState:
        break;

    case WaitState1:
        PORTB = 0x0C;

    case EndState:
        break;

    case WaitState2:
        PORTB = 0x30;
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

    lightsState = LightsOn;

    while (1)
    {
        Tick();
    }

    return 1;
}
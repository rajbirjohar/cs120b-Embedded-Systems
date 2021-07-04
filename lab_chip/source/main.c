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
#EndStateif

enum lightStates
{
    LightsOn,
    StartState,
    LightState1,
    LightState2,
    LightState3,
    LightState4,
    LightState5,
    LightState6,
    LightState7,
    WaitState1,
    WaitState2,
    WaitState3,
    WaitState4,
    WaitState5,
    WaitState6,
    WaitState7,

} lightState;

void Tick()
{
    switch (lightState)
    {
    case LightsOn:
        lightState = StartState;
        break;

    case StartState:
        if (~PINA & 0x01)
        {
            lightState = LightState1;
        }
        else
        {
            lightState = StartState;
        }
        break;

    case LightState1:
        if (!(~PINA & 0x01))
        {
            lightState = WaitState1;
        }
        else
        {
            lightState = LightState1;
        }
        break;

    case WaitState1:
        if (~PINA & 0x01)
        {
            lightState = LightState2;
        }
        else
        {
            lightState = WaitState1;
        }
        break;

    case LightState2:
        if (!(~PINA & 0x01))
        {
            lightState = WaitState2;
        }
        else
        {
            lightState = LightState2;
        }
        break;

    case WaitState2:
        if (~PINA & 0x01)
        {
            lightState = LightState3;
        }
        else
        {
            lightState = WaitState2;
        }
        break;

    case LightState3:
        if (!(~PINA & 0x01))
        {
            lightState = WaitState3;
        }
        else
        {
            lightState = LightState3;
        }
        break;

    case WaitState3:
        if (~PINA & 0x01)
        {
            lightState = LightState4;
        }
        else
        {
            lightState = WaitState3;
        }
        break;

    case LightState4:
        if (!(~PINA & 0x01))
        {
            lightState = WaitState4;
        }
        else
        {
            lightState = LightState4;
        }
        break;

    case WaitState4:
        if (~PINA & 0x01)
        {
            lightState = LightState5;
        }
        else
        {
            lightState = WaitState4;
        }
        break;

    case LightState5:
        if (!(~PINA & 0x01))
        {
            lightState = WaitState5;
        }
        else
        {
            lightState = LightState5;
        }
        break;

    case WaitState5:
        if (~PINA & 0x01)
        {
            lightState = LightState6;
        }
        else
        {
            lightState = WaitState5;
        }
        break;

    case LightState6:
        if (!(~PINA & 0x01))
        {
            lightState = WaitState6;
        }
        else
        {
            lightState = LightState6;
        }
        break;

    case WaitState6:
        if (~PINA & 0x01)
        {
            lightState = LightState7;
        }
        else
        {
            lightState = WaitState6;
        }
        break;

    case LightState7:
        if (!(~PINA & 0x01))
        {
            lightState = WaitState7;
        }
        else
        {
            lightState = LightState7;
        }
        break;

    case WaitState7:
        if (~PINA & 0x01)
        {
            lightState = StartState;
        }
        else
        {
            lightState = WaitState7;
        }
        break;

        switch (lightState)
        {
        case StartState:
            PORTB = 0x20;
            break;

        case LightState1:
            PORTB = 0x30;
            break;

        case LightState2:
            PORTB = 0x38;
            break;

        case LightState3:
            PORTB = 0x1C;
            break;

        case LightState4:
            PORTB = 0xE;
            break;

        case LightState5:
            PORTB = 0x7;
            break;

        case LightState6:
            PORTB = 0x3;
            break;

        case LightState7:
            PORTB = 0x1;
            break;

        case WaitState1:
        case WaitState2:
        case WaitState3:
        case WaitState4:
        case WaitState5:
        case WaitState6:
        case WaitState7:
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

        lightState = LightsOn;

        while (1)
        {
            Tick();
        }

        return 1;
    }
/*	Author: sjoha005
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *  LINK: https://youtu.be/NHh4vFTzcSs
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void transmit_data(unsigned char data)
{
    int i;
    for (i = 0; i < 8; ++i)
    {
        // Sets SRCLR to 1 allowing data to be set
        // Also clears SRCLK in preparation of sending data
        PORTC = 0x08;
        // set SER = next bit of data to be sent.
        PORTC |= ((data >> i) & 0x01);
        // set SRCLK = 1. Rising edge shifts next bit of data into the shift register
        PORTC |= 0x02;
    }
    // set RCLK = 1. Rising edge copies data from “Shift” register to “Storage” register
    PORTC |= 0x04;
    // clears all lines in preparation of a new transmission
    PORTC = 0x00;
}

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

unsigned char tempC = 0x00;

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
        tempC = 0x30;
        transmit_data(tempC);
        break;

    case WaitState:
        tempC = 0x03;
        transmit_data(tempC);
        break;

    case HalfState:
        break;

    case WaitState1:
        tempC = 0x0C;
        transmit_data(tempC);

    case EndState:
        break;

    case WaitState2:
        tempC = 0x30;
        transmit_data(tempC);
        break;

    default:
        break;
    }
}

int main(void)
{
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRC = 0xFF;
    PORTC = 0x00;

    lightsState = LightsOn;
    void transmit_data(tempC);
    while (1)
    {
        Tick();
    }

    return 1;
}

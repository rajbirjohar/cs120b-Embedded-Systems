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


enum buttonStates
{
    startButton,
    InitialState,
    WaitState,
    WaitState1,
    WaitState2,
    IncrementState,
    DecrementState,
    ResetState
} buttonState;

unsigned char IncrementStateButton = 0x00, DecrementStateButton = 0x00, tempC = 0x00;

void Tick()
{
    switch (buttonState)
    {
    case startButton:
        buttonState = InitialState;
        break;

    case InitialState:
        if (IncrementStateButton && DecrementStateButton)
        {
            buttonState = ResetState;
        }
        else if (IncrementStateButton)
        {
            buttonState = IncrementState;
        }
        else if (DecrementStateButton)
        {
            buttonState = DecrementState;
        }
        else
        {
            buttonState = InitialState;
        }
        break;

    case IncrementState:
    case WaitState1:
        if (IncrementStateButton && DecrementStateButton)
        {
            buttonState = ResetState;
        }
        else if (!IncrementStateButton && !DecrementStateButton)
        {
            buttonState = InitialState;
        }
        else if (DecrementStateButton)
        {
            buttonState = DecrementState;
        }
        else
        {
            buttonState = WaitState1;
        }
        break;

    case DecrementState:
    case WaitState2:
        if (IncrementStateButton && DecrementStateButton)
        {
            buttonState = ResetState;
        }
        else if (!IncrementStateButton && !DecrementStateButton)
        {
            buttonState = InitialState;
        }
        else if (IncrementStateButton)
        {
            buttonState = IncrementState;
        }
        else
        {
            buttonState = WaitState2;
        }
        break;

    case ResetState:
        if (!IncrementStateButton && !DecrementStateButton)
        {
            buttonState = InitialState;
        }
        else
        {
            buttonState = WaitState;
        }
        break;

    case WaitState:
        if (!IncrementStateButton && !DecrementStateButton)
        {
            buttonState = InitialState;
        }
        else if (IncrementStateButton)
        {
            buttonState = IncrementState;
        }
        else if (DecrementStateButton)
        {
            buttonState = DecrementState;
        }
        else
        {
            buttonState = WaitState;
        }
        break;
    }

    switch (buttonState)
    {
    case InitialState:
    case WaitState:
    case WaitState1:
    case WaitState2:
        break;

    case IncrementState:
        if (tempC < 255)
        {
            tempC = tempC + 1;
        }
        break;

    case DecrementState:
        if (tempC > 0)
        {
            tempC = tempC - 1;
        }
        break;

    case ResetState:
        tempC = 0;
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

    buttonState = startButton;

    while (1)
    {
        IncrementStateButton = PINA & 0x01;
        DecrementStateButton = PINA & 0x02;
        DecrementStateButton = (DecrementStateButton >> 1);
        Tick();
        transmit_data(tempC);
    }

    return 1;
}

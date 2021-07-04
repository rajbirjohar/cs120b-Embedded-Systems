/*	Author: sjoha005
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *  LINK: https://youtu.be/ZLjHHADGiKM
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

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
        else if (IncrementStateButton && !DecrementStateButton)
        {
            buttonState = IncrementState;
        }
        else if (!IncrementStateButton && DecrementStateButton)
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
        else if (!IncrementStateButton && DecrementStateButton)
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
        else if (IncrementStateButton && !DecrementStateButton)
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
        else if (IncrementStateButton && !DecrementStateButton)
        {
            buttonState = IncrementState;
        }
        else if (!IncrementStateButton && DecrementStateButton)
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
        break;

    case IncrementState:
        if (tempC < 9)
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

    case WaitState:
        break;

    case WaitState1:
        break;

    case WaitState2:
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
    tempC = 0x07;

    while (1)
    {
        IncrementStateButton = ~PINA & 0x01;
        DecrementStateButton = ~PINA & 0x02;
        DecrementStateButton = (DecrementStateButton >> 1);
        Tick();
        PORTC = tempC;
    }

    return 1;
}
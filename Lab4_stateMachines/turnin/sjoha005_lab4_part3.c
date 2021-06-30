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

enum keypadStates
{
    KeypadOn,
    DoorLocked,
    DoorUnlocked,
    PoundPressed,
    Wait
} keypadState;

unsigned char xButton = 0x00, yButton = 0x00, poundButton = 0x00, insideButton = 0x00, doorStatus = 0x00;
unsigned char currentState;

void Tick()
{
    switch (keypadState)
    {
    case KeypadOn:
        keypadState = DoorLocked;
        break;

    case DoorLocked:
        if (poundButton)
        {
            keypadState = PoundPressed;
        }
        else
        {
            keypadState = DoorLocked;
        }
        break;

    case PoundPressed:
        if (!xButton && !yButton && !poundButton)
        {
            keypadState = Wait;
        }
        else if (poundButton)
        {
            keypadState = PoundPressed;
        }
        else
        {
            keypadState = DoorLocked;
        }
        break;

    case Wait:
        if (yButton)
        {
            keypadState = DoorUnlocked;
        }
        else if (!xButton && !yButton && !poundButton)
        {
            keypadState = Wait;
        }
        else
        {
            keypadState = DoorLocked;
        }
        break;

    case DoorUnlocked:
        if (insideButton)
        {
            keypadState = DoorLocked;
        }
        else
        {
            keypadState = DoorUnlocked;
        }
        break;
    }

    switch (keypadState)
    {
    case DoorLocked:
        doorStatus = 0x00;
        currentState = DoorLocked;
        break;

    case PoundPressed:
        currentState = PoundPressed;
        break;

    case Wait:
        currentState = Wait;
        break;

    case DoorUnlocked:
        doorStatus = 0x01;
        currentState = DoorUnlocked;
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
    DDRC = 0xFF;
    PORTC = 0x00;

    keypadState = KeypadOn;

    while (1)
    {
        xButton = PINA & 0x01;
        yButton = PINA & (0x01 << 1);
        poundButton = PINA & (0x01 << 2);
        insideButton = PINA & (0x01 << 7);

        Tick();

        PORTB = doorStatus;
        PORTC = currentState;
    }

    return 1;
}
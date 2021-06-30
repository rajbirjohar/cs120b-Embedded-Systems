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
    keypadOn,
    DoorLocked,
    DoorUnlocked,
    OutsideCombo,
    InsideCombo,
    Restart

} keypadState;

unsigned char OutsideCombo[7] = {0x04, 0x00, 0x01, 0x00, 0x02, 0x00, 0x01};
unsigned char i;

void Tick()
{
    switch (keypadState)
    {
    case keypadOn:
        keypadState = DoorLocked;
        break;

    case DoorLocked:
        i = 0x00;
        if ((PINA & 0x07) == OutsideCombo[i])
        {
            keypadState = OutsideCombo;
        }
        else
        {
            keypadState = DoorLocked;
        }
        break;

    case DoorUnlocked:
        if ((PINA & 0x87) == 0x80)
        {
            keypadState = DoorLocked;
        }
        else if ((PINA & 0x87) == 0x00)
        {
            keypadState = Restart;
        }
        else
        {
            keypadState = DoorUnlocked;
        }
        break;

    case OutsideCombo:
        if ((PINA & 0x07) == OutsideCombo[i])
        {
            keypadState = OutsideCombo;
        }
        else if (i + 1 == 6)
        {
            i++;
            if ((PINA & 0x07) == OutsideCombo[i])
            {
                keypadState = DoorUnlocked;
            }
            else
            {
                keypadState = DoorLocked;
            }
        }
        else if (i < 6)
        {
            i++;
            if ((PINA & 0x07) == OutsideCombo[i])
            {
                keypadState = OutsideCombo;
            }
            else
            {
                keypadState = DoorLocked;
            }
        }
        break;

    case InsideCombo:
        if ((PINA & 0x87) == OutsideCombo[i])
        {
            keypadState = InsideCombo;
        }
        else if (i + 1 == 6)
        {
            i++;
            if ((PINA & 0x87) == OutsideCombo[i])
            {
                keypadState = DoorLocked;
            }
            else
            {
                keypadState = Restart;
            }
        }
        else if (i < 6)
        {
            i++;
            if ((PINA & 0x87) == OutsideCombo[i])
            {
                keypadState = InsideCombo;
            }
            else
            {
                keypadState = Restart;
            }
        }
        break;

    case Restart:
        if ((PINA & 0x87) == 0x80)
        {
            keypadState = DoorLocked;
        }
        else
        {
            i = 0x00;
            if ((PINA & 0x87) == OutsideCombo[i])
            {
                keypadState = InsideCombo;
            }
            else
            {
                keypadState = Restart;
            }
        }
        break;
    }

    switch (keypadState)
    {
    case DoorLocked:
        PORTB = 0x00;
        break;

    case DoorUnlocked:
        PORTB = 0x01;
        break;

    case OutsideCombo:
    case InsideCombo:
    case Restart:
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

    while (1)
    {
        Tick();
    }

    return 1;
}
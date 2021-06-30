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

enum ledStates
{
    startLed,
    led1,
    firstButtonPress,
    led2,
    secondButtonPress
} ledState;

unsigned char button = 0x00;
unsigned char tempB = 0x00;

void Tick()
{
    switch (ledState)
    {
    case startLed:
        ledState = led1;
        break;

    case led1:
        if (button == 0x01)
        {
            ledState = firstButtonPress;
        }
        else
        {
            ledState = led1;
        }
        break;

    case firstButtonPress:
        if (button == 0x00)
        {
            ledState = led2;
        }
        else
        {
            ledState = firstButtonPress;
        }
        break;

    case led2:
        if (button == 0x01)
        {
            ledState = secondButtonPress;
        }
        else
        {
            ledState = led2;
        }
        break;

    case secondButtonPress:
        if (button == 0x00)
        {
            ledState = led1;
        }
        else
        {
            ledState = secondButtonPress;
        }
        break;

    default:
        ledState = startLed;
        break;
    }

    switch (ledState)
    {
    case led1:
        tempB = 0x01;
        break;

    case firstButtonPress:
        tempB = 0x02;
        break;

    case led2:
        break;

    case secondButtonPress:
        tempB = 0x01;
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

    // Initializing
    ledState = startLed;

    while (1)
    {
        button = PINA & 0x01;
        Tick();
        PORTB = tempB;
    }

    return 1;
}

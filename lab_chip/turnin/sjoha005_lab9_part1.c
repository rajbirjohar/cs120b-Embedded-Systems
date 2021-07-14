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

unsigned char threeLEDs = 0x00, blinkingLED = 0x00;

enum LEDStates
{
    LEDStart,
    LED1State,
    LED2State,
    LED3State
} LEDState;
enum BlinkingLEDStates
{
    BlinkingLEDStart,
    OnState,
    OffState
} BlinkingLEDState;

void TickThreeLEDsSM()
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
        threeLEDs = 0x01;
        break;
    case LED2State:
        threeLEDs = 0x02;
        break;

    case LED3State:
        threeLEDs = 0x04;
        break;

    default:
        break;
    }
}

void TickBlinkingLEDsSM()
{
    switch (BlinkingLEDState)
    {
    case BlinkingLEDStart:
        BlinkingLEDState = OnState;
        break;

    case OnState:
        BlinkingLEDState = OffState;
        break;

    case OffState:
        BlinkingLEDState = OnState;
        break;
    }

    switch (BlinkingLEDState)
    {
    case OnState:
        blinkingLED = 0x08;
        break;

    case OffState:
        blinkingLED = 0x00;
        break;

    default:
        break;
    }
}

void TickCombineLEDsSM()
{
    PORTB = threeLEDs | blinkingLED;
}

int main(void)
{
    DDRB = 0xFF;
    PORTB = 0x00;

    TimerSet(1000);
    TimerOn();

    LEDState = LEDStart;
    BlinkingLEDState = BlinkingLEDStart;

    while (1)
    {
        TickThreeLEDsSM();
        TickBlinkingLEDsSM();
        TickCombineLEDsSM();
        while (!TimerFlag)
            ;
        TimerFlag = 0;
    }
}
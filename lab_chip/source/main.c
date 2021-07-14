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

unsigned char threeLEDs = 0x00, blinkingLED = 0x00, sound = 0x00, button = 0x00;

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

enum SoundStates
{
    SoundStart,
    SoundOnState,
    SoundOffState,
    SoundContinueState
} SoundState;

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

void TickSoundSM()
{
    button = ~PINA & 0x04;

    switch (SoundState)
    {
    case SoundStart:
        SoundState = SoundOffState;
        break;

    case SoundOnState:
        if (button)
        {
            SoundState = SoundContinueState;
        }
        else
        {
            SoundState = SoundOffState;
        }
        break;

    case SoundOffState:
        if (button)
        {
            SoundState = SoundOnState;
        }
        else
        {
            SoundState = SoundOffState;
        }
        break;

    case SoundContinueState:
        if (button)
        {
            SoundState = SoundOnState;
        }
        else
        {
            SoundState = SoundOffState;
        }
        break;

    default:
        break;
    }

    switch (SoundState)
    {
    case SoundOffState:
    case SoundContinueState:
        sound = 0x00;
        break;

    case SoundOnState:
        sound = 0x10;
        break;

    default:
        break;
    }
}

void TickCombineLEDsSM();
()
{
    PORTB = threeLEDs | blinkingLED | sound;
}

int main(void)
{
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRB = 0xFF;
    PORTB = 0x00;

    unsigned long LEDElapsedTime = 300, BlinkingLEDElapsedTime = 1000, SoundElapsedTime = 2;
    const unsigned long period = 1;

    PORTB = 0x00;

    TimerSet(period);
    TimerOn();

    LEDState = LEDStart;
    BlinkingLEDState = BlinkingLEDStart;
    SoundState = SoundStart;

    while (1)
    {
        if (LEDElapsedTime > 301)
        {
            TickThreeLEDsSM();
            LEDElapsedTime = 0;
        }

        if (BlinkingLEDElapsedTime > 1001)
        {
            TickBlinkingLEDsSM();
            BlinkingLEDElapsedTime = 0;
        }

        if (SoundElapsedTime > 3)
        {
            TickSoundSM();
            SoundElapsedTime = 0;
        }

        TickCombineLEDsSM();
        ();

        while (!TimerFlag)
            ;
        TimerFlag = 0;
        LEDElapsedTime += period;
        BlinkingLEDElapsedTime += period;
        SoundElapsedTime += period;
    }

    return 1;
}
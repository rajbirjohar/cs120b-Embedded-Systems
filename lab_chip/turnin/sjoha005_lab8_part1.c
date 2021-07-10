/*	Author: sjoha005
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *  LINK: https://youtu.be/-SRgLOhFlFA
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

// 0.954 hz is lowest frequency possible with this function,
// based on settings in PWM_on()
// Passing in 0 as the frequency will stop the speaker from generating sound
void set_PWM(double frequency)
{
    static double current_frequency; // Keeps track of the currently set frequency
    // Will only update the registers when the frequency changes, otherwise allows
    // music to play uninterrupted.
    if (frequency != current_frequency)
    {
        if (!frequency)
        {
            TCCR3B &= 0x08;
        } // stops timer/counter
        else
        {
            TCCR3B |= 0x03;
        } // resumes/continues timer/counter

        // prevents OCR3A from overflowing, using prescaler 64
        // 0.954 Hz is smallest frequency that will not result in overflow
        if (frequency < 0.954)
        {
            OCR3A = 0xFFFF;
        }

        // prevents OCR3A from underflowing, using prescaler 64
        // 31250 is largest frequency that will not result in underflow
        else if (frequency > 31250)
        {
            OCR3A = 0x0000;
        }

        // set OCR3A based on desired frequency
        else
        {
            OCR3A = (short)(8000000 / (128 * frequency)) - 1;
        }

        TCNT3 = 0; // resets counter
        current_frequency = frequency;
    }
}

void PWM_on()
{
    TCCR3A = (1 << COM3A0);
    // COM3A0: Toggle PB3 on compare match between counter and OCR3A
    TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
    // WGM32: When counter (TCNT3) matches OCR3A, reset counter
    // CS31 & CS30: Set a prescaler of 64
    set_PWM(0);
}

void PWM_off()
{
    TCCR3A = 0x00;
    TCCR3B = 0x00;
}

enum soundStates
{
    Sound_Start,
    WaitState,
    C4Sound,
    D4Sound,
    E4Sound
} soundState;

unsigned char C4 = 0x00, D4 = 0x00, E4 = 0x00;

void Tick()
{
    switch (soundState)
    {
    case Sound_Start:
        soundState = WaitState;
        break;

    case WaitState:
        if (C4 && !D4 && !E4)
        {
            soundState = C4Sound;
        }
        else if (!C4 && D4 && !E4)
        {
            soundState = D4Sound;
        }
        else if (!C4 && !D4 && E4)
        {
            soundState = E4Sound;
        }
        else
        {
            soundState = WaitState;
        }
        break;

    case C4Sound:
        if (C4 && !D4 && !E4)
        {
            soundState = C4Sound;
        }
        else
        {
            soundState = WaitState;
        }
        break;

    case D4Sound:
        if (!C4 && D4 && !E4)
        {
            soundState = D4Sound;
        }
        else
        {
            soundState = WaitState;
        }
        break;

    case E4Sound:
        if (!C4 && !D4 && E4)
        {
            soundState = E4Sound;
        }
        else
        {
            soundState = WaitState;
        }
        break;
    }

    switch (soundState)
    {
    case WaitState:
        set_PWM(0);
        break;

    case C4Sound:
        set_PWM(261.63);
        break;

    case D4Sound:
        set_PWM(293.66);
        break;

    case E4Sound:
        set_PWM(329.63);
        break;

    default:
        break;
    }
}

int main(void)
{
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRB = 0x40;
    PORTB = 0x00;

    PWM_on();
    soundState = Sound_Start;

    while (1)
    {
        C4 = ~PINA & 0x01;
        D4 = ~PINA & 0x02;
        E4 = ~PINA & 0x04;

        Tick();
    }

    return 1;
}
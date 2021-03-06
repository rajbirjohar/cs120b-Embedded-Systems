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

void PWM_OffState()
{
    TCCR3A = 0x00;
    TCCR3B = 0x00;
}

enum soundStates
{
    SoundStart,
    OffState,
    WaitOnState,
    OnState,
    WaitOffState,
    Up,
    Down
} soundState;

const double musicalNotes[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
unsigned char i, power = 0x00, up = 0x00, down = 0x00;

void Tick()
{
    switch (soundState)
    {
    case SoundStart:
        soundState = OffState;
        break;

    case OffState:
        i = 0x00;
        if (power)
        {
            soundState = WaitOnState;
        }
        else
        {
            soundState = OffState;
        }
        break;

    case WaitOnState:
        if (!power)
        {
            soundState = OnState;
        }
        else
        {
            soundState = WaitOnState;
        }
        break;

    case OnState:
        if (up && (i < 7))
        {
            i++;
            soundState = Up;
        }
        else if (down && (i > 0))
        {
            i--;
            soundState = Down;
        }
        else if (power)
        {
            soundState = WaitOffState;
        }
        else
        {
            soundState = OnState;
        }
        break;

    case WaitOffState:
        if (!power)
        {
            soundState = OffState;
        }
        else
        {
            soundState = WaitOffState;
        }
        break;

    case Up:
        if (!up)
        {
            soundState = OnState;
        }
        else
        {
            soundState = Up;
        }
        break;

    case Down:
        if (!down)
        {
            soundState = OnState;
        }
        else
        {
            soundState = Down;
        }
        break;
    }

    switch (soundState)
    {
    case OffState:
        set_PWM(0.0);
        break;

    case OnState:
        set_PWM(musicalNotes[i]);
        break;

    case WaitOnState:
    case WaitOffState:
    case Up:
    case Down:
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

    PWM_on();
    soundState = SoundStart;

    while (1)
    {
        power = ~PINA & 0x01;
        up = ~PINA & 0x02;
        down = ~PINA & 0x04;

        Tick();
    }

    return 1;
}
/*	Author: sjoha005
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *  LINK: https://youtu.be/tFIegE2Mdc4
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "timer.h"
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
    WaitState,
    CState,
    FState,
    GState,
    FState2,
    EState,
    BState,
    AState,
    GState2,
} soundState;

// C D E F G A B C
// C F G F E B A G
const double musicalNotes[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
unsigned char i, button = 0x00;

void Tick()
{
    switch (soundState)
    {
    case SoundStart:
        soundState = WaitState;
        break;
    case WaitState:
        if (button)
        {
            soundState = CState;
        }
    case CState:
        soundState = FState;
        break;
    case FState:
        soundState = GState;
        break;
    case GState:
        soundState = FState2;
        break;
    case FState2:
        soundState = EState;
        break;
    case EState:
        soundState = BState;
        break;
    case BState:
        soundState = AState;
        break;
    case AState:
        soundState = GState2;
        break;
    case GState2:
        soundState = CState;
        break;
    }

    switch (soundState)
    {
    case CState:
        set_PWM(musicalNotes[1]);
        break;
    case FState:
        set_PWM(musicalNotes[4]);
        break;
    case GState:
        set_PWM(musicalNotes[5]);
        break;
    case FState2:
        set_PWM(musicalNotes[4]);
        break;
    case EState:
        set_PWM(musicalNotes[3]);
        break;
    case BState:
        set_PWM(musicalNotes[7]);
        break;
    case AState:
        set_PWM(musicalNotes[6]);
        break;
    case GState2:
        set_PWM(musicalNotes[5]);
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
    TimerSet(500);
    TimerOn();
    PWM_on();
    soundState = SoundStart;

    while (1)
    {
        button = ~PINA & 0x01;
        Tick();
        while (!TimerFlag)
            ;
        TimerFlag = 0;
    }

    return 1;
}
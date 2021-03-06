/*	Author: sjoha005
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *  LINK: https://youtu.be/zWCFs3jE76M
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init()
{
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
    // ADEN: setting this bit enables analog-to-digital conversion
    // ADSC: setting this bit starts the first conversion
    // ADATE: setting this bit enables auto-triggering. Since we are
    //		  in Free Running Mode, a new conversion will trigger whenever
    //		  the previous conversion completes.
}

int main(void)
{
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRB = 0xFF;
    PORTB = 0x00;

    unsigned short my_short = 0x00;

    ADC_init();

    while (1)
    {
        my_short = ADC;

        if (my_short >= 475)
        {
            PORTB = 0xFF;
        }
        else if (my_short >= (475 / 2))
        {
            PORTB = 0X7F;
        }
        else if (my_short >= (475 / 3))
        {
            PORTB = 0x3F;
        }
        else if (my_short >= (475 / 4))
        {
            PORTB = 0x1F;
        }
        else if (my_short >= (475 / 5))
        {
            PORTB = 0x0F;
        }
        else if (my_short >= (475 / 6))
        {
            PORTB = 0x07;
        }
        else if (my_short >= (475 / 7))
        {
            PORTB = 0x03;
        }
        else
        {
            PORTB = 0x01;
        }
    }

    return 1;
}
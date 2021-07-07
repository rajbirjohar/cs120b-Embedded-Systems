/*	Author: sjoha005
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *  LINK: https://youtu.be/l8BGl0bi_4E
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
    DDRD = 0xFF;
    PORTB = 0x00;

    unsigned short my_short = 0x00;

    ADC_init();

    while (1)
    {
        my_short = ADC;
        PORTB = (char)my_short;
        PORTD = (char)(my_short >> 8);
    }

    return 1;
}
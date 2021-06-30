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

int main(void)
{
    DDRB = 0xFE;
    PORTB = 0x01;
    DDRD = 0x00;
    PORTD = 0xFF;

    unsigned char minWeight = 0x00, maxWeight = 0x00, airBag;

    while (1)
    {
        minWeight = PINB & 0x01;
        maxWeight = PIND;

        airBag = 0x00;

        if ((minWeight == 0 && maxWeight >= 0x46) || 
            (minWeight == 1 && maxWeight >= 0x45))
        {
            airBag = 0x02;
        }
        else if ((minWeight == 0 && maxWeight > 0x05) || 
                 (minWeight == 1 && maxWeight > 4))
        {
            airBag = 0x04;
        }

        PORTB = airBag;
    }

    return 1;
}
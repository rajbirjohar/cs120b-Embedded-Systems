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
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRB = 0xFF;
    PORTB = 0x00;
    DDRC = 0xFF;
    PORTC = 0x00;

    unsigned char tempA = 0x00;

    while (1)
    {
        tempA = PINA;
        // PA7 to PA4 and PB3 to PB0
        PORTB = (tempA >> 4) & 0x0F; 
        // PA3 to PA0 and PB7 to PB4
        PORTC = (tempA << 4) & 0xF0; 
    }

    return 1;
}
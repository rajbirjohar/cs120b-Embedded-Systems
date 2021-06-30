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
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRB = 0x00;
    PORTB = 0xFF;
    DDRC = 0xFF;
    PORTC = 0x00;
    /* Insert your solution below */

    unsigned char tempA = 0x00, tempB = 0x00, currentBit = 0x00;
    unsigned char onesCount;
    unsigned char i;

    while (1)
    {
        tempA = PINA;
        tempB = PINB;
        onesCount = 0x00;

        for (i = 0; i < 8; ++i)
        {
            currentBit = (tempA >> i) & 0x01;
            if (currentBit != 0)
            {
                onesCount++;
            }
            currentBit = (tempB >> i) & 0x01;
            if (currentBit != 0)
            {
                onesCount++;
            }
        }
        PORTC = onesCount;
    }
    return 1;
}

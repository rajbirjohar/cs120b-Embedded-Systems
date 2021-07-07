/*	Author: sjoha005
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *  LINK: https://youtu.be/pzG9jiLuUfU
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
    DDRC = 0xFF;
    PORTC = 0x00;

    unsigned char fuelLevel = 0x00, fuelIndicator = 0x00;

    while (1)
    {
        fuelLevel = ~PINA & 0x0F;
        // PC6
        if (fuelLevel == 0x00)
        {
            fuelIndicator = 0x40;
        }
        // PC6 and PC5
        else if (fuelLevel == 0x01 || fuelLevel == 0x02)
        {
            fuelIndicator = 0x60;
        }
        // PC6 to PC4
        else if (fuelLevel == 0x03 || fuelLevel == 0x04)
        {
            fuelIndicator = 0x70;
        }
        // PC5 to PC3
        else if (fuelLevel == 0x05 || fuelLevel == 0x06)
        {
            fuelIndicator = 0x38;
        }
        // PC5 to PC2
        else if (fuelLevel == 0x07 || fuelLevel == 0x08 || fuelLevel == 0x09)
        {
            fuelIndicator = 0x3C;
        }
        // PC5 to PC1
        else if (fuelLevel == 0x0A || fuelLevel == 0x0B || fuelLevel == 0x0C)
        {
            fuelIndicator = 0x3E;
        }
        // PC5 to PC0
        else
        {
            fuelIndicator = 0x3F;
        }

        PORTC = fuelIndicator;
    }

    return 1;
}

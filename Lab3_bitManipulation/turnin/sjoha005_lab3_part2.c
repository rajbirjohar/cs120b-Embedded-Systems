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
    DDRC = 0xFF;
    PORTC = 0x00;

    unsigned char fuelLevel = 0x00, fuelLight = 0x00, tempA = 0x00;

    while (1)
    {
        fuelLevel = PINA & 0x0F;
        tempA = PINA & 0x70;      

        // PC6
        if (fuelLevel == 0x00)
        {
            fuelLight = 0x40; 
        }
        // PC6 and PC5
        else if (fuelLevel == 0x01 || fuelLevel == 0x02)
        {
            fuelLight = 0x60; 
        }
        // PC6 to PC4
        else if (fuelLevel == 0x03 || fuelLevel == 0x04)
        {
            fuelLight = 0x70; 
        }
        // PC5 to PC3
        else if (fuelLevel == 0x05 || fuelLevel == 0x06)
        {
            fuelLight = 0x38; 
        }
        // PC5 to PC2
        else if (fuelLevel == 0x07 || fuelLevel == 0x08 || fuelLevel == 0x09)
        {
            fuelLight = 0x3C; 
        }
        // PC5 to PC1
        else if (fuelLevel == 0x0A || fuelLevel == 0x0B || fuelLevel == 0x0C)
        {
            fuelLight = 0x3E; 
        }
        // PC5 to PC0
        else
        {
            fuelLight = 0x3F; 
        }

        if ((tempA >> 4) == 0x03)
        {
            PORTC = fuelLight | 0x80;
        }
        else
        {
            PORTC = fuelLight;
        }
    }

    return 1;
}

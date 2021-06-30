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

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */

    unsigned char onesCount = 0x00, currentPin = 0x01, i;    

    while (1) {
        for(i = 0; i < 9; i++){
           if(PINA & currentPin || PINB & currentPin){
               onesCount++;
           }
           currentPin *= 2;
        }
        PORTC = onesCount;
        onesCount = 0x00;
    }
    return 1;
}

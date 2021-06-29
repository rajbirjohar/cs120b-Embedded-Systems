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
#include <stdlib.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0x00; PORTC = 0xFF;
    DDRD = 0xFF; PORTD = 0x00;
   
    unsigned char weight = 0x00, seatA = 0x00, seatB = 0x00, seatC = 0x00, tempD = 0x00;
    
    while(1){
        seatA = PINA;
        seatB = PINB;
        seatC = PINC;
    
        weight = seatA + seatB + seatC;
    
        if(weight > 0x8D){
            tempD = tempD | 0x01;
        }else{
            tempD = tempD & 0xFE;
        }
        if(abs(seatA - seatC) > 0x51){
            tempD = tempD | 0x02;
        }else{
            tempD = tempD & 0xFD;
        }
        
        weight = weight & 0xFC;
        PORTD = weight | tempD;
    } 
    
    return 1;
}






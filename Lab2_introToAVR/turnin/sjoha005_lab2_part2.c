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
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    
    unsigned char cntavail; // tracks number of free spaces
    unsigned char parkingSpace1 = 0x00; 
    unsigned char parkingSpace2 = 0x00;  
    unsigned char parkingSpace3 = 0x00; 
    unsigned char parkingSpace4 = 0x00; 

    while(1){
        cntavail = 0x04;
        parkingSpace1 = PINA & 0x01;
        parkingSpace2 = PINA & 0x02;
        parkingSpace3 = PINA & 0x04;
        parkingSpace4 = PINA & 0x08;

        if(parkingSpace1 == 0x01){
	    cntavail--;
	}
        if(parkingSpace2 == 0x02){
	    cntavail--;
	}	
        if(parkingSpace3 == 0x04){
	    cntavail--;
 	}
        if(parkingSpace4 == 0x08){
	    cntavail--;
	}
	// sets PC7 to 1 if no more parking spaces
	if(cntavail == 0x00){
	cntavail = 0x80;
	}
	PORTC = cntavail;
    }
    return 1;
}






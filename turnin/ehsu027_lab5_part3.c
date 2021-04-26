/*	Author: ehsu027
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

	unsigned char i = 1;
	unsigned char pattern[9] = {0x20, 0x30, 0x38, 0x1C, 0x0E, 0x07, 0x03, 0x01, 0x20};

enum SM_STATES { SM_Start, SM_Go, SM_Wait } SM_State;

void Tick_LED() {
	switch(SM_State) {
		case SM_Start:
			SM_State = SM_Wait;
		break;
		
		case SM_Wait:
			if ((PINA & 0x01) == 0x00) {
				SM_State = SM_Go;
			}
			else if ((PINA & 0x01) == 0x01) {
				SM_State = SM_Wait;
			}
		break;

		case SM_Go:
			if ((PINA & 0x01) == 0x01) {
				++i;
				SM_State = SM_Wait;
			}
			else {
				SM_State = SM_Go;
			}
		break;

		default:
			SM_State = SM_Wait;
		break;
	}

	switch(SM_State) {
		case SM_Wait:
			PORTB = PORTB;
		break;

		case SM_Go:
			PORTB = pattern[i];
			if (i == 9) {
				i = 1;
			}
		break;

		default:
		break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	SM_State = SM_Start;
	while (1) {
		Tick_LED();
    }
    return 1;
}

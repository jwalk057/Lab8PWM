/*	Author: lab
 *  Partner(s) Name: Jeremy Walker
 *	Lab Section:
 *	Assignment: Lab # 8 Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo link: https://youtu.be/OIYR1HbEtOY
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void set_PWM(double frequency) {
    static double current_frequency;

    if (frequency != current_frequency) {
        if(!frequency)
            TCCR3B &= 0x08;
        else
            TCCR3B |= 0x03;

        if(frequency < 0.954)
            OCR3A = 0xFFFF;
        else if (frequency > 31250)
            OCR3A = 0x0000;
        else
            OCR3A = (short) (8000000 / (128 * frequency)) - 1;
        
        TCNT3 = 0;
        current_frequency = frequency;
    }
}

void PWM_on() {
    TCCR3A = (1 << COM3A0);
    TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
    set_PWM(0);
}

void PWM_off() {
    TCCR3A = 0x00;
    TCCR3B = 0x00;
}

double C4 = 261.63;
double D4 = 293.66;
double E4 = 329.63;

//enum setToneSM {Start, B1, B2, B3} ex1SET;
//enum playToneSM {Off, Play} ex1PLAY;

// Couldn't get this to work
/*
void Tick(unsigned char b1, unsigned char b2, unsigned char b3){
	switch(ex1SET){
		case Start:
			if(b1){ex1SET = B1;}
    			else {ex1SET = Start;}
			break;
		case B1:
			if(b1){
				set_PWM(C4);
				PWM_on();
			}
			else{set_PWM(0);}
			break;
		case B2:
			break;
		case B3:
			break;
	

	}
}
*/

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0x40; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	//ex1SET = Start;
	//ex1PLAY = Off;
	unsigned char b1 = 0x00;
	unsigned char b2 = 0x00;
	unsigned char b3 = 0x00;
	PWM_on();
    /* Insert your solution below */
    while (1) {
	b1 = ~PINA & 0x01;
	b2 = ~PINA & 0x02;
	b3 = ~PINA & 0x04;
	if(b1&&!b2&&!b3){set_PWM(C4);}
	else if(!b1&&b2&&!b3){set_PWM(D4);}
	else if(!b1&&!b2&&b3){set_PWM(E4);}
        else{set_PWM(0);}

    }
    return 1;
}

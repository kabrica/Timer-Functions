/*
 * Timers.c
 *
 * Created: 10/28/2017 12:16:09 AM
 * Author : Night
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "8BITDELAY256.h"     // Prescaler of 256
//#include "8BITDELAY1024.h"  // Prescaler of 1024


int main(void)
{
	DDRC = (1<<DDC0) | (1<<DDC1) | (1<<DDC2);    //Define DDRC as output
	
	timer0define();    //Call timer/interrupt define function

    while (1) 
    {
				PINC = (1<<PINC0) | (1<<PINC1) | (1<<PINC2);        //Blink the led
				delay(1000);										//Self made delay
		}    
}


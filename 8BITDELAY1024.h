// 8-Bit timer function with prescaler of 1024
// Author: Denis Mrdalj



			/*Calculation Explanation*/
/*
		1. 1/F_CPU/(prescaler, in this case 1024)*1000 to get miliseconds for 1 tact, 1/(16000000/1024)*1000 = 0.064ms
		2. Multiply the last value with 256 (since its 8-bit timer) to get maximum delay without overflowing,  0.064 * 256 = 16.384ms
		3. If for example we need 50ms delay, divide 50ms with max delay without overflowing to see how many overflows we need,  50ms/16.384ms = 3.051
		4. We can see that we need 3 overflows for 50ms, which means that for 1000ms we need 60 overflows, we can use decimals for maximum precision, but not now
*/

volatile unsigned char overflow;				/*	Variable that counts timer overflows (Count up to max value, since it's 8-bit timer, it's 256),*/

ISR(TIMER0_OVF_vect)						/*  Function that detects overflowing of timer, in this case it just counts overflows */
{
	overflow++;
}

void delay (unsigned long sec){				/* Precise delay function, with prescaler of 1024 */
	while(1){
		if (overflow>=240.0/1000*sec){		/* 60 overflows is 1 second for prescaler of 1024, when we divide it with 1000 we get 1ms, then we can multiply it with x to get precise ms delay */					
				overflow = 0;				/* Set overflow back to 0 so the next time we call the function it starts over */
				break;
		}
	}
}

void timer0define()							/* Defining registers of timers and interrupts */
{
	//Timer
	TCCR0B = (1<<CS02) | (1<<CS00);						/* Timer with prescaler of 1024 */
	TCNT0 = 0;								/* Current value of timer is 0, incrementation is done automatically, when it reaches 256 it goes back to 0 */
	
	//Interrupts
	TIMSK0 = (1<<TOIE0);					/* With this register we activate timer overflow interrupt */
	sei();									/* Activation of interrupts globally */
	overflow=0;								/* Starting value of overflow is 0 */
}
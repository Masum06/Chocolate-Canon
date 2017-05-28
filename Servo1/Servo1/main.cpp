#include <avr/io.h>

#include <util/delay.h>

#define F_CPU 1000000UL

#define SERVO_MAX 2300
#define SERVO_MIN 500

unsigned short degreeToOcr(int degree){
	return (SERVO_MIN + (SERVO_MAX-SERVO_MIN)/180*degree);//(1000)*(1 + degree/180);
}

int main()
{
	//Configure TIMER1
	TCCR1A|=(1<<COM1A1)|(1<<COM1A0)|(1<<WGM11);        //NON Inverted PWM
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)

	ICR1=19999;  //fPWM=50Hz (Period = 20ms Standard).

	DDRD|=0xFF;//(1<<PD4);   //PWM Pins as Out

	while(1)
	{
		OCR1A=ICR1-degreeToOcr(0);   //0 degree 500;//
		_delay_ms(1000);
		
		OCR1A=ICR1-degreeToOcr(45);   //45 degree 950;//
		_delay_ms(1000);
		
		OCR1A=ICR1-degreeToOcr(90);   //90 degree 1400;//
		_delay_ms(1000);
		
		OCR1A=ICR1-degreeToOcr(135);   //135 degree ;//
		_delay_ms(1000);

		OCR1A=ICR1-degreeToOcr(180);  //180 degree 2300;//
		_delay_ms(1000);
		
		OCR1A=ICR1-degreeToOcr(135);   //135 degree ;//
		_delay_ms(1000);
		
		OCR1A=ICR1-degreeToOcr(90);   //90 degree 1400;//
		_delay_ms(1000);
		
		OCR1A=ICR1-degreeToOcr(45);   //45 degree 950;//
		_delay_ms(1000);
	}
}
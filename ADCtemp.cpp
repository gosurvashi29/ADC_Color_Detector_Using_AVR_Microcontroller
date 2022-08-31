/*
 * ADCcolor.cpp
 *
 * Created: 13-09-2014 18:40:05
 *  Author: Urvashi
 */ 


# define F_CPU 8000000UL
#include <avr/io.h>
# include <util/delay.h>
void lcd_init();
void disp_cmd(unsigned int cmd);
void disp_data(int cmd);
void disp_num(unsigned int num);
void disp_string(  char *str);
int adc_read(int channel);
int temp(int k);
int main(void)
{
	
	DDRB = 0XFF;
	lcd_init();
	disp_cmd(0X80);
	disp_string("WELCOME");
	_delay_ms(1000);
	disp_cmd(0X01);
	_delay_ms(2);
	//disp_cmd(0X80);
	//disp_string("Enter the value");
	

	
	int X;
	while (1)
	{
		X=adc_read(0);
		
		_delay_ms(1000);
		disp_cmd(0X01);
		_delay_ms(2);
		disp_cmd(0XC5);
		disp_num(X);
		//disp_cmd(0X86);
		
		//temp(X);
		
		_delay_ms(1000);
	}
	return 0;
}			
		
	int adc_read(int channel)
	{
		ADMUX=0X40 + channel;
		ADCSRA=0XD7;
		while((ADCSRA & 0X10) ==0);
		return ADC;
	}
	void disp_cmd(unsigned int cmd)
	{
		PORTB=((cmd & 0XF0)+0X04);
		_delay_ms(1);
		PORTB=PORTB - 0X04;
		PORTB=(((cmd<<4)& 0XF0)+0X04);
		_delay_ms(1);
		PORTB=PORTB-0X04;
		
	}
	void disp_data( int cmd)
	{
		PORTB=((cmd  & 0XF0)+0X05);
		_delay_ms(1);
		PORTB=PORTB - 0X04;
		PORTB=(((cmd <<4)& 0XF0)+0X05);
		_delay_ms(1);
		PORTB=PORTB-0X04;
		
	}

	void disp_string( char *str)
	{
		int i=0;
		while (str[i]!='\0')
		{
			disp_data (str[i]);
			i++;
			
		}
	}

	void disp_num(unsigned int num)
	{
		int a=0;
		if (num==0)
		{
			disp_data(48);
		}
		disp_cmd (0X04);
		while (num!=0)
		{
			a=num % 10;
			disp_data(a+48);
			num=num/10;
		}
		disp_cmd (0X06);
	}
	void lcd_init()
	{
		disp_cmd(0X02);
		disp_cmd(0X28);
		disp_cmd(0X0C);
		disp_cmd(0X06);
	}
	int temp(int k)
	{
		if (k>100 && k<250)
		{
			disp_string("BLACK");
		}
		if (k>250 && k<450)
		{
			disp_string("VIOLET");
		}
		if (k>450 && k<500)
		{
			disp_string("RED");
		}
		if (k>500 && k<600)
		{
			disp_string("BLUE");
		}
		if (k>600 && k<700)
		{
			disp_string("GREEN");
		}
		if (k>700 && k<750)
		{
			disp_string("WHITE");
		}
		if (k>750 && k<800)
		{
			disp_string("YELLOW");
		}
		
	}
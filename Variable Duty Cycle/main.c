
#include <reg51.h>

#define input P1
sbit output = P2^0;
sbit error = P2^6;
sbit output_switch = P2^7;

char get_input();
void Timer(unsigned char, unsigned char);

char high_input, low_input;
char TimerH_high, TimerH_low, TimerL_high, TimerL_low;
float duty_cycle = 0;
short int delay_total;

void main(){
	output_switch = 1;
	input = 0xff;
	
	while(1){
		get_input();
		while(output_switch == 0){
			output = 1; 
			Timer(TimerH_high, TimerH_low);
			output = 0;
			Timer(TimerL_high, TimerL_low);
		}
	}
}

char get_input()
{
	low_input = input & 0x0f;
	high_input = (input >> 4) & 0x0f ;
	
	if( high_input > 9 || low_input > 9 )
	{
		error = 0;
		return -1;
	}
	error = 1;
	
	duty_cycle = ((high_input * 10) + low_input) / 100;
	
	delay_total =  0xffff - (0x0e67 * duty_cycle);
	TimerH_high = (delay_total >> 8) & 0x00ff;
	TimerH_low = delay_total & 0x00ff;
	
	delay_total =  0xffff - (0x0e67 * (1 - duty_cycle));
	TimerL_high = (delay_total >> 8) & 0x00ff;
	TimerL_low = delay_total & 0x00ff;
	
	return 0;
}

void Timer(unsigned char High, unsigned char Low){
	 TMOD = 0x01;
	 TL0 = Low;
	 TH0 = High;
	 TR0 = 1;
	 while(TF0 == 0);
	 TR0 = 0;
	 TF0 = 0;	 
	} 
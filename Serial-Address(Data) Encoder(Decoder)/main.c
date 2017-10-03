
#include <reg51.h>

#define input P1
#define output P2

short int message;
unsigned char check = 0;

void get_input (void) interrupt 0 {
	message = input & 0x0f;
	check = 1;
	}

void main(){
	IT0 = 1;
	EX0 = 1;
	EA = 1;
	input = 0xff;
	while(1){
		if(check == 1){
			if(message == 0x00) { output = 0x03; }
			else if(message == 0x01) { output = 0x9F; }
			else if(message == 0x02) { output = 0x25; }
			else if(message == 0x03) { output = 0x0D; }
			else if(message == 0x04) { output = 0x99; }
			else if(message == 0x05) { output = 0x49; }
			else if(message == 0x06) { output = 0x41; }
			else if(message == 0x07) { output = 0x1D; }
			else if(message == 0x08) { output = 0x01; }
			else if(message == 0x09) { output = 0x09; }
			else if(message == 0x0A) { output = 0x11; }
			else if(message == 0x0B) { output = 0xC1; }
			else if(message == 0x0C) { output = 0x63; }
			else if(message == 0x0D) { output = 0x85; }
			else if(message == 0x0E) { output = 0x61; }
			else if(message == 0x0F) { output = 0x71; }
		}
	}
}

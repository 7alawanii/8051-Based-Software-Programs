
#include <reg51.h>

#define input P1
sbit unlocked = P2^0;
sbit locked = P2^1;
short int key_lock = 0x2580;
short int keys,temp,temp_old;
unsigned char option;
unsigned char count = 0;
unsigned char change = 0;
unsigned char finish_change = 0;
unsigned char count_new = 0;

void get_input (void) interrupt 0 {
	option = input & 0x0F;
	if(option == 0x0C){ finish_change = 1; 
	count_new = 0;} 
	else if(count == 0){ 
		temp_old = input & 0x0F; 
		count = 1; }
	else if(count == 1){
		temp = input & 0x0F;
		temp_old = (temp_old << 4);
		temp_old = temp_old + temp;
		count_new +=1;
		if(count_new == 3 && change == 1){ 
			finish_change =0; 
			unlocked = 1;
			locked = 0; 
			change = 1;}}
		keys = temp_old;
		if(change == 1){ 
			key_lock = temp_old;}
		if(option == 0x0C || option == 0x0B ){ count = 0; }
}

void main(){
	IT0 = 1;
	EX0 = 1;
	EA = 1;
	input = 0xFF;
	unlocked = 1;
	locked = 0;
	while(1){
		if(keys == key_lock){
			unlocked = 0;
			locked = 1;
			if( option == 0x0B){	//when press on star (*) button the lock is locked again
				unlocked = 1;
				locked = 0;
				count = 0;
				keys = 0xABAB; }
			while(finish_change == 1){	//when press on window (#) button you can reset the key_lock
				unlocked = 0;
				locked = 1;
				change = 1;
				keys = 0xABAB; }
		}			
	}
}

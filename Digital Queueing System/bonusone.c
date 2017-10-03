#include <at89c51xd2.h>
#include <stdio.h>

sbit r0 = P1^7;
sbit r1 = P1^6;
sbit r2 = P1^5;
sbit r3 = P1^4;

sbit c0 = P1^3;
sbit c1 = P1^2;
sbit c2 = P1^1;
sbit c3 = P1^0;
static unsigned char first = 0x00;
static unsigned char second = 0x00;
void debounce()
{
	int i = 10000;
	int j = 1000000;

	for(;i>0;i--)
		for(; j>0;j--)
			;
}
void reset()
{
	first = 0x00;
second = 0x00;
P2=(first << 4) | second;
}

void decrement()
{
	if (second == 0x00)
						{
							if (first == 0x00)
								{
									first = 0x09;
									second = 0x09;
									P2=(first << 4) | second;
								}
							else
								{
									second = 0x09;
									first--;
									P2=(first << 4) | second;
								}
						}
					 else
						{
							second--;
							P2=(first << 4) | second;
							}		
}
void increment()
{
	 if (second == 0x09)
						{
							if (first == 0x09)
								{
									first = 0x00;
									second = 0x00;
									P2=(first << 4) | second;
								}
							else
								{
									second= 0x00;
									first++;
									P2=(first << 4) | second;
								}
						}
					 else
						{
							second++;
							P2=(first << 4) | second;
							}		
}
void normalkey(char key);
#define KEYPAD_NO_NEW_DATA '-'
static char Last_valid_Key_G = KEYPAD_NO_NEW_DATA;
char pKey;

char KeyPad_Scan()
{
	  static char Old_Key;
	  char Key = KEYPAD_NO_NEW_DATA;

	  r0 =0;
		     if(c3 == 0) {
					 //if A so imcrement
					 increment();
					 }
		else if(c2 == 0) {Key = 0x03;
											normalkey(Key);
											}
		else if(c1 == 0) {Key = 0x02;
											normalkey(Key);
											}
		else if(c0 == 0) {Key = 0x01;
											normalkey(Key);
											}
		r0 = 1;
	

		r1 =0;
			   if(c3 == 0) {
					 //if B so decrement
					 decrement();
					  }
		else if(c2 == 0) {Key =  0x06;
											normalkey(Key);								
											}
		else if(c1 == 0) {Key =  0x05;
											normalkey(Key);	
											}
		else if(c0 == 0) {Key =  0x04;
											normalkey(Key);	
											}		
		r1 = 1;
	

	r2 = 0;
		if(c3 == 0) {Key = 'C'; }
		if(c2 == 0) {	Key = 0x09;
									normalkey(Key);	
									}
		if(c1 == 0) { Key = 0x08;
									normalkey(Key);	
									}
		if(c0 == 0) { Key = 0x07;
									normalkey(Key);		
									}		
		r2 = 1;
	
	r3 = 0;
		     if(c3 == 0) {Key = 'D'; }
		else if(c2 == 0) {Key = '#'; }
		else if(c1 == 0) {Key = 0x00;
			               normalkey(Key);
											}
		else if(c0 == 0) {
											reset();
											}
		
		r3 = 1;
	
		debounce();
		
		if(Key == KEYPAD_NO_NEW_DATA)
		{
			Old_Key = KEYPAD_NO_NEW_DATA;
			Last_valid_Key_G = KEYPAD_NO_NEW_DATA;
			return 0;			
		}
		
		if(Key == Old_Key)
		{
			if(Key != Last_valid_Key_G)
			{
				pKey = Key;				
				Last_valid_Key_G = Key;
				return 1;
			}
		}
		Old_Key = Key	;			
		return 0;
}
void normalkey(char key)
{
	first= second;
	second = key;
	P2=(first << 4) | second;
}
void main() 
{

  bit result;
	
	P1 = 0x0F;
	P2 = 0x00;
	r0 = 1;
	r1 = 1;
	r2 = 1;
	r3 = 1;

	while(1)
	{
		result = KeyPad_Scan();				
	}
}
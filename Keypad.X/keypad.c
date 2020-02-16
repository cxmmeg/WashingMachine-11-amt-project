//Keypad routines

#include "keypad.h"

key get_key(char delicate);

unsigned char process_key(unsigned char code);
unsigned char scan_code[6]={0xE7,0xED,0x77,0x7B,0x7D,0xB7};

void keypad_init()
{
		TRISD = 0xF0;
}

unsigned char Read_Key()
{
	unsigned char code,Col,value;
	int i;
	value = 0xFF;
	Col = 0b11111110;
	for (i=0;i<4;i++)
	{
		LATD = Col;
		code = PORTD;//read PORTD
		code = code | 0b00001111;//mask to obtain RD7,6,5,4
		code = code & Col;//put back original RD3,2,1,0
		if (code!=Col) 
		{
			value = get_key(code);
			break;
            
		}
		Col = (Col << 1) | 0x01;
	}
	return(value); 
}

key get_key(char delicate)
{
		if (delicate==scan_code[0]) 
            return KEY_PRESET;
        if(delicate==scan_code[1])
            return KEY_START;
        if(delicate==scan_code[2])
            return KEY_1;
        if(delicate==scan_code[3])
            return KEY_2;
        if(delicate==scan_code[4])
            return KEY_3;
        if(delicate==scan_code[5])
            return KEY_4;
    
	return(KEY_NONE);
}



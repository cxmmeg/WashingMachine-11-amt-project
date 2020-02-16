#include <xc.h>
#include "amt.h"
#include <stdio.h>
#include <string.h>
#include "RS232.h"

void RS232_init(void){
    clr_screen();
    
    for(int x = 0; x < 2 ; x ++){
        for(int y = 0; y < 4 ; y ++){
            if(ports[x*4+y]==(char*)0x0000)
                continue;
            print_port(ports[x*4+y], x, y);
        }
    }
    
    ui_init();
}

void uart_send_str(char str[]){
    
    int i = 0;
    while(str[i]!='\0'){
        uart_send_char(str[i]); 
        i++;
    } 
     
}

void set_position(int col, int line){
    
    unsigned char command[] = {0x1B , '['};
	int t=0;
  	while(t<2)
	{
		uart_send_char(command[t]);
   		t++;
	}
    
    if(line < 10)
    {
        uart_send_char(line + '0');
    }
    else
    {
        uart_send_char(line/10 + '0');
        uart_send_char(line%10 + '0');
    }
    
    uart_send_char(';');
    
    if(col < 10)
    {
        uart_send_char(col + '0');
    }
    else
    {
        uart_send_char(col/10 + '0');
        uart_send_char(col%10 + '0');
    }
    
        uart_send_char('H');
    
}

void print_port(char* address, int col, int line){
    
     char value = *address;
     
    char label = '?';
    if(address == (char*)0xF80)
        label = 'A';
    if(address == (char*)0xF81)
        label = 'B';
    if(address == (char*)0xF82)
        label = 'C';
    if(address == (char*)0xF83)
        label = 'D';
    if(address == (char*)0xF84)
        label = 'E';
    if(address == (char*)0xF85)
        label = 'F';
    if(address == (char*)0xF86)
        label = 'G';
    if(address == (char*)0xF87)
        label = 'H';
    if(address == (char*)0xF88)
        label = 'J';

    char binary[8] = "";
    for(int i = 7; i >= 0; i --)
    {
        if(((0x80>>i) & value) == 0x00)
            binary[i] = '0';
        else
            binary[i] = '1';
    }
 
    char portTemplate[5][28] = {"-----------------------", "|  Port %c   TRIS:0x%02X |", "-----------------------", "MSB | | | | | | | | LSB","    %c %c %c %c %c %c %c %c\0"};
    sprintf(portTemplate[1], portTemplate[1], label, *(address+0x12));    
    sprintf(portTemplate[4], portTemplate[4], binary[0], binary[1], binary[2], binary[3], binary[4], binary[5], binary[6], binary[7]);
     
    for(int i = 0; i < 5 ; i ++)
    {
        set_position(col*25+3, line*6 + i + 2);
        uart_send_str(portTemplate[i]); 
    }
    
}

void RS232_update(void){
        
        char* ptr;
        char value, value_t;
        for(int x = 0; x < 2; x ++)
        {
            for(int y = 0; y < 4; y++)
            {
                if(ports[x*4+y]==(char*)0x0000)
                    continue;
                ptr = ports[x*4+y];
                value = *ptr;
                value_t = *(ptr+0x12);
                
                if(cache[x*4+y] != value)
                {
                    char pins[] = "    %c %c %c %c %c %c %c %c\0";
                    char binary[8] = "";

                    for(int i = 7; i >= 0; i --)
                    {
                    if(((0x80>>i) & value) == 0x00)
                    binary[i] = '0';
                    else
                    binary[i] = '1';
                    }

                    sprintf(pins, pins, binary[0], binary[1], binary[2], binary[3], binary[4], binary[5], binary[6], binary[7]);            

                    cache[x*4+y] = value;

                    set_position(x*25+3, y*6 + 4 + 2);
                    uart_send_str(pins);   
                }
                
                if(cache_t[x*4+y] != value_t)
                {
                    char tris[] = "%02X";

                    sprintf(tris, tris, value_t);    

                    cache_t[x*4+y] = value_t;

                    set_position(x*25+3+19, y*6 + 1 + 2);
                    uart_send_str(tris);   
                }
                
                
                
            }
        }
    
}

void uart_sendCmd(char cmd[]) {
    
    int count= strlen(cmd);
    uart_send_char(0x1B);
    for(int t = 0; t < count; t++) {
        uart_send_char(cmd[t]);
    }
}

void uart_send(unsigned char str[]) {
    unsigned char moveDown[] = "[1B";
    unsigned char moveLeft[] = "[23D";
    
    int count = strlen(str);
    int n = 1;
	for(int t = 0; t < count; t++) {
        if(t == 23 * n) {
            uart_sendCmd(moveDown);
            uart_sendCmd(moveLeft);
            n++;
        }
        uart_send_char(str[t]);
    }
}

void setLayout() {    
    unsigned char moveLine[] = "[0;55H";
    unsigned char moveLeft[] = "[1D";
    unsigned char moveDown[] = "[1B";
    unsigned char moveLog[] = "[1;67H";
    unsigned char titleLog[] = "LOG";
    unsigned char underline[] = "[4m";
    unsigned char offCharAttr[] = "[m";    
    
    uart_sendCmd(moveLine);
    // Print out a vertical line 
    for(int i = 0; i < 25; i++) {
        uart_send_char('|');
        uart_sendCmd(moveDown);
        uart_sendCmd(moveLeft);
    } 
        
    // Print out the LOG Title
    uart_sendCmd(moveLog);
    uart_sendCmd(underline);
    uart_send(titleLog);
    uart_sendCmd(offCharAttr);
}

void ui_init() {
    logStatus = 0;
    previousLog = 1;
    setLayout();
    setDarkMode();
}

void setDarkMode() {
    unsigned char dark[] = "[40;37m";
    uart_sendCmd(dark);
}

void clearLog() {
    unsigned char clear[] = "[0K";
    unsigned char cursorStart[] = "[2;57H";
    unsigned char cursorDown[] = "[1B";
    uart_sendCmd(cursorStart);
    for(int i = 0; i < 23; i++) {
        uart_sendCmd(clear);
        uart_sendCmd(cursorDown);
    }
}


void outputLog(char msg[]) {
    sending = 1;
    
    unsigned char log[255];
    unsigned char cursorNextLog[255];
    
    sprintf(log, "[%d]: %s", logStatus + 1, msg);
    int length = strlen(log);
    int row = (length / 23) + 1;
    if((previousLog + row + 1) > 23) {
        clearLog();
        set_position(57, 2);
        previousLog = 1;
    } else {
        sprintf(cursorNextLog, "[%d;57H", previousLog + 1);
        uart_sendCmd(cursorNextLog);
    }
    uart_send(log);
    previousLog += row;
    previousLog ++;
    logStatus++;
    
    sending = 0;
}

//unsigned char portA[] = "            ------------------------------\n            |            Port A            |\n            ------------------------------\n    MSB    |   |   |   |   |   |   |   |    LSB\n               1  0  1  0  1  1  0  0";
//unsigned char portA[] = "       ------------------------------\r\n       |           Port A           |\r\n       ------------------------------\r\n    MSB    |  |  |  |  |  |  |  |    LSB\r\n           1  0  1  0  1  1  0  0\r\n";
//    unsigned char portA[] = "-----------------------\r\n|        Port A       |\r\n----------------------\r\nMSB | | | | | | | | LSB\r\n    1 0 1 0 1 1 0 0\r\n";
//    sprintf(portA, "-----------------------\r\n|        Port A       |\r\n----------------------\r\nMSB | | | | | | | | LSB\r\n    %i %i %i %i %i %i %i %i\r\n", PORTBbits.RB7, PORTBbits.RB6, PORTBbits.RB5, PORTBbits.RB4, PORTBbits.RB3, PORTBbits.RB2, PORTBbits.RB1, PORTBbits.RB0);
//    char portTemplate[5][28] = {"-----------------------", "|        Port %c       |", "----------------------", "MSB | | | | | | | | LSB","    %c %c %c %c %c %c %c %c\0"};
//    sprintf(portTemplate[1], portTemplate[1], label);    
//    sprintf(port, "-----------------------\r\n|        Port %c       |\r\n----------------------\r\nMSB | | | | | | | | LSB\r\n    %c %c %c %c %c %c %c %c\r\n", label, binary[0], binary[1], binary[2], binary[3], binary[4], binary[5], binary[6], binary[7]);

//    if(&PORTB == (char*)0xF81)
//            uart_send_char('Y');
//    else
//            uart_send_char('N');
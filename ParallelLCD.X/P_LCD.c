#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 25000000

//FUNCTIONS FOR INTERNAL USE WITHIN THIS HEADER OR FOR DEBUGGING

//delay by x*1 ms (millisecond)
void Pause_ms(int x);

//delay by x*40 us (microsecond)
void Pause_us(int x);

//Sends byte to Parallel LCD
//msg_or_cmd = 0 is send command, = 1 is send message
//fast_or_slow = 0 is set slow, = 1 is set fast
//if set to command mode, it will automatically toggle fast mode
void P_LCD_send_byte(char c, int msg_or_cmd, int fast_or_slow);

//FUNCTIONS TO BE USED IN MAIN FILE

//Initialize parallel LCD
void P_LCD_init(void);

//Sets cursor to either turn on or off
//on_or_off 0 = off, 1 = on
void P_LCD_set_cursor(int on_or_off);

//Sets cursor to either top or bottom line
//top_or_bottom 1 = top line, 2 = bottom line
void P_LCD_cursor(int top_or_bottom);

//Sends a message smaller than 15 chars to the Parallel LCD
//top_or_bottom 1 = top line, 2 = bottom line
void P_LCD_send(char c[], int top_or_bottom);

//Sends a message that is <= 32 chars to the Parallel LCD
void P_LCD_send_all(char c[]);

//Clears the screen
//row = 0 clear both row, = 1 clear top row, = 2 clear bottom row
void P_LCD_CLR(int row);

//Scrolls a message vertically downwards
void P_LCD_scroll_vertical(char c[]);

//Scrolls a message horizontally sideways
//top_or_bottom 1 = top line, 2 = bottom line
void P_LCD_scroll_horizontal(char c[], int top_or_bottom);

//Flashes a message that is <= 16 chaars
//top_or_bottom 1 = top line, 2 = bottom line
void P_LCD_flash(char c[], int time, int top_or_bottom);

#define LCDEN LATHbits.LATH0
#define LCDRS LATHbits.LATH2

#pragma config XINST = OFF
#pragma config FOSC = HS
#pragma config WDT = OFF


//Pause for 1 millisecond
void Pause_ms(int x) 
{
    for (int i = 0; i < x; i++) 
	{
        __delay_ms(1);
    }
}

//Pause for 1 microsecond
void Pause_us(int x) 
{
    for (int i = 0; i < x; i++) 
	{
        //Minimum execution time for one command is 37 microseconds
        //Hence 40 microsecond delay will allow the command to execute
        //with enough time
        __delay_us(40);
    }
}

//Initialize the Parallel LCD
void P_LCD_init(void)
{
    TRISE = 0x00;
	TRISH = 0b11111000;
	LATHbits.LATH1 = 0;
	LCDEN = 0;
	LCDRS = 0;
	Pause_ms(1);

	P_LCD_send_byte(0x30 , 0 , 1);
	P_LCD_send_byte(0x30 , 0 , 1);
	P_LCD_send_byte(0x30 , 0 , 1);
	P_LCD_send_byte(0x38 , 0 , 1);
	P_LCD_send_byte(0x10 , 0 , 1);
	P_LCD_send_byte(0x0F , 0 , 1);
	P_LCD_send_byte(0x06 , 0 , 1);
	P_LCD_send_byte(0x01 , 0 , 1);
	Pause_ms(10);
	P_LCD_send_byte(0x8A , 0 , 1);

}

//Send a single char to wherever the cursor is
//set msg_or_cmd to 0 to send command, 1 to send message
//set fast_or_slow to 0 for slow, 1 to fast
//if it is set to send command, the speed will be set as fast no matter 
//the fast_or_slow parameter
void P_LCD_send_byte(char c, int msg_or_cmd, int fast_or_slow)
{
    int speed;
    
    //Set speed to slow
    if (fast_or_slow == 0)
    {
        //set the sending of char speed to slow
        speed = 750;
    }
    //Set speed to fast
    if (fast_or_slow == 1)
    {
        //set the sending of char speed to fast
        speed = 1;
    }
    //Set to command mode with speed as fast
    if (msg_or_cmd == 0)
    {
        //set to send command byte
        LCDRS = 0;
        //set speed to be fast if its command byte to send commands fast
        //which ignores if fast_or_slow is set to slow(0)
        speed = 1;
    }
    //Set to message mode with varying speed from above
    if (msg_or_cmd == 1)
    {
        //set to send message byte
        LCDRS = 1;
    }
    
    //Sending the byte 
    Pause_us(1*speed);

	LATE = c;
	LCDEN = 1;
	Pause_us(1*speed);
	LCDEN = 0;
	Pause_us(1*speed); 
    
}

//Toggle cursor on or off, 1 is on, 0 is off
void P_LCD_set_cursor(int on_or_off)
{
    //Toggle cursor on
    if (on_or_off == 1)
    {
        //cursor turns on and blinks
        P_LCD_send_byte( 0x0F , 0 , 1 );
    }
    //Toggle cursor off
    if (on_or_off == 0)
    {
        //cursor turns off, no blinking
        P_LCD_send_byte( 0x0C, 0 , 1 );
    }
}

//Toggle cursor to be on top or bottom row, 1 is top, 2 is bottom
void P_LCD_cursor(int top_or_bottom)
{
    char error[] = "_cursor:!=(1||2)";
    //Set cursor to the top
    if (top_or_bottom == 1) 
    {
        //Send command byte quickly to set cursor to the top
        P_LCD_send_byte( 0x80 , 0 , 1 );
    }
    //Set cursor to the bottom
    else if (top_or_bottom == 2) 
    {
        //Send command byte quickly to set cursor to the bottom
        P_LCD_send_byte( 0xC0 , 0 , 1 );
    }
    else
    {
        /*//Prints out error string on the P_LCD
        for (int i = 0; error[i]!=NULL; i++)
        {
            P_LCD_send_byte( 0x80 , 0 , 1 );
            P_LCD_send_msg(error[i]);
            Pause_ms(1);
            P_LCD_send_cmd(0x81+i);
        }*/
    }
}

//Sends char array
//if top_or_bottom = 1 is top row, = 2 is bottom
void P_LCD_send(char c[], int top_or_bottom)
{
    Pause_ms(100);
    //Toggle to top row
    if (top_or_bottom == 1)
    {
        //Set cursor on top line
        P_LCD_cursor(1);
    }
    //Toggle to bottom row
    if (top_or_bottom == 2)
    {
        //Set cursor on bottom line
        P_LCD_cursor(2);
    }
    
    //Sends a character, moves DDRAM one space forward, 
    //and repeat until the entire message is printed
    for (int i = 0; c[i]!=NULL; i++)
        {
            //send a message byte slowly
            P_LCD_send_byte(c[i], 1 , 0);
            Pause_ms(1);
            if (top_or_bottom == 1) P_LCD_send_byte((0x81+i), 0 , 1);
            if (top_or_bottom == 2) P_LCD_send_byte((0xC1+i), 0 , 1);
        }
    //Pause so user can read the message
    Pause_ms(1000);
    
}


//Send entire message to the top and bottom line then stops.
void P_LCD_send_all(char c[])
{ 
    Pause_ms(100);
    int i = 0;
    int j = 0;
    int counter = 0;
    
    //Count number of characters in the array
    for (i = 0; c[i] != NULL; i++) {
        counter ++;
    }
    
    //Print array on the top line if there are less than 16 characters
    if (counter <= 15)
    {
        if (counter <= 15)
        {
            for (i=0; c[i]!= NULL; i++) 
            {
                P_LCD_send_byte(c[i] , 1 , 0);
            }
        }
    }
    
    //Print array on the top line and bottom line 
    //if there are more than 16 characters but less than 32 characters
    if (counter >= 16 && counter <= 32) {
        for (i=0;i<=15;i++){
            //send a message byte slowly
            P_LCD_send_byte( c[i], 1 , 0 );
        }
        P_LCD_cursor(2);
        for (i=16;c[i]!=NULL;i++){
            //send a message byte slowly
            P_LCD_send_byte( c[i], 1 , 0 );
        }
    }
    
    //Print array on the top line and bottom line 
    //Stops at 32 characters, regardless of length
    if (counter > 32){
        for (i=0;i<=15;i++){
            //send a message byte slowly
            P_LCD_send_byte( c[i], 1 , 0 );
        }
        P_LCD_cursor(2);
        for (i=16; i < 32;i++){
            //send a message byte slowly
            P_LCD_send_byte( c[i], 1 , 0 );
        }
    }
    //Pause so user can read the message
    Pause_ms(1000);
}

// 0 for clear both rows, 1 for top row, 2 for bottom row
void P_LCD_CLR(int row)
{
    if(row == 0)
    {
        //Clears both rows
        //Sets cursor to top row
        //send command byte to clear everything
        P_LCD_send_byte(0x01 , 0 , 1);
    }
    
    else if (row == 1)
    {
        //Clears top row
        P_LCD_cursor(1);
        for (int i=0 ; i <= 15 ; i++)
        {
            //send a message byte for " " space
            P_LCD_send_byte(0x20 , 1 , 1);
        }
        //Sets cursor to top row
        P_LCD_cursor(1);
    }
    else if (row == 2)
    {
        //Clears bottom row
        P_LCD_cursor(2);
        for (int i=0 ; i <= 15 ; i++)
        {
            //send a message byte for " " space
            P_LCD_send_byte(0x20 , 1 , 1);
        }
        //Sets cursor to bottom row
        P_LCD_cursor(2);
    }
}

//Scrolls the message downwards if it exceeds the screen space
void P_LCD_scroll_vertical(char c[])
{
    Pause_ms(100);
    int i = 0;
    int j = 0;
    int m = 0;
    int print_line = 0;
    int extra_line = 0;
    int counter = 0;
    
    //Count number of characters in the array
    for (i = 0; c[i] != NULL; i++) {
        counter ++;
    }
    
    //Print array on the top line if there are less than 16 characters
    if (counter <= 15){
        for (i=0; c[i]!= NULL; i++) {
            //sends a message byte quickly
            P_LCD_send_byte(c[i], 1 , 1);
        }
    }
    
    //Print array on the top line and bottom line 
    //if there are more than 16 characters but less than 32 characters
    if (counter >= 16 && counter <= 32) {
        P_LCD_cursor(1);
        for (i=0;i<=15;i++){
             //sends a message byte quickly
            P_LCD_send_byte(c[i], 1 , 1);
        }
        P_LCD_cursor(2);
        for (i=16;c[i]!=NULL;i++){
             //sends a message byte quickly
            P_LCD_send_byte(c[i], 1 , 1);
        }
    }
    
    //If more than 32 characters, prints 16 top and 16 bottom
    //Scrolls for one line, bottom line becomes top and a new line of characters at the bottom
    if (counter > 32){
        print_line = counter / 16;
        extra_line = counter % 16;
        
        for (j=0; j < print_line; j++) {
            //Prints 16 characters to top line
            //Sets cursor to the top row
            P_LCD_cursor(1);
            //Turns off cursor
            P_LCD_set_cursor(0);
            
            for (i = j*16; (i<(j*16+16) && c[i]!=NULL) == 1 ; i++) 
            {
                //sends a message byte quickly
                P_LCD_send_byte(c[i], 1 , 1);
            }
            
            //Prints 16 characters to bottom line
            P_LCD_cursor(2);
            //Turns off cursor
            P_LCD_set_cursor(0);
            
            for (m =(j*16+16); (m<(j*16+32) && c[m]!=NULL) == 1 ; m++) 
            {
                //sends a message byte quickly
                P_LCD_send_byte(c[m], 1 , 1);
            }
            
            Pause_ms(1000);
            //Clears both lines
            P_LCD_CLR(0);
            //Turns off cursor
            P_LCD_set_cursor(0);
            Pause_us(50);
        }
        
        //checks for excess characters by variable % 16
        if (extra_line > 0){
            //Sets cursor to the top row
            P_LCD_cursor(1);
            //Turns off cursor
            P_LCD_set_cursor(0);
            //prints characters till the end of the char array
            for (i=(print_line*16); c[i]!=NULL; i++) {
                //sends a message byte quickly
                P_LCD_send_byte(c[i], 1 , 1);
            }
            Pause_ms(1000);
        }
    }
    //Pause so user can read the message
    Pause_ms(1000);
}

//Prints the entire message on the top line and scrolls the message to the left if it exceeds the top line
//top_or_bottom = 1 for top row, = 2 for bottom row
void P_LCD_scroll_horizontal(char c[], int top_or_bottom)
{
    Pause_ms(100);
    int i = 0;
    int j = 0;
    int count = 0;
    
    if (top_or_bottom == 1)
    {
        //Set cursor to the top
        P_LCD_cursor(1); 
    }
    
    if (top_or_bottom == 2)
    {
        //Set cursor to the bottom
        P_LCD_cursor(2); 
    }
    
    //Counts how many chars are in the message
    for (i = 0; c[i]!=NULL; i++)
    {
        count++;
    }
    
    //If the message is less than 16 chars (size of 1 row)
    if (count <= 16)
    {
        //Send the entire message
        for (i = 0; c[i]!= NULL; i++) 
        {
            //sends a message byte quickly
            P_LCD_send_byte(c[i], 1 , 1);
        }
        Pause_ms(1000);
    }
    //If the message exceeds 16 chars (size of 1 row)
    if (count > 16)
    {
        //Send batches of 16 chars very quickly to look like scrolling
        for (i = 0; i < (count-15); i++)
        {
            if (top_or_bottom == 1)
            {
                //Set cursor to the top
                P_LCD_cursor(1); 
            }

            if (top_or_bottom == 2)
            {
                //Set cursor to the bottom
                P_LCD_cursor(2); 
            }
            
            //Send 16 chars very quickly
            for (j = i; j < (i+16); j++)
            {
                //sends a message byte quickly
                P_LCD_send_byte(c[j], 1 , 1);           
            }
            //Comfortable scrolling speed
            Pause_ms(150);
        }
    }
    //Pause so user can read the message
    Pause_ms(1000);
}

//Flashes message <= 16 char for time * 1 second
void P_LCD_flash(char c[], int time, int top_or_bottom)
{
    Pause_ms(100);
    int i = 0;
    int j = 0;
    int count = 0;
    //counts the length of the message c[]
    for (i = 0; c[i]!=NULL; i++)
    {
        count++;
    }
    
    //if the length of the message is less than 16
    if (count <= 16)
    {
        for (j = 0; j < (10*time) ; j++)
        {   
            Pause_ms(50);
           
             if (top_or_bottom == 1)
            {
                //Set cursor to the top
                P_LCD_CLR(1); 
            }

            if (top_or_bottom == 2)
            {
                //Set cursor to the bottom
                P_LCD_CLR(2); 
            }
            
            Pause_ms(25);
            //turn off cursor for convincing flashing
            P_LCD_set_cursor(0);
            Pause_ms(25);
            //Send the entire message
            for (i = 0; c[i]!= NULL; i++) 
            {
                //sends a message byte quickly
                P_LCD_send_byte(c[i] , 1 , 1);
            }
            
        }
    }
    if (count > 16)
    {
        //This will print out nothing if the message exceeds 16 chars
    }
    //Pause so user can read the message
    Pause_ms(1000);
}




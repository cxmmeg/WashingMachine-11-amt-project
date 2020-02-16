#ifndef _P_LCD_HEADER_FILE
#define _P_LCD_HEADER_FILE

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

//Flashes a message that is <= 16 chars
//top_or_bottom 1 = top line, 2 = bottom line
void P_LCD_flash(char c[], int time, int top_or_bottom);


#endif
#ifndef _AMT_HEADER_FILE
#define _AMT_HEADER_FILE
//Parallel LCD
void Pause_ms(int x);
void Pause_us(int x);
void P_LCD_send_byte(char c, int msg_or_cmd, int fast_or_slow);
void P_LCD_init(void);
void P_LCD_set_cursor(int on_or_off);
void P_LCD_cursor(int top_or_bottom);
void P_LCD_send(char c[], int top_or_bottom);
void P_LCD_send_all(char c[]);
void P_LCD_CLR(int row);
void P_LCD_scroll_vertical(char c[]);
void P_LCD_scroll_horizontal(char c[], int top_or_bottom);
void P_LCD_flash(char c[], int time, int top_or_bottom);

#endif

#ifndef _AMT_HEADER_FILE
#define _AMT_HEADER_FILE
//RS232
char* ports[8] = {&PORTB, &PORTB, &PORTD, &PORTD, &TRISB, &PORTF, &RCREG1, &PORTJ};
char cache[8] = {};
char cache_t[8] = {};
int logStatus;
int previousLog;
int sending;

void uart_init(void);
void uart_send_char (unsigned char ucChar);
void clr_screen(void);
void cursor_home(void);

void uart_send_str(char str[]);
void set_position(int col, int line);
void print_port(char* address, int col, int line);
void RS232_update(void);
void RS232_init(void);
void uart_sendCmd(char cmd[]);
void ui_init(void);
void setDarkMode(void);
void uart_send(char str[]);
void setLayout(void);
void clearLog(void);
void outputLog(char log[]);

#endif
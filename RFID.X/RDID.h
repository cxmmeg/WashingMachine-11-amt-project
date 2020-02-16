#ifndef _AMT_HEADER_FILE
#define _AMT_HEADER_FILE

//void uart_init(void); // From UART library
const char * read_rfid(void); // From RFID.c
int verify_rfid(char id[]); // From RFID.c
void add_rfid(char id[]); // From RFID.c

//void uart_send_char (unsigned char ucChar);

void delete_rfid();
int guest_rfid(char id[]);

void SPI1init(void);
void SPI1out(char Code);
char SPI1in(void);

char read_byte_eeprom(unsigned char highAdd, unsigned char lowAdd);
void write_enable(void);
char write_byte_eeprom(unsigned char highAdd, unsigned char lowAdd, unsigned char data);
unsigned char list_presets(void);
void get_preset(char *buf, char preset_num);
void set_preset(char *data, char preset_num);
void reset_presets(void);

void uart_send_char (unsigned char ucChar);

void delay_ms(int x);
void test_add(char id[]);
void test_verify(void);

#endif
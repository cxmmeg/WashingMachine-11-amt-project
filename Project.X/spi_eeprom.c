#include <xc.h>
#include "eeprom.h"
#define CS LATDbits.LATD7

void SPI1init(void);
void SPI1out(char Code);
char SPI1in(void);

char read_byte_eeprom(unsigned char highAdd, unsigned char lowAdd);
void write_enable(void);
void write_byte_eeprom(unsigned char highAdd, unsigned char lowAdd, unsigned char data);
void get_preset(char *buf, char preset_num);
void set_preset(char *data, char preset_num);
void reset_presets(void);

// We will allow up to 6 presets
// 0000 - 0005 (Address)
// 0000: 0x0010
// 0003 - User preset 1
// 0004 - User preset 2
// 0005 - User preset 3

// Settings: Water level, Time, Temperature
// Water level (in litres) : 1 byte
// Time (minutes) : 1 byte
// Temperature (Celcius) : 1 byte

// Get the values for a given preset number
// Preset number range: 0-6
// Buffer with minimum length of 3
void get_preset(char *buf, char preset_num) {
    unsigned char preset_add = read_byte_eeprom(0x00, preset_num);
    unsigned char i = 0;
    while(i < 3) {
        buf[i] = read_byte_eeprom(0x00, preset_add + i);
        i++;
    }
}

// Set the values for a given preset number
// Preset number range: 0-6
// Buffer with minimum length of 3
// Buffer: {Water level, Time, Temperature}
void set_preset(char *buf, char preset_num) {
    unsigned char preset_add = read_byte_eeprom(0x00, preset_num);
    for(unsigned char i = 0; i < 3; i++) {
        write_byte_eeprom(0, preset_add + i, buf[i]);
    }
}

// Set the default presets
// Clear the user set presets
void reset_presets(void) {
    // Set the addresses for presets
    for(unsigned char i = 0; i < 6; i++) {
        write_byte_eeprom(0, i, (i + 1) * 10);
    }
    // Set default presets
    // Settings for load size
    unsigned char setting_small[] = {20, 30, 25};
    unsigned char setting_medium[] = {35, 45, 25};
    unsigned char setting_large[] = {40, 60, 25};
    
    set_preset(setting_small, 0);
    set_preset(setting_medium, 1);
    set_preset(setting_large, 2);
    
    // Clear away user presets
    for(unsigned char i = 3; i < 6; i++) {
        unsigned char preset_add = read_byte_eeprom(0x00, i);
        write_byte_eeprom(0, preset_add, 0);
        write_byte_eeprom(0, preset_add + 1, 0);
        write_byte_eeprom(0, preset_add + 2, 0);
    }
}

char read_byte_eeprom(unsigned char highAdd, unsigned char lowAdd) {    
    CS = 0;
    SPI1out(0x03); // Read instruction
    SPI1out(highAdd);
    SPI1out(lowAdd);
    char data = SPI1in();
    CS = 1;
    return data;
}

void write_byte_eeprom(unsigned char highAdd, unsigned char lowAdd, unsigned char data) {
    write_enable();
    CS = 0;
    SPI1out(0x02); // Write instruction
    SPI1out(highAdd);
    SPI1out(lowAdd);
    SPI1out(data);
    CS = 1;
    // Pool to check if write done
    char status;
    do{
        CS = 0;
        SPI1out(0x05);
        status = SPI1in();
        CS = 1;
    } while(status & 0x01);
}

void write_enable() {
    CS = 0;
    SPI1out(0x06); // WREN
    CS = 1;
}

// From School's SPI library
void SPI1init(void)
{
	SSP1CON1 = 0b00100010;	// Enable SPI, CKP=0, Master, Fosc/64
	SSP1STATbits.CKE = 1;	// CKE=1, (rising edge for shift register)
	TRISCbits.TRISC3 = 0;	// RC3 is SCk
	TRISCbits.TRISC5 = 0;	// RC5 is SDO
	SPI1out(0x00);
}

void SPI1out(char Code)
{
	SSP1BUF = Code;			// Transmit
	while(SSP1STATbits.BF==0);	// Wait for END (Receipt Buffer Full)
	Code = SSP1BUF;			// Just read to clear BF
}

char SPI1in(void)
{
    char temp = SSP1BUF; // Clear BF
    SSP1BUF = 0;
    while(SSP1STATbits.BF == 0);
    return SSP1BUF;
}


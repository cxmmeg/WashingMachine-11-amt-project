#include <p18f97j60.h>
void SPI1DACinit(void);
void sendDAC(char first,char second);
void DACwave(void);
void DAClvl0(void);
void DAClvl1(void);
void DAClvl2(void);
void DAClvl3(void);
void DAClvl4(void);
void DACblink(int times);

void SPI1DACinit(void){

//Prepare SPI Pins
TRISCbits.TRISC3 = 0; // SCK (output)
TRISCbits.TRISC5 = 0; // SD0 (output)
TRISCbits.TRISC7 = 0; // CS  (output)

//Initialize SPI
OSCTUNE = 0x40;
OSCCON =  0x70; //8MHz (INTOSC drives clock directly)
SSPCON1 = 0x20; //Serial ports enabled idle state is clock low
SSPSTAT = 0x40; //Transmit occurs from active to idle clock transition

}

void sendDAC(char first,char second){

    //SPI Transfer
    PORTCbits.RC7 = 0; //Make CS (chip select) low
    PIR1bits.SSPIF = 0; // Make Transmission flag low
    SSP1BUF = first; //Send table data
    while(PIR1bits.SSPIF == 0); // Wait until transmission is complete
    PORTCbits.RC7 = 1;
    PIR1bits.SSPIF = 0;
    PORTCbits.RC7 = 0;
    SSP1BUF = second;
    while(PIR1bits.SSPIF == 0);
    PORTCbits.RC7 = 1; //Make CS high, transfer done
    delay_ms(1000);
}

void DACwave(void) {
    sendDAC(0x90,0x00);
    sendDAC(0x93,0x30);
    sendDAC(0x96,0x60);
    sendDAC(0x9F,0xF0);
    sendDAC(0x9F,0xFF);
    sendDAC(0x9F,0xF0);
    sendDAC(0x96,0x60);
    sendDAC(0x93,0x30);
    sendDAC(0x90,0x00);
}

void DAClvl0(void) {
    sendDAC(0x90,0x00);
}

void DAClvl1(void) {
    sendDAC(0x93,0x30);
}

void DAClvl2(void) {
    sendDAC(0x96,0x60);
}

void DAClvl3(void) {
    sendDAC(0x9F,0xF0);
}

void DAClvl4(void) {
    sendDAC(0x9F,0xFF);
}

void DACblink(int times) {
    for(int i = 0; i <= times; i++) {
        sendDAC(0x90,0x00); 
        sendDAC(0x9F,0xFF);
        sendDAC(0x90,0x00); 
    }
}


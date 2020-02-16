#include "amt.h"
#include <p18f97j60.h>
#pragma config XINST = OFF
#pragma config WDT = OFF
#pragma config FOSC = HS

int main(void) {
    SPI1DACinit();
    //PORTCbits.RC7 = 0; 
    testDAC(0x90,0x00);
    //delay_ms(1000);
    testDAC(0x93,0x30);
    //delay_ms(1000);
    testDAC(0x96,0x60);
    //delay_ms(1000);
    testDAC(0x9F,0xF0);
    //delay_ms(1000);
    testDAC(0x9F,0xFF);
    //testDAC(31,100);
    //delay_ms(10);
    //PORTCbits.RC7 = 1; 
}
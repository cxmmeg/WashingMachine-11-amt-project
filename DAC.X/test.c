#include "amt.h"
#include <p18f97j60.h>
#pragma config XINST = OFF
#pragma config WDT = OFF
#pragma config FOSC = HS

int main(void) {
    SPI1DACinit();
    testDAC(0x90,0x00);
    testDAC(0x93,0x30);
    testDAC(0x96,0x60);
    testDAC(0x9F,0xF0);
    testDAC(0x9F,0xFF);
}
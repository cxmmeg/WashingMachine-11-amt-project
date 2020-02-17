#include <xc.h>
#include "rfid.h"
#include "mh.h"
#pragma config XINST = OFF
#pragma config FOSC = HS
#pragma config WDT = OFF

void main(void) {
    SPI1init();
    int verify = 0;
    while(verify == 0) {
        char * id = read_rfid();
        if(verify_rfid(id) == 0) {
            add_rfid(id);
            verify = 0;
        } else if (verify_rfid(id) == 1) {
            verify = 1;
        }
    }
    
    
    return;
}

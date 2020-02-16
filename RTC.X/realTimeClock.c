#include <xc.h>
#include "amt.h"
#include <stdio.h>

#pragma config XINST = OFF
#pragma config FOSC = HS
#pragma config WDT = OFF
int counter;
int sec;
int countdown = 1;
int counter2;


void interrupt HighIsr(void) // High priority interrupt
{
    counter++;
    counter2++;
    if (counter2 == 1000*60) {

        counter2 = 0;
        countdown--;
    }
    if (counter == 1000) {
   
        counter = 0;
        //keypadValue--;

    }

    if (countdown<0) {
        PIR1bits.TMR2IF = 1; //CLR TMR2IF

    } else {
        PIR1bits.TMR2IF = 0; //CLR TMR2IF
    }

}

void interrupt low_priority LowIsr(void) //Low priority interrupt
{

}

void rtcinit(void) {
 

    T2CON = 0b01111111; // Pre=16 Post=16 Turn on timer2
    PIR1bits.TMR2IF = 0; //CLR TMR2IF
    PR2 = 23; //count 1ms
    TRISJ = 0;
    counter = 0;
    counter2 = 0;
    T2intr();
        
    }

    /*
     void counter1(int keypad){
        keypadValue = keypad;
    }
     */

}
void setcountdownvalue(int value){
    countdown = value;
    
}


int getcountdown(void){
    return countdown;
}
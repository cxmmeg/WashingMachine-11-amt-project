//PIC18F97J60 Configuration Bit Settings
//Class: DCPE/FT/2A/21
//Module: Advanced Microcontroller Technology (ET0720)
//Wilfred Wong (P1719617) 
//Scott Sia (P1718418)
//C code for buzzer

#include <xc.h>
#include "amt.h"      
#include "buzzer.h"
#include <stdio.h>
#include <string.h>

#pragma config XINST = OFF      
#pragma config FOSC = HS
#pragma config WDT = OFF  


#define ToggleBit 3
#define BuzzerPort PORTC

#define _XTAL_FREQ 20000000L

//notes creation
#define DO1 262 
#define RA 294
#define MI 330
#define FA 349
#define SO 392
#define LA 440
#define TI 494
#define DO2 523

void Buzzer_init();
void Play_Sound(unsigned int freq, unsigned char duration);
void Selectsong(int song);

void Buzzer_init(){
    TRISC = 0x00; // set port C bit 3 to output
}

void Play_Sound(unsigned int freq, unsigned char duration)
{
    // freq is tone frequency in Hz
    // duration is tone dwell in 0.1 seconds
    unsigned int T1Set;
    // the dwell time in half period counts is the number of seconds times twice
    // the freq in cycles per second
    // the maximum dwell count is the 2 * maximum frequency * maximum duration
    // that's 2 * 20000 * 25 = 1000000 counts
    unsigned short dwell;
    unsigned char OutputByte, ToggleByte;
    
    ToggleByte = (1<<ToggleBit);
    // start with output low
    OutputByte = BuzzerPort & ~ToggleByte;
    BuzzerPort = OutputByte;
    // 1/freq is the period of the tone
    // each tone period consists of a high period and low period
    // Therefore, T1Set must be half the tone period
    T1Set = 65535L - (_XTAL_FREQ / (2L * 4L * freq));
    TMR1H = T1Set >> 8;
    TMR1L = T1Set & 0xFF;
    TMR1IF = 0;
    TMR1ON = 1;
    dwell = ((unsigned long)freq * 2L * (unsigned long)duration)/10L;
    for (;dwell>0;dwell--)
    {
        while (TMR1IF == 0);
        OutputByte = BuzzerPort ^ ToggleByte;
        BuzzerPort = OutputByte;
        TMR1IF = 0;
        TMR1H = T1Set >> 8;
        TMR1L = T1Set & 0xFF; 
    }
}

void Selectsong(int song){
    switch(song){
            case 1:   // turn on washing machine
            Play_Sound(DO1,5);
            Play_Sound(DO1,5);
            Play_Sound(SO,5);
            Play_Sound(SO,5);
            Play_Sound(LA,5);
            Play_Sound(LA,5);
            Play_Sound(SO,5);
            Play_Sound(FA,5);
            Play_Sound(FA,5);
            Play_Sound(MI,5);
            Play_Sound(MI,5);
            Play_Sound(RA,5);
            Play_Sound(RA,5);
            Play_Sound(DO1,5);
            break;
            
            case 2:   // start washing machine task
            Play_Sound(DO1,5);
            Play_Sound(RA,5);
            Play_Sound(MI,5);
            Play_Sound(FA,5);
            Play_Sound(SO,5);
            Play_Sound(LA,5);
            Play_Sound(TI,5);
            Play_Sound(DO2,5);
            Play_Sound(RA,5);
            break;
            
            case 3:   // when washing machine finishes its tasks
            Play_Sound(TI,5);
            Play_Sound(LA,10);
            Play_Sound(SO,10);
            Play_Sound(LA,10);
            Play_Sound(TI,5);
            Play_Sound(TI,5);
            Play_Sound(TI,5);
            Play_Sound(LA,10);
            Play_Sound(LA,10);
            Play_Sound(LA,10);
            Play_Sound(TI,5);
            Play_Sound(TI,5);
            Play_Sound(TI,5);
            Play_Sound(LA,10);
            Play_Sound(SO,10);
            Play_Sound(LA,10);
            break;
           
            default:   // included if the user keys in wrong value
            Play_Sound(MI,10);
            Play_Sound(MI,10);
            Play_Sound(MI,10);
            Play_Sound(MI,10);
            Play_Sound(MI,10);
            Play_Sound(MI,10);
            Play_Sound(MI,10);
            Play_Sound(SO,10);
            Play_Sound(DO1,10);
            Play_Sound(RA,10);
            Play_Sound(MI,10);
            Play_Sound(FA,10);
            Play_Sound(FA,10);
            Play_Sound(FA,10);
            Play_Sound(FA,10);
            Play_Sound(FA,10);
            Play_Sound(MI,10);
            Play_Sound(MI,10);
            Play_Sound(MI,10);
            break;
    }
}
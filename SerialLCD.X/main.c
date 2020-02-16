/*
 * File:   main.c
 * Author: Yi Wei
 *
 * Created on February 10, 2020, 2:24 PM
 */

#include <xc.h>
#include <stdio.h>
#include "amt.h"
#include <string.h>
#include <stdbool.h>
#pragma config XINST = OFF
#pragma config FOSC = HS
#pragma config WDT = OFF

void displayRTCAndTemp(int secs, float temp, bool animation);
void displayRTC(int secs, bool animation);
void displayTemp(float temp, bool animation);

void main(void) {
    displayRTCAndTemp(617, 35.5, true);
}

void displayRTCAndTemp(int secs, float temp, bool animation) {
    TRISC = 0x00;
    TRISD = 0x00;
    SPI1init();
    SPI_LCD4init();

    int rtcCursor = 0x80;
    int tempCursor = 0xC0;
    char rtcMsg[17] = {0};
    char tempMsg[17] = {0};
    char rtcLast, tempLast;
    short rtcIndex = 15, tempIndex = 15;

    for (int i = 0; i < 16; i++) {
        rtcMsg[i] = ' ';
        tempMsg[i] = ' ';
    }

    int multiple, min, hour;
    char hourStr[3], minStr[3], secsStr[3];

    multiple = min = hour = 0;

    if (secs > 59) {
        multiple = secs / 60;
        secs = secs - multiple * 60;
        min = multiple;
    }

    if (min > 59) {
        multiple = min / 60;
        min = min - multiple * 60;
        hour = multiple;
    }

    if (hour > 9)
        sprintf(hourStr, "%d", hour);
    else
        sprintf(hourStr, "0%d", hour);
    
    if (min > 9)
        sprintf(minStr, "%d", min);
    else
        sprintf(minStr, "0%d", min);
    
    if (secs > 9)
        sprintf(secsStr, "%d", secs);
    else
        sprintf(secsStr, "0%d", secs);
    
    sprintf(rtcMsg, "Time: %s:%s:%s", hourStr, minStr, secsStr);
    sprintf(tempMsg, "Temp: %.1fC", temp);

    bool initial = true;
    
    while (1) {
        rtcCursor = 0x80;
        tempCursor = 0xC0;
        
        SPI_LCD4send(0x01, 0);

        for (int n = 0; n < 16; n++) {
            if (rtcMsg[n]) {
                SPI_LCD4send(rtcCursor, 0);
                SPI_LCD4send(rtcMsg[n], 1);
            } else if (!rtcMsg[n] && initial) {
                rtcCursor--;
                SPI_LCD4send(0, 1);
                initial = false;
            }
            
            if (tempMsg[n]) {
                SPI_LCD4send(tempCursor, 0);
                SPI_LCD4send(tempMsg[n], 1);
            }

            rtcCursor++;
            tempCursor++;
        }
        
        if (!animation) while (1);
        
        if (rtcMsg[0] == 'T' && tempMsg[0] == 'T') {
            delay_ms(3000);
            SPI_LCD4send(0x01, 0);
            delay_ms(10);

            // flash animation odd
            rtcCursor = 0x80;
            tempCursor = 0xC0;
            for (int i = 0; i < 16; i+=2) {
                if (rtcMsg[i]) {
                    SPI_LCD4send(rtcCursor, 0);
                    SPI_LCD4send(rtcMsg[i], 1);
                }
                
                if (tempMsg[i]) {
                    SPI_LCD4send(tempCursor, 0);
                    SPI_LCD4send(tempMsg[i], 1);
                }
                
                rtcCursor += 2;
                tempCursor += 2;
                delay_ms(50);
            }

            delay_ms(100);
            
            // flash animation even
            rtcCursor = 0x81;
            tempCursor = 0xC1;
            for (int i = 1; i < 16; i += 2) {
                if (rtcMsg[i]) {
                    SPI_LCD4send(rtcCursor, 0);
                    SPI_LCD4send(rtcMsg[i], 1);
                }
                
                if (tempMsg[i]) {
                    SPI_LCD4send(tempCursor, 0);
                    SPI_LCD4send(tempMsg[i], 1);
                }
                
                rtcCursor += 2;
                tempCursor += 2;
                delay_ms(50);
            }
            
            delay_ms(1000);
        }

        rtcLast = rtcMsg[15];
        tempLast = tempMsg[15];
        rtcMsg[15] = ' ';
        tempMsg[15] = ' ';
        rtcIndex = tempIndex = 15;

        // move animation
        while (rtcIndex > 0) {
            if (rtcMsg[rtcIndex - 1]) {
                rtcMsg[rtcIndex] += rtcMsg[rtcIndex - 1];
                rtcMsg[rtcIndex - 1] = rtcMsg[rtcIndex] - rtcMsg[rtcIndex - 1];
                rtcMsg[rtcIndex] -= rtcMsg[rtcIndex - 1];
            }
            rtcIndex--;
        }

        while (tempIndex > 0) {
            if (tempMsg[tempIndex - 1]) {
                tempMsg[tempIndex] += tempMsg[tempIndex - 1];
                tempMsg[tempIndex - 1] = tempMsg[tempIndex] - tempMsg[tempIndex - 1];
                tempMsg[tempIndex] -= tempMsg[tempIndex - 1];
            }
            tempIndex--;
        }

        rtcMsg[0] = rtcLast;
        tempMsg[0] = tempLast;

        delay_ms(125);
    }
}

void displayRTC(int secs, bool animation) {
    TRISC = 0x00;
    TRISD = 0x00;
    SPI1init();
    SPI_LCD4init();
    
    int rtcCursor = 0x80;
    char rtcMsg[17] = {0};
    char rtcLast;
    short rtcIndex = 15;
    
    for (int i = 0; i < 16; i++)
        rtcMsg[i] = ' ';
    
    int multiple, min, hour;
    
    multiple = min = hour = 0;

    if (secs > 59) {
        multiple = secs / 60;
        secs = secs - multiple * 60;
        min = multiple;
    }

    if (min > 59) {
        multiple = min / 60;
        min = min - multiple * 60;
        hour = multiple;
    }
    
    sprintf(rtcMsg, "Time: %d:%d:%d", hour, min, secs);
    
    while (1) {
        rtcCursor = 0x80;
        SPI_LCD4send(0x01, 0);

        for (int n = 0; rtcMsg[n]; n++, rtcCursor++) {
            SPI_LCD4send(rtcCursor, 0);
            SPI_LCD4send(rtcMsg[n], 1);
        }

        if (!animation) while(1);
        
        if (rtcMsg[0] == 'T') {
            delay_ms(3000);
            SPI_LCD4send(0x01, 0);
            delay_ms(10);

            // flash animation odd
            rtcCursor = 0x80;
            for (int i = 0; rtcMsg[i]; i+=2, rtcCursor += 2) {
                SPI_LCD4send(rtcCursor, 0);
                SPI_LCD4send(rtcMsg[i], 1);
                delay_ms(50);
            }

            delay_ms(100);
            
            // flash animation even
            rtcCursor = 0x81;
            for (int i = 1; rtcMsg[i]; i += 2, rtcCursor += 2) {
                SPI_LCD4send(rtcCursor, 0);
                SPI_LCD4send(rtcMsg[i], 1);
                delay_ms(50);
            }
            SPI_LCD4send(rtcCursor, 0);
            
            delay_ms(1000);
        }

        rtcLast = rtcMsg[15];
        rtcMsg[15] = ' ';
        rtcIndex = 15;

        // move animation
        while (rtcIndex > 0) {
            if (rtcMsg[rtcIndex - 1]) {
                rtcMsg[rtcIndex] += rtcMsg[rtcIndex - 1];
                rtcMsg[rtcIndex - 1] = rtcMsg[rtcIndex] - rtcMsg[rtcIndex - 1];
                rtcMsg[rtcIndex] -= rtcMsg[rtcIndex - 1];
            }
            rtcIndex--;
        }

        rtcMsg[0] = rtcLast;

        delay_ms(250);
    }
}

void displayTemp(float temp, bool animation) {
    TRISC = 0x00;
    TRISD = 0x00;
    SPI1init();
    SPI_LCD4init();
    
    int tempCursor = 0x80;
    char tempMsg[17] = {0};
    char tempLast;
    short tempIndex = 15;

    for (int i = 0; i < 16; i++)
        tempMsg[i] = ' ';

    sprintf(tempMsg, "Temp: %.1fC", temp);

    while (1) {
        tempCursor = 0x80;
        SPI_LCD4send(0x01, 0);

        for (int n = 0; tempMsg[n]; n++, tempCursor++) {
            SPI_LCD4send(tempCursor, 0);
            SPI_LCD4send(tempMsg[n], 1);
        }

        if (!animation) while(1);
        
        if (tempMsg[0] == 'T') {
            delay_ms(3000);
            SPI_LCD4send(0x01, 0);
            delay_ms(10);

            // flash animation odd
            tempCursor = 0x80;
            for (int i = 0; tempMsg[i]; i+=2, tempCursor += 2) {
                SPI_LCD4send(tempCursor, 0);
                SPI_LCD4send(tempMsg[i], 1);
                delay_ms(50);
            }

            delay_ms(100);
            
            // flash animation even
            tempCursor = 0x81;
            for (int i = 1; tempMsg[i]; i += 2, tempCursor += 2) {
                SPI_LCD4send(tempCursor, 0);
                SPI_LCD4send(tempMsg[i], 1);
                delay_ms(50);
            }
            SPI_LCD4send(tempCursor, 0);
            
            delay_ms(1000);
        }

        tempLast = tempMsg[15];
        tempMsg[15] = ' ';
        tempIndex = 15;

        // move animation
        while (tempIndex > 0) {
            if (tempMsg[tempIndex - 1]) {
                tempMsg[tempIndex] += tempMsg[tempIndex - 1];
                tempMsg[tempIndex - 1] = tempMsg[tempIndex] - tempMsg[tempIndex - 1];
                tempMsg[tempIndex] -= tempMsg[tempIndex - 1];
            }
            tempIndex--;
        }

        tempMsg[0] = tempLast;

        delay_ms(250);
    }
}
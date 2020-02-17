/*
 * File:   Temp_Monitoring.c
 * Author: Yi Run & Jing Wei
 *
 * Created on 30 January, 2020, 11:10 AM
 */
#include <xc.h>
#include <math.h>
#include <stdio.h>
#include "temp.h"

void ADCinit(void);
float getTempC();
float getTempF();
float getTempK();

void ADCinit(void)//unsigned char ch)
{
    TRISAbits.RA3 = 1; // Set RA3 as input
    ADCON0 = 0b00001101; //Channel 3, A/D is off 
    ADCON1 = 0b00001011; // Vref(+)=AVdd, Vref(-)=AVss, AN3=analog input
    ADCON2 = 0b00111000; // Left Justified, 20TAD, Fosc/2
}
 
unsigned int ADCRead(int ch)///unsigned char ch)
{
    ADCON0bits.CHS = ch;
    ADCON0bits.GO_DONE=1; // Start conversion    
    while(ADCON0bits.GO_DONE); // Wait for the conversion to finish
    return ADRESH;
}
 
float getTempC()
{
    unsigned int val=ADCRead(3);      //voltage in binary
    float temperatureC;

    temperatureC = round((val*(11/850.0)-0.5)/0.01*10)/10;
    
    return temperatureC;
}

char* getTempCString()
{
    char message[5];
    sprintf(message, "%f", getTempC());
    
    return message;
}

float getTempF()
{
    unsigned int val=ADCRead(3);      //voltage in binary
    float temperatureC, temperatureF;
    
    temperatureC = (val*(11/850.0)-0.5)/0.01*10/10;
    temperatureF = temperatureC*1.8+32;    
    return temperatureF;
}

char* getTempFString()
{
    char message[5];
    sprintf(message, "%f", getTempF());
    
    return message;
}

float getTempK()
{
    unsigned int val=ADCRead(3);      //voltage in binary
    float temperatureC, temperatureK;
    
    temperatureC = (val*(11/850.0)-0.5)/0.01*10/10;
    temperatureK = temperatureC + 273.15;    
    return temperatureK;
}

char* getTempKString()
{
    char message[5];
    sprintf(message, "%f", getTempK());
    
    return message;
}
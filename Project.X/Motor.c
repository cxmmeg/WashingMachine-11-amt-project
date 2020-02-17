
#include <xc.h>
#include <stdio.h>
#include "motor.h"
#pragma config XINST = OFF
#pragma config FOSC = HS
#pragma config WDT = OFF
#define _XTAL_FREQ 25000000
#define steps 200

// Going to left is Clockwise
// Going to Right is Anti Clockwise
// 0 = CW | 1 = AW
// Everything will be done in full-drive (highest torque)
// 100 step is about 180 degree

void startMotor() {
    TRISD = 0;       // Setting PortD to Output
}

void stopMotor() {
    PORTD = 0x00;       // Clearing bits in Port D;
    TRISD = 0xFF;
}

void spinMotor(int rate, int direction) {
    int i = 0;
    for (; i < steps; i++) {
        if (direction == 0 ){
            PORTD = 0b00000011;
            delay_ms(rate);
            PORTD = 0b00000110;
            delay_ms(rate);
            PORTD = 0b00001100;
            delay_ms(rate);
            PORTD = 0b00001001;
            delay_ms(rate);
            PORTD = 0b00000011;
            delay_ms(rate);
        }
        else if (direction == 1){
            PORTD = 0b00001001;
            delay_ms(rate);
            PORTD = 0b00001100;
            delay_ms(rate);
            PORTD = 0b00000110;
            delay_ms(rate);
            PORTD = 0b00000011;
            delay_ms(rate);
            PORTD = 0b00001001;
            delay_ms(rate);
        }
    }
} 

void oscillateMotor (int rate, int step) {
    int j = 0;
    // Going Clockwise direction
    for (; j < step ; j ++) {
            PORTD = 0b00000011;
            delay_ms(rate);
            PORTD = 0b00000110;
            delay_ms(rate);
            PORTD = 0b00001100;
            delay_ms(rate);
            PORTD = 0b00001001;
            delay_ms(rate);
            PORTD = 0b00000011;
            delay_ms(rate);
    }
    
    // Going Anticlockwise direction
    for (j = 0 ; j < step ; j++) {
            PORTD = 0b00001001;
            delay_ms(rate);
            PORTD = 0b00001100;
            delay_ms(rate);
            PORTD = 0b00000110;
            delay_ms(rate);
            PORTD = 0b00000011;
            delay_ms(rate);
            PORTD = 0b00001001;
            delay_ms(rate);
    }
}

void rinse (int cycle) {
    
    for (int i = 0; i < cycle; i++) {
        oscillateMotor(5, 100);
    }
}

void wash (int cycle) {
   
    for (int i = 0; i < cycle; i++) {
        spinMotor(5, 0); 
    }
}

void dry (int cycle) {
    
    for (int i = 0; i < cycle; i++) {
        spinMotor(5, 1);
    }
}

void normalWashMode() {
    int cycle = 5;   
    rinse(cycle);    
    wash(cycle);   
    dry(cycle);
}

void quickWashMode () {
    int cycle = 10;
    rinse(cycle);    
    wash(cycle);   
    turboDry(cycle);
    
}

void turboDry(int cycle) {
    
     for (int i = 0; i < cycle; i++) {
        spinMotor(2, 1);
    }
}

void delay_ms(int x) 
{
    for (int i = 0; i < x; i++) 
	{
        __delay_ms(1);
    }
}

void delay_us(int x) 
{
    for (int i = 0; i < x; i++) 
	{
        __delay_us(1);
    }
}
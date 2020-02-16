//PIC18F97J60 Configuration Bit Settings
//Class: DCPE/FT/2A/21
//Module: Advanced Microcontroller Technology (ET0720)
//Wilfred Wong (P1719617) 
//Scott Sia (P1718418)
//Header file for buzzer

#ifndef BUZZER_H
#define	BUZZER_H

void Buzzer_init();
//Set PortC bit RC3 to output

void Play_Sound(unsigned int freq, unsigned char duration);
//* User does not have to use this function
//Takes in the frequency and duration to generate a melody
//Used timer 1 to calculate Pulse Wave Modulation (PWM))

void Selectsong(int song);
//* User uses this function to choose the melody to play
// Select 1 when turning on the machine
// Select 2 when starting the washing procedure
// Select 3 after the washing machine ends its tasks
// Default included in case user inputs wrong value( not 1, 2 or 3)

#endif	/* BUZZER_H */


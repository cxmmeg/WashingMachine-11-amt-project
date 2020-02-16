/* 
 * File: Motor.h
 * Author: Hafiz Kosno
 * Comments:
 */

#ifndef MOTOR_H
#define	MOTOR_H


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    void startMotor();
    // Initializes the stepper motor connected to PORTD to Output
    // Must be called after calling stopMotor()
    
    
    void stopMotor();
    // Clears any bit stored in the Stepper Motor to stop the motor
    // Must be called to stop the motor()
    
    
    void spinMotor(int rate, int direction);
    // rate - How fast the motor spins. Lower number = Faster
    // direction - 0 = Clockwise spin | 1 = Anticlockwise spin
    // This function uses the stepper motor in Full step sequence
    // Default step is 200 which will make the motor spin 360 degree once.
    // Function only sets the rate of spin and direction of spin in 1 cycle
    
    
    void oscillateMotor(int rate, int step);
    // rate - How fast the motor spins. Lower number = Faster
    // step - to set how many degree it will turn. (1.8 / step)
    // Function will turn the motor in clockwise direction for X amount of step and 
    // then turn in anticlockwise direction for X amount of step. 
    
    void rinse (int cycle);
    // cycle - to set how many times the motor will run the said function. 
    // Standard function to turn the motor to oscillate every 180Degree for 
    // set amount of cycle.
    
    void wash (int cycle);
    // cycle - to set how many times the motor will run the said function.
    // Standard function to spin the motor in a set amount of cycle.
    
    void dry (int cycle);
    // cycle - to set how many times the motor will run the said function.
    // Uses the centrifugal force created by the motor to dry the "clothes". 
    // Motor spins slightly faster and in the 
    
    void normalWashMode (); 
    // This function rinses, washes and dries the clothes. 
    // The cycle is set to 20.
    
    void quickWashMode();
    // This function rinses, washes and dries the clothes but in a less amount of time. 
    // The cycle is set to 20.
    // Also makes uses of the turboDry() instead of the standard dry()
    
    void turboDry(int cycle); 
    // cycle - to set how many times the motor will run the said function. 
    // Uses the spinMotor() but spin rate of motor is  higher.
    
#ifdef	__cplusplus
}
#endif

#endif	/*MOTOR_H*/


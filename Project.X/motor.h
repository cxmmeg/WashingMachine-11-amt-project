#ifndef _AMT_HEADER_FILE
#define _AMT_HEADER_FILE
//Motor
void startMotor();
void stopMotor();
void spinMotor(int rate, int direction);
void oscillateMotor(int rate, int step);
void rinse (int cycle);
void wash (int cycle);
void dry (int cycle);
void normalWashMode (); 
void quickWashMode();
void turboDry(int cycle);

#endif

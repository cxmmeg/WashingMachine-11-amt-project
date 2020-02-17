#ifndef _AMT_HEADER_FILE
#define _AMT_HEADER_FILE
//RTC
void T2intr(void);
int getcountdown(void);
void setCounter15(void);
void setCounter30(void);
void setCounter45(void);
void pauseAndResumeTImer();
void endTimer();
void stopTimer(void);

#endif
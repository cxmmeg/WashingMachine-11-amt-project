#ifndef _AMT_HEADER_FILE
#define _AMT_HEADER_FILE
//Temperature Monitoring
void ADCinit(void);
float getTempC();
float getTempF();
float getTempK();
char* getTempCString();
char* getTempFString();
char* getTempKString();

#endif
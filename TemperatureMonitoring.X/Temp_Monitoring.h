#ifndef TEMPERATURE_MONITORING_H
#define TEMPERATURE_MONITORING_H

void ADCinit(void);
float getTempC();
float getTempF();
float getTempK();
char* getTempCString();
char* getTempFString();
char* getTempKString();

#endif
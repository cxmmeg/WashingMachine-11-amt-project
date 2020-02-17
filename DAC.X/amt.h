#ifndef _AMT_HEADER_FILE
#define _AMT_HEADER_FILE

void SPI1DACinit(void);
void sendDAC(char first,char second);
void DACcontinuous(void);
void DAClvl0(void);
void DAClvl1(void);
void DAClvl2(void);
void DAClvl3(void);
void DAClvl(void);

#endif
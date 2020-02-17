#ifndef _AMT_HEADER_FILE
#define _AMT_HEADER_FILE

const char * read_rfid(void); // From RFID.c
int verify_rfid(char id[]); // From RFID.c
void add_rfid(char id[]); // From RFID.c
void delete_rfid();
int guest_rfid(char id[]);

#endif
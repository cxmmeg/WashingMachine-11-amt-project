#ifndef _AMT_HEADER_FILE
#define _AMT_HEADER_FILE
//RFID
const char * read_rfid(void);
int verify_rfid(char id[]);
void add_rfid(char id[]);
void delete_rfid();
int guest_rfid(char id[]);

#endif

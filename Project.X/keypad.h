#ifndef _AMT_HEADER_FILE
#define _AMT_HEADER_FILE

//Keypad
typedef enum{
    KEY_PRESET,     // * key
    KEY_START,      // # key
    KEY_1,          // 1 key
    KEY_2,          // 2 key
    KEY_3,          // 3 key
    KEY_4,          // 4 key
    KEY_5,          // 5 key
    KEY_6,          // 6 key
    KEY_7,          // 7 key
    KEY_8,          // 8 key          
    KEY_NONE,       //When key isn't pressed
} key;

unsigned char Read_Key();
key get_key(char delicate);
void keypad_init(); 

#endif
    /*
     * File:   RFID.c
     * Author: Sim
     *
     * Created on February 4, 2020, 2:36 PM
     */

    #include <xc.h>
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include "header.h"

    #pragma config XINST = OFF
    #pragma config FOSC = HS
    #pragma config WDT = OFF


    char ids[10]; 
    const char * ptr = ids;

    //Read and output detected RFID card's id
    const char * read_rfid(void){


        while(RCREG!=0x02); //Loop until RFID card is detected

            for(int i=0;i<10;i++){
                while(PIR1bits.RC1IF==0);
                ids[i] =RCREG; //Save RFID id in ids array
            }
        ids[10] = '\0';
        return ptr;
    }
    
    // Return 1 if tapped id is a guest id
    int guest_rfid(char id[]){ //Temporary verify
        char guest[] = "6A0014502D"; //Guest id arrray

        if (strcmp(guest, id) == 0){ //Compare tapped id to guest id
            // Access granted
             return 1;
        }
        else {
            // Access denied
             return 0;
        }
    }

    int verify_rfid(char id[]){
        char verifiedID[11];
        //Get ID String from address 0x0101 to 0x010B
        for(unsigned i=1;i<11;i++){
            delay_ms(200);
            verifiedID[i-1]=read_byte_eeprom(0x01,i);
            delay_ms(100);
        }
        
        if (strcmp(verifiedID, id) == 0){ //Compare tapped id to verified id
            // Access granted
             return 1;
        }
        else {
            // Access denied
             return 0;
        }
    }
    void add_rfid(char id[]){
        // Add ID String to address 0x0101 to 0x010B
        for(unsigned i = 1;i<11;i++){
            delay_ms(200);  
            write_byte_eeprom(0x01,i,id[i-1]);
            delay_ms(100);
        }
    }

    void delete_rfid(){
         // Remove ID String from address 0x0101 to 0x010B
        for (unsigned i=1;i<11;i++){
            write_byte_eeprom(0x01,i,'0');
        }
    }
    
   
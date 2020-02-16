RFID Reader Library Routine

Description:
	This is a RFID library routine with functions that includes.

  	- const char * read_rfid(void); //Read id from RFID
   	- int verify_rfid(char id[]); //Verify if id is valid
	- int guest_rfid(char id[]); //guest id
    	- void add_rfid(char id[]); //Add id to be a valid id
    	- void delete_rfid(void); //Delete id from System
    	
	Function description:
		const char * read_rfid(void)
			- Does not require any parameters
			- Wait for rfid to be detected
			- When detected, scan the rfid and return the id back as a String

		int guest_rfid(char id[])
			- Requires an id String/Array as parameter
			- Will check the inputted id with verified guest id (From local variable)
			- Return 1 if id is a valid guest, else return 0
		
		int verify_rfid(char id[])
			- Requires an id String/Array as parameter
			- Will check the inputted id with verified id (From Serial EEPROM)
			- Return 1 if id is valid, else return 0

		void add_rfid(char id[])
			- Requires an id String/Array as parameter
			- Save the id in an array of valid id (In Serial EEPROM)
			- Return void

		void delete_rfid(void)
			- Delete the id the array of valid id (In Serial EEPROM)
			- Return void

To Use:
	Add the "RFID.c" and "header.h" File into your main project and #include "header.h" 

Prerequisites:
	String library and header.h files are required
	#include <string.h>
	#include "header.h"

Contact:
	Project by Ng Jun Hong and Sim Jun Hong.
	Contact via simjunhong38@gmail.com
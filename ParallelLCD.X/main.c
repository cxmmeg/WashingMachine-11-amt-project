#include <xc.h>
#include <stdio.h>
#include "P_LCD.h"

int counter = 0;
int sec=0;

void main(void) {
    char hello [] = "Hello Serial LCD";
    char cursoron [] = "Turn cursor on";
    char cleartop [] = "Clear top row.";
    char cursoroff [] = "Turn cursor off";
    char clearbottom [] = "Clear bottom row";
    char cursortop [] = "Cursor is now set on top row";
    char cursorbottom [] = "Cursor is now set on row below";
    char clearall[] = "Going to clear  both lines now";
    char scrollvertical[] = "This is a very  long message    that will scroll vertically for as long as this message goes";
    char scrollhorizontaltop[] = "This is a very long message that will scroll horizontally to the left on the top row";
    char scrollhorizontalbottom[] = "This is a very long message that will scroll horizontally to the left on the bottom row";
    char flashtop[] = "Flash top row";
    char flashbottom[] = "Flash bottom row";
    
    int c = 0;
    while(1)
    {
        //initialize the Parallel LCD
        P_LCD_init();
        
        //clear both rows and set cursor to top row
        P_LCD_CLR(0);
        
        //Turn on cursor
        P_LCD_set_cursor(1);
        P_LCD_send(cursoron , 1);       
        
        
        P_LCD_send(cleartop , 1);
        Pause_ms(1000);
        //clear top line only
        P_LCD_CLR(1);
        
        P_LCD_send(cursoroff , 2);
        //Turn off cursor
        P_LCD_set_cursor(0);
       
        
        P_LCD_send(clearbottom , 2);
        //clear bottom line only
        P_LCD_CLR(2);
        
        
        //clear both lines
        P_LCD_CLR(0);
        
        //Send an array with size >16 and <=32 to print on both lines
        P_LCD_send_all(clearall);         
        P_LCD_CLR(0);
        
        Pause_ms(1000);
        
        //Send message that will scroll vertically
        P_LCD_scroll_vertical(scrollvertical);
        
        //Clear screen
        P_LCD_CLR(0);
        
        
        //Send an array that will scroll horizontally to the right
        P_LCD_scroll_horizontal(scrollhorizontaltop , 1);
        
        
        //Send an array that will scroll horizontally to the right
        P_LCD_scroll_horizontal(scrollhorizontalbottom , 2);
        
        
        P_LCD_CLR(0);
        
        
        //Flash for 2 seconds on the top row
        P_LCD_flash(flashtop, 2 , 1);
        
        
        //Flash for 2 seconds on the bottom row
        P_LCD_flash(flashbottom, 2 , 2);
        
    }
}

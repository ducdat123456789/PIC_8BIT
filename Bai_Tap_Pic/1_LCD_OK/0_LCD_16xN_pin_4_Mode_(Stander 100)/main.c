/*
 * File:   main.c
 * Author: Dat Nguyen
 *
 * Created on 17 November, 2021, 7:08 AM
 */

#include <xc.h>
#include "lcd.h"

void main(void) 
{
    ADCON1 = 0x06;
    
    LCD_Init();
    
    LCD_Set_Cursor(1,1);
    LCD_Write_String("DUC DAT");
    LCD_Set_Cursor(2,1);
    LCD_Write_Number(300720001);
    
    while(1)
    {
    }
    return;
}
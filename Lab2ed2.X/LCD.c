/* 
 * File: LCD.c  
 * Se utiliz? y se adaptaron las librer?as de Ligo George 
 * de la p?gina www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 * Revision history: 
 */

//LCD Functions Developed by electroSome

#include "LCD.h"

void Lcd_Port(char a) {
    
    if (a & 1)
        B0 = 1;
    else
        B0 = 0;
    
    if (a & 2)
        B1 = 1;
    else
        B1 = 0;
    
    if (a & 4)
        B2 = 1;
    else
        B2 = 0;
    
    if (a & 8)
        B3 = 1;
    else
        B3 = 0;
    
    /////////////////////
    
    if (a & 16)
        B4 = 1;
    else
        B4 = 0;

    if (a & 32)
        B5 = 1;
    else
        B5 = 0;

    if (a & 64)
        B6 = 1;
    else
        B6 = 0;

    if (a & 128)
        B7 = 1;
    else
        B7 = 0;
}

void Lcd_Cmd(char a) {
    RS = 0; // => RS = 0 // Dato en el puerto lo va interpretar como comando
    Lcd_Port(a);
    EN = 1; // => E = 1
    __delay_ms(4);
    EN = 0; // => E = 0
}

void Lcd_Clear(void) {
    Lcd_Cmd(0);
    Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b) {
    char temp, z, y;
    if (a == 1) {
        temp = 0x80 + b - 1;
        Lcd_Cmd(temp);
    } else if (a == 2) {
        temp = 0xC0 + b - 1;
        Lcd_Cmd(temp);
    }
}

void Lcd_Init(void) {
    Lcd_Port(0x00);
    __delay_ms(105);
    Lcd_Cmd(0x30);
    __delay_ms(5);
    Lcd_Cmd(0x30);
    __delay_ms(105);
    Lcd_Cmd(0x30);
    __delay_ms(105);

    /////////////////////////////////////////////////////
    Lcd_Cmd(0x38);
    __delay_us(55);

    Lcd_Cmd(0x08);
    __delay_us(55);
        
    Lcd_Cmd(0x01);
    __delay_ms(5);

    Lcd_Cmd(0x06);
    __delay_us(55);

    Lcd_Cmd(0x0C);
    __delay_us(55);

}

void Lcd_Write_Char(char a) {
    RS = 1; // => RS = 1
    Lcd_Port(a); //Data transfer
    EN = 1;
    __delay_us(40);
    EN = 0;
}

void Lcd_Write_String(char *a) {
    int i;
    for (i = 0; a[i] != '\0'; i++)
        Lcd_Write_Char(a[i]);
}

void Lcd_Shift_Right(void) {
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x0C);
}

void Lcd_Shift_Left(void) {
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x08);
}



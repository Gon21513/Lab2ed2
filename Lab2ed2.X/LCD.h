/* 
 * File: LCD.h  
 * Se utiliz? y se adaptaron las librer?as de Ligo George 
 * de la p?gina www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_H
#define	LCD_H

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000
#endif

#ifndef RS
#define RS PORTDbits.RD7
#endif

#ifndef EN
#define EN RD6
#endif

#ifndef B0
#define B0 RB0
#endif

#ifndef B1
#define B1 RB1
#endif

#ifndef B2
#define B2 RB2
#endif

#ifndef B3
#define B3 RB3
#endif

#ifndef B4
#define B4 RB4
#endif

#ifndef B5
#define B5 RB5
#endif

#ifndef B6
#define B6 RB6
#endif

#ifndef B7
#define B7 RB7
#endif

#include <xc.h> // include processor files - each processor file is guarded.  

//LCD Functions Developed by electroSome


void Lcd_Port(char a);

void Lcd_Cmd(char a);

void Lcd_Clear(void);

void Lcd_Set_Cursor(char a, char b);

void Lcd_Init(void);

void Lcd_Write_Char(char a);

void Lcd_Write_String(char *a);

void Lcd_Shift_Right(void);

void Lcd_Shift_Left(void);

#endif	/* LCD_H */


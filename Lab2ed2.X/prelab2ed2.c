/* 
 * File:   prelab10.c
 * Author: lpgp3
 *
 * Created on 30 de abril de 2023, 01:47 PM
 */
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ 8000000

#include<xc.h>
#include<pic.h>
#include <stdio.h>
#include<stdint.h>
#include "ADC.h"
#include "LCD.h"




//-------------------------------variables------------------------------------|
uint8_t counter;
int ADC; //valor del adc 
uint8_t numadc = 0; //variable para el valor del adc
char buffer[4]; // Variable para almacenar la cadena de caracteres del valor del ADC



//|------------------------------prototipos------------------------------------|

void setup(void);
void __interrupt() isr(void);



//-------------main----------------------

void    main(void){
    setup();
    
//------------LCD------------------------
    Lcd_Init(); //inicar el adc
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("ADC");


    while(1){

        Lcd_Set_Cursor(2,1);
        // Mostrar el valor del ADC en el LCD
        Lcd_Write_Char('0' + (ADC / 100)); // Muestra el dígito de las centenas
        Lcd_Write_Char('0' + ((ADC / 10) % 10)); // Muestra el dígito de las decenas
        Lcd_Write_Char('0' + (ADC % 10)); // Muestra el dígito de las unidades

        
        //este tambien funciona 
        //sprintf(buffer, "%3u", ADC);
        //Lcd_Write_String(buffer);
        //PORTC = counter; //poner el valor del contador en el puerto A

        //verifica la conversion adc
        if (ADCON0bits.GO == 0){
            ADCON0bits.GO = 1;
            __delay_ms(50);
        }



    }
}

//|------------------------------Setup----------------------

void setup(void){

    ANSEL = 0;

//-------------configuracion de puertos----------------
    TRISA  = 0;
    TRISC = 0;
    TRISD = 0;





//------------interrupciones-----------------
    INTCONbits.RBIE = 1; //habilitar interrupciones en portb
    INTCONbits.PEIE = 1;//habilitar interrupciones perifericas 
    INTCONbits.GIE = 1; //habilitar interrupciones globales
    INTCONbits.RBIF = 0; //limpirar bander de interrupcion de portb


    //del adc
    PIE1bits.ADIE = 1; // habilitar interrupciones de ADC



   //Se inician los puertos 
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;


// --------------- Oscilador --------------- 
    OSCCONbits.IRCF = 0b111; // 8 MHz
    OSCCONbits.SCS = 1; // Seleccionar oscilador interno

//----------------ADC ------------------
    //ADC
    adc_init(0);
    

}




//----------------Interrupcion--------------------
void __interrupt() isr(void) {

     //__delay_ms(10);

    if (PIR1bits.ADIF){
        ADC = read_ADC();
        //numadc = ADC; // pasar valor del adc a num1 
        PORTC = ADC;
    }
    PIR1bits.ADIF = 0;
    return;
}
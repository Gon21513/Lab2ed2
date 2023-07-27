/* 
 * File:   postlab8.c
 * Author: Luis Pedro Gonzalez 21513
 *
 * Created on 19 de abril de 2023, 03:34 PM
 */
#define _XTAL_FREQ 4000000

//variables
//uint16_t voltaje1; //Variable para guardar el voltaje del canal AN0

unsigned int centena; // Almacena las centenas en  ASCII
unsigned int decena; // Almacena las decenas en  ASCII
unsigned int unidad; // Almacena las unidades en  ASCII
unsigned int pot; // Guarda el valor le�do del potenci�metro
unsigned char opcion; // Variable para elegir una opci�n
unsigned char bandera; // Indicador para controlar bucles

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <pic16f887.h>

#include<pic.h>
#include "ADC.h"
#include "uart.h"
#include "LCD.h"


//-------------------------------variables------------------------------------|
uint8_t counter;
int ADC; //valor del adc 
uint16_t numadc; //variable para el valor del adc
char buffer[4]; // Variable para almacenar la cadena de caracteres del valor del ADC
char voltaje[3]; //arreglo para guardar valor del potenciometro y mostrar en terminal UART

int v1;//valor de voltaje 1 
int v2;

unsigned int unidadesv1;
unsigned int decenasv1;
unsigned int centenasv1;


// --------------- Rutina de  interrupciones --------------- 
void __interrupt() isr(void){
    // ---- INTERRUPCION DEL ADC --------
    if (PIR1bits.ADIF){ // Chequear bandera del conversor ADC
        
        ADC = read_ADC();
        numadc = ADC; // pasar valor del adc a num1
//        //mapeo y conversion del adc a voltaje
        v1 = map(numadc,0,255,0,100);
        unidadesv1 = (v1*5)/100;// obtener las unidades
        decenasv1 = ((v1*5)/10)%10; //obtener decenas 
        centenasv1  = (v1*5)%10; //obtener centenas del valor del voltaje
        
    }
        PIR1bits.ADIF = 0; // Borrar el indicador del conversor ADC
        return;

        
}

// --------------- Prototipos --------------- 
void setup(void);
void cadena(char *cursor);

// --------------- main --------------- 
void main(void){
    setup();
    adc_init(0);

    
//------------LCD------------------------
    Lcd_Init(); //inicar el adc
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
     //menu de opciones
        while (1){
//--------------mapeo
        
//        //mapeo y conversion del adc a voltaje
        v1 = map(numadc,0,255,0,100);
        unidadesv1 = (v1*5)/100;// obtener las unidades
        decenasv1 = ((v1*5)/10)%10; //obtener decenas 
        centenasv1  = (v1*5)%10; //obtener centenas del valor del voltaje

   // mostar en lcd el voltaje 1 
        Lcd_Set_Cursor(2,1);
        sprintf(buffer, "%u.%u%u", unidadesv1,decenasv1,centenasv1);
        Lcd_Write_String(buffer);
        __delay_ms(150);
        
        
        
        
        //verifica la conversion adc
        if (ADCON0bits.GO == 0){
            ADCON0bits.GO = 1;
            __delay_ms(50);
        }
//        
        
       // cadena("\n\r"); 
       // cadena("SELECCIONE UNA OPCION:\n\r"); 
       // cadena("1. VALOR DEL POTENCIOMETRO\n\r"); 
       // cadena("2. VALOR EN ASCII\n\r"); 
        //cadena("\n\r"); // Salto de l�nea
        cadena("\n\r EL VALOR DEL POTENCIOMETRO ES:\n\r"); // Mostrar mensaje
                //cadena("\n\r"); //salto


                
       TXREG = unidadesv1 + 48; // Enviar el valor de las unidades
       __delay_ms(10); 
                
       TXREG = '.'; // Enviar el valor de las unidades
       __delay_ms(10); 
                
       TXREG = decenasv1 + 48; // Enviar el valor de las decenas
       __delay_ms(10); 
                
       TXREG = centenasv1 + 48; // Enviar el valor de las centenas
       __delay_ms(10); 

                //cadena("\n\r\n\r"); // Salto de l�nea

        }  
        __delay_ms(500);                
    }


// --------------- Setup General --------------- 
void setup(void){
    // --------------- Definir analogicas --------------- 
    ANSELH = 0;
    
//-------------configuracion de puertos----------------
    TRISA  = 0;
    TRISB = 0;
    TRISD = 0;
   
   //Se inician los puertos 
    PORTA = 0;
    PORTB = 0;
    PORTD = 0;
    
// --------------- Oscilador --------------- 
    OSCCONbits.IRCF = 0b110; // 4 MHz
    OSCCONbits.SCS = 1; // Seleccionar oscilador interno

    // --------------- Banderas e interrupciones ---------------
 
    PIE1bits.ADIE = 1; // Habiliar interrupcion del conversor ADC
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    
    UART_RX_config (9600); 
    UART_TX_config (9600);
    
    //----------------ADC ------------------
    //ADC

}
    


//Funcion para mostrar texto
void cadena(char *cursor){
    while (*cursor != '\0'){ //verificar si llega al nulo
        while (PIR1bits.TXIF == 0); // no haces nada cuando envia
            TXREG = *cursor; // asigna el valor a enviae
            *cursor++; // incremeta posicion del cursor
    }
}
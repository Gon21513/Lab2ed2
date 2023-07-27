/*
 * File:   uart.c
 * Author: Luis Pedro González 21513
 *
 * Created on 25 de julio de 2023, 08:36 PM
 */


#include <xc.h>
#include "uart.h"

void UART_TX_config(uint16_t baudrate){ 
    if (baudrate == 9600){
        TXSTAbits.SYNC = 0; // Modo asincrónico
        TXSTAbits.BRGH = 1; // Alta velocidad de baudios

        BAUDCTLbits.BRG16 = 0; // Utilizar 16 bits para el baud rate

        //puede ser 51
        SPBRG = 25; // Configurar el valor del registro de baudios a 9615 (para una velocidad específica)
        SPBRGH = 0; // Los 8 bits más significativos del valor de baudios (para 16 bits)

        TXSTAbits.TXEN = 1; // Habilitar la transmisión

    }
    
    
}
void UART_RX_config(uint16_t baudrate){
    if (baudrate == 9600){
        RCSTAbits.SPEN = 1; // Habilitar la comunicación serial
        RCSTAbits.RX9 = 0; // Deshabilitar el bit de noveno bit de dirección
        RCSTAbits.CREN = 1; // Habilitar la recepción

    }
    
}


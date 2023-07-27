/*
 * File:   uart.c
 * Author: Luis Pedro Gonz�lez 21513
 *
 * Created on 25 de julio de 2023, 08:36 PM
 */


#include <xc.h>
#include "uart.h"

void UART_TX_config(uint16_t baudrate){ 
    if (baudrate == 9600){
        TXSTAbits.SYNC = 0; // Modo asincr�nico
        TXSTAbits.BRGH = 1; // Alta velocidad de baudios

        BAUDCTLbits.BRG16 = 0; // Utilizar 16 bits para el baud rate

        //puede ser 51
        SPBRG = 25; // Configurar el valor del registro de baudios a 9615 (para una velocidad espec�fica)
        SPBRGH = 0; // Los 8 bits m�s significativos del valor de baudios (para 16 bits)

        TXSTAbits.TXEN = 1; // Habilitar la transmisi�n

    }
    
    
}
void UART_RX_config(uint16_t baudrate){
    if (baudrate == 9600){
        RCSTAbits.SPEN = 1; // Habilitar la comunicaci�n serial
        RCSTAbits.RX9 = 0; // Deshabilitar el bit de noveno bit de direcci�n
        RCSTAbits.CREN = 1; // Habilitar la recepci�n

    }
    
}


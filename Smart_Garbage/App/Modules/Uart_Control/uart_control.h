#ifndef UART_CONTROL_H
#define UART_CONTROL_H

#include "hal_uart.h"
#include <stddef.h>


void UART_Init();


void UART_Echo();

void UART_BLUE();




void UART_GetRX2();

void UART_GetRX1();

void UART_APP_Control(void (*APP)(unsigned char *, unsigned char)); // 
void UART_PC_Control(void (*PC)(unsigned char *, unsigned char));  //
void UART_Test(void (*TEST)(unsigned char *, unsigned char));

#endif // UART_CONTROL_H
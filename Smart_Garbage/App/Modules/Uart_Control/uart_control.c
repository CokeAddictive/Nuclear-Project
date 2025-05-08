#include "uart_control.h"

static void (*APP_Control)(unsigned char *, unsigned char) = NULL;
static void (*PC_Control)(unsigned char *, unsigned char) = NULL;
static void (*Test)(unsigned char *, unsigned char) = NULL;

void UART_Init() {
    HAL_UART_Init();
}

void UART_Echo() {
    HAL_UART_Echo();
}

void UART_BLUE() {
    HAL_UART_BLUE();
}

void RX2RSV(unsigned char *RX2Buffer, unsigned char RX2Len){ 
    if (PC_Control != NULL) { 
        PC_Control(RX2Buffer, RX2Len);
    }
    if (APP_Control != NULL) { 
        APP_Control(RX2Buffer, RX2Len);
    }
}


void RX1RSV(unsigned char *RX1Buffer, unsigned char RX1Len){
    if(Test!=NULL){
        Test(RX1Buffer, RX1Len);
    }
}


void UART_GetRX2() {
    HAL_Rx2Callback(RX2RSV);
}

void UART_GetRX1(){
    HAL_Rx1Callback(RX1RSV);
}


void UART_APP_Control(void (*APP)(unsigned char *, unsigned char)) {
    APP_Control=APP;
}

void UART_PC_Control(void (*PC)(unsigned char *, unsigned char)) {
    PC_Control=PC;
}
void UART_Test(void (*TEST)(unsigned char *, unsigned char)) {
    Test=TEST;
}

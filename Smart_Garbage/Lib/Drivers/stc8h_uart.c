#include "hal_uart.h"

#include "STC8G_H_GPIO.h"
#include "STC8G_H_NVIC.h"
#include "STC8G_H_Switch.h"
#include "STC8G_H_UART.h"
#include "STRING.H"


// 定义一个静态的函数指针 uartRX2_Callback，用于指向一个回调函数。
// 初始时，该函数指针被赋值为 NULL，表示未指向任何函数。
static void (*uartRX2_Callback)(unsigned char *, unsigned char) = NULL;
static void (*uartRX1_Callback)(unsigned char *, unsigned char) = NULL;

static void GPIO_Config() {
    // 串口1 P30 P31
    GPIO_InitTypeDef GPIO_InitStructure;              // 结构定义
    GPIO_InitStructure.Mode = GPIO_PullUp;            // 指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin = GPIO_Pin_0 | GPIO_Pin_1; // 指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7
    GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);       // 初始化

    // 串口2 P10 P11
    GPIO_InitStructure.Pin = GPIO_Pin_0 | GPIO_Pin_1; // 指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7
    GPIO_Inilize(GPIO_P1, &GPIO_InitStructure);       // 初始化
}

static void UART_Config() {
    COMx_InitDefine UART_InitStructure;
    UART_InitStructure.UART_Mode = UART_8bit_BRTx;
    UART_InitStructure.UART_BaudRate = 115200; // 通常只有波特率需要改
    UART_InitStructure.UART_RxEnable = ENABLE; // 允许接收
    UART_InitStructure.BaudRateDouble = DISABLE;
    //===================UART1=============
    UART_InitStructure.UART_BRT_Use = BRT_Timer1;
    UART_Configuration(UART1, &UART_InitStructure); // ARTX代表你用的那一组串口
    NVIC_UART1_Init(ENABLE, Priority_1);            // 去NVIC.H里面找，用的串口几就选几,打开中断使能
    UART1_SW(UART1_SW_P30_P31);                     // 去Swtich.h里面找定义 ,切换引脚（可选）至P30,P31

    //==================UART2===============
    UART_InitStructure.UART_BRT_Use = BRT_Timer2;
    UART_Configuration(UART2, &UART_InitStructure); // ARTX代表你用的那一组串口
    NVIC_UART2_Init(ENABLE, Priority_2);            // 去NVIC.H里面找，用的串口几就选几,打开中断使能
    UART2_SW(UART2_SW_P10_P11);                     // 去Swtich.h里面找定义 ,切换引脚（可选）至P30,P31
}

void HAL_UART_Init() { // 优先级为2的串口1通讯
    GPIO_Config();     // 初始化GPIO
    UART_Config();     // 初始化UART
    EA = 1;
}

void HAL_UART_Echo() {
    char i;
    if (COM1.RX_Cnt > 0 && --COM1.RX_TimeOut == 0) { // 数组里有数据且能把5倒数到0
        if (uartRX1_Callback != NULL) { // 串口1接收回调
            uartRX1_Callback(RX1_Buffer, COM1.RX_Cnt);
        }
        for (i = 0; i < COM1.RX_Cnt; i++) {
            TX1_write2buff(RX1_Buffer[i]); // 读取数组里每个字符，并通过串口发送出去
        }
        COM1.RX_Cnt = 0; // 如果不置0程序会一直输出
    }
}

/**
 * @brief 串口1收到数据，串口2发送出去，串口2收到数据，串口1发送出去
 */
void HAL_UART_BLUE() {
    char i;
    if (COM1.RX_Cnt > 0 && --COM1.RX_TimeOut == 0) { // 数组里有数据且能把5倒数到0
        
        if (uartRX1_Callback != NULL) { // 串口1接收回调
            uartRX1_Callback(RX1_Buffer, COM1.RX_Cnt);
        }
        
        for (i = 0; i < COM1.RX_Cnt; i++) {
            TX2_write2buff(RX1_Buffer[i]); // 读取数组里每个字符，并通过串口发送出去
        }
        COM1.RX_Cnt = 0; // 如果不置0程序会一直输出
    }

    if (COM2.RX_Cnt > 0 && --COM2.RX_TimeOut == 0) { // 数组里有数据且能把5倒数到0
        // 在这里添加
        if (uartRX2_Callback != NULL) { // 串口2接收回调
            uartRX2_Callback(RX2_Buffer, COM2.RX_Cnt);
        }
        // for (i = 0; i < COM2.RX_Cnt; i++) {
        //     TX1_write2buff(RX2_Buffer[i]); // 读取数组里每个字符，并通过串口发送出去
        // }
        COM2.RX_Cnt = 0; // 如果不置0程序会一直输出
    }
}

// 用于注册回调函数，谁调用谁就需要实现RX2_CBack这个函数
void HAL_Rx2Callback(void (*RX2_CBack)(unsigned char *, unsigned char)) {
    uartRX2_Callback = RX2_CBack;
}
void HAL_Rx1Callback(void (*RX1_CBack)(unsigned char *, unsigned char)) {
    uartRX1_Callback = RX1_CBack;
}

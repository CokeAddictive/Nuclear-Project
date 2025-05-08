#ifndef HAL_UART_H
#define HAL_UART_H




/**
 * @brief 串口初始化（优先级为2的串口1通讯）
 * 
 */
void HAL_UART_Init();


/**
 * @brief 串口数据回显
 */
void HAL_UART_Echo();

void HAL_UART_BLUE();

void HAL_Rx2Callback(void (*RX2_CBack)(unsigned char *, unsigned char));
void HAL_Rx1Callback(void (*RX1_CBack)(unsigned char *, unsigned char));

#endif // HAL_UART_H
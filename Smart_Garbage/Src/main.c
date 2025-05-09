#include "RTX51TNY.H"
#include "engine_control.h"
#include "light_control.h"
#include "nixie_control.h"
#include "uart_control.h"
#include "oled_control.h"



void System_Init() _task_ 1 {
    UART_Init();   // 串口
    Engine_Init(); // 舵机
    Nixie_Init();  // 数码管
    OLED_Init();    //I2C屏幕
    OLED_ShowString(0,0,"Smart_Garbage",16);
    OLED_ShowString(0,2,"hello world",16);

    os_delete_task(1); // kill oneself
}

void Launch() _task_ 0 {
    os_create_task(1); // 系统初始化
    os_create_task(2); // 串口
    os_create_task(3); // 数码管

    os_delete_task(0); // kill oneself
}

void APP(unsigned char *RX2Buffer, unsigned char RX2Len) {
    static int angle = 0;
    unsigned char i;
    for (i = 0; i < RX2Len; i++) {
        printf("%c", RX2Buffer[i]); // 打印接收到的数据
        if (RX2Buffer[0] == 0x10) {
            Engine_SetAngle(0);
        } else if (RX2Buffer[0] == 0x11) {
            Engine_SetAngle(180);
        }
    }
}

void UART_Task() _task_ 2 { //
    UART_APP_Control(APP);
    UART_GetRX2();

    while (1) {
        // UART_Echo();// 回显
        UART_BLUE(); // 蓝牙通讯
        os_wait2(K_TMO, 5);
    }
}

void Nixie_Task() _task_ 3 {//数码管
    while (1) {
        Nixie_Show(6,0,NO); // 数码管
        //Nixie_NumShow(123);
        os_wait2(K_TMO, 1);
    }
}

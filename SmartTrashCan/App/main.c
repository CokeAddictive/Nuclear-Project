#include "light_control.h"
#include "RTX51TNY.H"

void System_Init() _task_ 1 {
    LightControl_Init();// 初始化灯光控制
    LightControl_SetMode(LIGHT_MODE_LEFT);// 初始模式为左灯

    os_create_task(2); // 灯光控制任务


    os_delete_task(1); // kill oneself
}

void Launch() _task_ 0 {
    os_create_task(1); // 系统初始化
    os_create_task(2); // 灯光控制任务


    os_delete_task(0); // kill oneself
}



void Light_Task() _task_ 2 {
    while(1){
        LightControl_Update();
        os_wait2(K_TMO,10);
    }
}






















#include "hal_light.h"
#include "STC8G_H_GPIO.h"

#define LIGHT_L P07
#define LIGHT_R P52

//引脚映射
//引脚模式映射

static void GPIO_Config() {
    P0_MODE_IO_PU(GPIO_Pin_7);
    P5_MODE_IO_PU(GPIO_Pin_2);
}

void HAL_Light_Init(void) {
    GPIO_Config();
    LIGHT_L = LIGHT_R = OFF;
}

char HAL_Light_GetState(Light_Position_t position) {
    return position == LIGHT_LEFT ? LIGHT_L : LIGHT_R;
}

void HAL_Light_Control(Light_Position_t position, char state) {
    if (position == LIGHT_LEFT) {
        LIGHT_L = state ? ON : OFF;
    } else {
        LIGHT_R = state ? ON : OFF;
    }
}
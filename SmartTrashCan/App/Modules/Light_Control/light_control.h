#ifndef LIGHT_CONTROL_H
#define LIGHT_CONTROL_H

#include "hal_light.h"
#include "RTX51TNY.H"

typedef enum {
    LIGHT_MODE_OFF,     // 关闭所有灯光
    LIGHT_MODE_LEFT,    // 左转灯模式
    LIGHT_MODE_RIGHT,   // 右转灯模式
    LIGHT_MODE_HAZARD    // 双闪警示灯模式
} Light_Mode_t;

void LightControl_Init();
void LightControl_SetMode(Light_Mode_t mode);

void LightControl_Update();

#endif // LIGHT_CONTROL_H
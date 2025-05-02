#include "light_control.h"

static Light_Mode_t current_mode = LIGHT_MODE_OFF;

void LightControl_Init() {
    HAL_Light_Init();
}

void LightControl_SetMode(Light_Mode_t mode) {
    current_mode = mode;
}

void LightControl_Update() {
    switch (current_mode) {
    case LIGHT_MODE_OFF:
        HAL_Light_Control(LIGHT_LEFT, OFF);
        HAL_Light_Control(LIGHT_RIGHT, OFF);
        break;
    case LIGHT_MODE_LEFT:
        HAL_Light_Control(LIGHT_LEFT, ON);
        os_wait2(K_TMO, 60);
        HAL_Light_Control(LIGHT_LEFT, OFF);
        os_wait2(K_TMO, 60);
        break;
    case LIGHT_MODE_RIGHT:
        HAL_Light_Control(LIGHT_RIGHT, ON);
        os_wait2(K_TMO, 60);
        HAL_Light_Control(LIGHT_RIGHT, OFF);
        os_wait2(K_TMO, 60);
        break;
    case LIGHT_MODE_HAZARD:
        HAL_Light_Control(LIGHT_LEFT, ON);
        HAL_Light_Control(LIGHT_RIGHT, ON);
        os_wait2(K_TMO, 60);
        HAL_Light_Control(LIGHT_LEFT, OFF);
        HAL_Light_Control(LIGHT_RIGHT, OFF);
        os_wait2(K_TMO, 60);
        break;
        // ... other cases ...
    }
}
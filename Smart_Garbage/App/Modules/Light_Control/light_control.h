#ifndef LIGHT_CONTROL_H
#define LIGHT_CONTROL_H

#include "hal_light.h"
#include "RTX51TNY.H"

typedef enum {
    LIGHT_MODE_OFF,     
    LIGHT_MODE_LEFT,    
    LIGHT_MODE_RIGHT,   
    LIGHT_MODE_HAZARD    
} Light_Mode_t;

void LightControl_Init();
void LightControl_SetMode(Light_Mode_t mode);

void LightControl_Update();

#endif // LIGHT_CONTROL_H
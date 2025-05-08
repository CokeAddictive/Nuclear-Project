#ifndef HAL_ENGINE_H
#define HAL_ENGINE_H

#include "STC8G_H_GPIO.h"
#include "STC8G_H_NVIC.h"
#include "STC8G_H_Switch.h"
#include "STC8H_PWM.h"

void HAL_Engine_Init();
void HAL_Engine_SetAngle(float angle);



#endif // HAL_ENGINE_H
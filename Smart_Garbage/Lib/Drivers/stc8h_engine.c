#include "hal_engine.h"

#define PERIOD (MAIN_Fosc / 1000)
#define ENGINE_GPIO_PORT GPIO_P2
#define ENGINE_GPIO_PIN GPIO_Pin_1


static void GPIO_Config() {
    GPIO_InitTypeDef GPIO_InitStructure;        // 结构定义
    GPIO_InitStructure.Mode = GPIO_OUT_PP;        // 指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin = ENGINE_GPIO_PIN;        // 指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7
    GPIO_Inilize(ENGINE_GPIO_PORT, &GPIO_InitStructure); // 初始化
}


static void PWM_Config() {
    PWMx_InitDefine PWM_InitStructure;
    PWM_InitStructure.PWM_Mode = CCMRn_PWM_MODE1; // 模式:CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,
                                                  // 1高/2低CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
    PWM_InitStructure.PWM_Period = PERIOD - 1;    // 周期时间,   0~65535 （通常设置1ms：PERIOD - 1）
    PWM_InitStructure.PWM_Duty = 0.5 * PERIOD;    // 占空比时间, 0~Period（变量/100 * PERIOD)
    PWM_InitStructure.PWM_DeadTime = 0;           // 死区发生器设置, 0~255
    PWM_InitStructure.PWM_EnoSelect = ENO6P;      // 输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
    PWM_InitStructure.PWM_CEN_Enable = ENABLE;    // 使能计数器, ENABLE,DISABLE
    PWM_InitStructure.PWM_MainOutEnable = ENABLE; // 主输出使能,  ENABLE,DISABLE

    // PWM要初始化2次
    PWM_Configuration(PWM6, &PWM_InitStructure); // 初始化组号
    PWM_Configuration(PWMB, &PWM_InitStructure); // 初始化通道A/B

    // PWM的中断使能(NVIC.h文件里找)，参数1填组号
    NVIC_PWM_Init(PWM6, DISABLE, Priority_0); // 禁用中断其实可以不写这一行

    // 切换引脚(Switch.h里面找)
    PWM6_SW(PWM6_SW_P21);

    //STCH_PWM.h  515行
    PWMB_Prescaler(20 - 1);
}



/**
 * @brief 设置马达角度
 * 
 * @param angle 
 */
void HAL_Engine_SetAngle(float angle) {
    PWMx_Duty duty;
    float value = 50 + ((angle / 180.0) * 200);
    duty.PWM6_Duty = (value / 2000) * PERIOD;
    UpdatePwm(PWMB, &duty);
}

/**
 * @brief 初始化
 *
 */
void HAL_Engine_Init() {
    EA = 1;
    EAXSFR(); /* 扩展寄存器访问使能 */
    GPIO_Config();
    PWM_Config();
}


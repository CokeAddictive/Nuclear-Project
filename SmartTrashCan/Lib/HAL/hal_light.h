#ifndef HAL_LIGHT_H
#define HAL_LIGHT_H

typedef enum {
    LIGHT_LEFT,
    LIGHT_RIGHT
} Light_Position_t;
#define ON 1    //开灯
#define OFF 0   //关灯

/**
 * @brief 灯光状态查询
 * @param position 灯光位置(LIGHT_LEFT=左, LIGHT_RIGHT=右)
 * @return 灯光当前状态
 */
char HAL_Light_GetState(Light_Position_t position);

/**
 * @brief 初始化灯光控制硬件
 */
void HAL_Light_Init(void);

/**
 * @brief 控制灯光状态
 * @param position 灯光位置(LIGHT_LEFT=左, LIGHT_RIGHT=右)
 * @param state 控制状态(true=开, false=关)
 */
void HAL_Light_Control(Light_Position_t position, char state);

#endif // HAL_LIGHT_H
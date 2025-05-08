#include "hal_nixie.h"

#include "STC8G_H_GPIO.h"
// 优化后的位检测宏，功能相同但括号更简洁
#define SET_Nixie(data, i) ((data & (1 << (7 - i))) ? 1 : 0)

#define NIX_DI P44  // 数据
#define NIX_RCK P43 // 锁存
#define NIX_SCK P42 // 移位

#define NIXIE_GPIO_PORT GPIO_P4
#define NIXIE_GPIO_DIPIN GPIO_Pin_4 | GPIO_Pin_3 | GPIO_Pin_2

// // 数码管段码表，共阴极
// code char LED_TABLE[12] = {
//     // 0    1    2      3    4       5    6     7     8     9    (索引0-9)
//     0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90,
//     // .    -                                            (索引20-21)
//     0x7F, 0xBF};

static void GPIO_Config() {
    GPIO_InitTypeDef GPIO_InitStructure;                           // 结构定义
    GPIO_InitStructure.Mode = GPIO_OUT_PP;                         // 指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin = NIXIE_GPIO_DIPIN; // 指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7
    GPIO_Inilize(NIXIE_GPIO_PORT, &GPIO_InitStructure);                    // 初始化
}


void HAL_Nixie_Init() {
    GPIO_Config();
}


/**
 * @brief 数码管显示，原始，需要传递内容和数字
 * 
 * @param Num_data 内容
 * @param Show_index 位置
 */
void HAL_Nixie_Original(char Num_data, char Show_index) {
    int i;
    // 内容
    for (i = 0; i < 8; i++) {
        NIX_DI = SET_Nixie(Num_data, i); // 高电平
        // 移位 0 -> 1
        NIX_SCK = 0;
        NOP2();
        NIX_SCK = 1;
        NOP2();
    }

    // 位置
    for (i = 0; i < 8; i++) {
        NIX_DI = SET_Nixie(Show_index, i); // 高电平
        // 移位 0 -> 1
        NIX_SCK = 0;
        NOP2();
        NIX_SCK = 1;
        NOP2();
    }

    // 锁存 0 -> 1
    NIX_RCK = 0;
    NOP2();
    NIX_RCK = 1;
    NOP2();
}





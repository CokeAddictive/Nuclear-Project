#include "nixie_control.h"

// 数码管段码表，共阴极
code char LED_TABLE[12] = {
    // 0    1    2      3    4       5    6     7     8     9    (索引0-9)
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90,
    // .    -                                            (索引20-21)
    0x7F, 0xBF};

void Nixie_Init() {
    HAL_Nixie_Init();
}

static void Delay1ms() { //@24.000MHz
    unsigned char data i, j;
    i = 32;
    j = 40;
    do {
        while (--j)
            ;
    } while (--i);
}

/**
 * @brief 用8个二进制位控制数码管
 *
 * @param Num_data 显示 0X00
 * @param Show_index 位置 0X00
 */
void Nixie_OrgShow(char Num_data, char Show_index) {
    HAL_Nixie_Original(Num_data, Show_index);
}

/**
 * @brief 拆分数字
 *
 * @param digit 拆分后存储的数组
 * @param num 被拆分的数字
 * @return int 返回数字一共有多少位
 */
static char split(char *digit, unsigned int num) {
    int i = 0;
    while (num != 0) {
        digit[i] = num % 10;
        num = num / 10;
        i++;
    }
    return i;
}

void Nixie_Show(char Num_data, char index, PointState DP_State) {
    // 检查数字范围(0-9)和位置下标0-7
    if ((Num_data < 0 || Num_data > 9) || (index < 0 || index > 8)) {
        return;
    }
    if (DP_State != 1 && DP_State != 0) {
        return; // 确保小数点状态有效
    }
    if (DP_State == 1) {
        HAL_Nixie_Original(LED_TABLE[Num_data] & LED_TABLE[10], 0x1 << index);
    } else {
        HAL_Nixie_Original(LED_TABLE[Num_data], 0x1 << index);
    }
}


/**
 * @brief 数码管直接显示数字，并且不显示小数点
 * 
 * @param num 需要被显示的数字0-65535 
 */
void Nixie_NumShow(unsigned int num) {
    char digit[8] = {0}; // 用于存储数字的每一位
    char i = 0;
    char cnt = split(digit, num); // 用于存储数字位数

    // 处理0的特殊情况
    if (num == 0) {
        Nixie_Show(0, 0, NO);
        return; // 直接返回，避免后续处理
    }

    for (i = 0; i < cnt; i++) {
        Nixie_Show(digit[cnt - 1 - i], i, NO); // cnt-1-i获取正序数字
        Delay1ms();
        Delay1ms();
    }
}

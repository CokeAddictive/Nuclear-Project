#ifndef NIXIE_CONTROL_H
#define NIXIE_CONTROL_H

#include "hal_nixie.h"
#include "RTX51TNY.H"

typedef enum {
    NO = 0,  // 小数点不显示
    YES = 1    // 小数点显示
} PointState;




void Nixie_Init();
void Nixie_OrgShow(char Num_data, char Show_index);
void Nixie_Show(char Num_data, char index, PointState DP_State);
void Nixie_NumShow(unsigned int num);

#endif // NIXIE_CONTROL_H
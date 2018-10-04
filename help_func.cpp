#include "help_func.h"

help_func::help_func()
{

}

float help_func::dw2float(uint16_t* ptr)
{
    float res=0;
    uint8_t* p = (uint8_t*)&res;

    p[0] = ptr[0]&0x00FF;
    p[1] = (ptr[0]>>8)&0x00FF;
    p[2] = ptr[1]&0x00FF;
    p[3] = (ptr[1]>>8)&0x00FF;

    return res;
}

void help_func::float2dw(float value, uint16_t* arr)
{
    uint16_t* p = (uint16_t*)&value;

    arr[0] = p[0];
    arr[1] = p[1];
}

#ifndef HELP_FUNC_H
#define HELP_FUNC_H

#include <QObject>

class help_func
{
public:
    help_func();
    float dw2float(uint16_t* ptr);
    void float2dw(float value, uint16_t* arr);
};

#endif // HELP_FUNC_H

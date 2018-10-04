#ifndef FUNCTIONTEST_H
#define FUNCTIONTEST_H

#include <QObject>
#include "excelconfig.h"
#include "ThPollDevices.h"

class FunctionTest
{
public:
    explicit FunctionTest(ExcelConfig* excel);

private:
    ExcelConfig *exc;
};

#endif // FUNCTIONTEST_H

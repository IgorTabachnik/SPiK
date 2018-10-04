#ifndef OPENSHORTTEST_H
#define OPENSHORTTEST_H
#include <QString>
#include "excelconfig.h"
#include <QFile>
#include <QTextStream>
#include <QList>

extern QString DUTs[52];

typedef struct
{
    QString name;
    QString  mal;
}SigMal;

class OpenShortTest
{

private:
    ExcelConfig *excel;
    bool Pos_neg;
public:
    explicit OpenShortTest(ExcelConfig *excel);
    ~OpenShortTest();
    void AnalyzeMalFunction(uint16_t data, QString* s_mal);
    QString ProcessingResult(uint16_t* data, uint8_t Sel_MKM);


    QList<SigMal>* ParseLogFile(QString pathfile);
    void setPos_NEG(bool p_n);
};
#endif // OPENSHORTTEST_H

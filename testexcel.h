#ifndef TESTEXCEL_H
#define TESTEXCEL_H

#include <QWidget>
#include "excelconfig.h"

namespace Ui {
class TestExcel;
}

class TestExcel : public QWidget
{
    Q_OBJECT

public:
    explicit TestExcel(QWidget *parent = 0);
    ~TestExcel();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::TestExcel *ui;
    ExcelConfig *excel;
};

#endif // TESTEXCEL_H

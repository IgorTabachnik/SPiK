#ifndef ENTERNUMBERLOT_H
#define ENTERNUMBERLOT_H

#include <QDialog>

namespace Ui {
class EnterNumberLot;
}

class EnterNumberLot : public QDialog
{
    Q_OBJECT

public:
    explicit EnterNumberLot(QDialog *parent = 0);
    ~EnterNumberLot();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EnterNumberLot *ui;
};

#endif // ENTERNUMBERLOT_H

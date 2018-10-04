#ifndef DMODBUSSETTINGS_H
#define DMODBUSSETTINGS_H

#include <QDialog>
#include <QMessageBox>
#include "modbus.h"
#include "modbus-private.h"
#include "qextserialenumerator.h"


namespace Ui {
class DModBusSettings;
}

class DModBusSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DModBusSettings(QWidget *parent = 0);
    ~DModBusSettings();
    void releaseSerialModbus(modbus_t* mb);

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::DModBusSettings *ui;
    modbus_t* mb;
    QMessageBox *mes;
signals:
    void sendMessage(const QString s);
};

#endif // DMODBUSSETTINGS_H

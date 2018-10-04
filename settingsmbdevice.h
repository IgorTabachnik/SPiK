#ifndef SETTINGSMBDEVICE_H
#define SETTINGSMBDEVICE_H

#include <QWidget>
#include <QMessageBox>
#include "modbus.h"
#include "modbus-private.h"
#include "qextserialenumerator.h"

namespace Ui {
class SettingsMBDevice;
}

class SettingsMBDevice : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsMBDevice(QWidget *parent = 0);
    ~SettingsMBDevice();
    QString getComPort();




private:
    void FillListOfPorts();

    Ui::SettingsMBDevice *ui;
};

#endif // SETTINGSMBDEVICE_H

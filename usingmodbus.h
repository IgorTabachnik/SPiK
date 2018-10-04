#ifndef USINGMODBUS_H
#define USINGMODBUS_H

#include <QObject>
#include "modbus.h"

class UsingModBus : public QObject
{
    Q_OBJECT
public:
    explicit UsingModBus(QObject *parent = nullptr, modbus_t * m_modbus = nullptr);
    void sendModbusRequest(const int slave, const int func, const int addr, int num,  uint16_t* dest );
signals:

public slots:

private:
    modbus_t * m_modbus;
};

#endif // USINGMODBUS_H

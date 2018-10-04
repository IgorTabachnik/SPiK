#ifndef MODBUS_H
#define MODBUS_H

#include <QObject>

class ModBus : public QObject
{
    Q_OBJECT
public:
    explicit ModBus(QObject *parent = nullptr);
    void sendModbusRequest(const int slave, const int func, const int addr, int num,  uint16_t* dest );
signals:

public slots:

private:
    modbus_t * m_modbus;

};

#endif // MODBUS_H

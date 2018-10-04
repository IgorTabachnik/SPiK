#ifndef THPOLLDEVICES_H
#define THPOLLDEVICES_H

#include <QThread>
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QList>

#include "modbus.h"
#include "modbus-private.h"
#include "qextserialenumerator.h"

typedef enum
{
 SendTabelExcel,
 CheckTabelExcel
}TaskName;

typedef struct
{
    TaskName task_name;
    int tabel_excel;
} Task;

class ThPollDevices : public QThread
{
    Q_OBJECT
public:
    explicit ThPollDevices(modbus_t* m_modbus);
    virtual ~ThPollDevices();
    void run() override;
    bool isRunning();
    void StopWorkerThread();

private:
    modbus_t* m_modbus;
    //QString InputFile;
    //QString OutputFile;
    //QFile input;
    //QFile output;
    bool work;
    int sendModbusRequest(const int slave, const int func, const int addr, int num,  uint16_t* dest );
    int sendTabelFromExcelAndCheck(int Tabel);
signals:
    void resultReady(const QString &s);
    void sendProgressStatus(const int procent);
    void sendMessage(const QString s);
};


#endif // THPOLLDEVICES_H

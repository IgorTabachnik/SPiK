#include "settingsmbdevice.h"
#include "ui_settingsmbdevice.h"

SettingsMBDevice::SettingsMBDevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsMBDevice)
{
    ui->setupUi(this);

    FillListOfPorts();
}

SettingsMBDevice::~SettingsMBDevice()
{
    delete ui;
}

void SettingsMBDevice::FillListOfPorts()
{
    int portIndex=0;
    int i = 0;

    ui->comPortDevice->clear();
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    //ports.append({"COM_test","COM_test","COM_test","COM_test",0,1});
    foreach( QextPortInfo port, ports)
    {
#ifdef Q_OS_WIN
        ui->comPortDevice->addItem( port.friendName );
#else
        ui->serialPort->addItem( port.physName );
        ui->Console->append(port.physName);
#endif
        QString d1 = port.friendName;
        QString name = port.portName.toLatin1().constData();
        ++i;
    }

    if(!ports.isEmpty())
    {
        ui->comPortDevice->setCurrentIndex( portIndex );
    }else
    {
        QMessageBox::information(this,"Информация","Не найден ни один ком порт на данном компьютере");
    }
}


QString SettingsMBDevice::getComPort()
{
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    const int iface = ui->comPortDevice->currentIndex();


    QString port = ports[iface].portName;

    // is it a serial port in the range COM1 .. COM9?
    if ( port.startsWith( "COM" ) )
    {
        // use windows communication device name "\\.\COMn"
        port = "\\\\.\\" + port;
    }

    return port;

}



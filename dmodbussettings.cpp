#include "dmodbussettings.h"
#include "ui_dmodbussettings.h"

DModBusSettings::DModBusSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DModBusSettings)
{
    ui->setupUi(this);


    this->setWindowTitle("Настройки RTU ModBus");

    mes = new QMessageBox();
    mb = NULL;

}

DModBusSettings::~DModBusSettings()
{
    delete ui;
}

void DModBusSettings::on_pushButton_3_clicked()
{
    QString port = ui->Device1->getComPort();
    releaseSerialModbus(mb);
    //port="\\\\.\\COM255";
    QString str = "Try to open port: ";
    QString com = port.mid(port.indexOf("COM"));
    str += com;
    //ui->Console->setText(str);
    mb = modbus_new_rtu(port.toLatin1().constData(),
                              115200,                           //baude rate
                              'N',                              //Parity
                              8,                                //Data bits
                              1);                               //Stop bits
    if( modbus_connect( mb ) == -1 )
    {
       mes->setText("Connection failed Could not connect serial port!");


       releaseSerialModbus(mb);
       mes->show();

    }else{
       emit sendMessage("Соединение установлено! com port:"+com);
       this->close();
    }
}


void DModBusSettings::releaseSerialModbus(modbus_t* mb)
{
  if(mb)
  {
      modbus_close(mb);
      modbus_free(mb);
      mb=NULL;
  }
}

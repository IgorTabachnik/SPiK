#include "serialsettings.h"
#include "ui_serialsettings.h"

SerialSettings::SerialSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialSettings)
{
    ui->setupUi(this);
}

SerialSettings::~SerialSettings()
{
    delete ui;
}

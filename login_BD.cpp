#include "login_BD.h"
#include "ui_login_navigo.h"
#include "mainwindow.h"

login_bd::login_bd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login_bd)
{
    ui->setupUi(this);
    this->setWindowTitle("Login in Navigo");
    ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    mes = new QMessageBox();

    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

    ui->checkBox->setChecked(settings.value(saveCheck,false).toBool());
    ui->lineEdit->setText(settings.value(AddressServerBD,"").toString());
    ui->lineEdit_2->setText(settings.value(NameBD,"").toString());
    ui->lineEdit_3->setText(settings.value(UserNameNavigo,"").toString());
    ui->lineEdit_4->setText(settings.value(Passwd,"").toString());
}

login_bd::~login_bd()
{
    delete ui;
}

void login_bd::on_pushButton_clicked()
{
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={SQL Server};SERVER="+ui->lineEdit->text()+";DATABASE="+ui->lineEdit_2->text()+";");
    db.setUserName(ui->lineEdit_3->text());
    db.setPassword(ui->lineEdit_4->text());

    if(db.open())
    {
        mes->setText("Соединилось");

    }else{
        mes->setText("Соединение НЕ установлено");
    }

    settings.setValue(saveCheck,ui->checkBox->isChecked());
    if(ui->checkBox->isChecked()){
        settings.setValue(AddressServerBD,ui->lineEdit->text());
        settings.setValue(NameBD,ui->lineEdit_2->text());
        settings.setValue(UserNameNavigo,ui->lineEdit_3->text());
        settings.setValue(Passwd,ui->lineEdit_4->text());
    }else{
        settings.setValue(AddressServerBD,"");
        settings.setValue(NameBD,"");
        settings.setValue(UserNameNavigo,"");
        settings.setValue(Passwd,"");
    }
    settings.sync();

    mes->show();
}

#include "dialog_testnavigo.h"
#include "ui_dialog_testnavigo.h"

Dialog_TestNavigo::Dialog_TestNavigo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_TestNavigo)
{
    ui->setupUi(this);


}

Dialog_TestNavigo::~Dialog_TestNavigo()
{
    delete ui;
}

void Dialog_TestNavigo::on_pushButton_clicked()
{
    query_model = new QSqlQueryModel();
    query_model->setQuery("SELECT TOP 10 [MaterialId],[ModifiedBy],[ModifiedOn],[Name],[PrimaryQuantity],[Priority] FROM [NavigoTestODS].[CoreDataModel].[T_Material]");
    ui->tableView->setModel(query_model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();


    if (query_model->lastError().isValid())
        QMessageBox::critical(this,"Error",query_model->lastError().text());
        qDebug() << query_model->lastError();
}

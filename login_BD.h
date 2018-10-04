#ifndef LOGIN_NAVIGO_H
#define LOGIN_NAVIGO_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>

#define AddressServerBD "AddressServerBDNavigo"
#define NameBD "NameBDNavigo"
#define UserNameNavigo "UserNameNavigo"
#define Passwd "PassWDNavigo"
#define saveCheck "saveCheckNavigo"

namespace Ui {
class login_bd;
}

class login_bd : public QWidget
{
    Q_OBJECT

public:
    explicit login_bd(QWidget *parent = 0);
    ~login_bd();

private slots:
    void on_pushButton_clicked();

private:
    Ui::login_bd *ui;
    QSqlDatabase db;
    QMessageBox *mes;
};

#endif // LOGIN_NAVIGO_H

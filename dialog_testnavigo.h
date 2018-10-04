#ifndef DIALOG_TESTNAVIGO_H
#define DIALOG_TESTNAVIGO_H
#include <QMessageBox>
#include <QDialog>
#include <QtSql>

namespace Ui {
class Dialog_TestNavigo;
}

class Dialog_TestNavigo : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_TestNavigo(QWidget *parent = 0);
    ~Dialog_TestNavigo();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_TestNavigo *ui;
    QSqlQueryModel* query_model;
    QMessageBox *mes;
};

#endif // DIALOG_TESTNAVIGO_H

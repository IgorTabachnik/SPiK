#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>

#include <QSettings>
#include "dmodbussettings.h"
#include "login_BD.h"
#include "enternumberlot.h"
#include "dialog_testnavigo.h"
#include "excelconfig.h"
#include "testexcel.h"

/*Defining*/
#define ORGANIZATION_NAME "GS NANOTECH"
#define ORGANIZATION_DOMAIN "http://www.gsnanotech.ru/"
#define APPLICATION_NAME "SPiK"
#define SETTINGS_TRAY "settings/tray"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionModBus_triggered();

    void on_actionTestBDNavigo_triggered();

    void on_actionEnter_Number_Lot_triggered();

    void on_actionTest_BD_Navigo_triggered();

    void on_pushButton_clicked();
    void rcvMesToStatusBar(const QString s);
    void resetStatus( void );

    void on_actionTest_Excel_File_triggered();

private:
    Ui::MainWindow *ui;
    QLabel *m_statusText;
    QWidget *m_statusInd;
    QTimer *m_timer;
    //QSqlTableModel *model;
    QSqlQueryModel *model;
    login_bd* login_BD_navigo;
    EnterNumberLot *enter_num_lot;
    DModBusSettings *dMBSettings;
    TestExcel *test;
};

#endif // MAINWINDOW_H

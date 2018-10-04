#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "functiontest.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("СПиК");
    /* При создании главного окна производим установку начальных параметров
     * из настроек, сохранённых в операционной системе(а точнее в регистрах regedit)
     * */
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    m_statusText = new QLabel;
    m_statusInd = new QWidget;
    m_statusInd->setFixedSize( 16, 16 );
    ui->statusBar->addWidget( m_statusInd );
    ui->statusBar->addWidget( m_statusText, 20 );
    m_timer = new QTimer();

    //enter_num_lot = new EnterNumberLot();
    //enter_num_lot->exec();
    QList<Task>* tasks = new QList<Task>();
    tasks->append({SendTabelExcel,1});
    test = NULL;

    resetStatus();
}

MainWindow::~MainWindow()
{
    if(test!=NULL){
        delete test;
    }
    delete ui;
}

void MainWindow::on_actionModBus_triggered()
{
   dMBSettings = new DModBusSettings(this);

   connect( dMBSettings, SIGNAL( sendMessage( QString ) ),
           this, SLOT( rcvMesToStatusBar( QString ) ) );
   dMBSettings->exec();
}

void MainWindow::on_actionTestBDNavigo_triggered()
{
    login_BD_navigo = new login_bd();
    login_BD_navigo->show();

}

void MainWindow::on_actionEnter_Number_Lot_triggered()
{
    enter_num_lot = new EnterNumberLot();
    enter_num_lot->show();
}

void MainWindow::on_actionTest_BD_Navigo_triggered()
{
    Dialog_TestNavigo(this).exec();
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::rcvMesToStatusBar(const QString s)
{
    m_statusText->setText(s);
    m_statusInd->setStyleSheet( "background: #0b0;" );
    QTimer::singleShot(2000,this,SLOT(resetStatus()));
}

void MainWindow::resetStatus( void )
{
    m_statusText->setText( tr( "Ready" ) );
    m_statusInd->setStyleSheet( "background: #aaa;" );
}


void MainWindow::on_actionTest_Excel_File_triggered()
{
    test = new TestExcel();
    test->show();
}

#include <QMessageBox>
#include <QFile>
#include "excelconfig.h"
#include "mainwindow.h"

ExcelConfig::ExcelConfig(QTableWidget *tableWidget)
{
    this->tableWidget = tableWidget;
    this->excel=NULL;
    this->sheet=NULL;
    this->sheets=NULL;
    this->workbook=NULL;
    this->workbooks=NULL;
    openshortTable = new QList<float>();
    options_fpga = new QList<uint16_t>();
}

ExcelConfig::~ExcelConfig(void)
{
    delete openshortTable;
    delete options_fpga;
    ClearAndClose();
}

void ExcelConfig::OpenFile(QString fileName)
{
    if(excel!=NULL){
        ClearAndClose();
    }
    if(fileName.isEmpty()){
       emit SendMessageError("Error;"+QString("Could not open config file %1").arg(fileName));
        return;
    }
    this->excel = new QAxObject("Excel.Application",0);
    this->workbooks = excel->querySubObject("Workbooks");
    this->workbook = workbooks->querySubObject("Open(const QString&)", fileName);
}

QAxObject* ExcelConfig::GetExcel(void)
{
    return this->excel;
}

QAxObject* ExcelConfig::GetWorkBook(void)
{
    return this->workbook;
}

void ExcelConfig::ClearAndClose(void)
{
    if(sheet!=NULL){
        this->sheet->clear();
        delete sheet;
        this->sheet = NULL;
        delete sheets;
        this->sheets=NULL;
        this->workbook->clear();
        delete workbook;
        this->workbook = NULL;
        this->workbooks->dynamicCall("Close()");
        this->workbooks->clear();
        delete workbooks;
        this->workbooks =NULL;
        this->excel->dynamicCall("Quit()");
        delete excel;
        this->excel=NULL;
    }
}

void ExcelConfig::ExtractOpenShortTabel()
{
    openshortTable->clear();
    ExtractSucces = true;
    this->sheets = workbook->querySubObject("Worksheets");
    this->sheet = sheets->querySubObject("Item(int)",SHEETOPENSHORT);

    this->NSheets = sheets->property("Count").toInt();

    this->usedRange = sheet->querySubObject("UsedRange");
    this->rows = usedRange->querySubObject("Rows");
    this->NRows = rows->property("Count").toInt();

    this->columns = usedRange->querySubObject("Columns");

    this->NCols = columns->property("Count").toInt();


    this->tableWidget->setRowCount(NRows);
    this->tableWidget->setColumnCount(NCols);

    for ( int row = BEGROWOPENSHORT; row < NRows; row++ ){
        for ( int column = BEGCOLOPENSHORT; column < NCols; column++ ){
            QAxObject* cell = sheet->querySubObject("Cells(int,int)", row + 1, column + 1);
            QVariant value = cell->property("Value");
            bool ok=false;
            float L = value.toFloat(&ok);
            if(ok){
                openshortTable->append(L);

            }else{
                emit SendMessageError("Error;"+QString("Could not conver \" %1 \" to float").arg(value.toString()));
                ExtractSucces=false;
                return;
            }
            QTableWidgetItem* item = new QTableWidgetItem(value.toString());//Построение графической таблицы
            this->tableWidget->setItem(row, column, item);
        }
    }
}

QList<float>* ExcelConfig::getOpenShortTable(void)
{
    if(ExtractSucces){
        return openshortTable;
    }else{
        emit SendMessageError("Error;"+QString("OpenShort tabel is not readable"));
        return 0;
    }
}

void ExcelConfig::ExtractOpenShortTabel_HowTXT(QString fileName)
{
    QFile f(fileName);
    openshortTable->clear();
    ExtractSucces = true;
    if(f.open(QIODevice::ReadOnly))
    {
        QByteArray arr;
        QString s;
        QStringList sl;
        f.readLine();
        int row=0;
        int column=0;
        this->tableWidget->setRowCount(7);
        this->tableWidget->setColumnCount(5);

        while(!f.atEnd())
        {
            arr = f.readLine();
            s = arr.constData();
            sl = s.split("\t");

            //!!!!!!!!!!!!!!!!!!!!!!!!!!! Считывание данных из ячеек!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            bool ok;
            foreach (QString var, sl) {
                float val = var.toFloat(&ok);
                if(ok){
                    openshortTable->append(val);

                    QTableWidgetItem* item = new QTableWidgetItem(var);//Построение графической таблицы
                    this->tableWidget->setItem(row, column, item);
                    //this->tableWidget->item(row,column)->setBackground(Qt::red);
                    column++;
                }
            }
            row++;
            column=0;
        }
    }
    else{
        ExtractSucces = false;
        emit SendMessageError("Error;"+QString("Файл%1 не открывается на чтение!").arg(fileName));
    }
    f.close();
}

bool ExcelConfig::ExtractOptionsFPGA()
{
   /// QFile f(fileName);
    ExtractSucces = true;
    options_fpga = new QList<uint16_t>();
    this->sheets = workbook->querySubObject("Worksheets");
    this->sheet = sheets->querySubObject("Item(int)",SHHETFPGAOPTIONS);

    this->NSheets = sheets->property("Count").toInt();

    this->usedRange = sheet->querySubObject("UsedRange");
    this->rows = usedRange->querySubObject("Rows");
    this->NRows = rows->property("Count").toInt();

    this->columns = usedRange->querySubObject("Columns");

    this->NCols = columns->property("Count").toInt();

    this->sheets = workbook->querySubObject("Worksheets");
    this->sheet = sheets->querySubObject("Item(int)",SHHETFPGAOPTIONS);

    this->NSheets = sheets->property("Count").toInt();

    this->usedRange = sheet->querySubObject("UsedRange");
    this->rows = usedRange->querySubObject("Rows");
    this->NRows = rows->property("Count").toInt();

    this->columns = usedRange->querySubObject("Columns");

    this->NCols = columns->property("Count").toInt();

    this->tableWidget->setRowCount(NRows);
    this->tableWidget->setColumnCount(NCols);
    for ( int row = BEGROWFUNCTESTPARAM; row < NRows; row++ ){

        QAxObject* cell = sheet->querySubObject("Cells(int,int)", row, BEGCOLFUNCTESTPARAM);
        QVariant value = cell->property("Value");
        bool ok=false;
        int L = value.toInt(&ok);
        if(ok){
            options_fpga->append(L);

        }else{
            emit SendMessageError("Error;"+QString("Could not conver \" %1 \" to float").arg(value.toString()));
            ExtractSucces=false;
            return ExtractSucces;
        }
        QTableWidgetItem* item = new QTableWidgetItem(value.toString());//Построение графической таблицы
        this->tableWidget->setItem(row, BEGCOLFUNCTESTPARAM, item);

    }


    return ExtractSucces;

}

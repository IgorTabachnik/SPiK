#ifndef EXCELCONFIG_H
#define EXCELCONFIG_H
#include <QAxObject>
#include <QtWidgets/QTableWidget>
#include <QObject>

/*********************************Tables*********************************************/
//OpenShort
#define SHEETOPENSHORT 1
#define BEGCOLOPENSHORT 1
#define BEGROWOPENSHORT 2

#define SHHETFPGAOPTIONS 2
#define BEGROWFUNCTESTPARAM 2
#define BEGCOLFUNCTESTPARAM 3


class ExcelConfig : public QObject
{
    Q_OBJECT
public:
    explicit ExcelConfig(QTableWidget* table);
    ~ExcelConfig(void);
    void OpenFile(QString fileName);
    void ClearAndClose(void);
    void ExtractOpenShortTabel();
    void ExtractOpenShortTabel_HowTXT(QString filename);
    bool ExtractOptionsFPGA();

    QAxObject* GetWorkBook(void);
    QAxObject* GetExcel(void);
    QList<float>* getOpenShortTable(void);

private:
    QAxObject* excel;
    QAxObject* workbooks;
    QAxObject* workbook;
    QAxObject* sheets;
    QAxObject* sheet;
    int NSheets;
    QAxObject* usedRange;
    QAxObject* rows;
    int NRows;
    QAxObject* columns;
    int NCols;
    bool ExtractSucces;
    QTableWidget *tableWidget;


    QList<float>* volatile  openshortTable;
    QList<uint16_t>* options_fpga;
signals:
    void SendMessageError(QString msg);

};

extern ExcelConfig* config;

#endif // EXCELCONFIG_H

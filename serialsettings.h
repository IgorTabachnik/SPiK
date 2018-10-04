#ifndef SERIALSETTINGS_H
#define SERIALSETTINGS_H

#include <QWidget>

namespace Ui {
class SerialSettings;
}

class SerialSettings : public QWidget
{
    Q_OBJECT

public:
    explicit SerialSettings(QWidget *parent = 0);
    ~SerialSettings();

private:
    Ui::SerialSettings *ui;
};

#endif // SERIALSETTINGS_H

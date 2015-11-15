#ifndef ICALCONNECT_H
#define ICALCONNECT_H

#include <QMainWindow>
#include <QDebug>
#include "filepicker.h"

namespace Ui {
class IcalConnect;
}

class IcalConnect : public QMainWindow
{
    Q_OBJECT

public:
    explicit IcalConnect(QWidget *parent = 0);
    ~IcalConnect();

private:
    Ui::IcalConnect *ui;
    FilePicker fpick;


};

#endif // ICALCONNECT_H

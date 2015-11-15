#include "icalconnect.h"
#include "ui_icalconnect.h"

IcalConnect::IcalConnect(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IcalConnect)
{
    fpick.getFile("https://localhost/test.ics");
    ui->setupUi(this);
}

IcalConnect::~IcalConnect()
{
    delete ui;
}

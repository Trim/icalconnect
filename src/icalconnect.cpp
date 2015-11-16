#include "icalconnect.h"

IcalConnect::IcalConnect(QWidget *parent) :
    QMainWindow(parent),
    //ui(new Ui::IcalConnect)
    winSettings(parent, f)
{
    fpick.getFile("https://localhost/test.ics");
    ui->setupUi(this);

    serverList = winSettings->getServers();
}

IcalConnect::~IcalConnect()
{
    delete ui;
}

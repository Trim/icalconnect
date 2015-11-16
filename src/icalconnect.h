#ifndef ICALCONNECT_H
#define ICALCONNECT_H

#include "ui_icalconnect.h"
#include "serversettings.h"
#include "filepicker.h"

#include <qpushbutton.h>
#include <qsoftmenubar.h>
#include <QMenu>
#include <QMessageBox>
#include <QDebug>

class IcalConnect : public QWidget, public Ui_IcalConnect {
    Q_OBJECT

public:
    explicit IcalConnect(QWidget *parent = 0);
    ~IcalConnect();

private:
    Ui::IcalConnect *ui;
    FilePicker fpick;

    // Import specific variables
    ServerSettings *servSettings;
    QList<IcalServer> servList;
    int totalServer;
    int currentServerImport;

};

Q_DECLARE_METATYPE(IcalServer);

#endif // ICALCONNECT_H

#include "serversettings.h"

ServerSettings::ServerSettings(QWidget *parent, Qt::WFlags f) :
    QWidget(parent, f),
    _editServer(parent, f)
{
    setupUi(this);
    qRegisterMetaType<IcalServer>("IcalServer");

    _settings = new QSettings("Trolltech", "Getcal");
    _serverMap = new QMap<QString,IcalServer>();

    readServerSettings();

    QMenu *menu = QSoftMenuBar::menuFor(this);
    menu->addAction("Add a new server", _editServer, SLOT(addServer()));
    QSoftMenuBar::setHelpEnabled(this,true);
    QSoftMenuBar::setInputMethodEnabled (this, false);

    QAction * editAction = menu->addAction("Edit this server", this, SLOT(editServer()));
    menu->insertSeparator(editAction);
    menu->addAction("Delete this server", this, SLOT(deleteServer()));

    QObject::connect(this, SIGNAL(editClickedServer(IcalServer *)), _editServer, SLOT(editServer(IcalServer*)));
    QObject::connect(_editServer, SIGNAL(endEdit(IcalServer*)), this, SLOT(setServer(IcalServer*)));
}

ServerSettings::~ServerSettings(){
    delete this;
}

void ServerSettings::editServer(){
    QListWidgetItem *serverItem = uiServerList->currentItem();
    QString serverName = serverItem->text();
    IcalServer server = _serverMap->value(serverName);
    emit editClickedServer(&server);
}

void ServerSettings::deleteServer(){
    QListWidgetItem *serverItem = uiServerList->currentItem();
    QString serverName = serverItem->text();

    delete serverItem;
    _serverMap->remove(serverName);

    _settings->beginGroup(SETTINGS_SERVER_GRP);
    _settings->remove(serverName);
    _settings->endGroup();
}

/* Create widget only when needed */
void ServerSettings::openSettings(){
    if(!isVisible()){
        showMaximized();
    }
}

void ServerSettings::setServer(IcalServer *server){
    _serverMap->insert(server->getServerName(), *server);
    uiServerList->clear();

    foreach(QString srvName, _serverMap->keys()){
        insertServer(srvName);
    }

    saveSettings();
}

/* Save all server settings */
void ServerSettings::saveSettings(){
    _settings->beginGroup(QString(SETTINGS_SERVER_GRP));
        QString srvName;
        for(QMap<QString, IcalServer>::iterator it=_serverMap->begin(); it!=_serverMap->end(); ++it){
            IcalServer& srv = it.value();
            _settings->beginGroup(it.key());
                _settings->setValue("serveraddress", srv.getServerAddress());
                _settings->setValue("username", srv.getUserName());
                _settings->setValue("password", srv.getPassword());
                _settings->setValue("calendars", srv.getCalendars());
            _settings->endGroup();
        }
    _settings->endGroup();
    qDebug()<< "ServerSettings : Settings saved.";
}

/* Read all server from settings */
void ServerSettings::readServerSettings(){
    _settings->beginGroup(QString("servers"));
        QStringList serverNames = _settings->childGroups();
        foreach(QString srvName, serverNames){
            _settings->beginGroup(srvName);
                QString srvAddress=(_settings->value("serveraddress")).toString();
                QString usrName=(_settings->value("username")).toString();
                QString usrPass=(_settings->value("password")).toString();
                QStringList calendars = (_settings->value("calendars")).toStringList();
            _settings->endGroup();

            IcalServer* tmp = new IcalServer(srvName, srvAddress, usrName, usrPass, calendars);
            _serverMap->insert(srvName, *tmp);
            insertServer(srvName);
        }
    _settings->endGroup();
}

void ServerSettings::insertServer(QString srvName){
    QListWidgetItem * srvItem = new QListWidgetItem(srvName, uiServerList);
    QSize * srvSize = new QSize(100,SETTINGS_SERVER_LIST_HEIGHT);
    srvItem->setSizeHint(*srvSize);
}

QList<IcalServer> ServerSettings::getServers(){
    return _serverMap->values();
}

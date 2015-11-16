#ifndef FILEPICKER_H
#define FILEPICKER_H

#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QAuthenticator>

#define MAX_AUTH_ERROR 3

class FilePicker : public QObject
{
    Q_OBJECT

public:
    FilePicker();
    void getFile(QString _url);

signals:
    void needAuthentication(QAuthenticator *_netAuth);
    void sslError(QBool *_bool);

private:
    QNetworkAccessManager *netManager;
    QNetworkRequest netRequest;
    QNetworkReply *netReply;
    int nbAuthError;

private slots:
    void replyReceived(QNetworkReply *_netReply);
    void authenticationRequested(QNetworkReply *_netReply, QAuthenticator *_netAuth);
    void sslErrorReceived(QNetworkReply *_netReply, const QList<QSslError> & _Errors);
    void replyInError(QNetworkReply::NetworkError _error);
};

#endif // FILEPICKER_H

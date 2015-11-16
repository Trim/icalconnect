#include "filepicker.h"

FilePicker::FilePicker()
{
    netManager = new QNetworkAccessManager();

    connect(netManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyReceived(QNetworkReply*)));
    connect(netManager, SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)),
            this, SLOT(authenticationRequested(QNetworkReply*, QAuthenticator*)));
}

// Begin connection
void FilePicker::getFile(QString _url){
    netRequest = QNetworkRequest(QUrl(_url));
    netRequest.setRawHeader("User-Agent", "IcalConnect 1.0");

    netReply = netManager->get(netRequest);
    connect(netReply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(replyInError(QNetworkReply::NetworkError)));
}

// Reply finished handler
void FilePicker::replyReceived(QNetworkReply* _netReply){
    netReply = _netReply;

    qDebug() << _netReply->readAll();
}

// Reply is in error
void FilePicker::replyInError(QNetworkReply::NetworkError _error){
    QString debug;

    switch(_error){
    case QNetworkReply::ConnectionRefusedError:
        debug = "The server refused your request.";
        break;
    case QNetworkReply::HostNotFoundError:
        debug = "The host was not found: the URL is mistipped or the current DNS doesn't know this host.";
        break;
    case QNetworkReply::TimeoutError:
        debug = "The remote server didn't response enough fast.";
        break;
    default:
        debug = "Unknown error for IcalConnect";
    }

    qDebug() << "A network error was received: [" << _error << "]: " << debug;

    return;
}

// Authentication request handler
void FilePicker::authenticationRequested(QNetworkReply *_netReply, QAuthenticator *_netAuth){
    netReply = _netReply;

    qDebug() << "Retry : " << nbAuthError;
    qDebug() << _netReply->readAll();

    if(nbAuthError < 3){
        //emit needAuthentication(_netAuth);
        _netAuth->setUser("adrien");
        _netAuth->setPassword("dorsaz");
    }else{
        //emit authenticationFailed();
        qDebug() << "Too many authentication errors." ;
    }

    nbAuthError++;
}

// SSL Error handler
void FilePicker::sslErrorReceived(QNetworkReply *_netReply, const QList<QSslError> & _Errors){
    qDebug() << _Errors.count() << " SSL Error received !";

    // void QNetworkReply::ignoreSslErrors ()

    //while(_Errors.count()>0){
    //qDebug() << _Errors.indexOf(_Errors.first()); //_Errors.first().errorString();
    //_Errors.removeFirst();
    //}
}

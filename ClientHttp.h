#ifndef CLIENTHTTP_H
#define CLIENTHTTP_H

#include <QString>
#include <QFile>
#include <QtNetwork>
#include <QNetworkReply>

class ClientHttp : public QObject
{
    Q_OBJECT
public:
    ClientHttp();
    //~ClientHttp();
    void CommunicationChannel();
    void SetServer(QString m_sServerUrl);
    void SetUser(QString m_sUser, QString m_sPass);
    void SetUrl(QString m_sSiteUrl);
    QString GetUrl(QString m_sValPath);
    //QFile GetFile();
    QString str;
    void PostFile(QString m_sUrl, QString m_sFileName);
    bool IsOk();
    QString ErrorDescription(QNetworkReply::NetworkError m_sErr);


private:
    QString m_sUrlServer;
    QString m_sUserName;
    QString m_sPasswordUser;
    QString m_sFileNameCom;
    QString m_sUrlSite;
    bool m_bVal;
    QNetworkAccessManager *m_oNetworkManager;
    QNetworkReply *m_oReply;
};

#endif // CLIENTHTTP_H

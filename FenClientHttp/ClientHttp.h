#ifndef CLIENTHTTP_H
#define CLIENTHTTP_H

#include <QString>
#include <QFile>
#include <QtNetwork>
#include <QNetworkReply>
#include "FileHash.h"
#include <QDir>

class ClientHttp : public QObject
{
    Q_OBJECT
public:
    ClientHttp();
    //~ClientHttp();
    void ConnectServer();
    void CommunicationChannel();
    void UploadFileToServer();
    void DownloadData();
    void SetServer(QString m_sServerUrl);
    void SetUser(QString m_sUser, QString m_sPass);
    void SetUrl(QString m_sSiteUrl);
    void SetUserName(QString m_sNameUser);
    void SetUserPassword(QString m_sPasswordUser);
    void SetFileName(QString m_sNameFile);
    QString GetUrl(QString m_sValPath);
    //QFile GetFile();
    QString str;
    void PostFile(QString m_sUrl, QString m_sFileName);
    void DataRetrieve(QNetworkReply *m_oReplyVal);
    bool IsOk();
    QString ErrorDescription(QNetworkReply::NetworkError m_sErr);
    FileHash m_oHashMD5;
    void ReadFileDir(QString m_sDirPath);

    QByteArray body(QNetworkReply *m_oReplyResult);
    QByteArray Get(QString point);
    QByteArray Post(QString point, QByteArray to_post);
    QString getMimeType(QString extension) const;

private:
    QString m_sUrlServer;
    QString m_sUserName;
    QString m_sUserPassword;
    QString m_sFileNameCom;
    QString m_sUrlSite;
    bool m_bVal;
    QNetworkAccessManager *m_oNetworkManager;
    QNetworkReply *m_oReply;
};

#endif // CLIENTHTTP_H

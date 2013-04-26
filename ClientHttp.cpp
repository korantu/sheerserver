#include "ClientHttp.h"

ClientHttp::ClientHttp()
{
}

void ClientHttp::CommunicationChannel()
{
    m_oNetworkManager = new QNetworkAccessManager(this);
    QUrl m_oUrl(m_sUrlSite);

    m_oReply = m_oNetworkManager->get(QNetworkRequest(m_oUrl));
    QEventLoop loop;
    connect(m_oReply, SIGNAL(readyRead()), &loop, SLOT(quit()));
    loop.exec();

    if(m_oReply){
        m_bVal = true;
        if(m_oReply->error() == QNetworkReply::NoError) //If there is no error
        {
            qDebug() << "Received Network Reply\n";
            QByteArray m_oData = m_oReply->readAll();
            str = m_oData;
            qDebug() << m_oData;
        }else //there is an error
        {
            m_bVal = false;
            ErrorDescription(m_oReply->error());
        }
        m_oReply->deleteLater();
    }
}

QString ClientHttp::ErrorDescription(QNetworkReply::NetworkError m_sErr)
{
    m_bVal = false;
    QString m_sResult;
    switch(m_sErr)
    {
        case QNetworkReply::NoError:
            qDebug() << "No Error";
            m_sResult = "No Error";
            break;
        case QNetworkReply::ConnectionRefusedError:
            qDebug() << "The connection is not allowed";
            m_sResult = "The connection is not allowed";
            break;
        case QNetworkReply::HostNotFoundError:
            qDebug() << "The Host is not Found";
            m_sResult = "The Host is not Found";
            break;
        case QNetworkReply::TimeoutError:
            qDebug() << "Connection Time Out";
            m_sResult = "Connection Time Out";
            break;
        case QNetworkReply::RemoteHostClosedError:
            qDebug() << "The remote Host is closed";
            m_sResult = "The remote Host is closed";
            break;
        default:
            qDebug() << "There is an error"+m_sErr;
            m_sResult = "There is an error"+m_sErr;
    }
    return m_sResult;
}

QString ClientHttp::GetUrl(QString m_sValPath)
{
    return m_sUrlServer+"/"+m_sValPath;
}

/*QFile ClientHttp::GetFile()
{
    QFile m_oFile(m_sFileNameCom);
    return m_oFile;
}*/

void ClientHttp::SetServer(QString m_sServerUrl)
{
    m_sUrlServer = m_sServerUrl;
}

void ClientHttp::SetUser(QString m_sUser, QString m_sPass)
{
    m_sUserName = m_sUser;
    m_sPasswordUser = m_sPass;
}

bool ClientHttp::IsOk()
{
    return m_bVal;
}

void ClientHttp::SetUrl(QString m_sSiteUrl)
{
    m_sUrlSite = m_sSiteUrl;
}


#include "ClientHttp.h"

ClientHttp::ClientHttp()
{
}

//To connect to the server and post data(username, Password) and file
void ClientHttp::ConnectServer()
{    
    m_oNetworkManager = new QNetworkAccessManager(this);
    QUrl m_oUrl(m_sUrlServer);

    QString bound="margin";
    QByteArray m_bDataToSend(QString("--" + bound + "\r\n").toUtf8());

    m_bDataToSend.append("--" + bound + "--\r\n");

    QNetworkRequest m_oRequest = QNetworkRequest(m_oUrl);
    m_oRequest.setRawHeader("User", m_sUserName.toUtf8());
    m_oRequest.setRawHeader("Password", m_sUserPassword.toUtf8());
    m_oRequest.setRawHeader(QString("Content-Type").toUtf8(),QString("multipart/form-data; boundary=" + bound).toUtf8());
    m_oRequest.setRawHeader(QString("Content-Lenght").toUtf8(), QString::number(m_bDataToSend.length()).toUtf8());

    QEventLoop loop;
    m_oReply = m_oNetworkManager->post(m_oRequest, m_bDataToSend);
    connect(m_oNetworkManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    loop.exec();

    DataRetrieve(m_oReply);
}

// Connect to the server and get a response
void ClientHttp::CommunicationChannel()
{
    m_oNetworkManager = new QNetworkAccessManager(this);
    QUrl m_oUrl(m_sUrlSite);

    m_oReply = m_oNetworkManager->get(QNetworkRequest(m_oUrl));
    QEventLoop loop;
    connect(m_oReply, SIGNAL(readyRead()), &loop, SLOT(quit()));
    loop.exec();

    DataRetrieve(m_oReply);
}

void ClientHttp::UploadFileToServer()
{
    //Here the Hash Code Calculate
    QString m_sResValCryptoMD5;
    m_oHashMD5.SetInFile(m_sFileNameCom);
    m_oHashMD5.SetOutFile("C:/Data/OutFile");
    m_oHashMD5.CalculateCryptoMD5();


    m_oNetworkManager = new QNetworkAccessManager(this);
    QUrl m_oUrl(m_sUrlServer);

    QString bound="margin";
    QByteArray m_bDataToSend(QString("--" + bound + "\r\n").toUtf8());

    //file to upload
    QFile m_oMyFile(m_sFileNameCom);
    if(!m_oMyFile.open(QIODevice::ReadOnly))
    {
        return;
    }
    m_bDataToSend.append(m_oMyFile.readAll());
    m_bDataToSend.append("--" + bound + "--\r\n");

    QNetworkRequest m_oRequest = QNetworkRequest(m_oUrl);

    m_oRequest.setRawHeader(QString("Content-Lenght").toUtf8(), QString::number(m_bDataToSend.length()).toUtf8());
    if(m_oHashMD5.IsOk() == true)
    {
        m_sResValCryptoMD5 = m_oHashMD5.GetResCryptoMD5();
        m_oRequest.setRawHeader("MD5", m_sResValCryptoMD5.toUtf8());
    }

    QEventLoop loop;
    m_oReply = m_oNetworkManager->post(m_oRequest, m_bDataToSend);
    connect(m_oNetworkManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    loop.exec();

    DataRetrieve(m_oReply);
}

QString ClientHttp::ErrorDescription(QNetworkReply::NetworkError m_sErr)
{
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

void ClientHttp::DataRetrieve(QNetworkReply *m_oReplyVal)
{
    qDebug() << "Hello" << m_oReplyVal->isFinished() << m_oReplyVal->error() << "\n";
    if(m_oReplyVal){
        m_bVal = true;
        if(m_oReplyVal->error() == QNetworkReply::NoError) //If there is no error
        {
            qDebug() << "Received Network Reply\n";
            qDebug() << "Here is the error: " << ErrorDescription(m_oReplyVal->error()) << "\n";
            QByteArray m_oData = m_oReplyVal->readAll();
            str = m_oData;
            qDebug() << m_oData;
        }else //there is an error
        {
            m_bVal = true;
            qDebug() << "Here is the error: " << ErrorDescription(m_oReplyVal->error()) << "\n";
        }
        m_oReplyVal->deleteLater();
    }else{
        m_bVal = false;
        qDebug() << "Error";
        qDebug() << "Here is the error: " << ErrorDescription(m_oReplyVal->error());
    }
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
    m_sUserPassword = m_sPass;
}

bool ClientHttp::IsOk()
{
    return m_bVal;
}

void ClientHttp::SetUrl(QString m_sSiteUrl)
{
    m_sUrlSite = m_sSiteUrl;
}

void ClientHttp::SetUserName(QString m_sNameUser)
{
    m_sUserName = m_sNameUser;
}

void ClientHttp::SetUserPassword(QString m_sPasswordUser)
{
    m_sUserPassword = m_sPasswordUser;
}

void ClientHttp::SetFileName(QString m_sNameFile)
{
    m_sFileNameCom = m_sNameFile;
}

void ClientHttp::PostFile(QString m_sUrl, QString m_sFileName)
{
    m_sUrlServer = m_sUrl;
    m_sFileNameCom = m_sFileName;
}

void ClientHttp::ReadFileDir(QString m_sDirPath)
{
    QDir m_oDirectory(m_sDirPath);
    if(!m_oDirectory.exists()){
        m_bVal = false;
    }
    else{
        m_bVal = true;
        m_oDirectory.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        m_oDirectory.setSorting(QDir::Size | QDir::Reversed);

        QFileInfoList m_oFileInfoList = m_oDirectory.entryInfoList();

        for(int i = 0; i < m_oFileInfoList.size(); ++i){
            QFileInfo m_oFileInfo = m_oFileInfoList.at(i);
            qDebug() << qPrintable(QString("%1 %2").arg(m_oFileInfo.size(), 10 ).arg(m_oFileInfo.fileName()));
            qDebug() << "\n";
        }
    }
}

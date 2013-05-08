#include "ClientHttp.h"

ClientHttp::ClientHttp()
{
}

//To connect to the server and post data(username, Password)
void ClientHttp::ConnectServer()
{    
    m_oNetworkManager = new QNetworkAccessManager(this);
    QUrl m_oUrl(m_sUrlServer);//Server Url

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
    QUrl m_oUrl(m_sUrlSite); //Url of the site

    m_oReply = m_oNetworkManager->get(QNetworkRequest(m_oUrl));
    QEventLoop loop;
    connect(m_oReply, SIGNAL(readyRead()), &loop, SLOT(quit()));
    loop.exec();

    DataRetrieve(m_oReply);
}

//Upload a file to the server with post
void ClientHttp::UploadFileToServer()
{
    //Here the Hash Code Calculate
    QString m_sResValCryptoMD5;
    m_oHashMD5.SetInFile(m_sFileNameCom);
    m_oHashMD5.SetOutFile("C:/Data/OutFile");
    m_oHashMD5.CalculateCryptoMD5();


    m_oNetworkManager = new QNetworkAccessManager(this);
    QUrl m_oUrl(m_sUrlServer); //the Server URL

    QString bound="margin";
    QByteArray m_bDataToSend(QString("--" + bound + "\r\n").toUtf8());

    //file to upload with the other data
    QFile m_oMyFile(m_sFileNameCom);
    if(!m_oMyFile.open(QIODevice::ReadOnly))
    {
        return;
    }
    m_bDataToSend.append(m_oMyFile.readAll());
    m_bDataToSend.append("--" + bound + "--\r\n");

    //file to post
    QFile *file = new QFile(m_sFileNameCom);
    file->open(QIODevice::ReadOnly);

    QNetworkRequest m_oRequest = QNetworkRequest(m_oUrl);
    m_oRequest.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));

    m_oRequest.setRawHeader(QString("Content-Lenght").toUtf8(), QString::number(m_bDataToSend.length()).toUtf8());
    if(m_oHashMD5.IsOk() == true)
    {
        m_sResValCryptoMD5 = m_oHashMD5.GetResCryptoMD5();
        m_oRequest.setRawHeader("MD5", m_sResValCryptoMD5.toUtf8());
        m_oRequest.setRawHeader("FileName",m_sFileNameCom.toUtf8());
    }

    QEventLoop loop;
    m_oReply = m_oNetworkManager->post(m_oRequest, file);
    //connect(m_oNetworkManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    connect(m_oReply, SIGNAL(uploadProgress(qint64, qint64)), SLOT(uploadProgress(qint64, qint64)));
    connect(m_oReply, SIGNAL(finished()), this, SLOT(responseUpload()));
    loop.exec();

    //DataRetrieve(m_oReply);
}

//Function to describe some errors retrieved
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

//Function to manage data retrieve from the reply after get/post request
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

//return the URL of a given path
QString ClientHttp::GetUrl(QString m_sValPath)
{
    return m_sUrlServer+"/"+m_sValPath;
}

/*QFile ClientHttp::GetFile()
{
    QFile m_oFile(m_sFileNameCom);
    return m_oFile;
}*/

//define the URL of the server
void ClientHttp::SetServer(QString m_sServerUrl)
{
    m_sUrlServer = m_sServerUrl;
}

//define a User by his name and his password
void ClientHttp::SetUser(QString m_sUser, QString m_sPass)
{
    m_sUserName = m_sUser;
    m_sUserPassword = m_sPass;
}

//return True when it is ok
bool ClientHttp::IsOk()
{
    return m_bVal;
}

//define the URL of a given site
void ClientHttp::SetUrl(QString m_sSiteUrl)
{
    m_sUrlSite = m_sSiteUrl;
}

//define the name of an user
void ClientHttp::SetUserName(QString m_sNameUser)
{
    m_sUserName = m_sNameUser;
}

//define the password of an user
void ClientHttp::SetUserPassword(QString m_sPasswordUser)
{
    m_sUserPassword = m_sPasswordUser;
}

//define the name of a file
void ClientHttp::SetFileName(QString m_sNameFile)
{
    m_sFileNameCom = m_sNameFile;
}

//define the Url and the name of a file
void ClientHttp::PostFile(QString m_sUrl, QString m_sFileName)
{
    m_sUrlServer = m_sUrl;
    m_sFileNameCom = m_sFileName;
}

//list all file of a folder
void ClientHttp::ReadFileDir(QString m_sDirPath)
{
    QDir m_oDirectory(m_sDirPath);
    if(!m_oDirectory.exists()){ //if the directory doesn't exists
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

QByteArray ClientHttp::body(QNetworkReply *m_oReplyResult)
{
    QByteArray data = m_oReplyResult->readAll();
    qDebug() << ErrorDescription(m_oReplyResult->error());
    m_oReplyResult->deleteLater();

    return data;
}

QByteArray ClientHttp::Get(QString point)
{
    QNetworkReply *m_Resp = m_oNetworkManager->get(QNetworkRequest(QUrl("http://localhost:8080/" + point)));
    qDebug() << ErrorDescription(m_Resp->   error());
    return body(m_Resp);
}

//return the content type of the request http
QString ClientHttp::getMimeType(QString extension) const
{
    //texte
    if (extension == QString("txt"))			return QString("text/plain");
    if (extension == QString("htm") || extension == QString("html"))	return QString("text/html");
    if (extension == QString("css"))			return QString("text/css");
    //Images
    if (extension == QString("png"))			return QString("image/png");
    if (extension == QString("gif"))			return QString("image/gif");
    if (extension == QString("jpg") || extension == QString("jpeg"))	return QString("image/jpeg");
    if (extension == QString("bmp"))			return QString("image/bmp");
    if (extension == QString("tif"))			return QString("image/tiff");
    //Archives
    if (extension == QString("bz2"))			return QString("application/x-bzip");
    if (extension == QString("gz"))			return QString("application/x-gzip");
    if (extension == QString("tar") )			return QString("application/x-tar");
    if (extension == QString("zip") )			return QString("application/zip");
    //Audio
    if ( extension == QString("aif") || extension == QString("aiff"))	return QString("audio/aiff");
    if ( extension == QString("mid") || extension == QString("midi"))	return QString("audio/mid");
    if ( extension == QString("mp3"))			return QString("audio/mpeg");
    if ( extension == QString("ogg"))			return QString("audio/ogg");
    if ( extension == QString("wav"))			return QString("audio/wav");
    if ( extension == QString("wma"))			return QString("audio/x-ms-wma");
    //Video
    if ( extension == QString("asf") || extension == QString("asx"))	return QString("video/x-ms-asf");
    if ( extension == QString("avi"))			return QString("video/avi");
    if ( extension == QString("mpg") || extension == QString("mpeg"))	return QString("video/mpeg");
    if ( extension == QString("wmv"))			return QString("video/x-ms-wmv");
    if ( extension == QString("wmx"))			return QString("video/x-ms-wmx");
    //XML
    if ( extension == QString("xml"))			return QString("text/xml");
    if ( extension == QString("xsl"))			return QString("text/xsl");
    //Microsoft
    if ( extension == QString("doc") || extension == QString("rtf"))	return QString("application/msword");
    if ( extension == QString("xls"))			return QString("application/excel");
    if ( extension == QString("ppt") || extension == QString("pps"))	return QString("application/vnd.ms-powerpoint");
    //Adobe
    if ( extension == QString("pdf"))			return QString("application/pdf");
    if ( extension == QString("ai") || extension == QString("eps"))	return QString("application/postscript");
    if ( extension == QString("psd"))			return QString("image/psd");
    //Macromedia
    if ( extension == QString("swf"))			return QString("application/x-shockwave-flash");
    //Real
    if ( extension == QString("ra"))			return QString("audio/vnd.rn-realaudio");
    if ( extension == QString("ram"))			return QString("audio/x-pn-realaudio");
    if ( extension == QString("rm"))			return QString("application/vnd.rn-realmedia");
    if ( extension == QString("rv"))			return QString("video/vnd.rn-realvideo");
    //Other
    if ( extension == QString("exe"))			return QString("application/x-msdownload");
    if ( extension == QString("pls"))			return QString("audio/scpls");
    if ( extension == QString("m3u"))			return QString("audio/x-mpegurl");

    return QString("text/plain"); // default
}

//slot when a file is uploaded to a server
void ClientHttp::responseUpload()
{
    DataRetrieve(m_oReply);
}

//slot when a file is downloaded from a server
void ClientHttp::responseDownload()
{
    FileRetrieve("C:/Data",m_oReply);
}

//slot to check the upload progress
void ClientHttp::uploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    qDebug() << "Uploaded" << bytesSent << "of" << bytesTotal;
}

//slot to check the download progress
void ClientHttp::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug() << "Downloaded " << bytesReceived << " of " << bytesTotal;
}

//slot when a file is downloaded
void ClientHttp::DownloadData()
{
    m_oNetworkManager = new QNetworkAccessManager(this);
    QUrl m_oUrl(m_sUrlSite);

    m_oReply = m_oNetworkManager->get(QNetworkRequest(m_oUrl));
    QEventLoop loop;
    connect(m_oReply, SIGNAL(downloadProgress(qint64, qint64)), SLOT(downloadProgress(qint64, qint64)));
    //connect(m_oReply, SIGNAL(finished()), &loop, SLOT(quit()));
    connect(m_oReply, SIGNAL(finished()), SLOT(responseDownload()));
    loop.exec();

    //FileRetrieve("C:/Data", m_oReply);
}

//function to manage the file downloaded
void ClientHttp::FileRetrieve(QString m_sFileNamePath, QNetworkReply *m_oResponse)
{
    qDebug() << "Hello" << m_oResponse->isFinished() << m_oResponse->error() << "\n";
    if(m_oResponse){
        if(m_oResponse->error() == QNetworkReply::NoError) //If there is no error
        {
            m_bVal = true;
            QUrl m_oUrl(m_sUrlSite);
            qDebug() << "Received Network Reply\n";
            qDebug() << "Here is the error: " << ErrorDescription(m_oResponse->error()) << "\n";
            QFileInfo m_oFileInfo = m_oUrl.path();
            QFile m_oFile(m_sFileNamePath+"/"+m_oFileInfo.fileName());
            m_oFile.open(QIODevice::WriteOnly);
            m_oFile.write(m_oResponse->readAll());
            qDebug() << "File Name : " << m_oFileInfo.fileName();
        }else {

            m_bVal = true;
            qDebug() << "Here is the error: " << ErrorDescription(m_oResponse->error()) << "\n";
        }
        m_oResponse->deleteLater();
    }else{
        m_bVal = false;
        qDebug() << "Error";
        qDebug() << "Here is the error: " << ErrorDescription(m_oResponse->error());
    }
}

#include "FileHash.h"


FileHash::FileHash()
{
}

/*Calculate the Hash code Md5 of the Infile and fill the result in the Outfile*/
void FileHash::CalculateCryptoMD5()
{
    QCryptographicHash m_oCryptoMD5(QCryptographicHash::Md5);

    QFile m_oInFile(m_sInFile);
    QFile m_oOutFile(m_sOutFile);

    bool m_bValue = false;

    if(m_oInFile.exists() == true){ //If Infile exists
        QString m_sErrMsg;
        QFileDevice::FileError m_oErrFile = QFileDevice::NoError;
        if(m_oInFile.open(QIODevice::ReadOnly) == true){//If Infile is opened
            while(!m_oInFile.atEnd()){
                m_oCryptoMD5.addData(m_oInFile.read(8192));
            }
            m_oInFile.close();
            QByteArray m_oHashMD5 = m_oCryptoMD5.result();
            if(m_oOutFile.exists() == true){ //If Outfile exists
                m_oOutFile.open(QIODevice::WriteOnly);//If the file doesn't exist it will be created
                QTextStream m_oWriteFile(&m_oOutFile);
                m_oWriteFile << m_oHashMD5.toHex() << "\n";
				m_sResCryptoMD5 = QString(m_oHashMD5.toHex());
                m_bIsOk = true;
                m_oOutFile.close();
            }
        } else //if Infile can't be opened
        {
            SetError(m_oInFile.errorString());
            m_sErrMsg = m_oInFile.errorString();
            m_oErrFile = m_oInFile.error();
            GetErr(m_sErrMsg,m_oErrFile);
        }

    }else{//if the Infile not exists
        IsFileExists(m_bValue,m_sInFile);
    }
}

/*Set the name of the Infile*/
void FileHash::SetInFile(QString m_sInFileName)
{
    m_sInFile = m_sInFileName;
}

/*Set the name of the Outfile*/
void FileHash::SetOutFile(QString m_sOutFileName)
{
    m_sOutFile = m_sOutFileName;
}

/*Test of the existing file*/
void FileHash::IsFileExists(bool m_bVal, QString m_sFileName)
{
    if(m_bVal == false)
        qDebug() << "File "+m_sFileName+" not exists" <<"\n";
}

/*Manage erreurs on file opening*/
void FileHash::GetErr(QString m_sErrString, QFileDevice::FileError m_oFileErr)
{
    qDebug() << m_sErrString << m_oFileErr;
}

bool FileHash::IsOk()
{
    return m_bIsOk;
}

QString FileHash::ErrorCause()
{
    return m_sError;
}

void FileHash::SetError(QString err){
        m_bIsOk = false;
        m_sError = err;
}

QString FileHash::GetResCryptoMD5()
{
    return m_sResCryptoMD5;
}

void FileHash::SetResCryptoMD5(QString m_sValResCrytoMD5)
{
    m_sResCryptoMD5 = m_sValResCrytoMD5;
}

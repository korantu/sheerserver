#ifndef FILEHASH_H
#define FILEHASH_H

#include "FileHash_global.h"
#include <QCryptographicHash>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>

class FILEHASHSHARED_EXPORT FileHash
{
public:
    FileHash();
    void CalculateCryptoMD5();
    void SetInFile(QString m_sInFileName);
    void SetOutFile(QString m_sOutFileName);
    void IsFileExists(bool m_bVal, QString m_sFileName);
    bool IsOk();
    QString ErrorCause();
    void GetErr(QString m_sErrString,QFileDevice::FileError m_oFileErr);
    QString GetResCryptoMD5();
    void SetResCryptoMD5(QString m_sValResCrytoMD5);

private:
    void SetError(QString);
    bool m_bIsOk;
    QString m_sError;
    QString m_sInFile;
    QString m_sOutFile;
	QString m_sResCryptoMD5;
};

#endif // FILEHASH_H

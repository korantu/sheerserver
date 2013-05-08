#ifndef SHEERCLOUD_H
#define SHEERCLOUD_H

#include <QString>

class SheerCloud
{
public:
    SheerCloud();
    bool Authorize(QString location, QString login, QString password);
    bool Upload(QString, const QByteArray &);
    bool Download(QString, QByteArray & out);

    QString lastError();

private:
    QString m_location;
    QString m_login;
    QString m_password;
    QString m_lastError;
};

#endif // SHEERCLOUD_H

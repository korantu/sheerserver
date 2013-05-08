#include "SheerCloud.h"

SheerCloud::SheerCloud()
{
}

bool SheerCloud::Authorize(QString location, QString login, QString password)
{
    m_location = location;
    m_login = login;
    m_password = password;
    return true;
}

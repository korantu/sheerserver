#include "sheer_cloud.h"

// Header
class RealSheerCloud: public SheerCloud {
public:
  RealSheerCloud();
  virtual ~RealSheerCloud();

  virtual bool Authorize( QString location, QString login, QString password);
  virtual bool Upload( QString, const QByteArray &);
  virtual bool Download( QString, QByteArray & out);

  virtual QString lastError();

private:
  QString m_location;
  QString m_login;
  QString m_password;
  QString m_lastError;
};

#include <QDebug>
#include <map>

// Implementation
RealSheerCloud::RealSheerCloud(){
};

RealSheerCloud::~RealSheerCloud(){
};

bool RealSheerCloud::Authorize(QString location, QString login, QString password){
  m_location = location;
  m_login = login;
  m_password = password;
  return true;
};

// Testing
std::map<QString, QByteArray> minicloud;

bool RealSheerCloud::Upload(QString file, const QByteArray & data){
  minicloud[file] = data;
  return true;
};

bool RealSheerCloud::Download( QString file,  QByteArray & out){
  if ( minicloud.find( file) == minicloud.end()) {
    m_lastError = "File not found in the cloud";
    return false;
  };
  out = minicloud[ file];
  return true;
};

QString RealSheerCloud::lastError(){
  return m_lastError;
};


// API object
RealSheerCloud connection;

// API entrance
SheerCloud * GetSheerCloud(){
  return &connection;
};


#include "sheer_cloud.h"

#include <QDebug>
#include <map>

// Header
class RealSheerCloud: public SheerCloud {
public:
  RealSheerCloud();
  virtual ~RealSheerCloud();

  virtual Result Authorize( QString login, QString password);
  virtual Result Upload( QString, QByteArray);
  virtual Result Download( QString, QByteArray & out);

private:
  QString m_login;
  QString m_password;
};

// Local tools
void Log(QString msg){
  qDebug() << "[" << msg << "]\n";
}

// Implementation
RealSheerCloud::RealSheerCloud(){
};

RealSheerCloud::~RealSheerCloud(){
};

SheerCloud::Result RealSheerCloud::Authorize(QString login, QString password){
  m_login = login;
  m_password = password;
  Log("we are in");
  return OK;
};

// Testing
std::map<QString, QByteArray> minicloud;

SheerCloud::Result RealSheerCloud::Upload(QString file, QByteArray data){
  minicloud[file] = data;
  return OK;
};

SheerCloud::Result RealSheerCloud::Download( QString file,  QByteArray & out){
  out = minicloud[ file];
  return OK;
};

// API object
RealSheerCloud connection;

// API entrance
SheerCloud * GetSheerCloud(){
  return &connection;
};


#include "sheer_cloud.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
//#include <QtNetwork/QUrl>
// Header
class SheerCloudHttp: public SheerCloud {
public:
  SheerCloudHttp();
  virtual ~SheerCloudHttp();

  virtual bool Authorize( QString location, QString login, QString password);
  virtual bool Upload( QString, const QByteArray &);
  virtual bool Download( QString, QByteArray & out);

  virtual QString lastError();

private:
  QString m_location;
  QString m_login;
  QString m_password;
  QString m_lastError;

  QNetworkAccessManager m_network;
  QNetworkReply * m_reply;				 

private slots:
  void finish(QNetworkReply * m_reply);
};

#include <QDebug>
#include <map>

// Implementation
SheerCloudHttp::SheerCloudHttp(){
  m_reply = NULL;
};

SheerCloudHttp::~SheerCloudHttp(){
};

void SheerCloudHttp::finish(QNetworkReply * reply){
  m_reply = reply;
}

bool SheerCloudHttp::Authorize(QString location, QString login, QString password){
  m_location = location;
  m_login = login;
  m_password = password;

  QNetworkRequest req( QUrl( location + "/authorize?login=" + m_login + "&password=" + m_password ));
  m_network.get( req);
  while( ! m_reply ) {
  };
  qDebug() << m_reply->readAll();
  
  return true;
};

// Testing
std::map<QString, QByteArray> minicloud_tmp;

bool SheerCloudHttp::Upload(QString file, const QByteArray & data){
  minicloud_tmp[file] = data;
  return true;
};

bool SheerCloudHttp::Download( QString file,  QByteArray & out){
  if ( minicloud_tmp.find( file) == minicloud_tmp.end()) {
    m_lastError = "File not found in the cloud";
    return false;
  };
  out = minicloud_tmp[ file];
  return true;
};

QString SheerCloudHttp::lastError(){
  return m_lastError;
};


// API object
SheerCloudHttp connection_http;

// API entrance
SheerCloud * GetSheerCloudHttp(){
  return &connection_http;
};


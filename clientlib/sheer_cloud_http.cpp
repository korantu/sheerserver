#include "sheer_cloud.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
//#include <QtNetwork/QUrl>
// Header

#include <QTest> // For QSleep

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

  QNetworkAccessManager * m_network;
  QNetworkReply * m_reply;				 

private slots:
  void finish(QNetworkReply * m_reply);
};

#include <QDebug>
#include <map>

// Implementation
SheerCloudHttp::SheerCloudHttp(){
  m_reply = NULL;
  m_network = new QNetworkAccessManager();
  /*  connect( m_network, SIGNAL(finished(QNetworkReply*)),
	  this, SLOT(finished(QNetworkReply*)));
  */
};

SheerCloudHttp::~SheerCloudHttp(){
  delete m_network;
};

void SheerCloudHttp::finish(QNetworkReply * reply){
  m_reply = reply;
  qDebug() << "Got reply!!!";
}

bool SheerCloudHttp::Authorize(QString location, QString login, QString password){
  m_location = location;
  m_login = login;
  m_password = password;

  QString where = location + "/authorize?login=" + m_login + "&password=" + m_password;

  qDebug() << "Attempting to authorize: " << where;

  m_reply = m_network->get( QNetworkRequest( QUrl( where )));

  QTest::qSleep(1000);

  if ( ! m_reply->error() ) {
    qDebug() << "Connection succeeded";
  } else {
    qDebug() << "Connection failed";
  }

  qDebug() << m_reply->readAll();
  
  return m_reply->readAll() == "OK";
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


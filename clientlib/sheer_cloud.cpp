#include "sheer_cloud.h"

#include <QDebug>

SheerCloudLink::SheerCloudLink(QString location, QString login, QString password){
  m_is_authorized = false;

  m_location = location;
  m_login = login;
  m_password = password;
  m_out = NULL;
};

SheerCloudLink::~SheerCloudLink(){
};
  
void SheerCloudLink::Authorize(){
  get( QNetworkRequest( QUrl( m_location + "/authorize?login=" + m_login + "&password=" + m_password ) ));
  connect( this, SIGNAL(finished( QNetworkReply *)), 
	   this, SLOT(login_completed( QNetworkReply *)) );
}

void SheerCloudLink::Upload(QString file, const QByteArray & in){
  QNetworkRequest upload_req( QUrl( m_location + "/upload?login=" + m_login + "&password=" + m_password + "&file=" + file ));
  upload_req.setRawHeader( "content-type", "application/octet-stream");
  post( upload_req, in);
  connect( this, SIGNAL(finished( QNetworkReply *)), 
	   this, SLOT(upload_completed( QNetworkReply *)) );

};

void SheerCloudLink::Download(QString file, QByteArray & out){
  get( QNetworkRequest( QUrl( m_location + "/download?login=" + m_login + "&password=" + m_password + "&file=" + file ) ));
  m_out = &out;
  connect( this, SIGNAL(finished( QNetworkReply *)), 
	   this, SLOT(download_completed( QNetworkReply *)) );
};

void SheerCloudLink::Delete(QString file){
  QNetworkRequest upload_req( QUrl( m_location + "/delete?login=" + m_login + "&password=" + m_password + "&file=" + file ));
  get( upload_req);
  connect( this, SIGNAL(finished( QNetworkReply *)), 
	   this, SLOT(delete_completed( QNetworkReply *)) );

};

bool SheerCloudLink::Authorized(){
  return m_is_authorized;
};

void SheerCloudLink::login_completed( QNetworkReply * reply){
  if( QString(reply->readAll()).contains( "OK" ) ) {
    m_is_authorized = true;
  };
  disconnect( this, SLOT(login_completed( QNetworkReply *)) );
  done();
};

void SheerCloudLink::upload_completed( QNetworkReply * resp){
  QByteArray got = resp->readAll();
  //TODO error reporting
  disconnect( this, SLOT(upload_completed( QNetworkReply *)) );
  done();
};

void SheerCloudLink::download_completed( QNetworkReply * resp){
  QByteArray got = resp->readAll();
  if( m_out != NULL ) {
    *m_out = got;
  };
  disconnect( this, SLOT(download_completed( QNetworkReply *)) );
  done();
};

void SheerCloudLink::delete_completed( QNetworkReply * resp){
  QByteArray got = resp->readAll();
  //TODO error reporting
  disconnect( this, SLOT(upload_completed( QNetworkReply *)) );
  done();
};

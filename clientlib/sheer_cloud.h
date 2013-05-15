#ifndef __cloud_h__
#define __cloud_h__

#include <QString>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>


class SheerCloudLink: public QNetworkAccessManager {
  Q_OBJECT;
 public:
  SheerCloudLink(QString location, QString login, QString password);
  virtual ~SheerCloudLink();
  
  void Authorize();
  bool Authorized();

  void Upload(QString, const QByteArray &);
  void Download(QString, QByteArray &);
  void Delete(QString);

 private:
  QString m_location, m_login, m_password;

  bool m_is_authorized;

  QByteArray * m_out; // Keep track of output

  private slots:
  void login_completed( QNetworkReply *);
  void upload_completed( QNetworkReply *);
  void download_completed( QNetworkReply *);
  void delete_completed( QNetworkReply *);

  signals:
  void done();
};

#endif

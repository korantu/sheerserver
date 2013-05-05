#ifndef __cloud_h__
#define __cloud_h__

#include <QString>
#include <QByteArray>

class SheerCloud {
 public:
  virtual bool Authorize(QString location, QString login, QString password) = 0;
  virtual bool Upload(QString, const QByteArray &) = 0;
  virtual bool Download(QString, QByteArray &) = 0;

  virtual QString lastError() = 0;
};

// Various implementations:
SheerCloud * GetSheerCloudHttp();
SheerCloud * GetSheerCloudStub();
#endif

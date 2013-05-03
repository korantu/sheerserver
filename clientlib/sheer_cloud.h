#ifndef __cloud_h__
#define __cloud_h__

#include <QString>
#include <QByteArray>

class SheerCloud {
 public:
  typedef enum {
    OK,
    FAIL
  } Result;

  virtual Result Authorize(QString login, QString password) = 0;
  virtual Result Upload(QString, QByteArray) = 0;
  virtual Result Download(QString, QByteArray &) = 0;
};

SheerCloud * GetSheerCloud();

#endif

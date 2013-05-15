#ifndef __test_h__
#define __test_h__

#include <sheer_cloud.h>

#include <QtTest/QtTest>

class TestSheerCloud: public QObject {
  Q_OBJECT

  SheerCloudLink link;
  QEventLoop loop;
 
 public:
 TestSheerCloud(): link("http://localhost:8080", "abc", "123") {
    link.connect( &link, SIGNAL(done()), &loop, SLOT(quit()));
  };


    public slots:
  void VerifyTesting();
  void SheerLinkLogin();
  void SheerLinkUploadDownload();
  void SheerLinkUploadDownloadBulk();
  void SheerLinkDelete();
};

#endif //  __test_h__

#ifndef __test_h__
#define __test_h__

#include <sheer_cloud.h>

#include <QtTest/QtTest>

class TestSheerCloudReally: public QObject {
  Q_OBJECT

  SheerCloudLink link;
  QEventLoop loop;
 
 public:
 TestSheerCloudReally(): link("http://localhost:8080", "abc", "123") {
    link.connect( &link, SIGNAL(done()), &loop, SLOT(quit()));
  };


    private slots:
  void VerifyTesting();
  void SheerLinkLogin();
  void SheerLinkUploadDownload();
  void SheerLinkUploadDownloadBulk();
  void SheerLinkDelete();
};

#endif //  __test_h__

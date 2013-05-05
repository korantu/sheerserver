#ifndef __test_h__
#define __test_h__

#include <sheer_cloud.h>

#include <QByteArray>
#include <QtTest/QtTest>

class TestSheerCloud: public QObject {
  Q_OBJECT

  void Basics(SheerCloud * cloud);

    private slots:
  void VerifyTesting();
  void TestStub();
  void TestHttp();
};


#endif //  __test_h__

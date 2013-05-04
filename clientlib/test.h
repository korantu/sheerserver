#ifndef __test_h__
#define __test_h__

#include <sheer_cloud.h>

#include <QByteArray>
#include <QtTest/QtTest>

class TestSheerCloud: public QObject {
  Q_OBJECT
    private slots:
  void VerifyTesting();
  void Basics();
};


#endif //  __test_h__

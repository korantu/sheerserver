#include "test.h"

int counter = 0;
void TestSheerCloud::VerifyTesting() {
  QVERIFY2(2+2==4, "Really");
  QCOMPARE("123", "123");
}

const char * str(QString in){
  return in.toStdString().c_str();
}

void TestSheerCloud::Basics() {
  QByteArray out;
  SheerCloud * cloud = GetSheerCloudStub();

  QVERIFY2(cloud->Authorize("neverland", "big", "boss"), str( cloud->lastError()));
  QVERIFY2(cloud->Upload("file1.txt", "123"), str( cloud->lastError()));
  QVERIFY2(cloud->Download("file2.txt", out), str( cloud->lastError()));
}

QTEST_MAIN(TestSheerCloud)

#include "test.h"

int counter = 0;
void TestSheerCloud::VerifyTesting() {
  QVERIFY2(2+2==4, "Really");
  QCOMPARE("123", "123");
}

const char * str(QString in){
  return in.toStdString().c_str();
}

void TestSheerCloud::Basics( SheerCloud * cloud ) {
  QByteArray out;
  QVERIFY2(cloud->Authorize("neverland", "big", "boss"), str( cloud->lastError()));
  QVERIFY2(cloud->Upload("file1.txt", "123"), str( cloud->lastError()));
  bool was_downloaded = cloud->Download("file1.txt", out);
  QVERIFY2(was_downloaded && out == "123" , str( cloud->lastError()));
  QVERIFY2(! cloud->Download("file2.txt", out), "File must not be found.");
}

void TestSheerCloud::TestStub(){
  Basics( GetSheerCloudStub() );
};

void TestSheerCloud::TestHttp(){
  //  Basics( GetSheerCloudHttp() );
  SheerCloud * cloud = GetSheerCloudHttp();
  QVERIFY2(false, "TODO: Authorization");
  QVERIFY(cloud->Authorize("http://localhost:8080", "abc", "123"));
};


QTEST_MAIN(TestSheerCloud)

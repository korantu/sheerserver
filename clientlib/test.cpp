#include "test.h"

#include <QByteArray>

void TestSheerCloud::VerifyTesting() {
  QVERIFY2(2+2==4, "Really");
}

void TestSheerCloud::SheerLinkLogin() {
  link.Authorize();
  loop.exec();
  QVERIFY2( link.Authorized(), "Password should match; Make sure the server is running.");
};

void TestSheerCloud::SheerLinkUploadDownload() {
  SheerLinkLogin();

  link.Upload("very/important/file.txt", "123");
  loop.exec();

  QByteArray result;
  link.Download("very/important/file.txt", result);
  loop.exec();

  QVERIFY2( result.contains("123"), "Sent/recieved data mismatch");
};


void TestSheerCloud::SheerLinkUploadDownloadBulk() {
  SheerLinkLogin();

  QByteArray massive("1234567890abcdefg"); // Every letter is a megabyte.
  massive = massive.repeated(1000000);
  link.Upload("very/huge/file.txt", massive);
  loop.exec();

  QByteArray result;
  link.Download("very/huge/file.txt", result);
  loop.exec();

  QVERIFY2( result == massive, "Sent/recieved data mismatch");
};


QTEST_MAIN(TestSheerCloud)

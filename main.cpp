#include "FenClientHttp.h"
#include <QApplication>
#include <QString>
#include "ClientHttp.h"

bool testHttp()
{
    ClientHttp test;
    test.SetServer("http://qt-project.org/doc/qt-5.0/qtnetwork");
    QString m_sMyUrl = test.GetUrl("qnetworkreply.html");

    test.SetUrl(m_sMyUrl);
    test.CommunicationChannel();
    if(test.IsOk())
    {
        qDebug() << "It worked.\n";
    } else {
        qDebug() << "Problem \n";
    }
    return test.IsOk();
}

bool testLog()
{
    ClientHttp test1;
    test1.SetServer("http://localhost:8080/info");
    test1.SetUserName("Alvine");
    test1.SetUserPassword("Senami");

    test1.ConnectServer();
    if(test1.IsOk())
    {
        qDebug() << "It worked.\n";
    } else {
        qDebug() << "Problem \n";
    }
    return test1.IsOk();
}


bool testFileUpload()
{
    ClientHttp test2;
    test2.PostFile("http://localhost:8080/info", "C:/Data/InFile");

    test2.UploadFileToServer();
    if(test2.IsOk())
    {
        qDebug() << "It worked.\n";
    } else {
        qDebug() << "Problem \n";
    }
    return test2.IsOk();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Hi\n";

    //qDebug() << testHttp();//communication to server
    //qDebug() << testLog();// send data to server
    qDebug() << testFileUpload();
    
    return a.exec();
}

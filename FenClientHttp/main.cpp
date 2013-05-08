#include <QApplication>
#include <QString>
#include "ClientHttp.h"
#include "FenClientHttp.h"

/*bool testHttp()
{
    ClientHttp test;
    test.SetServer("http://localhost:8080");
    QString m_sMyUrl = test.GetUrl("info");

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
*/
/*bool testLog()
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

*/
/*bool testFileUpload()
{
    ClientHttp test2;
    test2.PostFile("http://localhost:8080/info", "C:/Data/test.pdf");

    test2.UploadFileToServer();
    if(test2.IsOk())
    {
        qDebug() << "It worked.\n";
    } else {
        qDebug() << "Problem \n";
    }
    return test2.IsOk();
}
*/
/*bool testReadDir()
{
    ClientHttp testRead;
    testRead.ReadFileDir("C:/Data");
    if(testRead.IsOk() == true){
        qDebug() << "It worked.\n";
    } else {
        qDebug() << "Problem \n";
    }
    return testRead.IsOk();
}*/

bool testDownload()
{
    ClientHttp testDown;
    testDown.SetUrl("https://www.java.net//today/2004/07/30/Spring.pdf");
    testDown.DownloadData();

    if(testDown.IsOk() == true){
        qDebug() << "It worked.\n";
    } else {
        qDebug() << "Problem \n";
    }
    return testDown.IsOk();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Hi\n";

    //qDebug() << testHttp();//communication to server
    //qDebug() << testLog();// send data to server
    //qDebug() << testFileUpload();
    //qDebug() << testReadDir();
    qDebug() << testDownload();
    
    return a.exec();


    /*QApplication app(argc, argv);
    FenClientHttp w;
    w.show();

    return app.exec();*/
}

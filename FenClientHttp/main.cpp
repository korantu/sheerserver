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
    //test1.SetServer("http://localhost:8080/authorize?login=abc&password=123");
    test1.SetUserName("abc");
    test1.SetUserPassword("123");
    QString m_Url = "http://localhost:8080/authorize?login="+test1.GetUser()+"&password="+test1.GetPassword();
    test1.SetServer(m_Url);

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

bool testFileUpload()
{
    ClientHttp test2;
    test2.SetUserName("abc");
    test2.SetUserPassword("123");
    test2.SetFileName("C:/Data/J2EEStrutsSpringHibernate.pdf");
    QString m_sFile = test2.GetFileName().section('/',-1);
    QString m_sUrl = "http://localhost:8080/upload?login="+test2.GetUser()+"&password="+test2.GetPassword()+"&file="+m_sFile;
    test2.SetServer(m_sUrl);

    test2.UploadFileToServer();
    if(test2.IsOk())
    {
        qDebug() << "It worked.\n";
    } else {
        qDebug() << "Problem \n";
    }
    return test2.IsOk();
}

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
/*
bool testDownload()
{
    ClientHttp testDown;
    testDown.SetUserName("abc");
    testDown.SetUserPassword("123");
    QString m_sUrl = "http://localhost:8080/download?login="+testDown.GetUser()+"&password="+testDown.GetPassword()+"&file=oldfile.txt";
    testDown.SetUrl(m_sUrl);
    testDown.DownloadData();

    if(testDown.IsOk() == true){
        qDebug() << "It worked.\n";
    } else {
        qDebug() << "Problem \n";
    }
    return testDown.IsOk();
}
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Hi\n";

    //qDebug() << testHttp();//communication to server
    //qDebug() << testLog();// send data to server
    qDebug() << testFileUpload();
    //qDebug() << testReadDir();
    //qDebug() << testDownload();
    
    return a.exec();


    /*QApplication app(argc, argv);
    FenClientHttp w;
    w.show();

    return app.exec();*/
}

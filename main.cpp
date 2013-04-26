#include "FenClientHttp.h"
#include <QApplication>
#include <QString>
#include "ClientHttp.h"

bool testHttp()
{
    ClientHttp test;
    test.SetServer("http://localhost:8080");
    QString m_sMyUrl = test.GetUrl("ui");

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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "Hi\n";

    qDebug() << testHttp();
    
    return a.exec();
}

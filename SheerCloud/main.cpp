#include "SheerCloudWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SheerCloudWidget w;
    w.show();
    
    return a.exec();
}

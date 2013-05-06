#ifndef FENCLIENTHTTP_H
#define FENCLIENTHTTP_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QTableWidget>
#include <QDir>
#include <QDesktopServices>
#include <QGridLayout>
#include <QWidget>
#include "ClientHttp.h"


namespace Ui {
class Form;
}

class FenClientHttp : public QWidget
{
    Q_OBJECT
    
public:
    FenClientHttp(QWidget *parent = 0);
    //explicit FenClientHttp(QWidget *parent = 0);
    ~FenClientHttp();
    void createFilesTable();

public slots:
    void chargerFiles();
    void adjustGoButton();
    void inputPassword();
    void inputPath();
    void openFileOfItem(int row, int);
    void sendFileToServer(int row, int);

private:
    Ui::Form *ui;
    ClientHttp m_oClient;
};

#endif // FENCLIENTHTTP_H

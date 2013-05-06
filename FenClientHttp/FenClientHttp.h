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
    //void sendFileToServer();

private:
    Ui::Form *ui;
};

#endif // FENCLIENTHTTP_H

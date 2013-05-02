#ifndef FENCLIENTHTTP_H
#define FENCLIENTHTTP_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPlainTextEdit>

class FenClientHttp : public QMainWindow
{
    Q_OBJECT
    
public:
    FenClientHttp(QWidget *parent = 0);
    ~FenClientHttp();

public slots:
    void chargerFiles();
    void adjustGoButton();
    void inputPassword();
    void inputPath();

private:
    QLabel *m_oUserNameLabel;
    QLineEdit *m_oUserNameLineEdit;
    QLabel *m_oPasswordLabel;
    QLineEdit *m_oPasswordLineEdit;
    QLabel *m_oFileDirectoryLabel;
    QLineEdit *m_oFileDirectoryLineEdit;
    QPushButton *m_oGoPushButton;
    QPlainTextEdit *m_oShowFiles;
};

#endif // FENCLIENTHTTP_H

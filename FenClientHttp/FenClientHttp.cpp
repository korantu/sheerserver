#include "FenClientHttp.h"

FenClientHttp::FenClientHttp(QWidget *parent)
    : QMainWindow(parent)
{
    m_oUserNameLabel = new QLabel(tr("User Name"));
    m_oUserNameLineEdit = new QLineEdit;
    m_oUserNameLabel->setBuddy(m_oUserNameLineEdit);

    connect(m_oUserNameLineEdit, SIGNAL(returnPressed()), SLOT(inputPassword()));

    m_oPasswordLabel = new QLabel(tr("Password"));
    m_oPasswordLineEdit = new QLineEdit;
    m_oPasswordLabel->setBuddy(m_oPasswordLineEdit);

    connect(m_oPasswordLineEdit, SIGNAL(returnPressed()), SLOT(inputPath()));

    m_oFileDirectoryLabel = new QLabel(tr("Enter the file/directory Path"));
    m_oFileDirectoryLineEdit = new QLineEdit;
    m_oFileDirectoryLabel->setBuddy(m_oFileDirectoryLineEdit);

    connect(m_oFileDirectoryLineEdit, SIGNAL(returnPressed()), SLOT(adjustGoButton()));

    m_oGoPushButton = new QPushButton("Go");

    m_oShowFiles = new QPlainTextEdit(this);
    m_oShowFiles->setEnabled(false);

    connect(m_oGoPushButton, SIGNAL(clicked()), this, SLOT(chargerFiles()));
}

void FenClientHttp::chargerFiles()
{
    m_oShowFiles->setEnabled(true);
    QDir dir(m_oFileDirectoryLineEdit->text());
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
    //std::cout << "     Bytes Filename" << std::endl;
    m_oShowFiles->appendPlainText("Bytes FileName");
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        /*std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
                                                .arg(fileInfo.fileName()));
        std::cout << std::endl;*/
        //Insert into the box the list of the files

    }
}

void FenClientHttp::adjustGoButton()
{
    bool ok = m_oUserNameLineEdit->text().isEmpty() &&
              m_oPasswordLineEdit->text().isEmpty() &&
              m_oFileDirectoryLineEdit->text().isEmpty();
    m_oGoPushButton->setEnabled(ok);
}

void FenClientHttp::inputPassword()
{
    if(!m_oUserNameLineEdit->text().isEmpty()){
        m_oPasswordLineEdit->setFocus();
    }
}

void FenClientHttp::inputPath()
{
    if(!(m_oUserNameLineEdit->text().isEmpty() && m_oPasswordLineEdit->text().isEmpty())){
        m_oFileDirectoryLineEdit->setFocus();
    }
}

FenClientHttp::~FenClientHttp()
{
    
}

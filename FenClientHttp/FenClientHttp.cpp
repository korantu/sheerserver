#include "FenClientHttp.h"
#include "ui_form.h"
#include <QDebug>

FenClientHttp::FenClientHttp(QWidget *parent) :
    QWidget(parent), ui(new Ui::Form)
{
    ui->setupUi(this);
    connect(ui->m_oUserNameLineEdit, SIGNAL(returnPressed()), SLOT(inputPassword()));
    connect(ui->m_oFileDirectoryLineEdit, SIGNAL(returnPressed()), SLOT(adjustGoButton()));
    connect(ui->m_oGoPushButton, SIGNAL(clicked()), this, SLOT(chargerFiles()));
}

void FenClientHttp::chargerFiles()
{
    //createFilesTable();
    QDir m_oFileDir(ui->m_oFileDirectoryLineEdit->text());
    m_oFileDir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    m_oFileDir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList m_oList = m_oFileDir.entryInfoList();

    for (int i = 0; i < m_oList.size(); ++i) {
        QFileInfo m_oFileInfo = m_oList.at(i);
        QFile m_oFile(m_oFileInfo.fileName());

        QTableWidgetItem *m_oFileNameItem = new QTableWidgetItem(m_oFile.fileName());
        QTableWidgetItem *m_oSizeItem = new QTableWidgetItem(m_oFile.size());

        qDebug() << m_oFile.fileName() << m_oFile.size();

        int m_nRow = ui->m_oShowFiles->rowCount();
        ui->m_oShowFiles->insertRow(m_nRow);
        ui->m_oShowFiles->setItem(m_nRow, 0, m_oFileNameItem);
        ui->m_oShowFiles->setItem(m_nRow, 1, m_oSizeItem);
    }
    connect(ui->m_oShowFiles, SIGNAL(cellDoubleClicked(int,int)),
            this, SLOT(openFileOfItem(int,int)));
}

void FenClientHttp::adjustGoButton()
{
    bool ok = ui->m_oUserNameLineEdit->text().isEmpty() &&
              ui->m_oPasswordLineEdit->text().isEmpty() &&
              ui->m_oFileDirectoryLineEdit->text().isEmpty();
    ui->m_oGoPushButton->setEnabled(ok);
}

void FenClientHttp::inputPassword()
{
    if(!ui->m_oUserNameLineEdit->text().isEmpty()){
        ui->m_oPasswordLineEdit->setFocus();
    }
}

void FenClientHttp::inputPath()
{
    if(!(ui->m_oUserNameLineEdit->text().isEmpty() && ui->m_oPasswordLineEdit->text().isEmpty())){
        ui->m_oFileDirectoryLineEdit->setFocus();
    }
}

FenClientHttp::~FenClientHttp()
{
    delete ui;
}

void FenClientHttp::createFilesTable()
{
    //ui->m_oShowFiles->setVisible(true);
    ui->m_oShowFiles->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->m_oShowFiles->setShowGrid(false);

    connect(ui->m_oShowFiles, SIGNAL(cellActivated(int,int)),
            this, SLOT(openFileOfItem(int,int)));
}

void FenClientHttp::openFileOfItem(int row, int /*column */)
{
    QTableWidgetItem *m_oItem = ui->m_oShowFiles->item(row, 0);

    QDir m_oCurrentDir = QDir(ui->m_oFileDirectoryLineEdit->text());

    QDesktopServices::openUrl(QUrl::fromLocalFile(m_oCurrentDir.absoluteFilePath(m_oItem->text())));
}

void FenClientHttp::sendFileToServer()
{

}

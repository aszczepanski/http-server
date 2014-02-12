#include <QTime>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>

#include "uploaderwindow.h"
#include "ui_uploaderwindow.h"

UploaderWindow::UploaderWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UploaderWindow),
    network(new QNetworkAccessManager)
{
    ui->setupUi(this);
}

UploaderWindow::~UploaderWindow()
{
    delete ui;
}

void UploaderWindow::performDownload()
{
    QString token = ui->downloadPickerEdit->text();
    log("trying to download: " + token);\
    reply = network->get(QNetworkRequest(QUrl(token)));

    connect(reply, SIGNAL(finished()),  this, SLOT(finishedDownload()));
    connect(reply, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(updateDownloadBar(qint64,qint64)));
    connect(reply, SIGNAL(metaDataChanged()), this, SLOT(replyDataChanged()));
}

void UploaderWindow::log(QString message) {
    ui->logBrowser->append(QTime::currentTime().toString() + " " + message);
}

void UploaderWindow::finishedDownload() {
    log("finished downloading");
}

void UploaderWindow::readyRead() {
    log("reply: " + reply->readAll());
}

void UploaderWindow::updateDownloadBar(qint64 bytes_read, qint64 total_bytes) {
    ui->downloadProgressBar->setMaximum(total_bytes);
    ui->downloadProgressBar->setValue(bytes_read);
}

void UploaderWindow::replyDataChanged() {
    QVariant statusCode = reply->attribute( QNetworkRequest::HttpStatusCodeAttribute );
     if ( !statusCode.isValid() )
         return;
     int status = statusCode.toInt();
     if ( status >= 400 )
     {
         log("HTTP error: " + QString::number(status));
         QMessageBox msgBox;
         if (status == 404)
             msgBox.setText("File not found!");
         else
             msgBox.setText("Error " + QString::number(status));
         msgBox.exec();

     }
}

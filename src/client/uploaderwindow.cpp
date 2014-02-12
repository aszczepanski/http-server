#include <QTime>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include <QFileDialog>

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

void UploaderWindow::performDownload() {
    QString token = ui->downloadPickerEdit->text();
    if (token.size() == 0) return;
    QString fileName = QFileDialog::getSaveFileName(this, "Save");
    this->downloadFileName = fileName;
    if (fileName.size() == 0) return;
    log("saving as: " + fileName);
    log("trying to download: " + token);

    fileToDownload = new QFile(downloadFileName);
    fileToDownload->open(QIODevice::WriteOnly);

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
    log("finished downloading to " + this->downloadFileName);
    fileToDownload->flush();
    fileToDownload->close();
    delete(fileToDownload);
    fileToDownload = 0;
}

void UploaderWindow::readyRead() {

    if (fileToDownload)
             fileToDownload->write(reply->readAll());
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

void UploaderWindow::on_filePickerButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open");
    this->uploadFileName = fileName;
    QFileInfo uploadFileInfo(fileName);
    ui->filePickerLabel->setText(uploadFileInfo.fileName());
}

void UploaderWindow::on_uploadButton_clicked() {
    QString url = ui->uploadStatusEdit->text();
    if (uploadFileName.size() == 0) return;
    log("uploading: " + uploadFileName);
    log("trying to upload: " + url);

    fileToUpload = new QFile(uploadFileName);
    fileToUpload->open(QIODevice::ReadOnly);

    reply = network->put(QNetworkRequest(QUrl(url)), fileToUpload);

    connect(reply, SIGNAL(finished()),  this, SLOT(finishedUpload()));
    connect(reply, SIGNAL(metaDataChanged()), this, SLOT(replyDataChanged()));
}

void UploaderWindow::finishedUpload() {
    log("finished uploading");
    fileToUpload->close();
    delete(fileToUpload);
    fileToUpload = 0;
}

void UploaderWindow::performDelete() {
    QString url = ui->deleteEdit->text();
    if (url.length() == 0) return;
    log("deleting " + url);
    reply = network->deleteResource(QNetworkRequest(QUrl(url)));
    connect(reply, SIGNAL(metaDataChanged()), this, SLOT(replyDataChanged()));
}

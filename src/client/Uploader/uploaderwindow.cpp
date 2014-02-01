#include <QTime>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

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
    network->get(QNetworkRequest(QUrl(token)));
}

void UploaderWindow::log(QString message) {
    ui->logBrowser->append(QTime::currentTime().toString() + " " + message);
}

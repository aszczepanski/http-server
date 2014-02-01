#include <QTime>

#include "uploaderwindow.h"
#include "ui_uploaderwindow.h"

UploaderWindow::UploaderWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UploaderWindow)
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
    log("trying to download: " + token);
}

void UploaderWindow::log(QString message) {
    ui->logBrowser->append(QTime::currentTime().toString() + " " + message);
}

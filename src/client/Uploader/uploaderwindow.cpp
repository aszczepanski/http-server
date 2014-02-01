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

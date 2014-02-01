#ifndef UPLOADERWINDOW_H
#define UPLOADERWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>

namespace Ui {
class UploaderWindow;
}

class UploaderWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UploaderWindow(QWidget *parent = 0);
    ~UploaderWindow();
    void log(QString message);

private:
    Ui::UploaderWindow *ui;
    QNetworkAccessManager *network;

private slots:
    void performDownload();
};

#endif // UPLOADERWINDOW_H

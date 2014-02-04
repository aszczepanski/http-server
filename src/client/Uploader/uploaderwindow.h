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
    QNetworkReply* reply;

private slots:
    void performDownload();
    void readyRead();
    void finishedDownload();
    void updateDownloadBar(qint64 bytes_read, qint64 total_bytes);
};

#endif // UPLOADERWINDOW_H

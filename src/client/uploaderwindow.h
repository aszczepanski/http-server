#ifndef UPLOADERWINDOW_H
#define UPLOADERWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class QFile;

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
    QString downloadFileName;
    QString uploadFileName;
    QFile* fileToUpload;

private slots:
    void performDownload();
    void performDelete();
    void readyRead();
    void finishedDownload();
    void updateDownloadBar(qint64 bytes_read, qint64 total_bytes);
    void replyDataChanged();

    void finishedUpload();

    void on_filePickerButton_clicked();
    void on_uploadButton_clicked();
};

#endif // UPLOADERWINDOW_H

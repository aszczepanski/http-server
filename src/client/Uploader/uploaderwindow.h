#ifndef UPLOADERWINDOW_H
#define UPLOADERWINDOW_H

#include <QMainWindow>

namespace Ui {
class UploaderWindow;
}

class UploaderWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UploaderWindow(QWidget *parent = 0);
    ~UploaderWindow();

private:
    Ui::UploaderWindow *ui;
};

#endif // UPLOADERWINDOW_H

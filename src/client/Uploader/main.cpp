#include "uploaderwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UploaderWindow w;
    w.show();

    return a.exec();
}

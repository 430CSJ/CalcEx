#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ExData exData;
    MainWindow w(&exData);
    w.show();
    return a.exec();
}

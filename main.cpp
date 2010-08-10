#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //qApp->addLibraryPath(qApp->applicationDirPath() + "\\plugins\\"); //uncomment for Windows deployment
    w.show();

    return a.exec();
}

#include <QApplication>
#include <QtGui>
#include <QSettings>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //qApp->addLibraryPath(qApp->applicationDirPath() + "\\plugins\\"); //uncomment for Windows deployment
    QCoreApplication::setOrganizationName("Andrew Harris");
    QCoreApplication::setApplicationName("Hobby Lobby Coupon Downloader");
    QCoreApplication::setApplicationVersion("2.1");
    w.show();

    return a.exec();
}

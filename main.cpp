#include <QApplication>
#include <QtGui>
#include <QSettings>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //qApp->addLibraryPath(qApp->applicationDirPath() + "\\plugins\\"); //uncomment for Windows deployment
    QCoreApplication::setOrganizationName("Le Fauve");  // the beast
    QCoreApplication::setApplicationName("Hobby Lobby Coupon Downloader");
    QCoreApplication::setApplicationVersion("2.0dev");
    w.show();

    return a.exec();
}

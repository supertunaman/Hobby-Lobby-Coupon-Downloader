#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    scene.setSceneRect(0, 0, 620, 940); // I pulled these numbers from my ass, justsayin'
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(drawCoupons(int)));
    ui->statusBar->showMessage(tr("Grabbing Coupon page..."));
    coupon.setUrl(QUrl("http://hobbylobby.com/weekly/coupon.cfm"));
    ui->statusBar->showMessage(tr("Click the Get Coupon icon to fetch this week's Hobby Lobby coupon."));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionGetCoupon_triggered()
{
    ui->statusBar->showMessage(tr("Looking for Coupon..."));    // I love status bar messages. They're so futuristic!
    couponImg.loadFromData(coupon.getCoupon());
    ui->statusBar->showMessage(tr("Got the coupon!"));
    couponImg = couponImg.scaled(QSize(300, 179));  //This is about 60% the original size. It's pretty tough to read the text at this size
    ui->horizontalSlider->setEnabled(true);
    ui->actionPrint->setEnabled(true);
    drawCoupons(ui->horizontalSlider->value());
}

void MainWindow::drawCoupons(int count)
{
    scene.clear();
    ui->graphicsView->show();   // had some weird issues earlier where the view wouldn't clear all the way.
    coupon.drawCouponPage(&scene, couponImg, count);
    ui->graphicsView->show();
}

void MainWindow::on_actionPrint_triggered()
{
    QGraphicsScene printScene;
    QPixmap img;
    QPrinter printer;
    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    dialog->setWindowTitle("Print Coupons");
    if (dialog->exec() != QDialog::Accepted)
        return;
    QPainter painter(&printer);
    printScene.setSceneRect(0, 0, 920, 1400);
    img.loadFromData(coupon.couponFile);
    coupon.drawCouponPage(&printScene, img, ui->horizontalSlider->value());
    printScene.render(&painter);
    ui->statusBar->showMessage("Coupon page sent to printer.");
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsDialog dialog(this);
    dialog.exec();
}

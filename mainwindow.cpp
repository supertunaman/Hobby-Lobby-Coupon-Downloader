#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    scene.setSceneRect(0, 0, 614, 980); // I pulled these numbers from my ass, justsayin'
    connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(drawCoupons(int)));
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
    Coupon::Coupon coupon(QUrl("http://hobbylobby.com/weekly/coupon.cfm"));
    coupon.getCoupon(); // Maybe I should just have getCoupon() return the byte array itself
    ui->statusBar->showMessage(tr("Got the coupon!"));
    couponImg.loadFromData(coupon.couponFile);
    couponImg = couponImg.scaled(QSize(300, 179));  //This is about 60% the original size. It's pretty tough to read the text at this size
    ui->horizontalSlider->setEnabled(true);
    ui->actionPrint->setEnabled(true);
    drawCoupons(ui->horizontalSlider->value());
}

void MainWindow::drawCoupons(int count)
{
    QGraphicsPixmapItem * pixmap;
    scene.clear();
    ui->graphicsView->show();   // had some weird issues earlier where the view wouldn't clear all the way.
    int rows = (count + 1) / 2;
    int ypad;   // this variable is to space out the rows.
    for (int i = 1; i <= rows; i++) // starting at 1 because of the conditional that deals with and odd number of coupons being drawn
    {
        ypad = (i - 1) * 10;
        if (i != rows || rows == count / 2) // this one
        {
            pixmap = scene.addPixmap(couponImg);
            pixmap->setPos(0, ((i - 1) * 179 + ypad));
            pixmap = scene.addPixmap(couponImg);
            pixmap->setPos(310, ((i - 1) * 179 + ypad));
        } else {
            pixmap = scene.addPixmap(couponImg);
            pixmap->setPos(0, ((i - 1) * 179 + ypad));
        }
    }
    ui->graphicsView->show();
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    dialog->setWindowTitle("Print Coupons");
    if (dialog->exec() != QDialog::Accepted)
        return;
    QPainter painter(&printer);
    ui->graphicsView->scene()->render(&painter);
    ui->statusBar->showMessage("Coupon page sent to printer.");
}

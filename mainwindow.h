#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPrinter>
#include <QPrintDialog>
#include <QSettings>
#include "coupon.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPixmap couponImg;
    QGraphicsScene scene;
    Coupon coupon;

private slots:
    void on_actionPrint_triggered();
    void on_actionGetCoupon_triggered();
    void on_actionExit_triggered();
    void drawCoupons(int count);
};

#endif // MAINWINDOW_H

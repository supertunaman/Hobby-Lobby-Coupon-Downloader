#ifndef COUPON_H
#define COUPON_H

#include <QObject>
#include <QDebug>
#include <QEventLoop>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStringList>

class Coupon : public QObject
{
    Q_OBJECT
public:
    Coupon();
    Coupon(const QUrl &url);
    QByteArray getCoupon(); // getCoupon() parses the coupon webpage and returns the image data it gets via httpGet
    QByteArray couponFile;  // it also stores this data in couponFile
    void drawCouponPage(QGraphicsScene * scene, QPixmap img, int count);
    void setUrl(const QUrl &url);

private:
    QString page;
    QByteArray httpGet(QUrl url);
};

#endif // COUPON_H

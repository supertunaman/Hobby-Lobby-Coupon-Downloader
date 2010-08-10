#ifndef COUPON_H
#define COUPON_H

#include <QObject>
#include <QDebug>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStringList>

class Coupon : public QObject
{
    Q_OBJECT
public:
    explicit Coupon(const QUrl &url);
    void getCoupon();
    QByteArray couponFile;

private:
    QString page;
    QByteArray httpGet(QUrl url);
};

#endif // COUPON_H

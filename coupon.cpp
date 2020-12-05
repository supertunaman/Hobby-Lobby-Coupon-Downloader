#include "coupon.h"

Coupon::Coupon() {}
Coupon::Coupon(const QUrl &url)
{
    page = httpGet(url);
}

QByteArray Coupon::getCoupon()
{
    QStringList sl = page.split("\n");
    QString line;
    foreach(line, sl)   // UGLY FUGLY MCLEPER CODE!
    {
        if (line.contains("<p class=\"coupon-print\">"))   // Whatever, it works for now.
            break;
    }
    line = line.trimmed();
    line.replace("<p class=\"coupon-print\"><a target=\"_blank\" href=\"", "https:");
    line.replace("\">Print coupon to take in-store</a></p>", "");
    couponFile = httpGet(line);
    return couponFile;
}

QByteArray Coupon::httpGet(QUrl url)
{
    QNetworkAccessManager nam(this);
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("User-Agent", "Mozilla/5.0");  // I figure Hobby Lobby could get tired of visitors with null user agents.
    QNetworkReply *reply = nam.get(request);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    return reply->readAll();
}

void Coupon::drawCouponPage(QGraphicsScene * scene, QPixmap img, int count)
{
    QGraphicsPixmapItem * pixmap;
    int rows = (count + 1) / 2;
    int ypad;   // this variable is to space out the rows.
    for (int i = 1; i <= rows; i++) // starting at 1 because of the conditional that deals with and odd number of coupons being drawn
    {
        ypad = (i - 1) * 10;
        if (i != rows || rows == count / 2) // this one
        {
            pixmap = scene->addPixmap(img);
            pixmap->setPos(0, ((i - 1) * img.height() + ypad));
            pixmap = scene->addPixmap(img);
            pixmap->setPos(img.width() + 10, ((i - 1) * img.height() + ypad));
        } else {
            pixmap = scene->addPixmap(img);
            pixmap->setPos(0, ((i - 1) * img.height() + ypad));
        }
    }
}

void Coupon::setUrl(const QUrl &url)
{
    page = httpGet(url);
}

#include "coupon.h"

Coupon::Coupon(const QUrl &url)
{
    page = httpGet(url);
}

void Coupon::getCoupon()
{
    QStringList sl = page.split("\n");
    QString line;
    foreach(line, sl)   // UGLY FUGLY MCLEPER CODE!
    {
        if (line.contains("/assets/dynamic/_weekly.coupon/"))   // Whatever, it works for now.
            break;
    }
    line = line.trimmed();
    line.replace("<a href=\"", "http://hobbylobby.com");
    line.replace("\">", "");
    couponFile = httpGet(line);
}

QByteArray Coupon::httpGet(QUrl url)
{
    QNetworkAccessManager nam(this);
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("User-Agent", "Mozilla/5.0");
    QNetworkReply *reply = nam.get(request);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    return reply->readAll();
}

#ifndef STOCKPACKET_H
#define STOCKPACKET_H

#include <QString>
#include <QList>
#include <QDateTime>
#include <QMetaType>

struct StockPacket
{
public:
    StockPacket();

    quint32 id;
    QString symbol;
    QString name;
    quint32 recordIntervalTime;
    QList<qreal> openPrices;
    QList<qreal> closePrices;
    QList<qreal> highPrices;
    QList<qreal> lowPrices;
    QList<qreal> volume;
    QDateTime lastPriceTime;
    QDateTime firstPriceTime;

    quint16 count();
};

Q_DECLARE_METATYPE(StockPacket)

#endif // STOCKPACKET_H

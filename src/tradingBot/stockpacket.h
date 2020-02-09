#ifndef STOCKPACKET_H
#define STOCKPACKET_H

#include <QString>
#include <QList>
#include <QDateTime>

class StockPacket
{
public:
    StockPacket();

    quint16 id;
    QString symbol;
    QString name;
    quint16 recordIntervalTime;
    QList<quint16> openPrices;
    QList<quint16> closePrices;
    QList<quint16> highPrices;
    QList<quint16> lowPrices;
    QList<quint16> volume;
    QDateTime lastPriceTime;
    QDateTime firstPriceTime;

private:
};

#endif // STOCKPACKET_H

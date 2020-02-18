#ifndef TRADEMANAGER_H
#define TRADEMANAGER_H

#include <QObject>
#include <QList>
#include "stockpacket.h"

class TradeManager : public QObject
{
    Q_OBJECT
public:
    explicit TradeManager(QObject *parent = nullptr);

    void startTeslaCall()
    {
        startNewCall("Tesla", "TSLA");
    }

public slots:
    void handleNewStockInformation(const StockPacket newStock);

signals:
    void requestNewStockInformation(StockPacket stock);

private:
    QList<StockPacket> m_stocks;

    quint32 startNewCall(QString name, QString symbol);
    quint32 m_idCounter;
};

#endif // TRADEMANAGER_H

#ifndef TRADEMANAGER_H
#define TRADEMANAGER_H

#include <QObject>

class TradeManager : public QObject
{
    Q_OBJECT
public:
    explicit TradeManager(QObject *parent = nullptr);

signals:

};

#endif // TRADEMANAGER_H

#include "trademanager.h"
#include "QDebug"

TradeManager::TradeManager(QObject *parent) : QObject(parent)
{
    m_idCounter = 0;
}

void TradeManager::handleNewStockInformation(const StockPacket newStock)
{
    m_stocks.append(newStock);
    qDebug() << "New Stock info with name: " << newStock.name;
}

quint32 TradeManager::startNewCall(QString name, QString symbol)
{
    StockPacket newPacket;
    newPacket.name = name;
    newPacket.symbol = symbol;

    m_idCounter++;

    emit requestNewStockInformation(newPacket);

    return m_idCounter;
}



//Initiate Stock information call

//format data

//Present information to algorithm - Decision making

//Initiate order

#include "alphaadvantagetranslator.h"
#include <QProcess>
#include <QJsonDocument>
#include <QBuffer>
#include <QTextStream>

#define AV_TIME_INTERVAL "1min"
#define AV_PROGRAM "python"
#define OUTPUT_FORMAT_JSON "json"
#define OUTPUT_FORMAT_PANDAS "pandas"
#define TEMPORARY_ADDRESS_OF_PYTHON_SCRIPT "C:/Projects/Python/tradingbot/src/alphaVantage.py"

AlphaAdvantageTranslator::AlphaAdvantageTranslator(QObject *parent) : QObject(parent)
{
    connect(&processManager, &ProcessManager::newProcessData, this, &AlphaAdvantageTranslator::handleNewStockInformation);
}

void AlphaAdvantageTranslator::handleStockCall(StockPacket stock)
{
    QStringList args;
    args.append(TEMPORARY_ADDRESS_OF_PYTHON_SCRIPT);
    args.append(stock.symbol);
    args.append(AV_TIME_INTERVAL);
    args.append(OUTPUT_FORMAT_PANDAS);
    quint32 id = processManager.createNewProcess(AV_PROGRAM, args);

    //TODO use Record interval time to determine length for alphavantage
    stock.recordIntervalTime = 60 * 1000;

    if (id != 0)
    {
        activeCalls.insert(id, stock);
    }
}

void AlphaAdvantageTranslator::handleNewStockInformation(quint32 id, QByteArray data)
{
    StockPacket newPacket = activeCalls.value(id);

    if (activeCalls.contains(id))
    {
        QString line;
        QStringList parts;
        QTextStream stream(data);

        line = stream.readLine();
        parts = line.split(",");

        if (parts.length() >= 6)
        {
            newPacket.lastPriceTime = QDateTime::fromString(parts.at(0), "yyyy-MM-dd HH:mm:ss");
            newPacket.openPrices.append(parts.at(1).toFloat());
            newPacket.highPrices.append(parts.at(2).toFloat());
            newPacket.lowPrices.append(parts.at(3).toFloat());
            newPacket.closePrices.append(parts.at(4).toFloat());
            newPacket.volume.append(parts.at(5).toFloat());
        }

        while (!stream.atEnd()) {
            line = stream.readLine();
            parts = line.split(",");

            if (parts.length() >= 6)
            {
                newPacket.firstPriceTime = QDateTime::fromString(parts.at(0), "yyyy-dd-MM HH:mm:ss");
                newPacket.openPrices.append(parts.at(1).toFloat());
                newPacket.highPrices.append(parts.at(2).toFloat());
                newPacket.lowPrices.append(parts.at(3).toFloat());
                newPacket.closePrices.append(parts.at(4).toFloat());
                newPacket.volume.append(parts.at(5).toFloat());
            }
        }
    }

    activeCalls.remove(id);
    emit newStockInformationReady(newPacket);
}

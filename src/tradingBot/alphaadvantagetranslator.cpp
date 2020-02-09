#include "alphaadvantagetranslator.h"
#include <QProcess>
#include <QJsonDocument>

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
    args.append(OUTPUT_FORMAT_JSON);
    quint16 id = processManager.createNewProcess(AV_PROGRAM, args);

    if (id != 0)
    {
        activeCalls.insert(id, stock);
    }
}

void AlphaAdvantageTranslator::handleNewStockInformation(quint16 id, QByteArray data)
{
    if (activeCalls.contains(id))
    {
        QJsonDocument doc = QJsonDocument::fromJson(data);
        quint8 test = 0;
        test++;
        //Process data and place it into stock packet
    }
}

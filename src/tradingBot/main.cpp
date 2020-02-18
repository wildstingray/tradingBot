#include <QCoreApplication>
#include "alphaadvantagetranslator.h"
#include "trademanager.h"
#include "stockpacket.h"
#include <QThread>
#include <QObject>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qRegisterMetaType<StockPacket>();

    QThread alphaThread;
    TradeManager manager(&a);
    AlphaAdvantageTranslator *alpha = new AlphaAdvantageTranslator;

    alpha->moveToThread(&alphaThread);
    QObject::connect(&alphaThread, &QThread::finished, alpha, &QObject::deleteLater);
    QObject::connect(&manager, &TradeManager::requestNewStockInformation, alpha, &AlphaAdvantageTranslator::handleStockCall);
    QObject::connect(alpha, &AlphaAdvantageTranslator::newStockInformationReady, &manager, &TradeManager::handleNewStockInformation);

    alphaThread.start();

    manager.startTeslaCall();

    a.exec();
    alphaThread.quit();
    return 0;
}

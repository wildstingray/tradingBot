#include <QCoreApplication>
#include "alphaadvantagetranslator.h"
#include "trademanager.h"
#include <QThread>
#include <QObject>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread alphaThread;

    AlphaAdvantageTranslator *alpha = new AlphaAdvantageTranslator;
    alpha->moveToThread(&alphaThread);
    QObject::connect(&alphaThread, &QThread::finished, alpha, &QObject::deleteLater);
    alphaThread.start();

    StockPacket packet;
    packet.symbol = "TSLA";

    alpha->handleStockCall(packet);

    return a.exec();
}

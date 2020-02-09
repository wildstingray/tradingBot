#ifndef ALPHAADVANTAGETRANSLATOR_H
#define ALPHAADVANTAGETRANSLATOR_H

#include <QObject>
#include "processmanager.h"
#include "stockpacket.h"
#include "QThread"

class AlphaAdvantageTranslator : public QObject
{
    Q_OBJECT
public:
    explicit AlphaAdvantageTranslator(QObject *parent = nullptr);

signals:
    void newStockInformationReady(StockPacket & stock);

public slots:
    void handleStockCall(StockPacket stock);

protected slots:
    void handleNewStockInformation(quint16 id, QByteArray data);

private:
    ProcessManager processManager;
    QMap<quint16, StockPacket> activeCalls;
};

#endif // ALPHAADVANTAGETRANSLATOR_H

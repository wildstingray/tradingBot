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
    void newStockInformationReady(const StockPacket & stock);

public slots:
    void handleStockCall(StockPacket stock);

protected slots:
    void handleNewStockInformation(quint32 id, QByteArray data);

private:
    ProcessManager processManager;
    QMap<quint32, StockPacket> activeCalls;
};

#endif // ALPHAADVANTAGETRANSLATOR_H

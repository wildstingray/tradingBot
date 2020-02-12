#include "stockpacket.h"

StockPacket::StockPacket()
{

}

quint16 StockPacket::count()
{
    return openPrices.length();
}

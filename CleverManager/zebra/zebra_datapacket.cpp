#include "zebra_datapacket.h"

Zebra_DataPacket::Zebra_DataPacket()
{
    dhtStatus = false;
}

Zebra_DataPacket *Zebra_DataPacket::bulid()
{
    static Zebra_DataPacket* sington = nullptr;
    if(sington == nullptr)
        sington = new Zebra_DataPacket();

    return sington;
}

#ifndef ZEBRA_DATAPACKET_H
#define ZEBRA_DATAPACKET_H

#include <QObject>
#include <QtCore>
#include <QDebug>

struct sZebraNode
{
    sZebraNode() {status=0;}

    int status;
    QString node_id;
    QString join_id;
    QString channel_id;
    QString ip;
};

class Zebra_DataPacket
{
    Zebra_DataPacket();
public:
    static Zebra_DataPacket *bulid();

    bool dhtStatus; // 分布区网络


private:
    QHash<QString, sZebraNode> mHash;
};

#endif // ZEBRA_DATAPACKET_H

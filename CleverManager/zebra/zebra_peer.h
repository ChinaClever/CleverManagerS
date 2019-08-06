#ifndef ZEBRA_PEER_H
#define ZEBRA_PEER_H
#include "zebra_client.h"

class Zebra_Peer //: public im
{
    Zebra_Peer(Zebra_Client *client);
public:

//    bool startZebra();
//    void stopZebra();
//    int send(const QString &id, uchar *buf, int len);

private:
    bool isRun;
    Zebra_Client *mClient;
};

#endif // ZEBRA_PEER_H

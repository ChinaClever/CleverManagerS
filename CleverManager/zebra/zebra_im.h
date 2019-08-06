#ifndef ZEBRA_IM_H
#define ZEBRA_IM_H

#include "zebra_client.h"

class Zebra_Im : public im
{
public:
     Zebra_Im(Zebra_Client *client);
     ~Zebra_Im();

     bool startZebra();
     void stopZebra();
     int send(const QString &id, uchar *buf, int len);

private:
    bool isRun;
};

#endif // ZEBRA_IM_H

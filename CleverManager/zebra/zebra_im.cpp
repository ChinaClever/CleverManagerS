#include "zebra_im.h"

Zebra_Im::Zebra_Im(Zebra_Client *client) : im(client)
{
    isRun = false;
}

Zebra_Im::~Zebra_Im()
{
    stopZebra();
}

bool Zebra_Im::startZebra()
{
    if(!isRun) {
        start();
        isRun = true;
    }

    return isRun;
}


void Zebra_Im::stopZebra()
{
    if(isRun) {
        stop();
        isRun = false;
    }
}


int Zebra_Im::send(const QString &id, uchar *buf, int len)
{
    int ret = 0;
    if(isRun) {
        std::string data((char*)buf,len);
        ret = send_message(id.toStdString(), data);
    }

    return ret;
}

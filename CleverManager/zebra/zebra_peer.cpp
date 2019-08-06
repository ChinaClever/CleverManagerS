/*
 *
 *
 *  Created on: 2019年10月1日
 *      Author: Lzy
 */
#include "zebra_peer.h"

Zebra_Peer::Zebra_Peer(Zebra_Client *client) //:im(client)
{
    isRun = false;
}

//bool Zebra_Peer::startZebra()
//{
//    if(!isRun) {
//        start();
//        isRun = true;
//    }

//    return isRun;
//}


//void Zebra_Peer::stopZebra()
//{
//    if(isRun) {
//        stop();
//        isRun = false;
//    }
//}


//int Zebra_Peer::send(const QString &id, uchar *buf, int len)
//{
//    int ret = 0;
//    if(isRun) {
//        std::string data((char*)buf,len);
//        ret = send_message(id.toStdString(), data);
//    }

//    return ret;
//}

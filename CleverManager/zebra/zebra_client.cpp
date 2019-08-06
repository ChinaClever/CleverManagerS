/*
 *
 *
 *  Created on: 2019年10月1日
 *      Author: Lzy
 */
#include "zebra_client.h"

Zebra_Client::Zebra_Client()
{
    mSql = Zebra_Sql::bulid();
}


void Zebra_Client::key_pair(std::string& public_key, std::string& private_key)
{
    sZebraSqlItem item = mSql->findById(mBootstrapNodes);
    if(item.id>=0) {
        public_key = item.public_key.toStdString();
        private_key = item.private_key.toStdString();
    } else {
        qDebug() << "read node key fail.";
    }
}


void Zebra_Client::handleBootstrapEvent(bootstrapEvent *evn)
{
    mBootstrapNodes = QString::fromStdString(evn->node_id());

    sZebraSqlItem item;
    item.node_id = QString::fromStdString(evn->node_id());
    item.public_key = QString::fromStdString(evn->key().Publick);
    item.private_key = QString::fromStdString(evn->key().Private);
    mSql->updateItem(item);
}


void Zebra_Client::handleGetDHTNodesEvent(dhtNodeEvent *evn) {
    std::vector<std::string> nodes;
    evn->nodes(nodes);
}


void Zebra_Client::handleCreateChannelEvent(channelEvent* evn)
{
    if(peersafe::imapi::channelType::CH_CHAT == evn->getChannel().type())
    {
        sZebraSqlItem item;
        std::string str = evn->getChannel().channel_id();
        item.node_id = QString::fromStdString(str);

        str = evn->getChannel().key().Publick;
        item.public_key = QString::fromStdString(str);

        str = evn->getChannel().key().Private;
        item.private_key = QString::fromStdString(str);
        mSql->updateItem(item);
    }
}


void Zebra_Client::handleConnectPeerEvent(connectEvent* evn)
{
    Zebra_DataPacket *dp = Zebra_DataPacket::bulid();
    if (evn->error_code()) {
        dp->dhtStatus = false;
        qDebug() << "DHT connected err";
    } else {
        dp->dhtStatus = true;
        qDebug() << "DHT connected ok";
    }
}


void Zebra_Client::handleJoinChannelEvent(joinEvent* evn)
{
    //	evn->reason("welcome to here");
    evn->allow(true);
}


void Zebra_Client::handleAllowEvent(allowEvent* evn)
{
    QString join_id = QString::fromStdString(evn->join_channel());
    QString channel_id = QString::fromStdString(evn->chat_channel());


    ////////////
}

void Zebra_Client::handleDisAllowEvent(disAllowEvent* evn)
{
    QString join_id = QString::fromStdString(evn->join_channel());

    ////////////////
}



void Zebra_Client::handleMessageEvent(messageEvent* evn)
{
    char rcv[256] = {0};
    QString from = QString::fromStdString(evn->from());
    QString id = QString::fromStdString(evn->channel());

    std::string data =  evn->data();
    int len = data.length();
    memcpy(rcv, data.c_str(), len);
    QByteArray ba(rcv, len);


}


void Zebra_Client::handleReplyEvent(replyEvent* evn)
{
    qDebug() << "Zebra A reply "
        << "  errorCode: " << evn->errorCode()
        << "  originator: " << evn->originatorType()
        << "  channel: " << QString::fromStdString(evn->channel()) ;
}



void Zebra_Client::handleNotifyEvent(notifyEvent* evn)
{
    qDebug() << "Zebra A notify \n"
        << "  channel: " << QString::fromStdString(evn->channel())
        << "  reason: " << evn->reason();
}


void Zebra_Client::handleLoadChEvent(localChannel* evn)
{
//    db_.get_channels(e);
}


void Zebra_Client::onEvent(eventCode code, event* evn)
{
    switch (code) {
    case BOOTSTRAP: // 引导完成通知事件
        handleBootstrapEvent(dynamic_cast<bootstrapEvent*>(evn));
        break;

    case GETDHTNODES: //路由表打印事件
        handleGetDHTNodesEvent(dynamic_cast<dhtNodeEvent*>(evn));
        break;

    case CREATECHANNEL: // 创建通道通知事件
        handleCreateChannelEvent(dynamic_cast<channelEvent*>(evn));
        break;

    case CONNECTION: // 连接事件
        handleConnectPeerEvent(dynamic_cast<connectEvent*>(evn));
        break;

    case JOINCHANNEL: // join请求事件
        handleJoinChannelEvent(dynamic_cast<joinEvent*>(evn));
        break;

    case ALLOWCHANNEL: // 同意join事件
        handleAllowEvent(dynamic_cast<allowEvent*>(evn));
        break;

    case  DISALLOWCHANNEL: // 不同意join事件
        handleDisAllowEvent(dynamic_cast<disAllowEvent*>(evn));
        break;

    case CHAT: // 消息通知事件
        handleMessageEvent(dynamic_cast<messageEvent*>(evn));
        break;

    case REPLY:  // 用户请求应答事件
        handleReplyEvent(dynamic_cast<replyEvent*>(evn));
        break;

    case NOTIFY: // 其他通知事件
        handleNotifyEvent(dynamic_cast<notifyEvent*>(evn));
        break;

    case LOADLOCALCHANNEL:
        handleLoadChEvent(dynamic_cast<localChannel*>(evn));
        break;

    default:
        break;
    }

}

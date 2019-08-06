#ifndef ZEBRA_CLIENT_H
#define ZEBRA_CLIENT_H
#include "im.h"
#include "zebra_sql.h"

using namespace peersafe;
using namespace imapi;

class Zebra_Client : public client
{
public:
    Zebra_Client();

protected:
    uint defaultPort() {return 37053;}
    void setBootstrapNodes(const QString& nodes) { mBootstrapNodes = nodes;}

    void node_id(std::string& id) {id = mNodeId;}
    void key_pair(std::string& public_key, std::string& private_key);
    bool readOnly() {return true;}

    // nodes eg: 10.100.0.100:37053;10.100.0.101:37053
    uint bootstraps(std::string& nodes) {nodes = mBootstrapNodes.toStdString(); return nodes.length();}
    uint usingMaxMemory() { return 512; }
    int client_threads() { return 1; }
    int service_threads() { return 2; }

    void onEvent(eventCode code, event* evn);

private:
    void handleBootstrapEvent(bootstrapEvent *evn);
    void handleGetDHTNodesEvent(dhtNodeEvent *evn);
    void handleConnectPeerEvent(connectEvent* evn);
    void handleJoinChannelEvent(joinEvent* evn);
    void handleCreateChannelEvent(channelEvent* evn);
    void handleAllowEvent(allowEvent* evn);
    void handleDisAllowEvent(disAllowEvent* evn) ;
    void handleMessageEvent(messageEvent* evn);
    void handleReplyEvent(replyEvent* evn);
    void handleNotifyEvent(notifyEvent* evn);
    void handleLoadChEvent(localChannel* evn);

private:
    QString mBootstrapNodes;
    std::string mNodeId;
    Zebra_Sql *mSql;
};

#endif // ZEBRA_CLIENT_H

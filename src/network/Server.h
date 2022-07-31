#ifndef SERVER_H
#define SERVER_H
#include"ServerUtils.h"
#include"../logger/Logger.h"

class Server{
public:
    void setServerUtils(ServerUtils serverUtils){this->serverUtils = serverUtils;};

    Message parseRequest(string s){return serverUtils.parseRequest(s);};

    string processMessage(Message& m){return serverUtils.processMessage(m);};

    void start(int port = 8080);

private:
    ServerUtils serverUtils;

    
    

};

#endif
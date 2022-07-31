#ifndef SERVERUTILS_H
#define SERVERUTILS_H

#include"../message/Message.h"

class ServerUtils{
public:
    Message parseRequest(string s);

    string processMessage(Message& message);
};

#endif
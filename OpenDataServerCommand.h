//
// Created by yuval on 21/12/2019.
//

#ifndef UNTITLED13_OPENDATASERVERCOMMAND_H
#define EX3_OPENDATASERVERCOMMAND_H

#include <thread>
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <sstream>
#include "globals.h"
#include "ex1.h"

class OpenDataServerCommand : public Command {
protected:
    bool isConnected = false;
public:
    virtual ~OpenDataServerCommand() {}

    OpenDataServerCommand() {}

    int execute(string str);


    int RunServer(int PORT);

    vector<string> makeXmlArray();
};


#endif //EX3_OPENDATASERVERCOMMAND_H

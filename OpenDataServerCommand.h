//
// Created by yuval on 21/12/2019.
//

#ifndef EX3_OPENDATASERVERCOMMAND_H
#define EX3_OPENDATASERVERCOMMAND_H

#include "Command.h"
#include <thread>
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>

class OpenDataServerCommand : public Command {
public:
    virtual ~OpenDataServerCommand() {}

    OpenDataServerCommand() {}

    int execute(string str);


    int RunServer(int PORT);

    string *makeXmlArray();
};


#endif //EX3_OPENDATASERVERCOMMAND_H

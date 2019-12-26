//
// Created by yuval on 21/12/2019.
//

#ifndef EX3_CONNECTCONTROLCLIENTCOMMAND_H
#define EX3_CONNECTCONTROLCLIENTCOMMAND_H
#include "Command.h"
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
class ConnectControlClientCommand:public Command {
public:
    virtual ~ConnectControlClientCommand(){}
    ConnectControlClientCommand(){}
    int execute(string str);
    int RunClient1(string ip, int PORT);
};
#endif //EX3_CONNECTCONTROLCLIENTCOMMAND_H

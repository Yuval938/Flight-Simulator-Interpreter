//
// Created by yuval on 21/12/2019.
//

#ifndef UNTITLED13_CONNECTCONTROLCLIENTCOMMAND_H
#define UNTITLED13_CONNECTCONTROLCLIENTCOMMAND_H
#include "globals.h"

class ConnectControlClientCommand:public Command {
public:
    virtual ~ConnectControlClientCommand(){}
    ConnectControlClientCommand(){}
    int execute(string str);
    bool ClientisConnected=false;
    int RunClient(string ipAsString, int port);
};
#endif //UNTITLED13_CONNECTCONTROLCLIENTCOMMAND_H

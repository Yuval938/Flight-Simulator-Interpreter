//
// Created by yuval on 21/12/2019.
//

#ifndef EX3_CONNECTCONTROLCLIENTCOMMAND_H
#define EX3_CONNECTCONTROLCLIENTCOMMAND_H
#include "Command.h"
class ConnectControlClientCommand:public Command {
public:
    virtual ~ConnectControlClientCommand(){}
    ConnectControlClientCommand(){}
    int execute(string str);


};
#endif //EX3_CONNECTCONTROLCLIENTCOMMAND_H

//
// Created by yuval on 17/12/2019.
//

#ifndef EX3_DEFINEVARCOMMAND_H
#define EX3_DEFINEVARCOMMAND_H

#include "Command.h"

class DefineVarCommand : public Command {

public:
    virtual ~DefineVarCommand() {}

    DefineVarCommand() {}

    int execute(string str);
};


#endif //EX3_DEFINEVARCOMMAND_H

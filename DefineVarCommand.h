//
// Created by yuval on 17/12/2019.
//

#ifndef UNTITLED13_DEFINEVARCOMMAND_H
#define UNTITLED13_DEFINEVARCOMMAND_H

#include "globals.h"

class DefineVarCommand : public Command {

public:
    virtual ~DefineVarCommand() {}

    DefineVarCommand();

    int execute(string str);
};


#endif //UNTITLED13_DEFINEVARCOMMAND_H

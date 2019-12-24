//
// Created by yuval on 21/12/2019.
//

#ifndef EX3_PRINTCOMMAND_H
#define EX3_PRINTCOMMAND_H

#include "Command.h"

class PrintCommand : public Command {
public:
    virtual ~PrintCommand() {}

    PrintCommand() {}

    int execute(string str);


};


#endif //EX3_PRINTCOMMAND_H

//
// Created by yuval on 21/12/2019.
//

#ifndef UNTITlED13_PRINTCOMMAND_H
#define UNTITLED13_PRINTCOMMAND_H

#include "globals.h"

class PrintCommand : public Command {
public:
    virtual ~PrintCommand() {}

    PrintCommand() {}

    int execute(string str);


};


#endif //UNTITLED13_PRINTCOMMAND_H

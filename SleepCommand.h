//
// Created by valdman40 on 12/21/19.
//

#ifndef EX3_2_SLEEPCOMMAND_H
#define EX3_2_SLEEPCOMMAND_H


#include "Command.h"

class SleepCommand : public Command {
public:
    virtual ~SleepCommand() {}

    SleepCommand() {}

    int execute(string str);

};


#endif //EX3_2_SLEEPCOMMAND_H

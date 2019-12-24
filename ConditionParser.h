//
// Created by valdman40 on 12/21/19.
//

#ifndef EX3_2_CONDITIONPARSER_H
#define EX3_2_CONDITIONPARSER_H


#include "Command.h"

class ConditionParser : public Command {

protected:

    map<string, Command *> CommandList;

public:
    ConditionParser(map<string, Command *> CommandList1){
        this->CommandList=CommandList1;
    }

};


#endif //EX3_2_CONDITIONPARSER_H

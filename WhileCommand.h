//
// Created by yuval on 21/12/2019.
//

#ifndef EX3_WHILECOMMAND_H
#define EX3_WHILECOMMAND_H
#include <map>
#include "ConditionParser.h"
#include "Command.h"

using namespace std;
class WhileCommand : public ConditionParser{
public:
    WhileCommand() {}
    int execute(string str);

};


#endif //EX3_WHILECOMMAND_H

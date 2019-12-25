//
// Created by valdman40 on 12/25/19.
//

#ifndef EX3_4_IFCOMMAND_H
#define EX3_4_IFCOMMAND_H

#include "ConditionParser.h"

using namespace std;
class IfCommand : public ConditionParser{
public:
    IfCommand() {}
    int execute(string str);

};

#endif //EX3_4_IFCOMMAND_H

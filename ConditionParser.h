//
// Created by valdman40 on 12/21/19.
//

#ifndef EX3_2_CONDITIONPARSER_H
#define EX3_2_CONDITIONPARSER_H


#include "Command.h"
#include "globals.h"

class ConditionParser : public Command {
public:
    ConditionParser() {}

    void replaceAll(std::string &str, const std::string &from, const std::string &to) {
        if (from.empty())
            return;
        size_t start_pos = 0;
        while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
        }
    }

};


#endif //EX3_2_CONDITIONPARSER_H

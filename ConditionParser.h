//
// Created by valdman40 on 12/21/19.
//

#ifndef EX3_2_CONDITIONPARSER_H
#define EX3_2_CONDITIONPARSER_H


#include "Command.h"

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

    bool is_number(const std::string &s) {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }

    int executeConditionParser(std::vector<std::string> content, int position, map<string, Command *> CommandsMap) {
        bool gotCurlyBraces = false;
        int pos;
        int posOfRoundBrace = content[position].find("(");
        int posOfFirstSpace = content[position].find(" ");

        if (posOfRoundBrace == -1) { //means there was no '('
            pos = posOfFirstSpace;
        } else if (posOfFirstSpace == -1) { //means there was no space
            pos = posOfRoundBrace;
        } else {
            pos = min(posOfFirstSpace, posOfRoundBrace); // take the first of them
        }

        string command = content[position].substr(0, pos); // get the first word
        string ExecuteInfo = content[position].substr(pos); // get the rest of the line
        if (content[position].find('{') != string::npos) {
            gotCurlyBraces = true;
            position++;
        }
        while (gotCurlyBraces) {
            if (content[position].find('}') != string::npos) {
                gotCurlyBraces = false;
            }
            ExecuteInfo += content[position];
            position++;
        }

        Command *c = CommandsMap[command];
        if (c != NULL) {
            c->execute(ExecuteInfo);
        } else { // for now, we assume that if it's not a command, it's probably a defined var
            cout << "the var \"" << command << "\"" << " is defined, need to update it" << endl;
        }

        return position;
    }
};


#endif //EX3_2_CONDITIONPARSER_H

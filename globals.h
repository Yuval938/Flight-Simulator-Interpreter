//
// Created by valdman40 on 12/24/19.
//

#ifndef EX3_3_GLOBALS_H
#define EX3_3_GLOBALS_H

#include <fstream>
#include <vector>
#include <map>
#include "Command.h"
#include "Var.h"
#include <queue>
#include "ex1.h"

extern map<string, Var> SymbolTable;
extern map<string, Command *> CommandList;
extern thread threads[2];
extern queue <string> SetCommands;
extern bool endOfFile;

Interpreter *makeInterpeter();

std::string ReplaceAll(std::string str, const std::string &from, const std::string &to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

bool is_number(const std::string &s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void updateVarValue(string var, string str) {
    // need to make the Expression
    Interpreter *in = makeInterpeter();
    Expression *e;
    int posOfEq = str.find('=') + 2;
    int posOfEndl = str.find("endl ");
    str = str.substr(posOfEq, posOfEndl - posOfEq - 1);
    std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
    str.erase(end_pos, str.end());
    int tt = 3;
    try {
        e = in->interpret(str);
        SymbolTable[var].setValue(e->calculate());
        string set = SymbolTable[var].getType() + " " + SymbolTable[var].getSim() + " " +
                     to_string(SymbolTable[var].getValue()) + "\r\n";
        SetCommands.push(set);
    } catch (const std::exception &) {
        cout << "error at updateVarValue" << endl;
    }
}

Interpreter *makeInterpeter() {
    Interpreter *i = new Interpreter();
    for (auto item: SymbolTable) {
        i->setVariables(item.first + "=" + std::to_string(item.second.getValue()));
    }

    return i;
}

int executeFromContent(std::vector<std::string> content, int position, map<string, Command *> CommandsMap) {
    bool gotCurlyBraces = false;
    int pos;
    int posOfRoundBrace = content[position].find("(");
    int posOfFirstSpace = content[position].find(" ");
    int posOfCloseCurlyBrace = content[position].find("}");

    if (posOfRoundBrace == -1) { //means there was no '('
        pos = posOfFirstSpace;
    } else if (posOfFirstSpace == -1) { //means there was no space
        pos = posOfRoundBrace;
    } else {
        pos = min(posOfFirstSpace, posOfRoundBrace); // take the first of them
    }
    if (posOfCloseCurlyBrace >= 0) {
        pos = 0;
    }
    string command = content[position].substr(0, pos); // get the first word
    string ExecuteInfo = content[position].substr(pos) + " endl "; // get the rest of the line
    if (content[position].find('{') != string::npos) {
        gotCurlyBraces = true;
        position++;
    }
    while (gotCurlyBraces) {
        if (content[position].find('}') != string::npos) {
            gotCurlyBraces = false;
            position--;
        } else {
            ExecuteInfo += content[position] + " endl ";
            position++;
        }
    }

    Command *c = CommandsMap[command];
    if (c != NULL) {
        c->execute(ExecuteInfo);
    } else { // for now, we assume that if it's not a command, it's probably a defined var
        if (command.compare("}") != 0 && command.compare("") != 0) {
            cout << "updating \"" << command << "\"" << endl;
            updateVarValue(command, ExecuteInfo);
        }
    }

    return position;
}


#endif //EX3_3_GLOBALS_H

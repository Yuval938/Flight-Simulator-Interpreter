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

extern map<string, Var> SymbolTable;
extern map<string, Command *> CommandList;
extern thread threads[2];
extern queue<string> SetCommands;

void updateVarValue(string var, string str) {

    int numPos = str.find("=") + 2;
    str = str.substr(numPos);
    int pos = str.find(" ");
    str = str.substr(0, pos);
    double newValue = std::stod(str);
    SymbolTable[var].setValue(newValue);
    //if we need to set a value in the game we will alert the client by pushing a command to the queue
    if (SymbolTable[var].getType().compare("set") == 0) {
        string set = SymbolTable[var].getType() + " " + SymbolTable[var].getSim() + " " +
                     to_string(SymbolTable[var].getValue()) + "\r\n";
        SetCommands.push(set);
    }

}


int executeFromContent(std::vector<std::string> content, int position, map<string, Command *> CommandsMap) {
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
    string ExecuteInfo = content[position].substr(pos) + " endl "; // get the rest of the line
    if (content[position].find('{') != string::npos) {
        gotCurlyBraces = true;
        position++;
    }
    while (gotCurlyBraces) {
        if (content[position].find('}') != string::npos) {
            gotCurlyBraces = false;
        }
        ExecuteInfo += content[position] + " endl ";
        position++;
    }

    Command *c = CommandsMap[command];
    if (c != NULL) {
        c->execute(ExecuteInfo);
    } else { // for now, we assume that if it's not a command, it's probably a defined var
        cout << "updating \"" << command << "\"" << endl;
        updateVarValue(command, ExecuteInfo);
    }

    return position;
}





#endif //EX3_3_GLOBALS_H

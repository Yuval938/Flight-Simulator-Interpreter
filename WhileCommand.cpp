//
// Created by yuval on 21/12/2019.
//

#include "WhileCommand.h"
#include "globals.h"


int WhileCommand::execute(string str) {
    cout << "WHILE_COMMAND: " << endl;
    // we want to split each line
    std::vector<std::string> content;
    replaceAll(str, "\t", "");

    int i, strLen = str.length();

    bool readingFirstLine = true;

    string conditionLine = "";
    string line = "";
    for (i = 0; i < strLen; i++) {
        string word = "";
        while (str.at(i) != ' ') {
            word += str.at(i);
            i++;
        }
        if(word.compare("}") != 0){
            line += word + " ";
            if (word.compare("endl") == 0) { //we're at the end of the line
                if (readingFirstLine) {
                    conditionLine = line;
                    readingFirstLine = false;
                } else {
                    content.push_back(line);
                }
                line = "";
            }
        } else {
            break;
        }
    }


    conditionLine.erase(conditionLine.begin(), std::find_if(conditionLine.begin(), conditionLine.end(),
                                                            std::bind1st(std::not_equal_to<char>(), ' ')));
    // example of str: warp -> sim("/sim/time/warp") endl
    int pos = conditionLine.find(" "); // getting the first space
    string leftSide = conditionLine.substr(0, pos); // getting first substring until first space
    conditionLine = conditionLine.substr(pos + 1); // desposing the var now got left with: -> sim("/sim/time/warp") endl
    pos = conditionLine.find(" "); // getting the second space
    string operand = conditionLine.substr(0, pos); // getting the arrow
    conditionLine = conditionLine.substr(pos + 1); // now we got left with: sim("/sim/time/warp") endl
    pos = conditionLine.find(" "); // getting the third space
    string rightSide = conditionLine.substr(0, pos);

    int number;
    string var;
    if (is_number(leftSide)) {
        number = std::stoi(leftSide);
        var = rightSide;
    } else if (is_number(rightSide)) {
        number = std::stoi(rightSide);
        var = leftSide;
    } else {
        cout << "error, one of the sides isnt a number" << endl;
    }

    i = 0;

    int contentSize = content.size();
    if (operand.compare("<=") == 0) {
        while (SymbolTable[var].getValue() <= number) {
            i = 0;
            while (i < contentSize) {
                i = executeFromContent(content, i, CommandList) + 1;
            }
        }
    } else if (operand.compare("<") == 0) {
        while (SymbolTable[var].getValue() < number) {
            i = 0;
            while (i < contentSize) {
                i = executeFromContent(content, i, CommandList) + 1;
            }
        }
    } else if (operand.compare(">=") == 0) {
        while (SymbolTable[var].getValue() >= number) {
            i = 0;
            while (i < contentSize) {
                i = executeFromContent(content, i, CommandList) + 1;
            }
        }
    } else if (operand.compare(">") == 0) {
        while (SymbolTable[var].getValue() > number) {
            i = 0;
            while (i < contentSize) {
                i = executeFromContent(content, i, CommandList) + 1;
            }
        }
    } else if (operand.compare("==") == 0) {
        while (SymbolTable[var].getValue() == number) {
            i = 0;
            while (i < contentSize) {
                i = executeFromContent(content, i, CommandList) + 1;
            }
        }
    } else if (operand.compare("!=") == 0) {
        while (SymbolTable[var].getValue() != number) {
            i = 0;
            while (i < contentSize) {
                i = executeFromContent(content, i, CommandList) + 1;
            }
        }
    }


    return 0;
}
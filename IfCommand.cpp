//
// Created by valdman40 on 12/25/19.
//

#include <algorithm>
#include "IfCommand.h"
#include "globals.h"


int IfCommand::execute(string str) {
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

    int varValue = SymbolTable[var].getValue();
    i = 0;

    int contentSize = content.size();
    if (operand.compare("<=") == 0) {
        if (varValue <= number) {
            i = 0;
            while (i < contentSize) {
                i = executeFromContent(content, i, CommandList) + 1;
                i++;
            }
        }
    } else if (operand.compare("<") == 0) {
        if (varValue < number) {
            i = 0;
            while (i < contentSize) {
                i = executeFromContent(content, i, CommandList) + 1;
                i++;
            }
        }
    } else if (operand.compare(">=") == 0) {
        if (varValue >= number) {
            i = 0;
            while (i < contentSize) {
                i = executeFromContent(content, i, CommandList) + 1;
                i++;
            }
        }
    } else if (operand.compare(">") == 0) {
        if (varValue > number) {
            i = 0;
            while (i < contentSize) {
                i = executeFromContent(content, i, CommandList) + 1;
                i++;
            }
        }
    } else if (operand.compare("==") == 0) {
        if (varValue == number) {
            i = 0;
            while (i < contentSize) {
                i = executeFromContent(content, i, CommandList) + 1;
                i++;
            }
        }
    } else if (operand.compare("!=") == 0) {
        if (SymbolTable[var].getValue() != number) {
            i = 0;
            while (i < contentSize) {
                i = executeFromContent(content, i, CommandList) + 1;
                i++;
            }
        }
    }


    return 0;
}
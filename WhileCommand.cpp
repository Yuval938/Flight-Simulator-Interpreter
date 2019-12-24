//
// Created by yuval on 21/12/2019.
//

#include "WhileCommand.h"
#include "globals.h"

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

int executeFromContent1(std::vector<std::string> content, int position, map<string, Command *> CommandsMap) {
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

int WhileCommand::execute(string str) {
    cout << "making a while Command with this string---> " << str << endl;
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
        while (varValue <= number) {
            i = 0;
            while (i < contentSize) {
                i = executeFromContent1(content, i, CommandList) + 1;
                i++;
                varValue += 150; //just for check
            }
        }
    } else if (operand.compare("<") == 0) {
        while (varValue < number) {
            i = 0;
            while (i < contentSize) {
                i = executeFromContent1(content, i, CommandList) + 1;
                i++;
                varValue += 150; //just for check
            }
        }
    } else if (operand.compare(">=") == 0) {
        while (varValue >= number) {
            i = 0;
            while (i < contentSize) {
                i = executeFromContent1(content, i, CommandList) + 1;
                i++;
            }
        }
    } else if (operand.compare(">") == 0) {
        while (varValue > number) {
            i = 0;
            while (i < contentSize) {
                i = executeFromContent1(content, i, CommandList) + 1;
                i++;
            }
        }
    } else if (operand.compare("==") == 0) {
        while (varValue == number) {
            i = 0;
            while (i < contentSize) {
                i = executeFromContent1(content, i, CommandList) + 1;
                i++;
            }
        }
    }


    return 0;
}
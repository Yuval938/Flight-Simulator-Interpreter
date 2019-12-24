//
// Created by yuval on 21/12/2019.
//

#include "WhileCommand.h"

int WhileCommand::execute(string str) {
    cout << "making a while Command with this string---> " << str << endl;
    // we want to split each line
    std::vector<std::string> content;

    int i, strLen = str.length();

    string line = "";
    for (i = 0; i < strLen; i++) {
        string word = "";
        while (str.at(i) != ' ') {
            word += str.at(i);
            i++;
        }
        line += word + " ";
        if (word.compare("endl") == 0) { //we're at the end of the line
            content.push_back(line);
            line = "";
        }
    }

    i = 0;
    while (i < strLen) {
//        i = this->executeFromContent(content, i, this->CommandList) + 1;
        i++;
    }
    return 0;
}
#include <fstream>
#include <vector>
#include <map>
#include "Command.h"
#include "DefineVarCommand.cpp"
#include "WhileCommand.h"
#include "WhileCommand.cpp"
#include "OpenDataServerCommand.h"
#include "OpenDataServerCommand.cpp"
#include "ConnectControlClientCommand.h"
#include "ConnectControlClientCommand.cpp"
#include "PrintCommand.h"
#include "PrintCommand.cpp"
#include "SleepCommand.h"
#include "SleepCommand.cpp"
#include "globals.h"

using namespace std;

std::vector<std::string> split(const std::string &s, char c);

int executeFromContent(std::vector<std::string> content, int position, map<string, Command *> CommandsMap);

bool ignoreChars(char ch);

void MakeCommandMap();

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

int executeFromContent(std::vector<std::string> content, int position, map<string, Command *> CommandsMap) {
    cout<<"test"<<endl;
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
        cout << "the var \"" << command << "\"" << " is defined, need to update it" << endl;
    }

    return position;
}

int main() {
    MakeCommandMap();
    std::string file_path("fly.txt"); // I assumed you have that kind of file
    std::ifstream in_s(file_path);

    std::vector<std::string> content;
    ifstream file("fly.txt");

    string line;
    while (std::getline(file, line)) {
        content.push_back(line);
    }

    // at this point, content contains fly.txt line by line.
    int i = 0, contentSize = content.size();
    while (i < contentSize) {
        i = executeFromContent(content, i, CommandList) + 1;
    }
    threads[0].join();

    return 0;
}

void MakeCommandMap() {
    CommandList["var"] = new DefineVarCommand();
    CommandList["while"] = new WhileCommand(CommandList);
    CommandList["openDataServer"] = new OpenDataServerCommand();
    CommandList["connectControlClient"] = new ConnectControlClientCommand();
    CommandList["Print"] = new PrintCommand();
    CommandList["Sleep"] = new SleepCommand();
}
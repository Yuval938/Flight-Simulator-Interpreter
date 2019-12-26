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
#include "globals.cpp"
#include "IfCommand.h"
#include "IfCommand.cpp"
#include "IfCommand.h"

using namespace std;

std::vector<std::string> split(const std::string &s, char c);

bool ignoreChars(char ch);

void MakeCommandMap();

void updateVarValue(string basicString, string basicString1);

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
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
    threads[1].join();

    return 0;
}

void MakeCommandMap() {
    CommandList["var"] = new DefineVarCommand();
    CommandList["while"] = new WhileCommand();
    CommandList["if"] = new IfCommand();
    CommandList["openDataServer"] = new OpenDataServerCommand();
    CommandList["connectControlClient"] = new ConnectControlClientCommand();
    CommandList["Print"] = new PrintCommand();
    CommandList["Sleep"] = new SleepCommand();
}
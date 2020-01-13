//
// Created by valdman40 on 12/24/19.
//

#ifndef UNTITLED13_GLOBALS_H
#define UNTITLED13_GLOBALS_H

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

bool is_number(const std::string &s);

void updateVarValue(string var, string str);

void replaceAll(std::string &str, const std::string &from, const std::string &to);

Interpreter *makeInterpeter();

int executeFromContent(std::vector<std::string> content, int position, map<string, Command *> CommandsMap);


#endif //UNTITLED13_GLOBALS_H

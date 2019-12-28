//
// Created by valdman40 on 12/24/19.
//

#include "globals.h"

map<string, Var> SymbolTable;
map<string, Command *> CommandList;
thread threads[2];
queue<string> SetCommands;
bool endOfFile;
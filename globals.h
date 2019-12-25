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







#endif //EX3_3_GLOBALS_H

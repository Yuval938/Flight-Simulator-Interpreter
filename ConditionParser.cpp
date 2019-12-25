//
// Created by valdman40 on 12/21/19.
//

#include "ConditionParser.h"
#include "DefineVarCommand.h"
#include "WhileCommand.h"
#include "IfCommand.h"
#include "OpenDataServerCommand.h"
#include "ConnectControlClientCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"

ConditionParser::ConditionParser(map<string, Var> &ClientSymbolTable, map<string, Var> &ServerSymbolTable) {

    this->CommandList["var"] = new DefineVarCommand(ClientSymbolTable, ServerSymbolTable);
    this->CommandList["while"] = new WhileCommand(ClientSymbolTable, ServerSymbolTable);
    this->CommandList["if"] = new IfCommand();
    this->CommandList["openDataServer"] = new OpenDataServerCommand(ClientSymbolTable, ServerSymbolTable);
    this->CommandList["connectControlClient"] = new ConnectControlClientCommand(ClientSymbolTable, ServerSymbolTable);
    this->CommandList["Print"] = new PrintCommand(ClientSymbolTable, ServerSymbolTable);
    this->CommandList["Sleep"] = new SleepCommand(ClientSymbolTable, ServerSymbolTable);
}

//
// Created by yuval on 17/12/2019.
//

#ifndef UNTITLED8_COMMAND_H
#define UNTITLED8_COMMAND_H

#include "Var.h"
#include "Var.cpp"

using namespace std;
#include <iostream>
#include <map>
#include <vector>
#include <thread>

/**
 * Command Interface
 */
class Command {
public:
virtual int execute(string str)=0;
    virtual ~Command() {}

};

#endif //UNTITLED8_COMMAND_H

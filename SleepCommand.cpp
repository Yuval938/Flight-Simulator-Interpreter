//
// Created by valdman40 on 12/21/19.
//

#include "SleepCommand.h"
#include <thread>
#include <chrono>

int SleepCommand::execute(string str) {
    // cout << "sleep for this time:     " << str << endl;
    cout << "SLEEP_COMMAND-> " << flush;
    int posOpenBrace = str.find("(");
    int posCloseBrace = str.find(")");
    str = str.substr(posOpenBrace + 1, posCloseBrace - posOpenBrace - 1);
    Interpreter *i = new Interpreter();
    int ms = (i->interpret(str))->calculate();
    cout << "sleeps for "<< ms  << " milliseconds"<< endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
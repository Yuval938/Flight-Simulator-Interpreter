//
// Created by yuval on 17/12/2019.
//
#include "DefineVarCommand.h"

DefineVarCommand::DefineVarCommand(){}
/*
 * DefineVarCommand::execute(string str) will make a new Var Object and will insert it to our map.
 */
int DefineVarCommand::execute(string str) {
    cout << "making a Var Object using this string:    " << str << endl;

    str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::bind1st(std::not_equal_to<char>(), ' ')));
    // example of str: warp -> sim("/sim/time/warp") endl
    int pos = str.find(" "); // getting the first space
    string var = str.substr(0, pos); // getting first substring until first space
    str = str.substr(pos + 1); // desposing the var now got left with: -> sim("/sim/time/warp") endl
    pos = str.find(" "); // getting the second space
    string arrow = str.substr(0, pos); // getting the arrow
    str = str.substr(pos + 1); // now we got left with: sim("/sim/time/warp") endl
    pos = str.find(" "); // getting the third space
    string sim = str.substr(0, pos);
    pos = sim.find("\"");
    sim = sim.substr(pos + 1);
    pos = sim.find("\"");
    sim = sim.substr(0, pos);

    bool defineVarWithoutPath = false;
    string var2 = "";
    string type = "error";
    if (arrow.compare("<-") == 0) {
        type = "get";
    } else if (arrow.compare("->") == 0) {
        type = "set";
    } else if (arrow.compare("=") == 0) {
        defineVarWithoutPath = true;
        var2=sim;
        type = "set";
    }

    if (!defineVarWithoutPath) {
        SymbolTable[var] = Var(type, sim);
    } else {
        sim =""; // cause we dont have path
        SymbolTable[var] = Var("set", sim);
        if ( SymbolTable.find("f") == SymbolTable.end() ) {
            // not found so it's must be number
            SymbolTable[var].setValue(atof(var2.c_str()));
        } else {
            // found so we'll take the value in the map
            SymbolTable[var].setValue(SymbolTable[var2].getValue());
        }

    }

    return 0;
}

//make a new var object;
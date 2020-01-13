//
// Created by yuval on 21/12/2019.
//

#include "PrintCommand.h"
int PrintCommand::execute(string str) {
    //cout << "printing using this string:     " << str << endl;
    cout << "PRINT_COMMAND: " << flush;
    int posOpenBrace = str.find("(");
    int posCloseBrace = str.find(")");
    str = str.substr(posOpenBrace + 1, posCloseBrace - posOpenBrace - 1);

    if ( SymbolTable.find(str) == SymbolTable.end() ) {
        // not found - so we print the string inside the PrintCommand
        cout <<  str << endl;
    } else {
        // found - print var and it's value
        cout <<  str  << " = " << SymbolTable[str].getValue() << endl;


    }

    return 0;
}
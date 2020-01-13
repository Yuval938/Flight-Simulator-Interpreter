//
// Created by yuval on 19/12/2019.
//

#ifndef EX3_VAR_H
#define EX3_VAR_H

#include <fstream>
#include "ex1.h"

using namespace std;

class Var {
    string type;              //get or set (<- || ->)
    string sim;
    double value;

public:
    virtual ~Var() {};

    Var() {};

    Var(string type1, string sim1) {
        this->setType(type1);
        this->setSim(sim1);
    }

    string getSim() {
        return this->sim;
    }

    string getType() {
        return this->type;
    }

    double getValue() {
        return this->value;
    }

    void setValue(double newValue) {
        this->value = newValue;
    }

    void setType(string type1) {
        this->type = type1;
    }

    void setSim(string sim1) {
        this->sim = sim1;
    }

};

#endif //EX3_VAR_H

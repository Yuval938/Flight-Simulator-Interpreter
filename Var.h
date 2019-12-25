//
// Created by yuval on 19/12/2019.
//

#ifndef EX3_VAR_H
#define EX3_VAR_H
#include <fstream>

using namespace std;

class Var {
    string type;              //get or set (<- || ->)
    string sim;
    double value;

public:
    virtual ~Var() {};
    Var(){};
    Var(string type, string sim){
        this->setType(type);
        this->setSim(sim);
    }

    string getSim() {
        return this->sim;
    }
    string getType(){
        return this->type;
    }

    double getValue(){
        return this->value;
    }

    void setValue(double newVal){
        this->value=newVal;
    }

    void setType(string type){
        this->type= type;
    }

    void setSim(string sim){
        this->sim= sim;
    }

};

#endif //EX3_VAR_H

//
// Created by valdman40 on 11/10/19.
//
#include <iostream>
#include <stack>
#include <regex>

#ifndef UNTITLED13_H
#define UNTITLED13_H

using namespace std;

// Function to convert Infix expression to postfix
string InfixToPostfix(string mathExpression);

// // Function to verify whether a char is a part of number or not.
bool IsNumber(char ch);

// Function to evaluate operator according to the assignment demands.
int operatorValue(char c);

// Function to verify whether a string is a valid var according to the assignment or not.
bool varIsValid(string basicString);

// Function to verify whether a string is a number (int\double) or not.
bool valueIsValid(string basicString);

// Function to verify whether a character is operator symbol or not.
bool IsOperator(char C);

bool isLetter(char ch);

/**
 * Expression Interface
 */
class Expression {

public:
    virtual double calculate() = 0;

    virtual ~Expression() {}
};

Expression &action(Expression *operand1, Expression *operand2, char optor);

Expression &evaluatePostfix(string str);

/**
 * Value Class
 */
class Value : public Expression {

private:
    double value;

public:

    Value(double num);

    double calculate();

};

/**
 * BinaryOperator Interface
 */
class BinaryOperator : public Expression {
protected:
    Expression *Bright;
    Expression *Bleft;

public:
    BinaryOperator(Expression *left, Expression *right);

    virtual double calculate() = 0;

    ~BinaryOperator() {
        delete (Bleft);
        delete (Bright);
    };
};

/**
 * Variable Class
 */
class Variable : public Expression {
protected:
    string expName;
    double value;

public:
    Variable(string name, double num);

    double calculate();

    Variable &operator++();

    Variable &operator--();

    Variable &operator+=(double valToAdd);

    Variable &operator-=(double valToDec);

    Variable &operator++(int);

    Variable &operator--(int);

};

/**
 * Plus Class
 */
class Plus : public BinaryOperator {
public:
    Plus(Expression *Bleft, Expression *Bright);

    double calculate();


};

/**
 * Minus Class
 */
class Minus : public BinaryOperator {
public:
    Minus(Expression *Bleft, Expression *Bright);

    double calculate();

};

/**
 * Mul Class
 */
class Mul : public BinaryOperator {
public:
    Mul(Expression *Bleft, Expression *Bright);

    double calculate();
};

/**
 * Div Class
 */
class Div : public BinaryOperator {
public:
    Div(Expression *Bleft, Expression *Bright);

    double calculate();
};

/**
 * UnaryOperator Interface
 */
class UnaryOperator : public Expression {
protected:
    Expression *Ue;
public:
    UnaryOperator(Expression *e);

    virtual double calculate() = 0;

    ~UnaryOperator() {
        delete (this->Ue);
    };
};

/**
 * UPlus Class
 */
class UPlus : public UnaryOperator {
public:
    UPlus(Expression *e);

    double calculate();
};

/**
 * UMinus Class
 */
class UMinus : public UnaryOperator {
public:
    UMinus(Expression *e);

    double calculate();

};

/**
 * Interpreter Class
 */
class Interpreter {
protected:
    std::map<string, string> variables;
public:
    Expression *interpret(string);

    void setVariables(string);
};


#endif //UNTITLED13_H

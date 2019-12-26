//
// Created by valdman40 on 11/10/19.
//

#include "ex1.h"

Variable &Variable::operator++() {
    double temp = this->value;
    ++temp;
    this->value = temp;
    return *this;
}

Variable &Variable::operator++(int) {
    double temp = this->value;
    ++temp;
    this->value = temp;
    return *this;
}

Variable &Variable::operator--() {
    double temp = this->value;
    --temp;
    this->value = temp;
    return *this;
}

Variable &Variable::operator--(int) {
    double temp = this->value;
    --temp;
    this->value = temp;
    return *this;
}

Variable &Variable::operator+=(double valToAdd) {
    this->value = this->value + valToAdd;
    return *this;
}

Variable &Variable::operator-=(double valToDec) {
    this->value = this->value - valToDec;
    return *this;
}

Variable::Variable(string name, double num) {
    this->expName = name;
    this->value = num;
}

UnaryOperator::UnaryOperator(Expression *e) {
    this->Ue = e;
}

BinaryOperator::BinaryOperator(Expression *left, Expression *right) {
    this->Bleft = left;
    this->Bright = right;
}

Value::Value(double num) {
    this->value = num;
}

UPlus::UPlus(Expression *e) : UnaryOperator(e) {
    this->Ue = e;
}

UMinus::UMinus(Expression *e) : UnaryOperator(e) {
    this->Ue = e;
}

Plus::Plus(Expression *left, Expression *right) : BinaryOperator(left, right) {
    this->Bleft = left;
    this->Bright = right;
}

Minus::Minus(Expression *left, Expression *right) : BinaryOperator(left, right) {
    this->Bleft = left;
    this->Bright = right;
}

Div::Div(Expression *left, Expression *right) : BinaryOperator(left, right) {
    this->Bleft = left;
    this->Bright = right;
}

Mul::Mul(Expression *left, Expression *right) : BinaryOperator(left, right) {
    this->Bleft = left;
    this->Bright = right;
}

double UMinus::calculate() {
    return -(this->Ue->calculate());
}

double UPlus::calculate() {
    return (this->Ue->calculate());
}

double Div::calculate() {
    double right = this->Bright->calculate();
    if (right == 0) {
        throw "division by zero";
    } else {
        return this->Bleft->calculate() / right;
    }
}

double Mul::calculate() {
    return this->Bleft->calculate() * this->Bright->calculate();
}

double Variable::calculate() {
    return (this->value);
}

double Plus::calculate() {
    return this->Bleft->calculate() + this->Bright->calculate();
}

double Minus::calculate() {
    return this->Bleft->calculate() - this->Bright->calculate();
}

double Value::calculate() {
    return this->value;
}

bool IsNumber(char ch) {
    if ((ch >= '0' && ch <= '9') || ch == '.') {
        return true;
    }
    return false;
}

bool IsOperator(char C) {
    if (C == '+' || C == '-' || C == '*' || C == '/' || C == '&' || C == '%') {
        return true;
    }
    return false;
}

bool areParenthesisBalanced(string expr) {
    stack<char> s;
    char x;
    int length = expr.length();

    for (int i = 0; i < length; i++) {
        x = expr.at(i);
        if (x == '(') {
            s.push(x);
        } else if (x == ')') {
            if ((!s.empty()) && (s.top() == '(')) {
                s.pop();
            } else { // there was no matching pair for this Parenthesis
                return false;
            }
        }
    }
    return true;
}

bool validMathExpression(string expression) {
    int length = expression.length();
    char ch = expression.at(0);
    if (ch == '*' || ch == '/' || ch == ')') {
        return false;
    }
    for (int i = 0; i < length; i++) {
        ch = expression.at(i);
        if (!IsNumber(ch) && !IsOperator(ch) && ch != ('(') && ch != (')') && ch != '.') {
            return false;
        }
        if (i > 0) {
            if ((ch == '-' && expression.at(i - 1) == '-')
                || (ch == '+' && expression.at(i - 1) == '+')
                || (ch == '*' && expression.at(i - 1) == '*')
                || (ch == '/' && expression.at(i - 1) == '/')) {
                return false;
            }
        }
        // check if we got ')(' in a row
        if( (i < length - 1) && ch == ')' && expression.at(i + 1) == '('){
            return false;
        }
    }

    // the string is a valid expression, now we check if it's parenthesis are valid
    return areParenthesisBalanced(expression);
}

bool isLetter(char ch) {
    if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))) {
        return false;
    }
    return true;
}

bool validSetVeriableInput(string str) {

    // check all of the string if it has illigal chars
    int length = str.length();
    char ch = str.at(0);
    for (int i = 1; i < length; i++) {
        ch = str.at(i);
        if (!isLetter(ch) && !IsNumber(ch) && !IsOperator(ch) && ch != '=' && ch != ';' && ch != '_') {
            if (!isLetter(ch) && !IsNumber(ch) && !IsOperator(ch) && ch != '=' && ch != ';' && ch != '_') {
                return false;
            }
            if ((ch == ';' && str.at(i - 1) == ';')
                || (ch == '=' && str.at(i - 1) == '=')
                || (ch == '_' && str.at(i - 1) == '_')) {
                return false;
            }
        }
    }

    // check for every var and val if they are valid as well
    int start = 0;
    for (int i = 0; i < length; i++) {
        if (str[i] == ';' || i == length - 1) {
            if (i == length - 1) {
                i++;
            }
            string substr = str.substr(start, i - start); // now we got substring from ';' to ';'
            int substrLength = substr.length();
            string var = "";
            int j = 0;
            while (j < substrLength && (substr.at(j) != '=')) {
                var += substr.at(j);
                j++;
            }

            if (!varIsValid(var)) {
                return false;
            }

            j++;
            string value = "";
            while (j < substrLength && (substr.at(j) != ';')) {
                value += substr.at(j);
                j++;
            }

            if (!valueIsValid(value)) {
                return false;
            }

            start = i + 1;
        }
    }

    return true;
}

bool valueIsValid(string value) {
    int length = value.length();
    if (value.at(0) == '.') {
        return false;
    }
    for (int i = 0; i < length; i++) {
        if (!IsNumber(value.at(i)) &&
            value.at(i) != '-') { // check that each char in the value is actually a number or '.' , '-'
            return false;
        }
    }
    return true;
}

bool varIsValid(string var) {
    char firstChar = var.at(0);
    if (!isLetter(firstChar)) {
        return false;
    }
    int length = var.length();
    for (int i = 1; i < length; i++) {
        if (i == 1) { // part of the assignment demands
            if (var.at(i) == ';' || var.at(i) == '=' || IsOperator(var.at(i))) {
                return false;
            }
        }
        if (var.at(i) == '.' || var.at(i) == ';' || var.at(i) == '=')
            return false;
    }
    return true;
}

int operatorValue(char c) {
    if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else if (c == '&' || c == '%')
        return 3;
    else
        return -1;
}

string InfixToPostfix(string mathExpression) {
    stack<char> operatorStack;
    char token;
    string postfix = "";
    string infixString = "";
    int length = mathExpression.length();
    // first, we'll make all the unary numbers more visual for us, we'll sign
    // them with '&' (for UMinus) and '%' (for UPlus)
    for (int i = 0; i < length; i++) {
        token = mathExpression.at(i);
        if (token == '-' || token == '+') {
            if (i == 0 || mathExpression.at(i - 1) == '(' || mathExpression.at(i - 1) == '/'
                || mathExpression.at(i - 1) == '*') {
                if (token == '-') {
                    infixString += "&";
                } else {
                    infixString += "%";
                }
            } else {
                infixString += token;
            }
        } else {
            infixString += token;
        }
    }
    bool writingANum = false;
    for (int i = 0; i < length; i++) {
        token = infixString.at(i); // Reads the next token each loop
        if (IsNumber(token)) {
            if (writingANum) {
                postfix += token; // because we dont need a space
            } else {
                postfix = postfix + " " + token;
            }
            writingANum = true;
        } else if (IsOperator(token)) {
            writingANum = false;
            while (!operatorStack.empty() && (operatorValue(token) <= operatorValue(operatorStack.top()))) {
                postfix = postfix + " " + operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(token);
        } else if (token == '(') {
            operatorStack.push(token);
        } else if (token == ')') {
            while (operatorStack.top() != '(') {
                postfix = postfix + " " + operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop(); // discard '('
        }
    }

    while (!operatorStack.empty()) {
        postfix = postfix + " " + operatorStack.top();
        operatorStack.pop();
    }

    return postfix;
}

stack<string> getSubStrings(string str, char separator) {
    stack<string> s;
    int i = 0;
    int len = str.length();
    while (i < len) {
        // separating each substrings (stops when engage separator)
        int startSubString = i;
        while (i < len && separator != str.at(i)) {
            // here need to add illegal characters check
            i++;
        }
        int subStringLength = i - startSubString;
        string subString = str.substr(startSubString, subStringLength);
        s.push(subString);
        i++;
    }

    return s;

}

void Interpreter::setVariables(string str) {
    if (!validSetVeriableInput(str)) {
        throw "illegal variable assignment!";
    }
    stack<string> subStrings = getSubStrings(str, ';');
    while (!subStrings.empty()) {
        stack<string> varAndVal = getSubStrings(subStrings.top(), '=');
        string value = varAndVal.top();
        varAndVal.pop();
        string var = varAndVal.top();
        this->variables[var] = value;
        subStrings.pop();
    }
}

Expression *Interpreter::interpret(string str) {
    for (auto const &x : this->variables) {
        str = regex_replace(str, regex(x.first), "(" + x.second + ")");
    }

    // check if there are still characters in the expression
    bool legal = true;
    int length = str.length();
    for (int i = 0; i < length; i++) {
        if (isLetter(str.at(i))) {
            legal = false;
            break;
        }
    }

    if (!validMathExpression(str) || !legal) {
        throw "illegal math expression";
    }

    string pfString = InfixToPostfix(str);
    return &evaluatePostfix(pfString);
}

Expression &evaluatePostfix(string str) {
    stack<Expression *> expStack;
    int len = str.length();
    int i;
    char optor;
    for (i = 0; i < len; i++) {
        if (str.at(i) == ' ') {
            i++;
            if (IsNumber(str.at(i))) {
                string numString = "";
                while (i<len && IsNumber(str.at(i))) {
                    numString += str.at(i);
                    i++;
                }
                i--;
                Value *newNum = new Value(atof(numString.c_str()));
                expStack.push(newNum);
            } else {
                optor = str.at(i);
                if (optor != '&' && optor != '%') {
                    if (expStack.empty()) {
                        throw "Bad Input";
                    }
                    Expression *operand2 = expStack.top();
                    expStack.pop();
                    if (expStack.empty()) {
                        throw "Bad Input";
                    }
                    Expression *operand1 = expStack.top();
                    expStack.pop();
                    expStack.push(&action(operand1, operand2, optor));
                } else { // we got unary number so we push it alone instead of 2 elements
                    Expression *u;
                    if (optor == '&') {
                        u = new UMinus(expStack.top());
                    } else {
                        u = new UPlus(expStack.top());
                    }
                    expStack.pop();
                    expStack.push(u);
                }
            }
        }
    }
    return *expStack.top();
}


Expression &action(Expression *operand1, Expression *operand2, char optor) {
    Expression *e;
    if (optor == '+') { e = new Plus(operand1, operand2); }
    if (optor == '-') { e = new Minus(operand1, operand2); }
    if (optor == '*') { e = new Mul(operand1, operand2); }
    if (optor == '/') { e = new Div(operand1, operand2); }

    return *e;
}


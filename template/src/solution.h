#pragma once

#include <stdexcept>

inline bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

inline bool isOperation(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

inline double toDouble(char c)
{
    if(c < '0' || c > '9')
        throw std::invalid_argument("Non-digit passed to toDouble()");
        
    return c - '0';
}

inline int priority(char op)
{
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            throw std::invalid_argument("incorrect operation");
    }
}

double perform(char operation, double left, double right);

bool verify(const char* expression);
double evaluate(const char* expression);
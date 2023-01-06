#pragma once
#include <stack>
#include <string>

bool isCorrect(const char* expression);

bool find(std::stack<char> source, char value);
bool openedBracketClosed(std::stack<char> source, char open, char close);
bool areBracketsBalanced(std::string expr);
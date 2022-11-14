#include "solution.h"

#include <cassert>
#include <cmath>
#include <stdexcept>
#include <stack>

#include <iostream>

//time to finish the task: 6 hours 
//time the task SHOULD be completed: 1 hour

/// Performs an operation on two arguments
///
/// @param operation
///    The code of the operation as a character. Can be +, -, *, / or ^
///
/// @param left
///    First argument of the operation 
///
/// @param right
///    Second argument of the operation
///
/// @exception std::invalid_argument
///    If an invalid operation is passed to the function or
///    if the operation is division (/) and the right argument is 0.
///
double perform(char operation, double left, double right)
{
	switch(operation) {
		case '+': return left + right;
		case '-': return left - right;
		case '*': return left * right;
		case '^': return std::pow(left, right);
		case '/':
			if(right == 0)
				throw std::invalid_argument("Division by zero");
			return left / right;
		
		default:
			throw std::invalid_argument("Invalid operation symbol passed to perform()");
	}
}

bool verify(const char* expression)
{
	//TODO Complete this function
	std::string express;
	if (expression == nullptr) {
		return false;
	}
	else if (expression == "") {
		return true;
	}
	express = expression;
	std::stack<char> expr;
	for (size_t i = 0; i < express.length(); i++)
	{
		expr.push(express.at(i));
	}
	int count = 0;
	while (!expr.empty()) {
		if(!isDigit(expr.top()) && (count%2==0 || expr.size() == 1)) {
			return false;
		}
		else if (!isOperation(expr.top()) && count % 2 == 1) {
			return false;
		}
		++count;
		expr.pop();
	}

	return count==express.length();
}

double evaluate(const char* expression)
{
	int i = 0;
	if (!verify(expression)) {
		throw std::invalid_argument("Your argument is not a valid statement");
	}
	std::stack<double> arguments;
	std::stack<char> operations;
	std::string express = expression;
	for (i =0; i < express.length(); ++i)
	{
		if (isDigit(express.at(i))) {
			int val = 0;
			while (i < express.length() &&
				isdigit(express[i]))
			{
				val = (val * 10) + (express[i] - '0');
				i++;
			}

			arguments.push(val);
			i--;
		}
		else if (isOperation(express.at(i))) {
			while (!operations.empty() && priority(operations.top())
				>= priority(express[i])) {
				int val2 = arguments.top();
				arguments.pop();

				int val1 = arguments.top();
				arguments.pop();

				char op = operations.top();
				operations.pop();

				arguments.push(perform(val1, val2, op));
			}

			// Push current token to 'ops'.
			operations.push(express[i]);
		}
		while (!operations.empty()) {
			int val2 = arguments.top();
			arguments.pop();

			int val1 = arguments.top();
			arguments.pop();

			char op = operations.top();
			operations.pop();

			arguments.push(perform(val1, val2, op));
		}

		// Top of 'values' contains result, return it.
		return arguments.top();
	
}

double evaluate(const char* expression)
{
	int result = 0;
	if (!verify(expression)) {
		throw std::invalid_argument("Your argument is not a valid statement");
	}
	std::stack<double> arguments;
	std::stack<char> operations;
	std::string express = expression;
	for (int i = express.length() - 1; i >= 0; --i)
	{
		if (isDigit(express.at(i))) {
			arguments.push(toDouble(express.at(i)));
		}
		else if (isOperation(express.at(i))) {
			operations.push(express.at(i));
		}
	}
	std::stack<char> oper; //this part is a sorting algorithm found in GreekCodes 

	while (!operations.empty())
	{
		char temp = operations.top();
		operations.pop();
		while (!oper.empty() && priority(temp) < priority(oper.top()))
		{
			operations.push(oper.top());
			oper.pop();

		}
		oper.push(temp);
	}
	while (!arguments.empty()) {
		double left = arguments.top();
		arguments.pop();
		double right = arguments.top(); 
		arguments.pop();
		std::cout << oper.top() << " ";
		result = perform(oper.top(), left, right);
		oper.pop();
		if (oper.empty()) break;
		arguments.push(result);
	}

	std::cout << "\n";
	return result;
}

///not working with operation order

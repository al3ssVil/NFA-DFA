#include <iostream>
#include <stack>

bool isOperator(char c)
{
	return (c == '|' || c == '.' || c == '*');
}

bool IsValidExpresion(const std::string& r)
{
	std::stack<char> stack;
	bool lastOperand = false;
	bool lastOperator = true;
	for (auto i = 0; i < r.size(); ++i)
	{
		char c = r[i];
		if (isalnum(static_cast<unsigned char>(r[i])))
		{
			lastOperator = false;
			lastOperand = true;
		}
		else
		{
			if (c == '.')
			{
				if (i + 1 >= r.size())
					return false;
				if (i + 1 < r.size() && isOperator(r[i + 1]))
					return false;
				lastOperator = true;
				lastOperand = false;
			}
			else
			{
				if (c == '(')
				{
					stack.push(c);
					lastOperator = true;
					lastOperand = false;
				}
				else
				{
					if (c == ')')
					{
						if (stack.empty())
							return false;
						stack.pop();
						lastOperator = true;
						lastOperand = false;
					}
					else
					{
						if (!isOperator(c))
							return false;
						else
						{
							if (c == '|')
							{
								if (i == 0)
									return false;
								if (i + 1 >= r.size())
									return false;
								if (i - 1 < 0)
									return false;
								if (i + 1 < r.size() && (r[i + 1] == ')' || isOperator(r[i + 1])))
									return false;
								lastOperator = true;
								lastOperand = false;
							}
							else
							{
								if (c == '*')
								{
									if (i - 1 < 0)
										return false;
									if (i - 1 > 0 && r[i - 1] == '|')
										return false;
									lastOperator = true;
									lastOperand = false;
								}
							}
						}
					}
				}
			}
		}
	}
	return stack.empty();
}

int precedence(char op)
{
	if (op == '*') 
		return 3;
	if (op == '.')  
		return 2;
	if (op == '|')  
		return 1;
	return 0;
}

std::string addConcatenation(const std::string& regex)
{
	std::string result;
	for (size_t i = 0; i < regex.size(); ++i)
	{
		char current = regex[i];
		result += current;

		if (i + 1 < regex.size())
		{
			char next = regex[i + 1];

			if ((isalnum(current) || current == ')' || current == '*') && (isalnum(next) || next == '('))
			{
				result += '.';
			}
		}
	}
	return result;
}

std::string infixToPostfix(const std::string& infix)
{
	std::stack<char> operators;  
	std::string postfix;        

	for (size_t i = 0; i < infix.length(); ++i)
	{
		char current = infix[i];

		if (isalnum(current))
		{
			postfix += current;  
		}
		else if (current == '(')
		{
			operators.push(current);
		}
		else if (current == ')')
		{
			while (!operators.empty() && operators.top() != '(')
			{
				postfix += operators.top();
				operators.pop();
			}
			operators.pop(); 
		}
		else if (isOperator(current))
		{
			while (!operators.empty() && precedence(operators.top()) >= precedence(current))
			{
				postfix += operators.top();  
				operators.pop();
			}
			operators.push(current);  
		}
	}

	while (!operators.empty())
	{
		postfix += operators.top();
		operators.pop();
	}

	return postfix;
}

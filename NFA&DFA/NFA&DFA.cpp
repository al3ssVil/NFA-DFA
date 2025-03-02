#include "NFAclass.h"
#include "DFAclass.h"
#include <fstream>

int main()
{
	std::string r;
	std::ifstream f("file.in");
	f >> r;
	if (IsValidExpresion(r))
	{
		std::cout << "Expression is valid: " << r << std::endl;
		r = addConcatenation(r);

		std::cout << "\nConcatenate form: " << r << std::endl;
		std::string postFixForm = infixToPostfix(r);

		std::cout << "\nPostfixed form is: " << postFixForm << std::endl;
		NFA nfa = buildNFA(r);

		std::cout << "\nNFA FORM\n";
		nfa.printNFA();

		std::cout << "\nDFA FORM\n";
		DeterministicFiniteAutomaton dfa = convertRegextoDFA(r);
		dfa.PrintAutomaton();

		std::cout << "\nDFA FORM AS TABLE\n";
		dfa.PrintAutomatonTable();

		std::cout << '\n';

		dfa.saveAutomatonToFile("file.out");

		std::cout << '\n';

		std::string word;
		std::cout << "Check word: ";
		std::cin >> word;
		if (dfa.CheckWord(word))
			std::cout << "\nThe word is accepted by ADF!\n";
		else
			std::cout << "\nThe word is not accepted by AFD!\n";
	}
	else
	{
		std::cout << "Expression is invalid." << std::endl;
	}
	return 0;
}

#include "NFAclass.h"
#include "DFAclass.h"
#include <fstream>

int main()
{
	std::string r;
	std::ifstream f("fisier.in");
	f >> r;
	if (IsValidExpresion(r))
	{
		std::cout << "Expression is valid: " << r << std::endl;
		r = addConcatenation(r);

		std::cout << "Concatenate form: " << r << std::endl;
		std::string postFixForm = infixToPostfix(r);

		std::cout << "Postfixed form is: " << postFixForm << std::endl;
		NFA nfa = buildNFA(r);

		std::cout << "NFA FORM\n";
		nfa.printNFA();

		std::cout << "\nDFA FORM\n";
		DeterministicFiniteAutomaton dfa = convertRegextoDFA(r);
		dfa.PrintAutomaton();

		std::cout << "\nDFA FORM AS TABLE\n";
		dfa.PrintAutomatonTable();

		dfa.saveAutomatonToFile("file.out");

		std::string word;
		std::cout << "Check word: ";
		std::cin >> word;
		if (dfa.CheckWord(word))
			std::cout << "The word is accepted by ADF!";
		else
			std::cout << "The word is not accepted by AFD!";
	}
	else
	{
		std::cout << "Expression is invalid." << std::endl;
	}
	return 0;
}

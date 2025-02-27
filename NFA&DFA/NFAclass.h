#include <iostream>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include "ValidRegex&Postfix.h"

struct StateComparator
{
	bool operator()(const std::string& a, const std::string& b) const
	{
		int num_a = std::stoi(a.substr(1));  
		int num_b = std::stoi(b.substr(1));  
		return num_a < num_b;  
	}
};

struct TransitionComparator
{
	bool operator()(const std::pair<std::string, char>& a, const std::pair<std::string, char>& b) const
	{
		int num_a = std::stoi(a.first.substr(1));
		int num_b = std::stoi(b.first.substr(1));

		if (num_a == num_b)
		{
			return a.second < b.second;
		}
		return num_a < num_b;
	}
};

class NFA
{
public:
	std::set<std::string, StateComparator> states;
	std::set<char> alphabet;
	std::map<std::pair<std::string, char>, std::set<std::string>, TransitionComparator> transitions;
	std::string start_state;
	std::set<std::string> final_states;

	NFA() : start_state("q0")
	{

	}

	void addState(const std::string& state)
	{
		states.insert(state);
	}

	void addAlphabet(char symbol)
	{
		alphabet.insert(symbol);
	}

	void addTransition(const std::string& from, char symbol, const std::string& to)
	{
		transitions[{from, symbol}].insert(to);
	}

	void addEpsilonTransition(const std::string& from, const std::string& to)
	{
		transitions[{from, 'λ'}].insert(to);
	}

	void printNFA()
	{
		std::cout << "States: ";
		for (const auto& state : states)
			std::cout << state << " ";
		std::cout << std::endl;

		std::cout << "Alphabet: ";
		for (const auto& symbol : alphabet)
			std::cout << symbol << " ";
		std::cout << std::endl;

		std::cout << "Start State: " << start_state << std::endl;

		std::cout << "Final States: ";
		for (const auto& final_state : final_states)
			std::cout << final_state << " ";
		std::cout << std::endl;

		std::cout << "Transitions: " << std::endl;
		for (const auto& transition : transitions)
		{
			for (const auto& to_state : transition.second)
			{
				if (transition.first.second == 'λ')
				{
					std::cout << "(" << transition.first.first << ", lambda) -> " << to_state << std::endl;
				}
				else
				{
					std::cout << "(" << transition.first.first << ", " << transition.first.second << ") -> " << to_state << std::endl;
				}
			}
		}
	}

};

NFA buildNFA(const std::string& r)
{
	std::stack<NFA> nfa_stack;
	int state_counter = 0;
	std::string postfix = infixToPostfix(r);

	for (char c : postfix)
	{
		if (isalnum(c))
		{  
			NFA nfa;
			std::string state1 = "q" + std::to_string(state_counter++);
			std::string state2 = "q" + std::to_string(state_counter++);

			nfa.states.insert(state1);
			nfa.states.insert(state2);

			nfa.start_state = state1;
			nfa.final_states.insert(state2);

			nfa.addAlphabet(c); 

			nfa.addTransition(state1, c, state2);

			nfa_stack.push(nfa);
		}
		else if (c == '|')
		{  
			NFA nfa2 = nfa_stack.top(); nfa_stack.pop();
			NFA nfa1 = nfa_stack.top(); nfa_stack.pop();

			NFA nfa;
			std::string start_state = "q" + std::to_string(state_counter++);
			std::string final_state = "q" + std::to_string(state_counter++);

			nfa.states.insert(start_state);
			nfa.states.insert(final_state);

			nfa.start_state = start_state;
			nfa.final_states.insert(final_state);

			nfa.addEpsilonTransition(start_state, nfa1.start_state);
			nfa.addEpsilonTransition(start_state, nfa2.start_state);

			for (const auto& state : nfa1.final_states)
				nfa.addEpsilonTransition(state, final_state);
			for (const auto& state : nfa2.final_states)
				nfa.addEpsilonTransition(state, final_state);

			nfa.states.insert(nfa1.states.begin(), nfa1.states.end());
			nfa.states.insert(nfa2.states.begin(), nfa2.states.end());

			nfa.transitions.insert(nfa1.transitions.begin(), nfa1.transitions.end());
			nfa.transitions.insert(nfa2.transitions.begin(), nfa2.transitions.end());

			nfa.alphabet.insert(nfa1.alphabet.begin(), nfa1.alphabet.end());
			nfa.alphabet.insert(nfa2.alphabet.begin(), nfa2.alphabet.end());

			nfa_stack.push(nfa);
		}
		else if (c == '.')
		{  
			NFA nfa2 = nfa_stack.top(); nfa_stack.pop();
			NFA nfa1 = nfa_stack.top(); nfa_stack.pop();

			for (const auto& final_state : nfa1.final_states)
				nfa1.addEpsilonTransition(final_state, nfa2.start_state);  

			nfa1.final_states = nfa2.final_states;
			nfa1.states.insert(nfa2.states.begin(), nfa2.states.end());
			nfa1.transitions.insert(nfa2.transitions.begin(), nfa2.transitions.end());
			nfa1.alphabet.insert(nfa2.alphabet.begin(), nfa2.alphabet.end());

			nfa_stack.push(nfa1);
		}
		else if (c == '*')
		{  
			NFA nfa = nfa_stack.top(); nfa_stack.pop();

			std::string start_state = "q" + std::to_string(state_counter++);
			std::string final_state = "q" + std::to_string(state_counter++);

			nfa.states.insert(start_state);
			nfa.states.insert(final_state);

			nfa.addEpsilonTransition(start_state, nfa.start_state);
			nfa.addEpsilonTransition(start_state, final_state);

			for (const auto& state : nfa.final_states)
			{
				nfa.addEpsilonTransition(state, nfa.start_state);
				nfa.addEpsilonTransition(state, final_state);
			}

			nfa.start_state = start_state;
			nfa.final_states.clear();
			nfa.final_states.insert(final_state);
			nfa_stack.push(nfa);
		}
	}

	return nfa_stack.top();
}

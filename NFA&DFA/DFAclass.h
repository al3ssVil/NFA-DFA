#include <set>
#include <map>
#include <string>
#include <iostream>
#include <queue>
#include <iomanip>
#include <fstream>

struct NumericStateComparator
{
	bool operator()(const std::string& a, const std::string& b) const
	{
		int num_a = std::stoi(a.substr(1));  
		int num_b = std::stoi(b.substr(1));  

		return num_a < num_b; 
	}
};

struct NumericTransitionComparator
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

class DeterministicFiniteAutomaton
{
public:
	DeterministicFiniteAutomaton() : q0{ q0 }
	{

	};

	DeterministicFiniteAutomaton(std::set<std::string, NumericStateComparator> Q, std::set<char> Sigma, std::map<std::pair<std::string, char>, std::string, NumericTransitionComparator> delta, std::string q0, std::set<std::string, NumericStateComparator> F)
		: Q(Q), Sigma(Sigma), delta(delta), q0(q0), F(F)
	{

	}

	bool VerifyAutomaton()
	{
		if (Q.find(q0) == Q.end())
		{
			std::cout << "Starea initiala nu este valida!" << std::endl;
			return false;
		}
		for (const auto& state : F)
		{
			if (Q.find(state) == Q.end())
			{
				std::cout << "Starea finala " << state << " nu este in Q!" << std::endl;
				return false;
			}
		}

		for (const auto& state : Q)
		{
			for (const auto& symbol : Sigma)
			{
				if (delta.find({ state, symbol }) == delta.end())
				{
					std::cout << "Nu există tranziție definită pentru " << state << " cu simbolul " << symbol << std::endl;
					return false;
				}
			}
		}

		return true;
	}

	void PrintAutomaton()
	{
		std::cout << "Starile Q: ";
		for (const auto& state : Q)
		{
			std::cout << state << " ";
		}
		std::cout << std::endl;

		std::cout << "Alfabetul Sigma: ";
		for (const auto& symbol : Sigma)
		{
			std::cout << symbol << " ";
		}
		std::cout << std::endl;

		std::cout << "Starea initiala q0: " << q0 << std::endl;

		std::cout << "Starile finale F: ";
		for (const auto& finalState : F)
		{
			std::cout << finalState << " ";
		}
		std::cout << std::endl;

		std::cout << "Functia de tranzitie delta:" << std::endl;
		for (const auto& transition : delta)
		{
			std::cout << "(" << transition.first.first << ", " << transition.first.second << ") -> " << transition.second << std::endl;
		}
	}

	void PrintAutomatonTable()
	{
		std::cout << "Starile Q: ";
		for (const auto& state : Q)
		{
			std::cout << state << " ";
		}
		std::cout << std::endl;

		std::cout << "Alfabetul Sigma: ";
		for (const auto& symbol : Sigma)
		{
			std::cout << symbol << " ";
		}
		std::cout << std::endl;

		std::cout << "Starea initiala q0: " << q0 << std::endl;

		std::cout << "Starile finale F: ";
		for (const auto& finalState : F)
		{
			std::cout << finalState << " ";
		}
		std::cout << std::endl;

		std::cout << "Functia de tranzitie delta:" << std::endl;

		std::cout << std::setw(15) << "Starea/Simb. ";
		for (const auto& symbol : Sigma)
		{
			std::cout << std::setw(10) << symbol;
		}
		std::cout << std::endl;

		for (const auto& state : Q)
		{
			std::cout << std::setw(15) << state;  

			for (const auto& symbol : Sigma)
			{
				auto transition = delta.find({ state, symbol });
				if (transition != delta.end())
					std::cout << std::setw(10) << transition->second;
				else
					std::cout << std::setw(10) << "-";
			}
			std::cout << std::endl;
		}

	}

	bool CheckWord(const std::string& word)
	{
		std::string currentState = q0;  
		for (char symbol : word)
		{
			auto transition = delta.find({ currentState, symbol });
			if (transition != delta.end())
			{
				currentState = transition->second; 
			}
			else
			{
				return false;  
			}
		}

		return F.find(currentState) != F.end();
	}

	void saveAutomatonToFile(const std::string& filename) {
		std::ofstream fout(filename);
		if (!fout.is_open())
		{
			std::cerr << "Error opening file for writing!" << std::endl;
			return;
		}
		fout << "DFA States:\n";
		for (const auto& state : Q)
		{
			fout << state << " ";
		}
		fout << "\nAlphabet:\n";
		for (const auto& symbol : Sigma)
		{
			fout << symbol << " ";
		}
		fout << "\nTransitions:\n";
		for (const auto& transition : delta)
		{
			fout << transition.first.first << " -- " << transition.first.second << " --> " << transition.second << "\n";
		}
		fout << "Start State: " << q0 << "\n";
		fout << "Final States:\n";
		for (const auto& state : F)
		{
			fout << state << " ";
		}
		fout.close();
		std::cout << "Automaton saved to file: " << filename << std::endl;
	}

private:
	std::set<std::string, NumericStateComparator> Q; 
	std::set<char> Sigma;
	std::map<std::pair<std::string, char>, std::string, NumericTransitionComparator> delta; 
	std::string q0;  
	std::set<std::string, NumericStateComparator> F; 
};

std::set<std::string> epsilonClosure(const NFA& nfa, const std::set<std::string>& states)
{
	std::set<std::string> closure = states;
	std::stack<std::string> to_process;

	for (const auto& state : states)
		to_process.push(state);

	while (!to_process.empty())
	{
		std::string current = to_process.top();
		to_process.pop();

		auto transition = nfa.transitions.find({ current, 'λ' });
		if (transition != nfa.transitions.end())
		{
			for (const auto& next_state : transition->second)
			{
				if (closure.insert(next_state).second)
				{ 
					to_process.push(next_state);
				}
			}
		}
	}

	return closure;
}

DeterministicFiniteAutomaton convertRegextoDFA(const std::string& r)
{
	NFA nfa = buildNFA(r);  

	std::set<std::string, NumericStateComparator> dfaStates;  
	std::set<char> dfaAlphabet = nfa.alphabet;  
	std::map<std::pair<std::string, char>, std::string, NumericTransitionComparator> dfaDelta;  
	std::set<std::string, NumericStateComparator> dfaFinalStates; 
	std::map<std::set<std::string>, std::string> stateMapping; 

	std::set<std::string> startState = epsilonClosure(nfa, { nfa.start_state });
	std::string startStateName = "q0"; 
	stateMapping[startState] = startStateName;
	dfaStates.insert(startStateName);

	std::cout << "Start DFA state: " << startStateName << std::endl;

	std::queue<std::set<std::string>> stateQueue;
	stateQueue.push(startState);

	for (const auto& state : startState)
	{
		if (nfa.final_states.count(state))
		{
			dfaFinalStates.insert(startStateName);
			break;  
		}
	}

	while (!stateQueue.empty())
	{

		std::set<std::string> currentStateSet = stateQueue.front();
		stateQueue.pop();

		if (currentStateSet.empty())
		{
			continue;  
		}

		std::string currentDFAState = stateMapping[currentStateSet];

		for (const auto& state : currentStateSet)
		{
			if (nfa.final_states.count(state))
			{
				dfaFinalStates.insert(currentDFAState);
				break;  
			}
		}

		for (char symbol : dfaAlphabet)
		{
			std::set<std::string> nextStateSet;
			for (const auto& state : currentStateSet)
			{
				auto transition = nfa.transitions.find({ state, symbol });
				if (transition != nfa.transitions.end())
				{
					nextStateSet.insert(transition->second.begin(), transition->second.end());
				}
			}

			std::set<std::string> nextEpsilonClosure = epsilonClosure(nfa, nextStateSet);
			if (nextEpsilonClosure.empty())
			{
				continue;
			}

			std::string nextStateName;
			if (stateMapping.find(nextEpsilonClosure) == stateMapping.end())
			{
				nextStateName = "q" + std::to_string(stateMapping.size());
				stateMapping[nextEpsilonClosure] = nextStateName;
				dfaStates.insert(nextStateName);
				stateQueue.push(nextEpsilonClosure);
			}
			else
			{
				nextStateName = stateMapping[nextEpsilonClosure];
			}

			dfaDelta[{currentDFAState, symbol}] = nextStateName;

			for (const auto& state : nextEpsilonClosure)
			{
				if (nfa.final_states.count(state))
				{
					dfaFinalStates.insert(nextStateName);
					break;  
				}
			}
		}
	}

	return DeterministicFiniteAutomaton(dfaStates, dfaAlphabet, dfaDelta, startStateName, dfaFinalStates);
}

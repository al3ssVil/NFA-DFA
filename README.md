# Converting Regex to Deterministic Finite Automaton (DFA) and Non-deterministic Finite Automaton (NFA)
## Description
This project implements an algorithm that converts a regular expression (regex) into a Non-deterministic Finite Automaton (NFA) and further converts it into a Deterministic Finite Automaton (DFA). These automata can be used to check whether a given word is accepted by the automaton derived from the regular expression.

Project Steps:
Regex Validation: The regular expression is validated to ensure it follows correct syntax.

Concatenation Handling: The concatenation operator (.) is added where necessary in the regular expression.

Conversion to Postfix: The regular expression is converted from infix notation to postfix (Reverse Polish notation).

Building an NFA: The regular expression is used to construct a Non-deterministic Finite Automaton.

Conversion to DFA: The NFA is then converted into a Deterministic Finite Automaton (DFA).

Word Checking: A function is provided to check if a given word is accepted by the generated DFA.

## Project Structure
Main Files:

main.cpp: Contains the main implementation, which takes a regular expression, constructs the NFA and DFA, and allows checking a word.

NFAclass.h: Defines the NFA class, representing a Non-deterministic Finite Automaton.

DFAclass.h: Defines the DeterministicFiniteAutomaton class, representing a Deterministic Finite Automaton.

ValidRegex&Postfix.h: Contains functions for validating the regular expression and converting it from infix to postfix.

## How to Use the Code
You need a C++ compiler and the source files set up properly in your project.

Steps to Run
Open the main file (main.cpp) and ensure that the input file (fisier.in) contains the regular expression you want to validate and convert.

Example input file (fisier.in):
![image](https://github.com/user-attachments/assets/61ef4075-6568-4cc7-8c71-f42edfc134b1)

Compile and run the program.

Enter a word for checking. After running, the program will prompt you for a word to check if it is accepted by the generated DFA.

Example interaction:

![image](https://github.com/user-attachments/assets/b272d4ff-becf-458e-aed3-6268f0f74e8a)

![image](https://github.com/user-attachments/assets/06d50440-94a3-4b9b-a1a2-c1bfa4ad5c88)

![image](https://github.com/user-attachments/assets/9708e81a-bf30-492b-96a4-2548ac144cfb)


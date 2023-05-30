#include "../structures/finite_automaton.h"

// define lambda closure function. It takes a set of states and returns a set of states
Node* lambdaClosure(NDFA ndfa, Node* set);

// define move function. It takes a set of states and a symbol and returns a set of states
Node* move(NDFA ndfa, Node* set, int symbol);

// convert NDFA to DFA
DFA convertNDFAtoDFA(NDFA ndfa);
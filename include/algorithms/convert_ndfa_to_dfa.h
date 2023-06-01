#ifndef ALGORITHMS_CONVERT_NDFA_TO_DFA_H
#define ALGORITHMS_CONVERT_NDFA_TO_DFA_H

#include "../structures/ndfa.h"
#include "../structures/dfa.h"

// define lambda closure function. It takes a set of states and returns a set of states
Node* lambdaClosure(NDFA ndfa, Node* set);

// define move function. It takes a set of states and a symbol and returns a set of states
Node* move(NDFA ndfa, Node* set, int symbol);

// convert NDFA to DFA
DFA convertNDFAtoDFA(NDFA ndfa);

#endif
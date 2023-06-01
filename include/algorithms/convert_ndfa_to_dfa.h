#ifndef ALGORITHMS_CONVERT_NDFA_TO_DFA_H
#define ALGORITHMS_CONVERT_NDFA_TO_DFA_H

#include "../structures/ndfa.h"
#include "../structures/dfa.h"

/**
 * This function define lambda closure
 * 
 * @param ndfa Non deterministic finite automata
 * @param set Set of states
 * @return Node* Set of states
*/
Node* lambdaClosure(NDFA ndfa, Node* set);

/**
 * This function define move 
 * 
 * @param ndfa Non deterministic finite automata
 * @param set Set of states 
 * @param symbol Symbol to move
 * @return Node* Set of states
*/
Node* move(NDFA ndfa, Node* set, int symbol);

/**
 * This function convert NDFA to DFA
 * 
 * @param ndfa Non deterministic finite automata
 * @return DFA Deterministic finite automata
*/
DFA convertNDFAtoDFA(NDFA ndfa);

#endif
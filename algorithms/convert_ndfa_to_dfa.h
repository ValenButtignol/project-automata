#include "../data_structures/finite_automaton.h"

/**
 * This function calculates the lambda clausure of a set of states.
 * 
 * @param automaton The automaton to use.
 * @param states The set of states to calculate the lambda clausure.
 * @return The lambda clausure of the set of states.
*/
Array lambdaClausure(NDFA automaton, Array states);

/**
 * This function calculates the move of a set of states with a symbol.
 * 
 * @param automaton The automaton to use.
 * @param states The set of states to calculate the move.
 * @param symbol The symbol to use.
 * @return The move of the set of states with the symbol.
*/
Array move(NDFA automaton, Array states, int symbol);

/**
 * This function converts a NDFA to a DFA.
 * 
 * @param automaton The automaton to convert.
 * @return The converted automaton.
*/
DFA convertToDFA(NDFA automaton);
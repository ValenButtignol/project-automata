#ifndef ALGORITHMS_KLEENE_CLOSURE_NDFA_H
#define ALGORITHMS_KLEENE_CLOSURE_NDFA_H

#include "../structures/ndfa.h"

/**
 * This function computes the kleene closure.
 * 
 * @param automaton The non deterministic automata.
 * @return The kleene closure of the ndfa.
*/
NDFA kleeneClosure(NDFA ndfa);

#endif
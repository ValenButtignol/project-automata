#ifndef ALGORITHMS_UNION_NDFA_H
#define ALGORITHMS_UNION_NDFA_H

#include "../structures/ndfa.h"

/**
 * This function computes the union of two given automatons.
 * 
 * @param ndfa1 The first non deterministic automata.
 * @param ndfa2 The second non deterministic automata.
 * @return The union of the given automatons.
*/
NDFA unionNDFA(NDFA ndfa1, NDFA ndfa2);

#endif
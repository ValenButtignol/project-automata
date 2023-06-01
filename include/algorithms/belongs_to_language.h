#ifndef ALGORITHMS_BELONGS_TO_LANGUAGE_H
#define ALGORITHMS_BELONGS_TO_LANGUAGE_H

#include "../structures/ndfa.h"

/**
 * This function checks if a given string is accepted by a given automata.
 * 
 * @param automaton The non deterministic automata.
 * @param string The string to accept.
*/
int belongsToLanguage(NDFA automaton, char *string);

#endif
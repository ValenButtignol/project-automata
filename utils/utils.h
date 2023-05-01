#include <stdio.h>
#include "../data_structures/array.h"
#include "../data_structures/finite_automaton.h"

/**
 * This functions checks if a given NDFA automaton contains a given array as a final state.
 * 
 * @param automaton The automaton to check.
 * @param states The array of states to check.
 * @return TRUE if the automaton contains the array as a final state, FALSE otherwise.
*/
int containsFinalState(NDFA automaton, Array states);

/**
 * This function converts a string to an array of integers.
 * 
 * @param string The string to convert.
 * @return The array of integers.
*/
Array stringToArray(char string[]);
#include "convert_ndfa_to_dfa.h"

/**
 * This function checks if a string belongs to the language of a given NDFA automaton.
 * 
 * @param automaton The automaton to use.
 * @param string The string to check.
 * @return TRUE if the string belongs to the language of the automaton, FALSE otherwise.
*/
int belongsToLanguage(NDFA automaton, char string[]);


/**
 * This function converts a string to an array of integers.
 * 
 * @param string The string to convert.
 * @return The array of integers.
*/
Array stringToArray(char string[]);
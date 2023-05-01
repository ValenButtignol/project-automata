#include "../data_structures/finite_automaton.h"
#include "../utils/utils.h"


/**
 * This function checks if a string belongs to the language of a given NDFA automaton.
 * 
 * @param automaton The automaton to use.
 * @param string The string to check.
 * @return TRUE if the string belongs to the language of the automaton, FALSE otherwise.
*/
int belongsToLanguage(NDFA automaton, char string[]);

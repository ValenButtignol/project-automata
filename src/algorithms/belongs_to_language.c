#include "../../include/algorithms/belongs_to_language.h"
#include "../../include/algorithms/convert_ndfa_to_dfa.h"
#include "../../include/structures/dfa.h"
#include "../../include/constants.h"
#include <string.h>
#include <stdlib.h>


/**
 * This function transforms a given string into an integer array.
 * 
 * @param string The string to transform.
 * @param length The length of the string.
 * @param stringArray The array to keep the numbers.
*/
void stringToArray(char string[], int length, int stringArray[]){
    for (int i = 0; i < length; i++){
        stringArray[i] = string[i] - '0';
    }
}

/**
 * This function checks if a given string is accepted by a given automata.
 * 
 * @param automaton The non deterministic automata.
 * @param string The string to accept.
 * @return TRUE (1) if the string is accepted, FALSE (0) otherwise.
*/
int belongsToLanguage(NDFA automaton, char *string){
    int length = strlen(string);
    int stringArray[length];
    stringToArray(string, length, stringArray);
    DFA dfa = convertNDFAtoDFA(automaton);

    int currentState = dfa.initialState;
    for (int i = 0; i < length; i++){
        currentState = searchDFATransition(dfa, currentState, stringArray[i]);
        if (currentState == -1){
            return FALSE;
        }
    }

    int result = containsData(dfa.finalStates, currentState);
    freeDFA(dfa);
    return result;
}


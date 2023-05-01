#include "belongs_to_language.h"
#include "../data_structures/finite_automaton.c"


/**
 * This function checks if a string belongs to the language of a given NDFA automaton.
 * 
 * @param automaton The automaton to use.
 * @param string The string to check.
 * @return TRUE if the string belongs to the language of the automaton, FALSE otherwise.
*/
int belongsToLanguage(NDFA automaton, char string[]) {
    Array stringArray = stringToArray(string);
    DFA dfa = convertToDFA(automaton);
    int count = 0;
    int currentState = dfa.initialState;

    for (int i = 0; i < stringArray.length; i++) {
        if (dfa.delta[currentState][stringArray.a[i]] != EMPTY) {
            currentState = dfa.delta[currentState][stringArray.a[i]];
            count++;
        } else {
            return FALSE;
        }
    }
    
    for (int i = 0; i < dfa.finalStates.length; i++) {
        if(currentState == dfa.finalStates.a[i]){
            return TRUE;
        }
    }

    return FALSE;
}
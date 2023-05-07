#include "belongs_to_language.h"

/**
 * This function checks if a string belongs to the language of a given NDFA automaton.
 * 
 * @param automaton The automaton to use.
 * @param string The string to check.
 * @return TRUE if the string belongs to the language of the automaton, FALSE otherwise.
*/
int belongsToLanguage(NDFA automaton, char *string) {
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


/**
 * This function converts a string to an array of integers.
 * 
 * @param string The string to convert.
 * @return The array of integers.
*/
Array stringToArray(char string[]){
    Array result;
    int length = strlen(string);
    for (int i = 0; i < length; i++){
        char stringNumber[2];
        stringNumber[0] = string[i];
        stringNumber[1] = '\0';
        result.a[i] = atoi(stringNumber);
        result.length++;
    }
    return result;
}
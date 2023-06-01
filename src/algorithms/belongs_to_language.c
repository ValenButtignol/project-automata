#include "../../include/algorithms/belongs_to_language.h"
#include "../../include/algorithms/convert_ndfa_to_dfa.h"
#include "../../include/structures/dfa.h"
#include "../../include/constants.h"
#include <string.h>

void stringToArray(char string[], int length, int *result[]){
    int result[length];
    for (int i = 0; i < length; i++){
        char stringNumber[2];
        stringNumber[0] = string[i];
        stringNumber[1] = '\0';
        result[i] = atoi(stringNumber);
    }
    return result;
}

int belongsToLanguage(NDFA automaton, char *string){
    int length = strlen(string);
    int stringArray[length];
    stringToArray(string, length, stringArray);
    DFA dfa = convertNDFAtoDFA(automaton);

    int currentState = dfa.initialState;
    for (int i = 0; i < length; i++){
        currentState = searchDFATransition(dfa, currentState, stringArray);
        if (currentState == -1){
            return FALSE;
        }
    }

    int result = containsData(dfa.finalStates, currentState);
    freeDFA(dfa);
    return result;
}


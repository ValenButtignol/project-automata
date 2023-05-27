#include "belongs_to_language.h"

int belongsToLanguage(NDFA automaton, char *string){
    Array stringArray = stringToArray(string);
    DFA dfa = convertNDFAtoDFA(automaton);

    int currentState = dfa.startState;
    for (int i = 0; i < stringArray.length; i++){
        currentState = searchTransitionDFA(dfa, currentState, stringArray.a[i]);
        if (currentState == -1){
            return 0;
        }
    }
    int result =  containsElement(dfa.finalStates, currentState);
    freeDFA(dfa);
    return result;
}

int searchTransitionDFA(DFA dfa, int fromState, int symbol){
    DFATransitionNode* current = dfa.transitions;
    while (current != NULL){
        if (current->transition.fromState == fromState && current->transition.symbol == symbol){
            return current->transition.toState;
        }
        current = current->next;
    }
    return -1;
}
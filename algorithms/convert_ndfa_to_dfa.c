#include "convert_ndfa_to_dfa.h"

DFA convertNDFAtoDFA(NDFA ndfa) {
    DFA dfa;
    dfa.transitions = NULL;
    dfa.finalStates = NULL;
    dfa.numSymbols = ndfa.numSymbols;
    dfa.startState = 0;
    SetOfMarkableSets* setOfMarkableSets = NULL;
    Node* startState = lambdaClosure(ndfa, createNode(ndfa.startState));
    //check if startState is a final state
    Node* current = startState;
    while (current != NULL) {
        if (containsElement(ndfa.finalStates, current->data) == 1) {
            addFinalStateDFA(&dfa, 0);
            break;
        }
        current = current->next;
    }
    insertSetOfMarkableSets(&setOfMarkableSets, startState);
    int numStates = 1;
    Node* finalStates = NULL;
    DFATransitionNode* transitions = NULL;

    while(getUnmarkedSet(setOfMarkableSets) != NULL){
        Node* currentSet = getUnmarkedSet(setOfMarkableSets);
        markSet(setOfMarkableSets, currentSet);
        for (int i = 0; i < dfa.numSymbols; i++) {
            Node* newSet = lambdaClosure(ndfa, move(ndfa, currentSet, i));
            if (newSet == NULL) {
                continue;
            }
            if(containsSet(setOfMarkableSets, newSet) == 0){
                insertSetOfMarkableSets(&setOfMarkableSets, newSet);
                numStates++;
            }
            // check if newSet is a final state
            Node* current = newSet;
            while (current != NULL) {
                if (containsElement(ndfa.finalStates, current->data) == 1) {
                    addFinalStateDFA(&dfa, getSetIndex(setOfMarkableSets, newSet));
                    break;
                }
                current = current->next;
            }
            insertTransitionDFA(&dfa, getSetIndex(setOfMarkableSets, currentSet), i, getSetIndex(setOfMarkableSets, newSet));
        }
    }
    freeSetOfMarkableSets(setOfMarkableSets);
    dfa.numStates = numStates;
    return dfa;
}

Node* lambdaClosure(NDFA ndfa, Node* set) {
    Node* closure = NULL;
    Node* current = set;
    while (current != NULL) {
        insertElement(&closure, current->data);
        current = current->next;
    }

    current = closure;
    while (current != NULL) {
        NDFATransitionNode* currentTransition = ndfa.transitions;
        while (currentTransition != NULL) {
            if (currentTransition->transition.fromState == current->data && currentTransition->transition.symbol == LAMBDA) {
                Node* currentToState = currentTransition->transition.toStates;
                while (currentToState != NULL) {
                    insertElement(&closure, currentToState->data);
                    currentToState = currentToState->next;
                }
            }
            currentTransition = currentTransition->next;
        }
        current = current->next;
    }
    

    return closure;
}

Node* move(NDFA ndfa, Node* set, int symbol) {
    Node* move = NULL;
    Node* current = set;
    while (current != NULL) {
        NDFATransitionNode* currentTransition = ndfa.transitions;
        while (currentTransition != NULL) {
            if (currentTransition->transition.fromState == current->data && currentTransition->transition.symbol == symbol) {
                Node* currentToState = currentTransition->transition.toStates;
                while (currentToState != NULL) {
                    insertElement(&move, currentToState->data);
                    currentToState = currentToState->next;
                }
            }
            currentTransition = currentTransition->next;
        }
        current = current->next;
    }
    return move;
}
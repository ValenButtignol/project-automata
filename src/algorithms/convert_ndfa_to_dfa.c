#include "../../include/algorithms/convert_ndfa_to_dfa.h"
#include "../../include/structures/set_of_markable_sets.h"
#include "../../include/constants.h"
#include "../../include/structures/dfa.h"
#include <stdlib.h>

/**
 * This function convert NDFA to DFA
 * 
 * @param ndfa Non deterministic finite automata
 * @return DFA Deterministic finite automata
*/
DFA convertNDFAtoDFA(NDFA ndfa) {
    DFA dfa;
    dfa.delta = NULL;
    dfa.finalStates = NULL;
    dfa.numSymbols = ndfa.numSymbols;
    dfa.initialState = 0;
    SetOfMarkableSets* setOfMarkableSets = NULL;
    Node* startState = lambdaClosure(ndfa, createNode(ndfa.initialState));
    //check if startState is a final state
    Node* current = startState;
    while (current != NULL) {
        if (containsData(ndfa.finalStates, current->data) == 1) {
            addDFAFinalState(&dfa, 0);
            break;
        }
        current = current->next;
    }
    addSet(&setOfMarkableSets, startState);
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
                addSet(&setOfMarkableSets, newSet);
                numStates++;
            }
            // check if newSet is a final state
            Node* current = newSet;
            while (current != NULL) {
                if (containsData(ndfa.finalStates, current->data) == 1) {
                    addDFAFinalState(&dfa, getSetIndex(setOfMarkableSets, newSet));
                    break;
                }
                current = current->next;
            }
            addDFATransition(&dfa, getSetIndex(setOfMarkableSets, currentSet), i, getSetIndex(setOfMarkableSets, newSet));
        }
    }
    freeSetOfMarkableSets(setOfMarkableSets);
    dfa.numStates = numStates;
    return dfa;
}

/**
 * This function define lambda closure
 * 
 * @param ndfa Non deterministic finite automata
 * @param set Set of states
 * @return Node* Set of states
*/
Node* lambdaClosure(NDFA ndfa, Node* set) {
    Node* closure = NULL;
    Node* current = set;
    while (current != NULL) {
        addData(&closure, current->data);
        current = current->next;
    }

    current = closure;
    while (current != NULL) {
        NDFATransitionNode* currentTransition = ndfa.delta;
        while (currentTransition != NULL) {
            if (currentTransition->transition.fromState == current->data && currentTransition->transition.symbol == LAMBDA) {
                Node* currentToState = currentTransition->transition.toStates;
                while (currentToState != NULL) {
                    addData(&closure, currentToState->data);
                    currentToState = currentToState->next;
                }
            }
            currentTransition = currentTransition->next;
        }
        current = current->next;
    }

    return closure;
}

/**
 * This function define move 
 * 
 * @param ndfa Non deterministic finite automata
 * @param set Set of states 
 * @param symbol Symbol to move
 * @return Node* Set of states
*/
Node* move(NDFA ndfa, Node* set, int symbol) {
    Node* move = NULL;
    Node* current = set;
    while (current != NULL) {
        NDFATransitionNode* currentTransition = ndfa.delta;
        while (currentTransition != NULL) {
            if (currentTransition->transition.fromState == current->data && currentTransition->transition.symbol == symbol) {
                Node* currentToState = currentTransition->transition.toStates;
                while (currentToState != NULL) {
                    addData(&move, currentToState->data);
                    currentToState = currentToState->next;
                }
            }
            currentTransition = currentTransition->next;
        }
        current = current->next;
    }
    return move;
}
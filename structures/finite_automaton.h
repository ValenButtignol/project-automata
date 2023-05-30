#include "set.h"

typedef struct DFATransition {
    int fromState;
    int symbol;
    int toState;
} DFATransition;

typedef struct DFATransitionNode {
    DFATransition transition;
    struct DFATransitionNode* next;
} DFATransitionNode;

typedef struct DFA {
    int numStates;
    int numSymbols;
    DFATransitionNode* transitions;
    int startState;
    Node* finalStates;
} DFA;

typedef struct NDFATransition {
    int fromState;
    int symbol;
    Node* toStates;
} NDFATransition;

typedef struct NDFATransitionNode {
    NDFATransition transition;
    struct NDFATransitionNode* next;
} NDFATransitionNode;

typedef struct NDFA {
    int numStates;
    int numSymbols;
    NDFATransitionNode* transitions;
    int startState;
    Node* finalStates;
} NDFA;

DFA createDFA(int numStates, int numSymbols, int startState);

void addFinalStateDFA(DFA* dfa, int state);

void insertTransitionDFA(DFA* dfa, int fromState, int symbol, int toState);

void insertDFATransitionNode(DFATransitionNode** head, DFATransition transition);

int searchTransitionDFA(DFA dfa, int fromState, int symbol);

void displayDFA(DFA dfa);

void freeDFA(DFA dfa);

NDFA createNDFA(int numStates, int numSymbols, int startState);

void addFinalStateNDFA(NDFA* ndfa, int state);

void insertTransitionNDFA(NDFA* ndfa, int fromState, int symbol, int toState);

void insertNDFATransitionNode(NDFATransitionNode** head, NDFATransition transition);

void displayNDFA(NDFA ndfa);

void freeNDFA(NDFA ndfa);

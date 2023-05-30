#include "finite_automaton.h"

// createDFA function
DFA createDFA(int numStates, int numSymbols, int startState) {
    DFA dfa;
    dfa.numStates = numStates;
    dfa.numSymbols = numSymbols;
    dfa.startState = startState;
    dfa.transitions = NULL;
    dfa.finalStates = NULL;
    return dfa;
}

// add final state function using insertElement
void addFinalStateDFA(DFA* dfa, int state) {
    insertElement(&(dfa->finalStates), state);
}

// insert transition function using insertDFATransitionNode
void insertTransitionDFA(DFA* dfa, int fromState, int symbol, int toState) {
    DFATransition transition;
    transition.fromState = fromState;
    transition.symbol = symbol;
    transition.toState = toState;
    insertDFATransitionNode(&(dfa->transitions), transition);
}

// insert DFATransitionNode
void insertDFATransitionNode(DFATransitionNode** head, DFATransition transition) {
    DFATransitionNode* newNode = (DFATransitionNode*)malloc(sizeof(DFATransitionNode));
    if (newNode == NULL) {
        exit(1);
    }
    newNode->transition = transition;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        DFATransitionNode* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// display DFA function
void displayDFA(DFA dfa) {
    printf("DFA with %d states and %d symbols.\n", dfa.numStates, dfa.numSymbols);
    printf("Start state: %d\n", dfa.startState);
    printf("Final states: ");
    Node* current = dfa.finalStates;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    printf("Transitions:\n");
    DFATransitionNode* currentTransition = dfa.transitions;
    while (currentTransition != NULL) {
        printf("From: %d Symbol: %d To: %d\n", currentTransition->transition.fromState, currentTransition->transition.symbol, currentTransition->transition.toState);
        currentTransition = currentTransition->next;
    }
}

// free DFA function
void freeDFA(DFA dfa) {
    Node* current = dfa.finalStates;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    DFATransitionNode* currentTransition = dfa.transitions;
    while (currentTransition != NULL) {
        DFATransitionNode* temp = currentTransition;
        currentTransition = currentTransition->next;
        free(temp);
    }
}

// createNDFA function
NDFA createNDFA(int numStates, int numSymbols, int startState) {
    NDFA ndfa;
    ndfa.numStates = numStates;
    ndfa.numSymbols = numSymbols;
    ndfa.startState = startState;
    ndfa.transitions = NULL;
    ndfa.finalStates = NULL;
    return ndfa;
}

// add final state function using insertElement
void addFinalStateNDFA(NDFA* ndfa, int state) {
    insertElement(&(ndfa->finalStates), state);
}

// insert transition function using insertNDFATransitionNode
void insertTransitionNDFA(NDFA* ndfa, int fromState, int symbol, int toState) {
    // search for the transition
    NDFATransitionNode* current = ndfa->transitions;
    while (current != NULL) {
        if (current->transition.fromState == fromState && current->transition.symbol == symbol) {
            insertElement(&(current->transition.toStates), toState);
            return;
        }
        current = current->next;
    }

    // if transition not found, create a new one
    NDFATransition transition;
    transition.fromState = fromState;
    transition.symbol = symbol;
    transition.toStates = NULL;
    insertElement(&(transition.toStates), toState);
    insertNDFATransitionNode(&(ndfa->transitions), transition);
}

// insert NDFATransitionNode
void insertNDFATransitionNode(NDFATransitionNode** head, NDFATransition transition) {
    NDFATransitionNode* newNode = (NDFATransitionNode*)malloc(sizeof(NDFATransitionNode));
    if (newNode == NULL) {
        exit(1);
    }
    newNode->transition = transition;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        NDFATransitionNode* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// display NDFA function
void displayNDFA(NDFA ndfa) {
    printf("NDFA with %d states and %d symbols.\n", ndfa.numStates, ndfa.numSymbols);
    printf("Start state: %d\n", ndfa.startState);
    printf("Final states: ");
    Node* current = ndfa.finalStates;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    printf("Transitions:\n");
    NDFATransitionNode* currentTransition = ndfa.transitions;
    while (currentTransition != NULL) {
        printf("From: %d Symbol: %d ", currentTransition->transition.fromState, currentTransition->transition.symbol);
        Node* currentToState = currentTransition->transition.toStates;
        printf("To: ");
        while (currentToState != NULL) {
            printf("%d ", currentToState->data);
            currentToState = currentToState->next;
        }
        printf("\n");
        currentTransition = currentTransition->next;
    }
}

// free NDFA function
void freeNDFA(NDFA ndfa) {
    Node* current = ndfa.finalStates;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    NDFATransitionNode* currentTransition = ndfa.transitions;
    while (currentTransition != NULL) {
        Node* currentToState = currentTransition->transition.toStates;
        while (currentToState != NULL) {
            Node* temp = currentToState;
            currentToState = currentToState->next;
            free(temp);
        }
        NDFATransitionNode* temp = currentTransition;
        currentTransition = currentTransition->next;
        free(temp);
    }
}
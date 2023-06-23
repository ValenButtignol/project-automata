
#include "../../include/algorithms/minimization.h"
#include "../../include/structures/dfa.h"
#include "../../include/structures/node.h"
#include "../../include/structures/set_of_markable_sets.h"
#include "../../include/constants.h"
#include <stdio.h>
#include <stdlib.h>




SetOfMarkableSets* quotientSet(DFA automata) {

    // create a list with the states of automata minus the final states: Q\F
    Node* states;
    Node* finalStates;
    for (int i = 0; i < automata.numStates; i++) {
        printf("Creating list of states...%d\n", i);
        if (!containsData(automata.finalStates, i)) {
            addData(&states, i);
        } else {
            addData(&finalStates, i); 
        }
    }

    SetOfMarkableSets* partitions;
    partitions->size = 0;
    addSet(&partitions, states);
    addSet(&partitions, finalStates);

    SetOfMarkableSets* partitionsDash;
    partitionsDash->size = 0;

    int marked[automata.numStates];

    int changePartition = FALSE;

    while (!changePartition) {
        
        resetMarks(marked, automata.numStates);
        
        for (int i = 0; i < partitions->size; i++) {
            Node* x = getSet(partitions, i);

            for (int j = 0; j < x->size; j++) {
                int e = getData(x, j);
                if (itIsMarked(marked, e)) {  
                    continue;
                }
                
                markState(marked, e);
                Node* xDash = createNode(e);
                
                for (int k = 0; k < x->size; k++) {
                    int eDash = getData(x, k);      

                    if (itIsMarked(marked, eDash)) {
                        continue;
                    }

                    int same_equivalence_class = TRUE;
                    for (int symbol = 0; symbol < automata.numSymbols; symbol++) {
                        int toStateE = searchDFATransition(automata, e, symbol);
                        int toStateEDash = searchDFATransition(automata, eDash, symbol);

                        if (getEquivalenceClass(partitions, toStateE) != getEquivalenceClass(partitions, toStateEDash)) {
                            same_equivalence_class = FALSE;
                            break;
                        }
                    }

                    if (same_equivalence_class) {
                        markState(marked, eDash);
                        addData(&xDash, eDash);
                    }
                }

                addSet(&partitionsDash, xDash);
            }
        }

        if (partitions->size == partitionsDash->size) {
            changePartition = TRUE;
            break;
        } else {
            partitions = partitionsDash;
            partitionsDash = NULL;
        }
    }

    return partitions;
}


int getEquivalenceClass(SetOfMarkableSets* partitions, int state) {
    for (int i = 0; i < partitions->size; i++) {
        Node* set = getSet(partitions, i);
        if (containsData(set, state)) {
            return i;
        }
    }
    return -1;
}


int getData(Node* x, int j) {
    Node* xAux = x;
    for (int i = 0; i < j; i++) {
        xAux = xAux->next;
    }
    return xAux->data;
}


void resetMarks(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = FALSE;
    }
}

Node* getSet(SetOfMarkableSets* partitions, int i) {
    SetOfMarkableSets* partitionsAux = partitions;
    for (int j = 0; j < i; j++) {
        partitionsAux = partitionsAux->next;
    }
    return partitionsAux->set;
}

int markState(int* arr, int el){
    arr[el] = TRUE;
}


int itIsMarked(int arr[], int el) {
    return arr[el];
}


void minimize(DFA automata, DFA* automataMinimized) {
    SetOfMarkableSets* partitions = quotientSet(automata);
    for (int i = 0; i < partitions->size; i++) {
        Node* set = getSet(partitions, i);
        printf("Set %d: ", i);
        for (int j = 0; j < set->size; j++) {
            int state = getData(set, j);
            printf("%d ", state);
        }
        printf("\n");
    }
    /* 
    automataMinimized->numStates = partitions->size;
    automataMinimized->numSymbols = automata.numSymbols;
    automataMinimized->initialState = getEquivalenceClass(partitions, automata.initialState);
    automataMinimized->finalStates = getFinalStates(partitions, automata.finalStates);
    generateTransitions(partitions, automataMinimized, automata); */
}

Node* getFinalStates(SetOfMarkableSets* partitions, Node* finalStates) {
    Node* finalStatesMinimized;
    for (int i = 0; i < partitions->size; i++) {
        Node* set = getSet(partitions, i);
        for (int j = 0; j < set->size; j++) {
            int state = getData(set, j);
            if (containsData(finalStates, state)) {
                addData(&finalStatesMinimized, i);
                break;
            }
        }
    }
    return finalStatesMinimized;
}

void generateTransitions(SetOfMarkableSets* partitions, DFA* minimizedAutomata, DFA automata){
    for (int i = 0; i < partitions->size; i++) {
        Node* set = getSet(partitions, i);
        for (int j = 0; j < set->size; j++) {
            int state = getData(set, j);
            for (int symbol = 0; symbol < automata.numSymbols; symbol++) {
                int toState = searchDFATransition(automata, state, symbol);
                int toStateClass = getEquivalenceClass(partitions, toState);
                addDFATransition(minimizedAutomata, i, toStateClass, symbol); 
            }
        }
    }
}

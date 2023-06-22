
#include "../../include/algorithms/minimization.h"
#include "../../include/structures/dfa.h"
#include "../../include/structures/node.h"
#include "../../include/structures/set_of_markable_sets.h"
#include "../../include/constants.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct MarkableSet {
    int data;
    int marked;
    struct Node* next;
} MarkableSet;

DFA minimize(DFA automata) {

    // create a list with the states of automata minus the final states: Q\F
    Node* states;
    for (int i = 0; i < automata.numStates; i++) {
        if (!containsData(automata.finalStates, i)) {
        states = addNode(states, i);
        }
    }
    // create a list with the final states of automata: F
    Node* finalStates = automata.finalStates;

    // create a set of markable sets
    SetOfMarkableSets* p;
    SetOfMarkableSets* pDash;
    //create two markable sets
    Node* x;
    Node* xDash;

    // add the set Q\F to the set of markable sets
    addSet(&p, states);
    // add the set F to the set of markable sets
    addSet(&p, finalStates);

    int changePartition = 0;
    while (!changePartition) {
        SetOfMarkableSets* currentSet = p;

        while (currentSet != NULL) {
            Node* x = currentSet->set;

            while (x != NULL) {
                int e = x->data;
                if (isMarked(e, x)) {   // Este isMarked no está implementado.
                    continue;
                } else {
                    markState(e, x);    // Este markState tampoco está implementado.
                }

                addData(xDash, e, FALSE);   // Este addData tampoco está implementado.
                
                Node* xDashAux = xDash;
                while (xDashAux != NULL) {
                    int eDash = xDashAux->data;
                    if (forAllWeirdFunction(automata, e, eDash)) {   // Este forAllWeirdFunction tampoco está implementado.
                        markState(eDash, x);    // Este markState tampoco está implementado.
                        addData(xDash, eDash, FALSE);   // Este addData tampoco está implementado.
                    }
                    xDashAux = xDashAux->next;
                }
                
                addData(pDash, xDash, FALSE);
                x = x->next;
            }

            currentSet = currentSet->next;
            if (notEquals(p, pDash)) {   // Este notEquals
                p = pDash;
                pDash = NULL;   // delete all its elements
            }
            else {
                changePartition = TRUE;
            }
        }
    }
}






/***************************************/
// create a list with the states of automata minus the final states: Q\F
    Node* states;
    for (int i = 0; i < automata.numStates; i++) {
        if (!containsData(automata.finalStates, i)) {
        states = addNode(states, i);
        }
    }
    // create a list with the final states of automata: F
    Node* finalStates = automata.finalStates;

    // create a set of markable sets
    SetOfMarkableSets* p;
    SetOfMarkableSets* pDash;
    //create two markable sets
    Node* x;
    Node* xDash;
    // create states for the algorithm
    int e;
    int eDash;

    // add the set Q\F to the set of markable sets
    addSet(&p, states);
    // add the set F to the set of markable sets
    addSet(&p, finalStates);

    int changePartition = 0;
    while (!changePartition) {
            SetOfMarkableSets* currentSet = p;

            while (currentSet != NULL) {
                // for each x in P
                Node* x = currentSet->set;

                // for each e in x
                while (x != NULL) {
                    int e = x->data;
                    if (isMarked(e, x)) {   // Este isMarked no está implementado.
                        continue;
                    } else {
                        markState(e, x);    // Este markState tampoco está implementado.
                    }

                    addData(xDash, e, false);   // Este addData tampoco está implementado.

                    Node* xAux = x;
                    while (xAux != NULL) {
                        int eDash = x->data;

                        if (forAllSymbols()) {
                            markState(eDash, xAux);
                            addData(xDash, eDash, false);
                        }

                        xAux = xAux->next;
                    }

                    addData(pDash, xDash, false);
                    x = x->next;
                }

                if (p != pDash) {
                    p = pDash;
                    pDash = NULL;   // delete all its elements
                }
                else {
                    changePartition = 1;
                }

                currentSet = currentSet->next;
            }
    }



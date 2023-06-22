
#include "../../include/algorithms/minimization.h"
#include "../../include/structures/dfa.h"
#include "../../include/structures/node.h"
#include "../../include/structures/set_of_markable_sets.h"
#include <stdio.h>
#include <stdlib.h>

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
    SetOfMarkableSets* setOfMarkableSets;
    // add the set Q\F to the set of markable sets
    addSet(&setOfMarkableSets, states);
    // add the set F to the set of markable sets
    addSet(&setOfMarkableSets, finalStates);

    //create two markable sets
    MarkableSet* X;
    MarkableSet* Xp;

    Node* e;
    Node* ep;

    // add to e and ep the states of the dfa
    for (int i = 0; i < automata.numStates; i++) {
        addData(&e, i);
        addNode(&ep, i);
    }


    int changed = 0;
    while(!changed){
        // iterate over P
        for (SetOfMarkableSets* P = setOfMarkableSets; P != NULL; P = P->next) {
            // iterate over e
            for (Node* e = P->set; e != NULL; e = e->next) {
                // check if e is marked and if X contains e
                if (isMarked(X, e) && containsData(X, e->data)) {
                    
                }
            } 
        }
    }

}
#include "array.h"

/**
 * This struct represents a non deterministic finite automaton.
 * 
 * @param states The set of states (K). From 0 to states - 1.
 * @param symbols The set of symbols that represents the alphabet. From 0 to symbols - 1.
 * @param delta The transition matrix delta[state][symbol] = [states].
 * @param initialState The initial state of the automaton.
 * @param finalStates The set of final states of the automaton.
*/
typedef struct NonDeterministicFiniteAutomaton {
    int states;
    int symbols;       
    int delta[MAX_ARRAY][MAX_ARRAY][MAX_ARRAY];   
    int initialState; 
    Array finalStates;
} NDFA;

/**
 * This struct represents a deterministic finite automaton.
 * 
 * @param states The set of states (K). From 0 to states - 1.
 * @param symbols The set of symbols that represents the alphabet. From 0 to symbols - 1.
 * @param delta The transition matrix delta[state][symbol] = state.
 * @param initialState The initial state of the automaton.
 * @param finalStates The set of final states of the automaton.
 */
typedef struct DeterministicFiniteAutomaton {
    int states; 
    int symbols;        
    int delta[MAX_ARRAY][MAX_ARRAY];    
    int initialState; 
    Array finalStates; 
} DFA;

/**
 * This function creates a non deterministic finite automaton.
 * 
 * @param num_states The number of states.
 * @param num_symbols The number of symbols.
 * @param initialState The initial state of the automaton.
 * @param finalStates The set of final states of the automaton.
 * @return The non deterministic finite automaton.
 */
NDFA createNDFAAutomaton(int num_states, int num_symbols, int initialState, Array finalStates);

/**
 * This function adds a transition to a non deterministic finite automaton.
 * 
 * @param automaton The non deterministic finite automaton.
 * @param fromState The origin state of the transition.
 * @param toStates The set of states to transitionate.
 * @param symbol The symbol of the transition.
 */
void addTransitionToNDFA(NDFA *automaton, int fromState, Array toStates, int symbol);


/**
 * This functions checks if a given NDFA automaton contains a given array as a final state.
 * 
 * @param automaton The automaton to check.
 * @param states The array of states to check.
 * @return TRUE if the automaton contains the array as a final state, FALSE otherwise.
*/
int containsFinalState(NDFA automaton, Array states);
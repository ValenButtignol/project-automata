#include "../../include/algorithms/parser.h"
#include "../../include/structures/ndfa.h"
#include "../../include/constants.h"
#include "../../include/algorithms/concatenate_ndfa.h"
#include "../../include/algorithms/kleene_closure_ndfa.h"
#include "../../include/algorithms/union_ndfa.h"
#include <stdio.h>

// E->TE'
int E(char** cursor, NDFA** ndfa){
    if(T(cursor, ndfa)){
        if(Edash(cursor, ndfa)){
            return TRUE;
        }
    }
    return FALSE;
}

//E'->|TE'
//E'->-1
int Edash(char** cursor, NDFA** ndfa){
    if(**cursor == '|'){
        NDFA *ndfa2;
        (*cursor)++;
        if(T(cursor, &ndfa2)){
            if(Edash(cursor, &ndfa2)){
                **ndfa = unionNDFA(**ndfa, *ndfa2);
                freeNDFA(*ndfa2);
                return TRUE;
            }
        }
    } else {
        return TRUE;
    }
    return FALSE;
}

//T->FT'
int T(char** cursor, NDFA** ndfa){
    if(F(cursor, ndfa)){
        if(Tdash(cursor, ndfa)){
            return TRUE;
        }
    }
    return FALSE;
}

//T'->.FT'
//T'->-1
int Tdash(char** cursor, NDFA** ndfa){
    if (**cursor == '.') {
        NDFA *ndfa2;
        (*cursor)++;
        if (F(cursor, &ndfa2)) {
            if (Tdash(cursor, &ndfa2)) {
                **ndfa = concatenateNDFA(**ndfa, *ndfa2);
                freeNDFA(*ndfa2);
                return TRUE;
            } 
        }
    } else {
        return TRUE;
    }
    return FALSE;
}

//F->PF'
int F(char** cursor, NDFA** ndfa){
    if(P(cursor, ndfa)){
        if(Fdash(cursor, ndfa)){
            return TRUE;
        }
    }
    return FALSE;
}

//F'->*F'
//F'->-1
int Fdash(char** cursor, NDFA** ndfa){
    if(**cursor == '*'){
        **ndfa = kleeneClosure(**ndfa);
        (*cursor)++;
        return TRUE;
    } else {
        return TRUE;
    }
    return FALSE;
}

//P->(E)
//P->L
int P(char** cursor, NDFA** ndfa) {
    if (**cursor == '(') {
        (*cursor)++;
        if (E(cursor, ndfa)) {
            if (**cursor == ')') {
                (*cursor)++;
                return TRUE;
            } 
        }
    } else if (L(cursor, ndfa)) {
        return TRUE;
    }
    
    return FALSE;
}

//L->0
//L->1
//L->2
int L(char** cursor, NDFA** ndfa){
    if(**cursor == '0' || **cursor == '1' || **cursor == '2'){
        *ndfa = createNDFAFromSymbol(**cursor - '0');
        (*cursor)++;
        return TRUE;
    }
    return FALSE;
}
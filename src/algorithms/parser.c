#include "../../include/algorithms/parser.h"
#include "../../include/structures/ndfa.h"
#include "../../include/constants.h"
#include <stdio.h>

// E->TE'
int E(char** cursor){
    if(T(cursor)){
        if(Edash(cursor)){
            return TRUE;
        }
    }
    return FALSE;
}

//E'->|TE'
//E'->-1
int Edash(char** cursor){
    if(**cursor == '|'){
        (*cursor)++;
        if(T(cursor)){
            if(Edash(cursor)){
                return TRUE;
            }
        }
    } else {
        return TRUE;
    }
    return FALSE;
}

//T->FT'
int T(char** cursor){
    if(F(cursor)){
        if(Tdash(cursor)){
            return TRUE;
        }
    }
    return FALSE;
}

//T'->.FT'
//T'->-1
int Tdash(char** cursor){
    if (**cursor == '.') {
        (*cursor)++;
        if (F(cursor)) {
            if (Tdash(cursor)){
                return TRUE;
            } 
        }
    } else {
        return TRUE;
    }
    return FALSE;
}

//F->PF'
int F(char** cursor){
    if(P(cursor)){
        if(Fdash(cursor)){
            return TRUE;
        }
    }
    return FALSE;
}

//F'->*F'
//F'->-1
int Fdash(char** cursor){
    if(**cursor == '*'){
        (*cursor)++;
        if(Fdash(cursor)){
            return TRUE;
        }
    } else {
        return TRUE;
    }
    return FALSE;
}

//P->(E)
//P->L
int P(char** cursor) {
    if (**cursor == '(') {
        (*cursor)++;
        if (E(cursor)) {
            if (**cursor == ')') {
                (*cursor)++;
                return TRUE;
            } 
        }
    } else if (L(cursor)) {
        return TRUE;
    }
    
    return FALSE;
}

//L->0
//L->1
//L->2
int L(char** cursor){
    if(**cursor == '0' || **cursor == '1' || **cursor == '2'){
        (*cursor)++;
        return TRUE;
    }
    return FALSE;
}
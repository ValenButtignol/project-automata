#ifndef PARSER_H
#define PARSER_H

#include "../../include/structures/ndfa.h"

/* 
E->TE'
E'->|TE'
E'->-1
T->FT'
T'->.FT'
T'->-1
F->PF'
F'->*F'
F'->-1
P->(E)
P->L
L->0
L->1
L->2
*/

int E(char** cursor, NDFA** ndfa);

int Edash(char** cursor, NDFA** ndfa);

int T(char** cursor, NDFA** ndfa);

int Tdash(char** cursor, NDFA** ndfa);

int F(char** cursor, NDFA** ndfa);

int Fdash(char** cursor, NDFA** ndfa);

int P(char** cursor, NDFA** ndfa);

int L(char** cursor, NDFA** ndfa);

#endif
#ifndef PARSER_H
#define PARSER_H

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

int E(char** cursor);

int Edash(char** cursor);

int T(char** cursor);

int Tdash(char** cursor);

int F(char** cursor);

int Fdash(char** cursor);

int P(char** cursor);

int L(char** cursor);

#endif
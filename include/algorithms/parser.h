#ifndef PARSER_H
#define PARSER_H
#include "../../include/structures/ndfa.h"

int E(char** cursor, NDFA** ndfa);

int Edash(char** cursor, NDFA** ndfa);

int T(char** cursor, NDFA** ndfa);

int Tdash(char** cursor, NDFA** ndfa);

int F(char** cursor, NDFA** ndfa);

int Fdash(char** cursor, NDFA** ndfa);

int P(char** cursor, NDFA** ndfa);

int L(char** cursor, NDFA** ndfa);

#endif
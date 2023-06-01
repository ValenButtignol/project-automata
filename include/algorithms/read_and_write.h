#ifndef ALGORITHMS_READ_AND_WRITE_H
#define ALGORITHMS_READ_AND_WRITE_H

#include <stdio.h>
#include "../structures/ndfa.h"

NDFA createFromFile(FILE *file, int numStates, int numSymbols);

void writeToFile(FILE *file, NDFA ndfa);

#endif
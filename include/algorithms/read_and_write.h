#ifndef ALGORITHMS_READ_AND_WRITE_H
#define ALGORITHMS_READ_AND_WRITE_H

#include <stdio.h>
#include "../structures/ndfa.h"

/**
* This function reads an NDFA from a file.dot and creates a new NDFA with that 
* information.
*
* @param file to read the NDFA from
* @param numStates number of states the NDFA has
* @param numSymbols number of symbols the NDFA has
* @return ndfa created from the file
*/
NDFA createFromFile(FILE *file, int numStates, int numSymbols);

/**
* This function writes a given NDFA on a file.dot
*
* @param file to write the NDFA on
* @param ndfa to write on the file
*/
void writeToFile(FILE *file, NDFA ndfa);

#endif
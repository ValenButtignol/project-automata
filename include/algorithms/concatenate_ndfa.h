#ifndef ALGORITHMS_CONCATENATE_NDFA_H
#define ALGORITHMS_CONCATENATE_NDFA_H

#include "../structures/ndfa.h"

/**
* This function computes the concatenation between two given NDFA's
* 
* @param ndfa1 first NDFA in the concatenation
* @param ndfa2 second NDFA in the concatenation
* @return concatenation between the two NDFA's
*/
NDFA concatenateNDFA(NDFA ndfa1, NDFA ndfa2);

#endif
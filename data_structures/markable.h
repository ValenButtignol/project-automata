#include <stdio.h>
#include "array.h"

/**
 * This struct represents a markable set.
 * 
 * @param elements The elements of the markable set.
 * @param marked The mark of the markable set
*/
typedef struct MarkableArray {
    Array elements;
    int isMarked;
}MarkableArray;

/**
 * This struct represents a set of markable arrays.
 * 
 * @param mArrays The set of markable arrays.
 * @param length The length of the set.
*/
typedef struct SetOfMarkableArray {
    MarkableArray mArrays[MAX_ARRAY];
    int length;
}SetOfMarkableArray;

/**
 * This function marks a markable array.
 * 
 * @param set The set of markable arrays.
 * @param idxOfArray The index of the array to mark.
*/
void mark(SetOfMarkableArray *set, int idxOfArray);

/**
 * This function checks if a markable array is in a set of markable arrays. It uses the areEquals function from array.c.
 * 
 * @param set The set of markable arrays.
 * @param array The markable array.
 * @return 1 if the array is in the set, 0 otherwise.
 * 
 * @ref areEquals
*/
int elemInSet(SetOfMarkableArray set, MarkableArray array);

/**
 * This function appends a sorted markable array to a set of markable arrays. It uses the arrayCopy and sort functions from array.c.
 * 
 * @param set The set of markable arrays.
 * @param array The markable array.
 * 
 * @ref arrayCopy
 * @ref sort
*/
void appendSorted(SetOfMarkableArray *set, MarkableArray array);



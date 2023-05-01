#include <stdio.h>
#include "markable.h"

/**
 * This function marks a markable array.
 * 
 * @param set The set of markable arrays.
 * @param idxOfArray The index of the array to mark.
*/
void mark(SetOfMarkableArray *set, int idxOfArray) {
    set->mArrays[idxOfArray].isMarked = 1;
}

/**
 * This function checks if a markable array is in a set of markable arrays. It uses the areEquals function from array.c.
 * 
 * @param set The set of markable arrays.
 * @param array The markable array.
 * @return 1 if the array is in the set, 0 otherwise.
 * 
 * @ref areEquals
*/
int elemInSet(SetOfMarkableArray set, MarkableArray array) {
    
    if(isEmpty(array.elements) == TRUE){
        return TRUE;
    }

    if (set.length == 0){
        return FALSE;
    }

    int flag = FALSE;
    for (int i = 0; i < set.length; i++){
        if (areEquals(set.mArrays[i].elements, array.elements) == TRUE){
            return TRUE;
        }
    }
    return flag;
}

/**
 * This function appends a sorted markable array to a set of markable arrays. It uses the arrayCopy and sort functions from array.c.
 *  
 * @param set The set of markable arrays.
 * @param array The markable array.
 * 
 * @ref arrayCopy
 * @ref sort
*/
void appendSorted(SetOfMarkableArray *set, MarkableArray array) {
    arrayCopy(&set->mArrays[set->length].elements, array.elements);
    sort(&set->mArrays[set->length].elements);
    set->mArrays[set->length].isMarked = FALSE;
    set->length++;
}
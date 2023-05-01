#include "../utils/constants.h"

typedef struct Array {
    int a[MAX_ARRAY];
    int length;
} Array;

/**
 * This function checks if two arrays are equals.
 * 
 * @param array The first array.
 * @param otherArray The second array.
 * @return 1 if the arrays are equals, 0 otherwise.
 */
int areEquals(Array array1, Array array2);

/**
 * This function copies the elements of an array to another.
 * 
 * @param array The array that will receive the elements.
 * @param copyArray The array that will be copied.
 */
void arrayCopy(Array* array, Array copyArray);

/**
 * This function merges two arrays.
 * 
 * @param array The array that will receive the elements.
 * @param left The left array.
 * @param right The right array.
 */
void merge(Array* array, Array left, Array right);

/**
 * This function sorts an array using the merge sort algorithm.
 * 
 * @param array The array that will be sorted.
 */
void sort(Array* array);

/**
 * This function checks if an array is empty.
 * 
 * @param array The array that will be checked.
 * @return 1 if the array is empty, 0 otherwise.
 */
int isEmpty(Array array);

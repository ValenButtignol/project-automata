#include "array.h"

/**
 * This function checks if two arrays are equals.
 * 
 * @param array The first array.
 * @param otherArray The second array.
 * @return 1 if the arrays are equals, 0 otherwise.
 */
int areEquals(Array array, Array otherArray) {
    int flag = TRUE;
    for (int i = 0; i < array.length && flag == TRUE; i++) {
        if (array.a[i] != otherArray.a[i]){
            flag = FALSE;
        }
    }
    return flag;
}

/**
 * This function copies the elements of an array to another.
 * 
 * @param array The array that will receive the elements.
 * @param copyArray The array that will be copied.
 */
void arrayCopy(Array* array, Array copyArray) {
    for (int i = 0; i < copyArray.length; i++) {
        array->a[i] = copyArray.a[i];
        array->length++;
    }
}

/**
 * This function merges two arrays.
 * 
 * @param array The array that will receive the elements.
 * @param left The left array.
 * @param right The right array.
 */
void merge(Array *array, Array left, Array right) {
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < left.length && j < right.length) {
        if (left.a[i] < right.a[j]) {
            array->a[k] = left.a[i];
            i++;
        } else {
            array->a[k] = right.a[j];
            j++;
        }
        k++;
    }

    while (i < left.length) {
        array->a[k] = left.a[i];
        i++;
        k++;
    }

    while (j < right.length) {
        array->a[k] = right.a[j];
        j++;
        k++;
    }
}

/**
 * This function sorts an array using the merge sort algorithm.
 * 
 * @param array The array that will be sorted.
 */
void sort(Array *array) {
    if (array->length > 1) {
        int middle = array->length / 2;
        Array left;
        Array right;

        left.length = middle;
        right.length = array->length - middle;

        for (int i = 0; i < middle; i++) {
            left.a[i] = array->a[i];
        }

        for (int i = middle; i < array->length; i++) {
            right.a[i - middle] = array->a[i];
        }

        sort(&left);
        sort(&right);
        merge(array, left, right);
    }
}

/**
 * This function checks if an array is empty.
 * 
 * @param array The array that will be checked.
 * @return 1 if the array is empty, 0 otherwise.
 */
int isEmpty(Array array) {
    if (array.length == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

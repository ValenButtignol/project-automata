#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

int containsFinalState(NDFA automaton, Array states) {
    int result = FALSE;
    for (int i = 0; i < states.length && result == FALSE; i++) {
        for (int j = 0; j < automaton.finalStates.length && result == FALSE; j++) {
            if (states.a[i] == automaton.finalStates.a[j]) {
                result = TRUE;
            }
        }
    }
    return result;
}

Array stringToArray(char string[]) {
    Array result;
    int length = strlen(string);
    for (int i = 0; i < length; i++){
        char stringNumber[2];
        stringNumber[0] = string[i];
        stringNumber[1] = '\0';
        result.a[i] = atoi(stringNumber);
        result.length++;
    }
    return result;
}






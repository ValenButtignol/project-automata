#include "include/algorithms/belongs_to_language.h"
#include "include/algorithms/concatenate_ndfa.h"
#include "include/algorithms/convert_ndfa_to_dfa.h"
#include "include/algorithms/kleene_closure_ndfa.h"
#include "include/algorithms/union_ndfa.h"
#include "include/algorithms/read_and_write.h"
#include "include/algorithms/parser.h"
#include "include/algorithms/minigrep.h"
#include "include/structures/ndfa.h"
#include "include/structures/dfa.h"
#include "include/structures/node.h"
#include "include/structures/set_of_markable_sets.h"
#include "include/constants.h"
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[]) {

    char* cursor;
    NDFA* ndfa;
    char* regex = argv[1];
    char* text = argv[2];
    cursor = regex;

    printf("String to parse: %s\n", regex);

    if (E(&cursor, &ndfa) && *cursor == '\0') { 
        printf("String is successfully parsed\n");
        printf("Text to evaluate: %s\n", text);
        if(minigrep(regex, text, *ndfa)){
            printf("Coincidence found\n");
        }
        else{
            printf("No coincidence found\n");
        }
    }
    else {
        printf("Error in parsing string: %s\n", regex);
    }

    freeNDFA(*ndfa);
    return 0;
}
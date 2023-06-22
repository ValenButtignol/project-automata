#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../include/algorithms/minigrep.h"
#include "../../include/structures/ndfa.h"
#include "../../include/constants.h"
#include "../../include/algorithms/belongs_to_language.h"

int minigrep(char* regex, char* text, NDFA ndfa){
  int length = strlen(text);
    
    // Generate all substrings
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j <= length; j++) {
            // build the substring
            char substring[length + 1];
            int k = 0;
            for (int l = i; l < j; l++) {
                substring[k++] = text[l];
            }
            substring[k] = '\0';
            // check if the substring belongs to the language
            if (belongsToLanguage(ndfa, substring)) {
                printf("Coincidence: %s\n", substring);
                return TRUE;
            }
        }
    }
    return FALSE;
}

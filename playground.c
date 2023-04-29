#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct List {
    int a[1000];
    int quantity;
} Array;

void createAFNDFromFile();

int main(void) {
    createAFNDFromFile();
}


void createAFNDFromFile() {

    FILE *file;
    file = fopen("automaton.dot", "r");
    if (file == NULL) {
        printf("Error\n");
        exit(1);
    }

    int estadoInicial;
    Array estadosFinales;
    estadosFinales.quantity = 0;
    char line[100];
    while (fgets(line, 100, file) != NULL) {
        printf("%s", line);
        char *inic = strstr(line, "inic->");
        if (inic) {
            char numberChar = inic[7];
            char cadenaNumero[2];
            cadenaNumero[0] = numberChar;
            cadenaNumero[1] = '\0';
            estadoInicial = atoi(cadenaNumero);  
        }
        char *final = strstr(line, "[shape=doublecircle];");
        if (final) {
            char numberChar = line[0];
            char cadenaNumero[2];
            cadenaNumero[0] = numberChar;
            cadenaNumero[1] = '\0';
            int estadoFinal = atoi(cadenaNumero); 
            estadosFinales.a[estadosFinales.quantity] = estadoFinal;
            estadosFinales.quantity++;
        }
        char *transition = strstr(line, "label");
        if (transition) {
            char numberChar = line[0];
            char cadenaNumero[2];
            cadenaNumero[0] = numberChar;
            cadenaNumero[1] = '\0';
            int from = atoi(cadenaNumero);
            
            char numberChar = line[3];
            char cadenaNumero[2];
            cadenaNumero[0] = numberChar;
            cadenaNumero[1] = '\0';
            int to = atoi(cadenaNumero);

            char numberChar = line[13];
            char cadenaNumero[2];
            cadenaNumero[0] = numberChar;
            cadenaNumero[1] = '\0';
            int label = atoi(cadenaNumero);
        }
    }

    printf("\n");
    printf("\n");
    printf("El inicial es: %d\n", estadoInicial);
    printf("Los finales son: ");
    for (int i = 0; i < estadosFinales.quantity; i++) {
        printf("%d ", estadosFinales.a[i]);
    }
    fclose(file);
}
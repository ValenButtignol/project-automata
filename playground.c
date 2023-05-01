#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define LAMBDA -100
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
            char cadenaNumero[3];
            cadenaNumero[0] = inic[7];
            cadenaNumero[1] = inic[8];
            cadenaNumero[2] = '\0';
            estadoInicial = atoi(cadenaNumero);  
        }
        char *final = strstr(line, "[shape=doublecircle];");
        if (final) {
            char cadenaNumero[3];
            cadenaNumero[0] = line[0];
            cadenaNumero[1] = line[1];
            cadenaNumero[2] = '\0';
            int estadoFinal = atoi(cadenaNumero);
            estadosFinales.a[estadosFinales.quantity] = estadoFinal;
            estadosFinales.quantity++;
        }
        char *transition = strstr(line, "label");
        if (transition) {
            char cadenaNumero[3];
            cadenaNumero[0] = line[0];
            cadenaNumero[1] = line[1];
            cadenaNumero[2] = '\0';
            int from = atoi(cadenaNumero);
            
            cadenaNumero[3];
            cadenaNumero[0] = line[4];
            cadenaNumero[1] = line[5];
            cadenaNumero[2] = '\0';
            int to = atoi(cadenaNumero);

            char label[(15 - strlen(line) - 4)]; 
            for (int i = 15; i < strlen(line) - 4; i++)
            {
                label[i - 15] = line[i];
            }
            label[strlen(line) - 4 - 15] = '\0';

            Array labels; 
            labels.quantity = 0;
            char s[2];
            s[0] = ',';
            s[1] = '\0';
            char* token = strtok(label, s);
            while( token != NULL ) {
                int label;
                if (token[0] == '_')
                {
                    label = LAMBDA;
                } else {
                    cadenaNumero[0] = token[0];
                    cadenaNumero[1] = token[1];
                    cadenaNumero[2] = '\0';
                    label = atoi(cadenaNumero);
                }
                labels.a[labels.quantity] = label;
                labels.quantity++;

                token = strtok(NULL, s);
            }
            printf("From: %d, To: %d\n", from, to);
            printf("Labels: ");
            for (int i = 0; i < labels.quantity; i++) {
                printf("%d ", labels.a[i]);
            }
            printf("\n");
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



    /* char st[4];
    st[0] = '"';
    st[1] = '\0';
    char* token2 = strtok(line, st);
    while(token2 != NULL) {
        st[0] = '"';
        st[1] = ']';
        st[2] = ';';
        st[3] = '\0';
        token2 = strtok(NULL, st);
        if (strcmp(token2, "\0") != 0) {
            printf("token2: %s \n", token2 );
        }
        st[0] = '"';
        st[1] = '\0';
    } */

}
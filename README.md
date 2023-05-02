# ProyectAutomatons

Para ejecutar: (Sería el main con el resto de archivos .c)
gcc main.c structures/array.c structures/finite_automaton.c structures/markable.c algorithms/convert_ndfa_to_dfa.c algorithms/belongs_to_language -o main 


Creo que anda todo menos el belongs_to_language.
Chequear los imports, creo que al repetirse imports en diferentes directiorios, se corrompe el main pq intenta redefinir los structs y algunas funciones de nuevo.
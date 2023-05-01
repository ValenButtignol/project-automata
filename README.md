# ProyectAutomatons

Para ejecutar: (Sería el main con el resto de archivos .c)
gcc main.c data_structures/array.c data_structures/finite_automaton.c data_structures/markable.c algorithms/convert_ndfa_to_dfa.c algorithms/belongs_to_language utils/utils.c -o main 


Creo que anda todo menos el belongs_to_language.
Chequear los imports, creo que al repetirse imports en diferentes directiorios, se corrompe el main pq intenta redefinir los structs y algunas funciones de nuevo.
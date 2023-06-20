# ProjectAutomatons

---
This project was made by [Delfina Buil](https://github.com/delfib), [Valentín Buttignol](https://github.com/ValenButtignol) and [Mateo Vieyra](https://github.com/mateovieyra). It consists on making an automaton from a certain input, and contains some automatons operations.
---

## Commands

For compiling this project, use the following command:
```
gcc main.c src/algorithms/belongs_to_language.c src/algorithms/concatenate_ndfa.c src/algorithms/convert_ndfa_to_dfa.c src/algorithms/kleene_closure_ndfa.c src/algorithms/read_and_write.c src/algorithms/union_ndfa.c src/structures/dfa.c src/structures/ndfa.c src/structures/node.c src/structures/set_of_markable_sets.c src/algorithms/parser.c -o main 
```

For executing this project, you must use the next commands:
```
./main quantityOfStates quantityOfSymbols automaton.dot "string" output.dot
```

Here's an example:
```
./main 4 2 automaton.dot "00110" "output.dot"
```


## Disclaimer
When recieved a quantity of symbols, the symbols represented in the automaton go from 0 to n-1.  E.g. When quantityOfSymbols = 2, the symbols represented are 0 and 1.
This same rule is applied to the quantityOfStates.

---

## Contents

According to the class assignment, the different activities can be found in the next index:
1) [NDFA Implementation](https://github.com/ValenButtignol/project-automatons/blob/main/structures/finite_automaton.c)
2) [BelongsToLanguage Implementation](https://github.com/ValenButtignol/project-automatons/blob/main/algorithms/belongs_to_language.c)
3) [Parse Input and Output Implementation](https://github.com/ValenButtignol/project-automatons/blob/main/algorithms/read_and_write.c)
4) [Convert NDFA to DFA Implementation](https://github.com/ValenButtignol/project-automatons/blob/main/algorithms/convert_ndfa_to_dfa.c)

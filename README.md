# ProjectAutomatons

## Commands for compiling this project:
- For compiling this project, use the following command:
```
gcc main.c structures/array.c structures/finite_automaton.c structures/markable.c algorithms/convert_ndfa_to_dfa.c algorithms/belongs_to_language.c algorithms/read_and_write.c -o main 
```


## Rules and commands for executing this project:
- For executing an input, every state and transition must be defined with two ciphers. For example:
The next input is not valid:
```
digraph{
inic[shape=point];
inic->0;
0->1 [label="0"];
1->2 [label="1"];
1->1 [label="1"];
1->3 [label="0"];
3->3 [label="0,1"];
[shape=doublecircle];
3[shape=doublecircle];
}
```

Instead, use the following:
```
digraph{
inic[shape=point];
inic->00;
00->01 [label="00"];
01->02 [label="01"];
01->01 [label="01"];
01->03 [label="00"];
03->03 [label="00,01"];
00[shape=doublecircle];
03[shape=doublecircle];
}
```

E.g. State = 0 is represented as 00 whereas State = 10 is representad as 10.


- For executing this project, you must use the next commands:
```
./main quantityOfStates quantityOfSymbols automaton.dot "string" output.dot
```

Here's an example:
```
./main 4 2 automaton.dot "00110"
```


## Disclaimer
When recieved a quantity of symbols, the symbols represented in the automaton go from 0 to n-1.  E.g. When quantityOfSymbols = 2, the symbols represented are 0 and 1.
This same rule is applied to the quantityOfStates.

# ProyectAutomatons

## Rules for executing commands:
- For executing an input, every state and transition must be defined with two ciphers. For example:
Is not valid the next input:
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


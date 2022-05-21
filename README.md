# -c---
浙江大学《编译原理》课程实验：c--编译器

```
yacc -d cParser.y -o cParser.cpp
flex -o cScanner.cpp cScanner.l
cc cScanner.cpp cParser.cpp cCompilerCommon.cpp main.cpp runner.cpp -o compiler -lm -lstdc++
cc runner.cpp runnerMain.cpp -o runner -lm -lstdc++

```
```
./compiler < ./tests/test1.c > parsetree.txt
./runner

```
```
test2:

5 4
213 456 987 321
786 132 786 98
12 321 9 7
1 0 4 5
4 5 6 7
4 5
1 46 1 5 7
4 1 2 5 4
65 57 234 6571 98
51 798 41 1 4
```

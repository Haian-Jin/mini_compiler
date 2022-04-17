# mini_compiler
Final project for the course named Compilers Principle in Zhejiang University

编译方法：
```
yacc -d cParser.y -o cParser.cpp
flex -o cScanner.cpp cScanner.l
cc cScanner.cpp cParser.cpp -o compiler -lm
```

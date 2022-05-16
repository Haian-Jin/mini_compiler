clear
rm cParser.hpp  cParser.cpp
bison -d cParser.y -o cParser.cpp
flex -o cScanner.cpp cScanner.l

cc cScanner.cpp cParser.cpp cCompilerCommon.cpp main.cpp -o compiler -lm -ljsoncpp -lstdc++ -std=c++14
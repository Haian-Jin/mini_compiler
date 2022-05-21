#include"./runner.hpp"
using namespace std;

int main(){
    ProgramRam program;
    program.readCode();
    Runner runner(program);
    //program.print();
    runner.run();
}
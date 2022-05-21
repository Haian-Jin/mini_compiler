#include "./cCompilerCommon.hpp"
#include "./runner.hpp"
extern Node *makeParseTree();
extern ProgramRam program;
int main(){
    csLineCnt++;
    try{
        Node *treeRoot = makeParseTree();
        std::cout<<"makeDone\n";
        if(treeRoot){
            treeRoot->printTree();
            treeRoot->simplify();
            std::cout<<"\n\nThe simplified tree is:\n\n";
            treeRoot->printTree();
        }
        std::cout<<"Original SymbolTable:\n\n";
        SymbolTable::viewAllSymbolTable();
        //symbolTableStack->push(SymbolTable::getSymbolTableByName("main"));
        treeRoot->codeGen();
        //symbolTableStack->pop();
        std::cout<<"\n\nGenerated:\n\n";
        SymbolTable::viewAllSymbolTable();
        program.push({"NULL","","",""});
        program.print(ofstream("midcode.m"));

        Runner runner(program);
        //runner.run();
    }catch(char const *s){
        std::cout<<s;
    }
    //if(treeRoot->semanticCheck());
    return 0;
}

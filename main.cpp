#include "./cCompilerCommon.hpp"
extern Node *makeParseTree();
int main(){
    try{
    Node *treeRoot = makeParseTree();
    if(treeRoot){
        treeRoot->printTree();
        treeRoot->simplify();
        std::cout<<"\n\nThe simplified tree is:\n\n";
        treeRoot->printTree();
    }
    SymbolTable::viewAllSymbolTable();
    }catch(char const *s){
        std::cout<<s;
    }
    //if(treeRoot->semanticCheck());
}

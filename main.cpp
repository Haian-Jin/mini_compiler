#include "./cCompilerCommon.hpp"
extern Node *makeParseTree();
int main(){
    Node *treeRoot = makeParseTree();
    if(treeRoot){
        treeRoot->printTree();
        treeRoot->simplify();
        std::cout<<"\n\nThe simplified tree is:\n\n";
        treeRoot->printTree();
    }
    //if(treeRoot->semanticCheck());
}

#include "./cCompilerCommon.hpp"
#include <iostream>
#include <fstream>
extern Node *makeParseTree();
using std::string;
int main(){
    csLineCnt++;
    // try{
    Node *treeRoot = makeParseTree();
    // if(treeRoot){
    //     treeRoot->printTree();
    //     // treeRoot->simplify();
    //     std::cout<<"\n\nThe simplified tree is:\n\n";
    //     treeRoot->printTree();
    // }
    // SymbolTable::viewAllSymbolTable();
    // }catch(char const *s){
    //     std::cout<<s;
    // }

    auto root = treeRoot->jsonGen();


    string jsonFile = "./A_tree.json";
    std::ofstream astJson(jsonFile);
    if( astJson.is_open() ){
        astJson << root;
        astJson.close();
        std::cout << "json write to " << jsonFile << std::endl;
    }


    //if(treeRoot->semanticCheck());
}

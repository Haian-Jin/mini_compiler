#include "./cCompilerCommon.hpp"
#include <iostream>
#include <fstream>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/Support/raw_ostream.h>
extern Node *makeParseTree();
extern std::unique_ptr<Module> TheModule;
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
    TheModule = std::make_unique<Module>("test", TheContext);
    printf("1\n");
    treeRoot->codeGen();
    printf("2\n");
    TheModule->print(llvm::errs(), nullptr);
//    if(treeRoot->semanticCheck());
}

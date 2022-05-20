#include "./cCompilerCommon.hpp"
#include <iostream>
#include <fstream>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/raw_os_ostream.h>
#include <llvm/IR/AssemblyAnnotationWriter.h>
extern Node *makeParseTree();
//extern Module* TheModule;
using std::string;

int main(){
    csLineCnt++;
    Node *treeRoot = makeParseTree();


    auto root = treeRoot->jsonGen();


    string jsonFile = "./A_tree.json";
    std::ofstream astJson(jsonFile);
    if( astJson.is_open() ){
        astJson << root;
        astJson.close();
        std::cout << "json write to " << jsonFile << std::endl;
    }
    treeRoot->codeGen();
    llvm::AssemblyAnnotationWriter *aaw = new llvm::AssemblyAnnotationWriter();
    llvm::raw_ostream &e=errs();
    TheModule->print(outs(), aaw);
    e.flush();
}

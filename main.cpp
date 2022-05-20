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
//    printf("begin codeGen\n");
    treeRoot->codeGen();//std::cout<<"a\n";
    //llvm::raw_os_ostream errs();
    /*
    auto &functionList = TheModule->getFunctionList();
    int o=0;
    for(auto i=functionList.begin(),e=functionList.end();i!=e;i++){
        llvm::Function *f = &*i;
        errs()<<f->getName()<<(o++)<<"\n";
    }
    
    llvm::Function * mainFunction = TheModule->getFunction("aa");std::cout<<"a\n";
    assert(mainFunction!=NULL);
    BasicBlock &mainFunctionEntry = mainFunction->getEntryBlock();std::cout<<"a\n";
    //outs()<<mainFunctionEntry;
    //printf("print finished\n");
    std::cout<<"a\n";
    for(BasicBlock::iterator i=mainFunctionEntry.begin(), e=mainFunctionEntry.end();i!=e;i++){
        std::cout<<"a\n";
        Instruction* ii = &*i;
        outs()<<(*ii);
        outs()<<"\n";
    }
    */
    llvm::AssemblyAnnotationWriter *aaw = new llvm::AssemblyAnnotationWriter();
    llvm::raw_ostream &e=errs();
    TheModule->print(outs(), aaw);
    e.flush();
    //aaw->printInfoComment()
    //errs()<<"foo\n";
    //TheModule->dump();=-
//    printf("print finished\n");
//    if(treeRoot->semanticCheck());
}

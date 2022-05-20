#include "./cCompilerCommon.hpp"
#include <iostream>
#include <fstream>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/raw_os_ostream.h>
#include <llvm/IR/AssemblyAnnotationWriter.h>

#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/ADT/Optional.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/FileSystem.h>

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
    string objectFile = "output.o";
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



    InitializeAllTargetInfos();
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmParsers();
    InitializeAllAsmPrinters();
    auto targetTriple = llvm::sys::getDefaultTargetTriple();
    TheModule->setTargetTriple(targetTriple);

    std::string error;
    auto Target = TargetRegistry::lookupTarget(targetTriple, error);
    if(!Target){
        errs()<<"Target not found: "<<error<<"\n";
        return 1;
    }

    auto CPU = "generic";
    auto features = "";

    TargetOptions opt;
    auto RM = Optional<Reloc::Model>();
    auto theTargetMachine = Target->createTargetMachine(targetTriple, CPU, features, opt, RM);

    TheModule->setDataLayout(theTargetMachine->createDataLayout());
    TheModule->setTargetTriple(targetTriple);

    std::error_code EC;
    raw_fd_ostream dest(objectFile.c_str(), EC, sys::fs::F_None);
    legacy::PassManager pass;
    auto fileType = llvm::CGFT_ObjectFile;
    if(theTargetMachine->addPassesToEmitFile(pass, dest, nullptr, fileType)){
        errs()<<"The target machine can't emit a file of this type\n";
        return 1;
    }

    pass.run(*TheModule);
    dest.flush();

    outs() << "Object code wrote to " << objectFile.c_str() << "\n";

}

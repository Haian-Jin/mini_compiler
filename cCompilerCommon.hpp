#pragma once
#ifndef __C_COMPILER_COMMON_HPP__  //tnnd, zhe ge fang fa zai c++ li mian bu guan yong.
#define __C_COMPILER_COMMON_HPP__  
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<string>
#include<sstream>
#include<iostream>
#include<vector>
#include<map>
#include<cstdarg>
#include<cassert>
class SymbolTableStack;
class SymbolTable;
class VariableDeclarationNode;
class VariableDeclarationStatementNode;
struct Attribute;
extern int csLineCnt;
extern int csColumnCnt;
extern SymbolTableStack *symbolTableStack;

class NameCounter{
private:
    std::map<std::string, int> map;
public:
    NameCounter(){}
    std::string getNumberedName(std::string name){
        if(map.find(name)==map.end()){
            map.insert({name,0});
        }
        return name+"["+std::to_string(map[name]++)+"]";
    }
};

class AddressCounter{
private:
    int addr;
public:
    AddressCounter():addr(0){}
    int getNextAddr(){
        return addr++;
    }
    int getNextNAddr(int n){
        int t = addr;
        addr += n;
        return t;
    }
};
extern AddressCounter* addressCounter;
struct Tuple4{
    std::string op, sa1, sa2, da;
};
class Memory{
public:
    std::vector<Tuple4> mmemory;
    void load(int addr, Tuple4 t){
        while(mmemory.size()<addr){
            mmemory.push_back({"var","","",""});
        }
        mmemory.push_back(t);
    }
};

class Node{
public:
    enum Type{
        TYPE_INT,TYPE_FLOAT,TYPE_DOUBLE,TYPE_CHAR,TYPE_STRING,TYPE_VOID,TYPE_STRUCT
    };
    enum Kind{
        KIND_FUNCTION,KIND_VARIABLE,KIND_ARGUMENT,KIND_ATTRIBUTE,KIND_CONSTANT
    };
protected:
    std::string mSymbolName;
    std::string mTokenValue; //(token string)
    bool mIsTerminal;
    bool mIsNegligible;
    std::vector<Node*> mChildren;
public:
    Node(){};
    Node(std::string _symbolName, int childrenNumber, ...):mIsNegligible(false),mSymbolName(_symbolName),mIsTerminal(false),mTokenValue("I am not a terminal."){
        va_list vl;
        va_start(vl, childrenNumber);
        for(int i=0;i<childrenNumber;i++){
            mChildren.push_back(va_arg(vl,Node*));
        }
    }
    Node(std::string _tokenValue, bool negligible=false):mIsNegligible(negligible),mSymbolName("I am a terminal, valued "+_tokenValue),mIsTerminal(true),mTokenValue(_tokenValue){
        
    }
    void addChild(Node *newChild){
        mChildren.push_back(newChild);
    }
    Node* getChildrenById(int i){
        if(i>=mChildren.size())return NULL;
        return mChildren[i];
    }
    int getChildrenNumber(){
        return mChildren.size();
    }
    std::vector<Node*> getChildren(){
        return mChildren;
    }
    bool isTerminal()const{
        return mIsTerminal;
    }
    bool isNegligible(){
        return mIsTerminal && mIsNegligible;
    }
    std::string getSymbolName()const{
        return this->mSymbolName;
    }
    std::string getTokenValue(){
        if(!(this->mIsTerminal)){
            //std::cout<<"("<<mSymbolName<<") ";
            //throw("I am not a terminal.");
            return getSymbolName();
        }
        return this->mTokenValue;
    }
    std::string getName()const{
        return mIsTerminal?mTokenValue:mSymbolName;
    }
    void printTree(int depth=0){
        for(int i=0;i<depth;i++){
            std::cout<<"    ";
        }
        std::cout<<this->getName()<<std::endl;
        for(int i=0;i<mChildren.size();i++){
            mChildren[i]->printTree(depth+1);
        }
    }
    void simplify(){
        if(mIsTerminal)return;
        for(int i=0;i<mChildren.size();i++){
            if(mChildren[i]->isNegligible()){
                delete mChildren[i];
                mChildren.erase(mChildren.begin()+i, mChildren.begin()+i+1);
                i--;
            }
        }
        for(auto child : mChildren){
            child->simplify();
        }
    }
    

public:
    virtual std::string codeGen(){
        for(auto i : mChildren){
            std::cout<<i->getName()<<" codeGen begin\n";
            i->codeGen();
            std::cout<<i->getName()<<" codeGen finished\n";
        }
        return "`";
    }
    virtual void setType(Node::Type _type){std::cout<<"wrong\n";}
    virtual void setType(Node* c){std::cout<<"wrong\n";}
    virtual Node::Type getType(){std::cout<<"wrong\n";}
    virtual std::string getTypeString(){std::cout<<"wrong\n";}
    virtual void setKind(Node::Kind _kind){std::cout<<"wrong\n";}
    virtual Node::Kind getKind(){std::cout<<"wrong\n";}
    virtual void setArgList(std::vector<Node::Type> _argList){std::cout<<"wrong\n";}
    virtual std::vector<Node::Type> getArgList(){std::cout<<"wrong\n";}
    virtual void setArgListStructName(std::vector<std::string> _structName){std::cout<<"wrong\n";}
    virtual std::vector<std::string> getArgListStructName(){std::cout<<"wrong\n";}
    virtual void setArraySizes(std::vector<int> _sizes){std::cout<<"wrong\n";}
    virtual std::vector<int> getArraySizes(){std::cout<<"wrong\n";}
    virtual bool isArray(){std::cout<<"wrong\n";}
    virtual int getArrayDimension(){std::cout<<"wrong\n";}
    virtual void setStructTypeName(std::string _name){std::cout<<"wrong\n";}
    virtual std::string getStructTypeName(){std::cout<<"wrong\n";}
    virtual void setVariableName(std::string _name){std::cout<<"wrong\n";}
    virtual std::string getVariableName(){std::cout<<"wrong\n";}
    virtual void setPosition(int l,int c){std::cout<<"wrong\n";}
    virtual void setPosition(Node*){std::cout<<"wrong\n";}
    virtual int getLineNumber(){std::cout<<"Wrong\n";}
    virtual int getColumnNumber(){std::cout<<"wrong\n";}
    virtual void setAttribute(void *p);
    virtual void copyFromChild(){
        //std::cout<<"Wrong copy\n";
        this->setType(mChildren[0]->getType());
        this->setKind(mChildren[0]->getKind());
        this->setArgList(mChildren[0]->getArgList());
        this->setArgListStructName(mChildren[0]->getArgListStructName());
        this->setArraySizes(mChildren[0]->getArraySizes());
        this->setStructTypeName(mChildren[0]->getStructTypeName());
        this->setVariableName(mChildren[0]->getVariableName());
        this->setPosition(mChildren[0]->getLineNumber(), mChildren[0]->getColumnNumber());
    }
    virtual void copyFrom(Node *c){
        //std::cout<<"Wrong copy\n";
        //this->setType(c->getType());
        this->setType(c);
        this->setKind(c->getKind());
        this->setArgList(c->getArgList());
        this->setArgListStructName(c->getArgListStructName());
        this->setArraySizes(c->getArraySizes());
        this->setStructTypeName(c->getStructTypeName());
        this->setVariableName(c->getVariableName());
        this->setPosition(c->getLineNumber(), c->getColumnNumber());
    }
    virtual void copyFrom(Attribute *c);
    virtual void fullCopyFrom(Node *c);
};


class AttributivedNode : public Node{
protected:
    AttributivedNode::Type mTokenType;
    AttributivedNode::Kind mTokenKind;
    std::vector<AttributivedNode::Type> mTokenArgList;
    std::vector<std::string> mTokenArgListStructTypeName;
    std::vector<int> mArraySizes;
    std::string mStructTypeName;
    std::string mVariableName;
    int mLineNumber;
    int mColumnNumber;
public:
    virtual std::string codeGen(){
        for(auto i : mChildren){
            std::cout<<i->getName()<<" codeGen begin\n";
            i->codeGen();
            std::cout<<i->getName()<<" codeGen finished\n";
        }
        return "`";
    }
    virtual int getSize(){return -1;}
    AttributivedNode(){};
    AttributivedNode(std::string _symbolName, int childrenNumber, ...):Node(_symbolName,0){
        va_list vl;
        va_start(vl, childrenNumber);
        for(int i=0;i<childrenNumber;i++){
            mChildren.push_back(va_arg(vl,Node*));
        }
        mIsNegligible=(false),mSymbolName=(_symbolName),mIsTerminal=(false),mTokenValue=("I am not a terminal.");
    }
    AttributivedNode(std::string _tokenValue, bool negligible=false):Node(_tokenValue,negligible){
        
    }
    void setType(AttributivedNode::Type _type){
        this->mTokenType = _type;
    }
    void setType(Node *c){
        this->setType(c->getType());
        if(c->getType()==Node::TYPE_STRUCT){
            this->setStructTypeName(c->getStructTypeName());
        }
    }
    AttributivedNode::Type getType(){
        return this->mTokenType;
    }
    std::string getTypeString(){
        std::string string;
        switch(this->mTokenType){
            case(Node::TYPE_DOUBLE):
                string+={"double"};
                break;
            case(Node::TYPE_INT):
                string+={"int"};
                break;
            case(Node::TYPE_STRUCT):
                string+=(std::string("struct ")+this->mStructTypeName);
                break;
            default :
                string+=std::to_string(this->mTokenType);
        }
        for(int i=0;i<this->mArraySizes.size();i++){
            string+="[]";
        }
        return string;
    }
    void setKind(AttributivedNode::Kind _kind){
        this->mTokenKind = _kind;
    }
    AttributivedNode::Kind getKind(){
        return this->mTokenKind;
    }
    void setArgList(std::vector<AttributivedNode::Type> _argList){
        mTokenArgList.assign(_argList.begin(),_argList.end());
    }
    std::vector<AttributivedNode::Type> getArgList(){
        return this->mTokenArgList;
    }
    void setArgListStructName(std::vector<std::string> _structName){
        mTokenArgListStructTypeName.assign(_structName.begin(), _structName.end());
    }
    std::vector<std::string> getArgListStructName(){
        return mTokenArgListStructTypeName;
    }
    void setArraySizes(std::vector<int> _sizes){
        mArraySizes.assign(_sizes.begin(),_sizes.end());
    }
    std::vector<int> getArraySizes(){
        return mArraySizes;
    }
    bool isArray(){
        return mArraySizes.size()>0;
    }
    int getArrayDimension(){
        return mArraySizes.size();
    }
    /*void copyFromChild(){
        std::cout<<"Right copy\n";
        this->setType(mChildren[0]->getType());
        this->setKind(mChildren[0]->getKind());
        this->setArgList(mChildren[0]->getArgList());
        this->setArraySizes(mChildren[0]->getArraySizes());
        this->setStructTypeName(mChildren[0]->getStructTypeName());
        this->setVariableName(mChildren[0]->getVariableName());
    }*/
    void setStructTypeName(std::string _name){
        mStructTypeName = _name;
    }
    std::string getStructTypeName(){
        return mStructTypeName;
    }
    void setVariableName(std::string _name){
        this->mVariableName = _name;
    }
    std::string getVariableName(){
        return mVariableName;
    }
    void setPosition(int l,int c){
        mLineNumber = l;
        mColumnNumber = c;
    }
    int getLineNumber(){
        return mLineNumber;
    }
    int getColumnNumber(){
        return mColumnNumber;
    }
    void setPosition(Node *c){
        mLineNumber = c->getLineNumber();
        mColumnNumber = c->getColumnNumber();
    }
};

class StructDeclarationNode : public AttributivedNode{
public:
    StructDeclarationNode(Node *a){
        this->fullCopyFrom(a);
    }
    Node::Type getType(){
        return Node::TYPE_STRUCT;
    }
    int getSize();
    virtual std::string codeGen();
    int mSizeSum = -1;
};

class StructMemberNode : public AttributivedNode{
public:
    StructMemberNode(Node *a){
        this->fullCopyFrom(a);
    }
    int getSize(){
        int arraySize = 1;
        if(isArray()){
            for(int i : this->getArraySizes()){
                arraySize *= i;
            }
        }
        int singleSize = 1;
        /*if(getType()==Node::TYPE_STRUCT){
            singleSize = symbolTableStack->lookUp(this->getStructTypeName())->size;
        }*/
        return arraySize * singleSize;
    }
    virtual std::string codeGen(){
        std::cout<<"skipped\n";
        return "`";
    }
};

class VariableDeclarationStatementNode : public AttributivedNode{
public:
    VariableDeclarationStatementNode(Node *a){
        this->fullCopyFrom(a);
    }

    Node::Type getType(){
        return mChildren[0]->getType();
    }
    std::string getTypeString(){
        return mChildren[0]->getTypeString();
    }
    virtual std::string codeGen();
};

class VariableDeclarationNode : public AttributivedNode{
public:
    VariableDeclarationNode(Node *a){
        this->fullCopyFrom(a);
    }
    Node::Type getType(){
        return AttributivedNode::getType();
    }
    std::string getTypeString(){
        return AttributivedNode::getTypeString();
    }
    int getSize();
    virtual std::string codeGen();
};

class FunctionDeclarationNode : public AttributivedNode{
public:
    FunctionDeclarationNode(Node *c):AttributivedNode(){
        this->fullCopyFrom(c);
    }
    virtual std::string codeGen();
    int getSize();
};

class ExpressionNode : public AttributivedNode{
public:
    ExpressionNode(std::string _symbolName, int childrenNumber, ...):AttributivedNode(_symbolName,0){
        va_list vl;
        va_start(vl, childrenNumber);
        for(int i=0;i<childrenNumber;i++){
            mChildren.push_back(va_arg(vl,Node*));
        }
        mIsNegligible=(false),mSymbolName=(_symbolName),mIsTerminal=(false),mTokenValue=("I am not a terminal.");
    }
    ExpressionNode(Node *c):AttributivedNode(){
        this->fullCopyFrom(c);
    }
    virtual std::string codeGen();


public:
    int intValue;
    double doubleValue;
};

class StringNode : public ExpressionNode{
public:
    StringNode(Node *c):ExpressionNode(c){}
    virtual std::string codeGen();
};

class IfNode : public AttributivedNode{
public:
    IfNode(Node *c):AttributivedNode(){
        this->fullCopyFrom(c);
    }
    virtual std::string codeGen();
};

class ForNode : public AttributivedNode{
public:
    ForNode(Node *c):AttributivedNode(){
        this->fullCopyFrom(c);
    }
    virtual std::string codeGen();
};

class RetNode : public AttributivedNode{
public:
    RetNode(Node* c):AttributivedNode(){
        this->fullCopyFrom(c);
    }
    virtual std::string codeGen();
};

class ReadNode : public ExpressionNode{
public:
    ReadNode(std::string _symbolName, int childrenNumber, ...):ExpressionNode(_symbolName,0){
        va_list vl;
        va_start(vl, childrenNumber);
        for(int i=0;i<childrenNumber;i++){
            mChildren.push_back(va_arg(vl,Node*));
        }
        mIsNegligible=(false),mSymbolName=(_symbolName),mIsTerminal=(false),mTokenValue=("I am not a terminal.");
    }
    virtual std::string codeGen();
};

class WriteNode : public ExpressionNode{
public:
    WriteNode(std::string _symbolName, int childrenNumber, ...):ExpressionNode(_symbolName,0){
        va_list vl;
        va_start(vl, childrenNumber);
        for(int i=0;i<childrenNumber;i++){
            mChildren.push_back(va_arg(vl,Node*));
        }
        mIsNegligible=(false),mSymbolName=(_symbolName),mIsTerminal=(false),mTokenValue=("I am not a terminal.");
    }
    virtual std::string codeGen();
};

struct Attribute{
    std::string name;
    Node::Type type;
    Node::Kind kind;
    std::vector<Node::Type> argList;
    std::vector<std::string> argListStructName;
    std::vector<int> arraySizes;
    std::string structTypeName;
    int addr;
    int size;
    int offset;
    int lineNumber;
    int columnNumber;
    Attribute(std::string _name, Node::Type _type, Node::Kind _kind, std::vector<Node::Type> _argList, std::vector<std::string> _argListStructName, std::vector<int> _arraySizes, std::string _structTypeName, int l, int c)
        : name(_name),type(_type),kind(_kind),argList(_argList),arraySizes(_arraySizes),structTypeName(_structTypeName),lineNumber(l),columnNumber(c),argListStructName(_argListStructName){};
    Attribute(){}
    Attribute(Node *p)
        : name(p->getVariableName()),type(p->getType()),kind(p->getKind()),argList(p->getArgList()),arraySizes(p->getArraySizes()),
          structTypeName(p->getStructTypeName()),lineNumber(p->getLineNumber()),columnNumber(p->getColumnNumber()),argListStructName(p->getArgListStructName()){std::cout<<"new attr\n";};
    void print(){
        std::cout<<name<<' ';
        switch(type){
            case Node::TYPE_INT:
                std::cout<<"int ";
                break;
            case Node::TYPE_DOUBLE:
                std::cout<<"double ";
                break;
            case Node::TYPE_STRUCT:
                std::cout<<"struct "<<structTypeName<<' ';
                break;
            default:
                std::cout<<type<<' ';
        }
        switch(kind){
            case Node::KIND_ARGUMENT:
                std::cout<<"augument ";
                break;
            case Node::KIND_ATTRIBUTE:
                std::cout<<"attribute ";
                break;
            case Node::KIND_CONSTANT:
                std::cout<<"constant ";
                break;
            case Node::KIND_FUNCTION:
                std::cout<<"function ";
                break;
            case Node::KIND_VARIABLE:
                std::cout<<"variable ";
                break;
            default:
                std::cout<<kind<<' ';
        }
        if(kind==Node::KIND_FUNCTION){
            std::cout<<'(';
            for(int i=0;i<argList.size();i++){
                auto string = argList[i];
                switch(string){
                    case Node::TYPE_INT:
                        std::cout<<"int";
                        break;
                    case Node::TYPE_DOUBLE:
                        std::cout<<"double";
                        break;
                    case Node::TYPE_STRUCT:
                        std::cout<<"struct "<<argListStructName[i];
                        break;
                    default:
                        std::cout<<type;
                }
                if(i!=argList.size()-1)std::cout<<",";
            }
            std::cout<<") ";
        }
        if(arraySizes.size()>0){
            for(auto size : arraySizes){
                std::cout<<"["<<size<<"]";
            }
            std::cout<<' ';
        }
        printf("addr:%d size:%d offset:%d ",addr,size,offset);
        printf(" --pos:l%dc%d\n", lineNumber, columnNumber);
    }
};

class SymbolTable{
private:
    std::string mSymbolTableName;
    std::map<std::string, Attribute*> map;
    static std::map<std::string, SymbolTable*> set;
public:
    SymbolTable():mSymbolTableName({"Unamed Symbol Table"}){
        set.insert({mSymbolTableName, this});
    }
    SymbolTable(std::string name):mSymbolTableName(name){
        set.insert({mSymbolTableName, this});
    }
    std::map<std::string, Attribute*> getTable(){
        return map;
    }
    std::string getName(){
        return mSymbolTableName;
    }
    bool insert(Attribute* t){
        if(map.find(t->name)!=map.end()){
            return false;
        }else{
            map.insert({t->name,t});
            return true;
        }
    }
    Attribute *lookUp(std::string name){
        if(map.find(name)==map.end()){
            return NULL;
        }else{
            return map[name];
        }
    }
    void print(){
        std::cout<<"Symbol Table Name: "<<mSymbolTableName<<std::endl;
        int i=1;
        for(auto pair : map){
            printf("No.%03d ",i++);
            //std::cout<<pair.first<<' ';
            pair.second->print();
        }
    }
    static SymbolTable *getSymbolTableByName(std::string symbolTableName){
        return set[symbolTableName];
    }
    static void viewAllSymbolTable(){
        std::cout<<"Printing All Symbol Tables attended...\n";
        for(auto pair : set){
            //std::cout<<"Symbol Table Name: "<<pair.first()<<std::endl;
            std::cout<<"----------------------------------------------\n";
            pair.second->print();
            std::cout<<"----------------------------------------------\n";
        }
    }
};

class SymbolTableStack{
private:
    std::vector<SymbolTable*> stack;
public:
    SymbolTableStack(SymbolTable *globalSymbolTable){
        stack.push_back(globalSymbolTable);
    }
    void push(SymbolTable* t){
        stack.push_back(t);
    }
    void pop(){
        if(stack.size()==1){
            throw("You cannot pop the global symbol table.");
        }
        stack.pop_back();
    }
    SymbolTable *top(){
        return stack[stack.size()-1];
    }
    Attribute *lookUp(std::string name){
        for(int i=stack.size()-1;i>=0;i--){
            if(stack[i]->lookUp(name)){
                return stack[i]->lookUp(name);
            }
        }
        return NULL;
    }
    bool insert(Attribute* t){
        std::cout<<"insert\n";
        return stack[stack.size()-1]->insert(t);
    }
};

//extern std::map<std::string, SymbolTable*> SymbolTable::set;

bool checkType(Node *p, Node::Type type);
bool checkKind(Node *p, Node::Kind kind);
bool typeMatch(Node *a, Node *b);
bool typeMatch(std::vector<Node::Type> a, std::vector<Node::Type> b);
bool typeMatch(std::vector<Node::Type> a,Node *c , std::vector<std::string> s);
bool typeMatch(Attribute *a, Node* b);
std::string type_to_string(Attribute *t);
#endif

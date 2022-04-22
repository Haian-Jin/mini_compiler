#pragma once
#ifndef __C_COMPILER_COMMON_HPP__  //tnnd, zhe ge fang fa zai c++ li mian bu guan yong.
#define __C_COMPILER_COMMON_HPP__  
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<string>
#include<iostream>
#include<vector>
#include<map>
#include<cstdarg>

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

class Node{
private:
    std::string mSymbolName;
    std::string mTokenValue; //(token string)
    bool mIsTerminal;
    bool mIsNegligible;
    std::vector<Node*> mChildren;
public:
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
    bool isTerminal()const{
        return mIsTerminal;
    }
    bool isNegligible(){
        return mIsTerminal && mIsNegligible;
    }
    std::string getSymbolName()const{
        return this->mSymbolName;
    }
    std::string getTokenValue()const{
        if(!(this->mIsTerminal))throw("I am not a terminal.");
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
    bool semanticCheck(){

    }
};


extern int csLineCnt;
extern int csColumnCnt;

#endif

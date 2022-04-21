#pragma once
#ifndef __C_COMPILER_COMMON_HPP__  //tnnd, zhe ge fang fa zai c++ li mian bu guan yong.
#define __C_COMPILER_COMMON_HPP__  
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
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
    std::string symbolName;
    std::string tokenValue; //(token string)
    bool isTerminal;
    std::vector<Node*> children;
public:
    Node(std::string _symbolName, int childrenNumber, ...):symbolName(_symbolName),isTerminal(false),tokenValue("I am not a terminal."){
        va_list vl;
        va_start(vl, childrenNumber);
        for(int i=0;i<childrenNumber;i++){
            children.push_back(va_arg(vl,Node*));
        }
    }
    Node(std::string _tokenValue):symbolName("I am a terminal, valued "+_tokenValue),isTerminal(true),tokenValue(_tokenValue){
        
    }
    void addChild(Node *newChild){
        children.push_back(newChild);
    }
    bool _isTerminal()const{
        return this->isTerminal;
    }
    std::string getSymbolName()const{
        return this->symbolName;
    }
    std::string getTokenValue()const{
        if(!(this->isTerminal))throw("I am not a terminal.");
        return this->tokenValue;
    }
    std::string getName()const{
        return isTerminal?tokenValue:symbolName;
    }
    void printTree(int depth=0){
        for(int i=0;i<depth;i++){
            std::cout<<"    ";
        }
        std::cout<<this->getName()<<std::endl;
        for(int i=0;i<children.size();i++){
            children[i]->printTree(depth+1);
        }
    }
};

extern int csLineCnt;
extern int csColumnCnt;

#endif

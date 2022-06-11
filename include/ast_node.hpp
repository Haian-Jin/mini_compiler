#pragma once

#include <cassert>
#include <cstdarg>
#include <cstring>
#include <iostream>
#include <json/json.h>
//#include "/usr/local/llvm/include/llvm/IR/Value.h"
#include <llvm/IR/Value.h>
#include <llvm/IR/Attributes.h>
#include <map>
#include <cmath>
#include <stack>
#include <string>
#include <vector>

// #include"noError.h"
#include <json/json.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <tr1/memory>
#include <unordered_map>
#include <regex>

//#include "exprNode.hpp"
//#include "ctrlNode.hpp"
//#include "funcNode.hpp"
//#include "statNode.hpp"
//#include "arrayNode.hpp"

using namespace llvm;
struct symAttribute;
//class Node;
struct Type_and_Address {
    llvm::Type::TypeID type;
    llvm::Value *address;
    bool isPtr = false;
    std::vector<int> arraySizes;
    bool isStruct = false;
    std::string stName;
};

extern llvm::LLVMContext TheContext;
extern llvm::IRBuilder<> Builder;//(TheContext);
extern Module *TheModule;// = new Module(llvm::StringRef(),TheContext);
extern std::unordered_map<std::string, Type_and_Address> variableTable;
extern std::stack<std::unordered_map<std::string, Type_and_Address> *> tableStack;
extern std::unordered_map<std::string, StructType *> structTable;

Value *LogErrorV(const char *Str);

Value *LogErrorV(std::string str);

/*
    命名器，输入一个字符串，输出它的带编号版本。用于输出parse
   tree的时候给各个节点命名。
    同时也用于给匿名作用域对应的符号表命名（比如statement block和匿名结构体）。
*/
class NameCounter {
private:
    std::map<std::string, int> map;

public:
    NameCounter() {}

    std::string getNumberedName(std::string name);
};

// 将各类型转换为boolean
Value *CastBool(Value *cond);

//生成zero initializer
llvm::Constant* con_0();

//获取block内临时变量表
std::unordered_map<std::string, Type_and_Address> *inheritTable();

/*
    语法分析树的结点。（不是抽象语法树）
    为属性文法做了一定的适配，有 AttributivedNode
   继承它，负责属性文法的各个功能。
*/
class Node {
public:
    /*
        Type：表明该变量/常量/表达式的数据类型
        Kind：表明该结点/变量/常量的类别
    */
    enum Type {
        TYPE_INT,
        TYPE_FLOAT,
        TYPE_DOUBLE,
        TYPE_CHAR,
        TYPE_STRING,
        TYPE_VOID,
        TYPE_STRUCT
    };
    enum Kind {
        KIND_FUNCTION,
        KIND_VARIABLE,
        KIND_ARGUMENT,
        KIND_ATTRIBUTE,
        KIND_CONSTANT
    };

protected:
    std::string mSymbolName; // 非终结符的名字，实际使用时会使用 NameCounter编号，比如“expressionStatement[0]”、“functionDeclaration[3]”等等。
    std::string  mTokenValue; // 终结符对应的字符串。这个是不编号的，输入什么就是什么。
    bool mIsTerminal; // 是否是终结符

    // expression
    std::vector<Node *> mChildren; // 树结点的孩子。只有非终结符才有孩子。
    Node::Type NodeType; // 节点的数据类型
    Node::Kind NodeKind; // 节点的类别

    /* 暂时保存 begin */

    std::vector<Node::Type> mTokenArgList; // 参数列表的类型，只有函数能用到
    std::vector<std::string> mTokenArgListStructTypeName; // 和参数列表配合使用，提供参数的结构体名字（如果是结构体的话）
    std::vector<int> mArraySizes; // 数组的各个维度的大小，只有数组能用到。如果不是数组，则这个容器的维度是0。
    std::string mStructTypeName; // 结构体名字，只有当类型是结构体的时候能用到。注：若类别是
                                // symAttribute 但数据类型是结构体，则说明这个节点正在定义一个结构体，此时这个变量就是定义的结构体的名字。
    std::string mVariableName; // 变量的名字。
    int mLineNumber;           // 位置（行）
    int mColumnNumber;         // 位置（列）
    /* 暂时保存 end */

public:
    Node() {};

    // 建立一个非终结符节点，挂接 childrenNumber 个孩子，分别是 ...
    Node(std::string _symbolName, int childrenNumber, ...);

    // 建立一个终结符结点，用在 scanner 里面。
    Node(std::string _tokenValue, bool negligible = false)
            : mSymbolName("I am a terminal, valued " + _tokenValue),
              mIsTerminal(true), mTokenValue(_tokenValue) {}

    // 是否是终结符，是 true 否 false
    bool isTerminal() const;

    // 返回名字，终结符就返回终结符对应的字符串，非终结符就返回非终结符的名字。
    std::string getName() const;

    // 设定节点的数据类型，不能自适应地一同取得结构体名。
    virtual void setType(Node::Type _type);

    // 将节点的数据类型设定成和 c 一样。而且如果 c 是结构体，也能一同设定结构体名。
    virtual void setType(Node *c);

    // 取得节点的数据类型
    virtual Node::Type getType();

    std::string getTokenValue() const;
    // 返回非终结符的名字
    std::string getSymbolName() const;

    // 设定节点的类别。
    virtual void setKind(Node::Kind _kind);

    // 取得节点的类别。
    virtual Node::Kind getKind();

    // 取得节点的参数列表。只有函数类型的节点才有可能用到。如果某个参数是结构体的话，需要和setArgListStructName/getArgListStructName 配合使用，以取得结构体名。
    virtual std::vector<Node::Type> getArgList();

    // 取得节点的参数列表的结构体名。只有函数类型的节点才有可能用到。和setArgList/getArgList 配合使用，以确定结构体的名字。 
    virtual std::vector<std::string> getArgListStructName();

    // 设定数组的维度和各个维度的大小。只有数组类型的节点才可能用到。
    virtual void setArraySizes(std::vector<int> _sizes);

    // 取得数组的维度和各个维度的大小。
    virtual std::vector<int> getArraySizes(); 

    // 判定该节点是不是数组，是 true 否 false
    virtual bool isArray() const; 

    // 判断改节点是不是double, float等type
    virtual bool isType() const {
        return Node::NodeKind == Node::KIND_ATTRIBUTE;
    }

    // 设定结构体的名字。只有当数据类型为结构体时才会用到这个。
    virtual void setStructTypeName(std::string _name);

    // 获得结构体的名字。只有当数据类型为结构体时才会用到这个。
    virtual std::string getStructTypeName();

    // 取得变量的名字，只有变量和函数这样的节点才会用到这个。
    virtual void setVariableName(std::string _name);

    // 设定位置，是这个词语/变量/定义/声明出现在文件中的为止。
    virtual void setPosition(int l, int c);

    // 把位置设定成和给定节点 c 一样。
    virtual void setPosition(Node *);

    // 取得行位置
    virtual int getLineNumber();

    // 取得列位置
    virtual int getColumnNumber();

    virtual std::string getNodeTypeName() const { return "!!!"; };

    virtual llvm::Value *codeGen() { return (llvm::Value *) 0; }

    virtual Json::Value jsonGen() const { return Json::Value(); }


};



// 属性。这个是变量的属性，是存在符号表里的，不是语法分析树的属性，它们会有细微的差别。
struct symAttribute {
    std::string name;
    Node::Type type;
    Node::Kind kind;
    std::vector<Node::Type> argList;
    std::vector<std::string> argListStructName;
    std::vector<int> arraySizes;
    std::string structTypeName;
    int lineNumber;
    int columnNumber;

    symAttribute(std::string _name, Node::Type _type, Node::Kind _kind,
                 std::vector<Node::Type> _argList,
                 std::vector<std::string> _argListStructName,
                 std::vector<int> _arraySizes, std::string _structTypeName,
                 int l, int c)
            : name(_name), type(_type), kind(_kind), argList(_argList),
              arraySizes(_arraySizes), structTypeName(_structTypeName),
              lineNumber(l), columnNumber(c),
              argListStructName(_argListStructName) {};

    symAttribute() {}

    symAttribute(Node *p)
            : name(), type(p->getType()), kind(p->getKind()),
              argList(p->getArgList()), arraySizes(p->getArraySizes()),
              structTypeName(p->getStructTypeName()),
              lineNumber(p->getLineNumber()), columnNumber(p->getColumnNumber()),
              argListStructName(p->getArgListStructName()) {};

    // 将这个属性打印在 stdout 上，用来看的。
    void print();
};

// 符号表。一般不用单个的符号表，而是直接使用符号表栈。
class SymbolTable {
private:
    std::string mSymbolTableName; // 表名。表明就是这个表对应的函数名/结构体名等。对匿名作用域来说，表名是用 NameCounter 自动生成的不重复的名字。
    std::map<std::string, symAttribute *> map;       // 符号表本体
    static std::map<std::string, SymbolTable *> set; // 所有的符号表
public:
    SymbolTable();

    SymbolTable(std::string name);

    std::string getName();

    // 向符号表中插入一个符号（符号的名字直接由 t->name 取得）。如果表中原本没有这个符号，则插入成功，返回 true；否则返回 false并且不插入。
    bool insert(symAttribute *t);

    // 查表。依据给定的 name 从表中取得对应的属性。没查到的话返回 NULL
    symAttribute *lookUp(std::string name);

    // 打印表，用来看的。
    void print();

    // 根据表名取得符号表。
    static SymbolTable *getSymbolTableByName(std::string symbolTableName);

    // 查看所有出现过的符号表。
    static void viewAllSymbolTable();
};

// 符号表栈。用于维护变量生命周期。
class SymbolTableStack {
private:
    std::vector<SymbolTable *> stack; // 栈本体，因为要查表，所以只能做成容器的形式。
public:
    SymbolTableStack(SymbolTable *globalSymbolTable);

    // 压栈
    void push(SymbolTable *t);

    // 出栈
    void pop();

    // 访问栈顶
    SymbolTable *top();

    // 查表，从栈顶开始查，查不到就一层层往下查。全都查不到的话返回 NULL
    symAttribute *lookUp(std::string name);

    // 将符号插入栈顶的符号表。
    bool insert(symAttribute *t);
};

extern int csLineCnt;
extern int csColumnCnt;
extern SymbolTableStack *symbolTableStack;

bool checkType(Node *p, Node::Type type);

bool checkKind(Node *p, Node::Kind kind);

bool typeMatch(Node *a, Node *b);

bool typeMatch(std::vector<Node::Type> a, std::vector<Node::Type> b);

bool typeMatch(std::vector<Node::Type> a, Node *c, std::vector<std::string> s);

bool typeMatch(symAttribute *a, Node *b);

std::string type_to_string(symAttribute *t);



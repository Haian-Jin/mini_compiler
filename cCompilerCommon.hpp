#pragma once
#include <assert.h>
#include <cstdarg>
#include <cstring>
#include <iostream>
#include <json/json.h>
//#include "/usr/local/llvm/include/llvm/IR/Value.h"
#include <llvm/IR/Value.h>
#include <map>
#include <math.h>
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

using namespace llvm;
using std::make_shared;
using std::shared_ptr;

static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> Builder(TheContext);
static std::unique_ptr<Module> TheModule;
static std::unordered_map<std::string, Value *> variableTable;
static std::unordered_map<std::string,
                          std::unordered_map<std::string, Value *> *>
    variableTables;
static std::stack<std::unordered_map<std::string, Value *> *> tableStack;

struct symAttribute;
// Value *LogErrorVV(const char *Str);

Value *LogErrorVV(std::string str);
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
static Value *CastBool(Value *cond) {
    if (cond->getType()->getTypeID() == Type::IntegerTyID) {
        cond = Builder.CreateIntCast(cond, Type::getInt1Ty(TheContext), true);
        return Builder.CreateICmpNE(
            cond, ConstantInt::get(Type::getInt1Ty(TheContext), 0, true));
    } else if (cond->getType()->getTypeID() == Type::DoubleTyID) {
        return Builder.CreateFCmpONE(cond,
                                     ConstantFP::get(TheContext, APFloat(0.0)));
    } else {
        return cond;
    }
}

//获取block内临时变量表
static std::unordered_map<std::string, Value *> *inheritTable() {
    std::unordered_map<std::string, Value *> *codeTable;
    if (tableStack.empty()) {
        codeTable = new std::unordered_map<std::string, Value *>(variableTable);
    } else {
        codeTable =
            new std::unordered_map<std::string, Value *>(*(tableStack.top()));
    }
    return codeTable;
}
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
    std::string
        mSymbolName; // 非终结符的名字，实际使用时会使用 NameCounter
                     // 编号，比如“expressionStatement[0]”、“functionDeclaration[3]”等等。
    std::string
        mTokenValue; // 终结符对应的字符串。这个是不编号的，输入什么就是什么。
    bool mIsTerminal; // 是否是终结符
    bool
        mIsNegligible; // 是否可以删掉。比如在规则 expressions : expression ','
                       // expression
                       // （举个例子）中，中间的逗号对语义分析是无效的，可以直接把他删了，不影响语法分析树的关键结构。
    std::vector<Node *> mChildren; // 树结点的孩子。只有非终结符才有孩子。
    Node::Type NodeType; // 节点的数据类型
    Node::Kind NodeKind; // 节点的类别

    /* 暂时保存 begin */

    std::vector<Node::Type> mTokenArgList; // 参数列表的类型，只有函数能用到
    std::vector<std::string>
        mTokenArgListStructTypeName; // 和参数列表配合使用，提供参数的结构体名字（如果是结构体的话）
    std::vector<int>
        mArraySizes; // 数组的各个维度的大小，只有数组能用到。如果不是数组，则这个容器的维度是
                     // 0。
    std::string
        mStructTypeName; // 结构体名字，只有当类型是结构体的时候能用到。注：若类别是
                         // symAttribute
                         // 但数据类型是结构体，则说明这个节点正在定义一个结构体，此时这个变量就是定义的结构体的名字。
    std::string mVariableName; // 变量的名字。
    int mLineNumber;           // 位置（行）
    int mColumnNumber;         // 位置（列）
                               /* 暂时保存 end */

public:
    Node(){};
    // 建立一个非终结符节点，挂接 childrenNumber 个孩子，分别是 ...
    Node(std::string _symbolName, int childrenNumber, ...);

    // 建立一个终结符结点，用在 scanner 里面。
    Node(std::string _tokenValue, bool negligible = false)
        : mIsNegligible(negligible),
          mSymbolName("I am a terminal, valued " + _tokenValue),
          mIsTerminal(true), mTokenValue(_tokenValue) {}

    virtual void print(std::string prefix) const {}

    // 添加一个孩子
    void addChild(Node *newChild);

    // 取得第 i 个孩子
    Node *getChildrenById(int i);

    // 取得孩子的个数
    int getChildrenNumber();

    // 是否是终结符，是 true 否 false
    bool isTerminal() const;

    // 返回名字，终结符就返回终结符对应的字符串，非终结符就返回非终结符的名字。
    std::string getName() const;

    // 打印出以这个节点为根节点的语法分析树。
    void printTree(int depth = 0);

    // 设定节点的数据类型，不能自适应地一同取得结构体名。
    // virtual void setType(Node::Type _type){}
    virtual void setType(Node::Type _type);

    // 将节点的数据类型设定成和 c 一样。而且如果 c
    // 是结构体，也能一同设定结构体名。 virtual void setType(Node * c){}
    virtual void setType(Node *c);

    // 取得节点的数据类型
    // virtual Node::Type getType(){}
    virtual Node::Type getType();

    // 取得节点的数据类型的字符串版本，用于输出的时候好看。
    // virtual std::string getTypeString(){}
    virtual std::string getTypeString();

    // 设定节点的类别。
    // virtual void setKind(Node::Kind _kind){}
    virtual void setKind(Node::Kind _kind);

    // 取得节点的类别。
    // virtual Node::Kind getKind(){}
    virtual Node::Kind getKind();

    // 设定节点的参数列表。只有函数类型的节点才有可能用到。如果某个参数是结构体的话，需要和
    // setArgListStructName/getArgListStructName 配合使用，以取得结构体名。
    // virtual void setArgList(std::vector<Node::Type> _argList){}
    virtual void setArgList(std::vector<Node::Type> _argList);

    // 取得节点的参数列表。只有函数类型的节点才有可能用到。如果某个参数是结构体的话，需要和
    // setArgListStructName/getArgListStructName 配合使用，以取得结构体名。
    // virtual std::vector<Node::Type> getArgList(){}
    virtual std::vector<Node::Type> getArgList();

    // 设定节点的参数列表的结构体名。只有函数类型的节点才有可能用到。和
    // setArgList/getArgList 配合使用，以确定结构体的名字。 virtual void
    // setArgListStructName(std::vector<std::string> _structName){}
    virtual void setArgListStructName(std::vector<std::string> _structName);

    // 取得节点的参数列表的结构体名。只有函数类型的节点才有可能用到。和
    // setArgList/getArgList 配合使用，以确定结构体的名字。 virtual
    // std::vector<std::string> getArgListStructName(){}
    virtual std::vector<std::string> getArgListStructName();

    // 设定数组的维度和各个维度的大小。只有数组类型的节点才可能用到。
    // virtual void setArraySizes(std::vector<int> _sizes){}
    virtual void setArraySizes(std::vector<int> _sizes);

    // 取得数组的维度和各个维度的大小。
    // virtual std::vector<int> getArraySizes(){} // jha
    virtual std::vector<int> getArraySizes(); // jha

    // 判定该节点是不是数组，是 true 否 false
    // virtual bool isArray(){} //jha
    virtual bool isArray() const; // jha

    // 判断改节点是不是double, float等type
    virtual bool isType() const {
        return Node::NodeKind == Node::KIND_ATTRIBUTE;
    }

    // 获得数组的维数（几维数组）。
    // virtual int getArrayDimension(){}
    virtual int getArrayDimension();

    // 设定结构体的名字。只有当数据类型为结构体时才会用到这个。
    // virtual void setStructTypeName(std::string _name){}
    virtual void setStructTypeName(std::string _name);

    // 获得结构体的名字。只有当数据类型为结构体时才会用到这个。
    // virtual std::string getStructTypeName(){}
    virtual std::string getStructTypeName();

    // 取得变量的名字，只有变量和函数这样的节点才会用到这个。
    // virtual void setVariableName(std::string _name){}
    virtual void setVariableName(std::string _name);

    // 设定变量的名字，只有变量和函数这样的节点才会用到这个。
    // virtual std::string getVariableName(){}
    virtual std::string getVariableName() const;

    // 设定位置，是这个词语/变量/定义/声明出现在文件中的为止。
    // virtual void setPosition(int l,int c){}
    virtual void setPosition(int l, int c);

    // 把位置设定成和给定节点 c 一样。
    // virtual void setPosition(Node *){}
    virtual void setPosition(Node *);

    // 取得行位置
    // virtual int getLineNumber(){}
    virtual int getLineNumber();

    // 取得列位置
    // virtual int getColumnNumber(){}
    virtual int getColumnNumber();

    // 将给定的属性复制给这个节点。（包括位置）
    virtual void setAttribute(void *p);

    // 从第一个孩子那里复制来所有的属性。（位置除外）
    virtual void copyFromChild();

    // 从给定的结点那里复制来所有的属性。（位置除外）
    virtual void copyFrom(Node *c);

    // 将给定的属性复制给这个节点。（包括位置）我承认这个是我写代码写到一半忘记了，又把
    // setAttribute 拿来重写了一遍...
    virtual void copyFrom(symAttribute *c);

    // 返回非终结符的名字。已弃置不用。
    std::string getSymbolName() const;

    // 返回终结符的名字。已弃置不用。
    std::string getTokenValue() const;

    /* defined by jha begins */
    virtual std::string getNodeTypeName() const { return "!!!"; };

    virtual llvm::Value *codeGen() { return (llvm::Value *)0; }

    virtual Json::Value jsonGen() const { return Json::Value(); }

    /* defined by jha ends */
};

class ExpressionNode : public Node {
public:
    ExpressionNode(){};
    ExpressionNode(std::string _symbolName, int childrenNumber, ...)
        : Node(_symbolName, 0) {
        va_list vl;
        va_start(vl, childrenNumber);
        for (int i = 0; i < childrenNumber; i++) {
            mChildren.push_back(va_arg(vl, Node *));
        }
        mIsNegligible = (false), mSymbolName = (_symbolName),
        mIsTerminal = (false), mTokenValue = ("I am not a terminal.");
    }
    ExpressionNode(std::string _tokenValue, bool negligible = false){};
    virtual std::string getNodeTypeName() const { return "ExpressionNode"; }
    virtual Json::Value jsonGen() const {
        Json::Value r;
        r["name"] = getNodeTypeName();
        return r;
    }
};

class StatementNode : public Node {

public:
    StatementNode() : Node() {}

    virtual std::string getNodeTypeName() const { return "StatementNode"; }

    virtual Json::Value jsonGen() const {
        Json::Value r;
        r["name"] = getNodeTypeName();
        return r;
    }
};

class IdentifierNode : public ExpressionNode {
public:
    IdentifierNode(std::string name, bool isType = false)
        : ExpressionNode(name) {
        assert(name.length() > 0);

        this->mSymbolName = name;
        if (isType) {
            this->setKind(Node::KIND_ATTRIBUTE);
            if (name == "int") {
                this->setType(Node::TYPE_INT);
            } else if (name == "float") {
                this->setType(Node::TYPE_FLOAT);
            } else if (name == "double") {
                this->setType(Node::TYPE_DOUBLE);
            } else if (name == "char") {
                this->setType(Node::TYPE_CHAR);
            } else if (name == "void") {
                this->setType(Node::TYPE_VOID);
            }
        }
    };

    bool isType() const { return Node::NodeKind == Node::KIND_ATTRIBUTE; }
    bool isArray() const { return Node::isArray(); }

    virtual std::string getNodeTypeName() const {

        if (isType()) {
            return std::string("TypeNode: ") + getTokenValue();
        } else {
            return std::string("IdentifierNode: ") + getTokenValue();
        }
    }

    // std::string getName(){
    //     return mSymbolName;
    // }
    // 用getVariableName

    // virtual llvm::Value* codeGen(CodeGenContext& context){return (llvm::Value
    // *)0;}
    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        return root;
    }

    virtual llvm::Value *codeGen() {
        if (!isType()) {
            Value *value = nullptr;
            if (tableStack.empty())
                value = variableTable[this->getVariableName()];
            else {
                value = (tableStack.top()->find(this->getVariableName()) ==
                         tableStack.top()->end())
                            ? ((*(tableStack.top()))[this->getVariableName()])
                            : (variableTable[this->getVariableName()]);
                ;
            }

            if (!value) {
                return LogErrorVV(this->getVariableName() + " is not defined\n");
            }
            if (value->getType()->isPointerTy()) {
                auto arrayPtr = Builder.CreateLoad(value, "arrayPtr");
                if (arrayPtr->getType()->isArrayTy()) {
                    std::vector<Value *> indices;
                    indices.push_back(ConstantInt::get(
                        llvm::Type::getInt32Ty(TheContext), 0, false));
                    auto ptr =
                        Builder.CreateInBoundsGEP(value, indices, "arrayPtr");
                    return ptr;
                }
            }
            return Builder.CreateLoad(value, false, "");
        } else {
            return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " +
                             "Keywords can\'t be used as identifier's name");
        }
    }
};

class IdentifierNodeList : public ExpressionNode {
public:
    std::vector<IdentifierNode *> mIdentifierNodeList;

    IdentifierNodeList() : ExpressionNode("IdentifierNodeList", 0) {}
    void addIdentifierNode(IdentifierNode *identifierNode) {
        assert(identifierNode != nullptr);
        mIdentifierNodeList.push_back(identifierNode);
    }

    virtual std::string getNodeTypeName() const { return "IdentifierNodeList"; }
    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        return root;
    }

    virtual llvm::Value *codeGen() {
        return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "I'm not sure this should be made a codeGen");
    }
};

class AssignmentNode : public ExpressionNode {
public:
    virtual std::string getNodeTypeName() const {
        return std::string("AssignmentNode ") + ("=");
    }

    AssignmentNode(IdentifierNode *lhs, ExpressionNode *rhs)
        : ExpressionNode("=", 0) {
        assert(lhs != nullptr);
        assert(rhs != nullptr);
        mLeftHandSide = lhs;
        mRightHandSide = rhs;
    }
    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        root["children"].append(mLeftHandSide->jsonGen());
        root["children"].append(mRightHandSide->jsonGen());
        return root;
    }

    virtual llvm::Value *codeGen() {
        Value *dst = nullptr;
        if (tableStack.empty())
            dst = variableTable[mLeftHandSide->getVariableName()];
        else
            dst = (tableStack.top()->find(this->getVariableName()) ==
                   tableStack.top()->end())
                      ? ((*(tableStack.top()))[this->getVariableName()])
                      : (variableTable[this->getVariableName()]);

        if (!dst)
            return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " +
                             "undeclared variable");
        auto type_l = dst->getType()->getTypeID();
        Value *R = mRightHandSide->codeGen();
        auto type_r = R->getType()->getTypeID();
        if (type_r == type_l) {
            Builder.CreateStore(R, dst);
            return R;
        } else if (type_r == llvm::Type::DoubleTyID) {
            return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " +
                             "Can't assign double to int");
        } else {
            R = Builder.CreateSIToFP(R, llvm::Type::getDoubleTy(TheContext));
            Builder.CreateStore(R, dst);
            return R;
        }
    }

private:
    std::string op;
    IdentifierNode *mLeftHandSide;
    ExpressionNode *mRightHandSide;
};

class VariableDeclarationNode : public StatementNode {
public:
    const IdentifierNode *type;
    IdentifierNode *id;
    AssignmentNode *assignmentExpr = nullptr;

    VariableDeclarationNode(IdentifierNode *inType, IdentifierNode *id,
                            AssignmentNode *assignmentExpr = nullptr)
        : StatementNode() {
        assert(inType != nullptr);
        assert(id != nullptr);
        this->type = inType;
        this->id = id;
        this->assignmentExpr = assignmentExpr;
        this->setKind(Node::KIND_VARIABLE);
        this->setType(inType->getType());
    }

    virtual std::string getNodeTypeName() const {
        return "VariableDeclarationNode";
    }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        root["children"].append(type->jsonGen());
        root["children"].append(id->jsonGen());

        if (assignmentExpr != nullptr) {
            root["children"].append(assignmentExpr->jsonGen());
        }
        return root;
    }

    virtual llvm::Value *codeGen() {
        if (!type->isType()) {
            return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " +
                             "This type is not supported");
        }
        std::string ty = type->getSymbolName();
        Value *res;
        if (!this->id->isArray()) {
            if (ty == "int" || ty == "char") {
                res = Builder.CreateAlloca(llvm::Type::getInt32Ty(TheContext));
            } else if (ty == "float" || ty == "double") {
                res = Builder.CreateAlloca(llvm::Type::getDoubleTy(TheContext));
            } else {
                return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                                 std::to_string(this->getColumnNumber()) + " " +
                                 "This type is not supported");
            }
            if (tableStack.empty())
                variableTable[this->id->getVariableName()] = res;
            else
                (*(tableStack.top()))[this->id->getVariableName()] = res;
            if (this->assignmentExpr != nullptr) {
                this->assignmentExpr->codeGen();
            }
            return res;
        } else {
            auto dimsize = this->getArraySizes();
            uint64_t array_size = 1;
            for (int a : dimsize) {
                array_size *= a;
            }
            Value *ArraySize = ConstantInt::get(
                llvm::Type::getInt32Ty(TheContext), array_size, false);
            if (ty == "int" || ty == "char") {
                res = Builder.CreateAlloca(llvm::Type::getInt32Ty(TheContext),
                                           ArraySize, "arrtemp");
            } else if (ty == "float" || ty == "double") {
                res = Builder.CreateAlloca(llvm::Type::getDoubleTy(TheContext),
                                           ArraySize, "arrtemp");
            }
            if (tableStack.empty())
                variableTable[this->id->getVariableName()] = res;
            else
                (*(tableStack.top()))[this->id->getVariableName()] = res;
            return res;
        }
    }
};

// store all the variable declaration, this is used for function declaration and
// struct declaraion
class VarDeclarationList : public StatementNode {
public:
    std::vector<VariableDeclarationNode *> mVarDeclarationList;

    VarDeclarationList() : StatementNode() {}

    virtual std::string getNodeTypeName() const { return "VarDeclarationList"; }
    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        for (auto it = mVarDeclarationList.begin();
             it != mVarDeclarationList.end(); it++) {
            root["children"].append((*it)->jsonGen());
        }
        return root;
    }

    virtual Value *codeGen() {
        return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "No need to codeGen this");
    }
};

// store all statements nodes of the same block
class StatementNodesBlock : public StatementNode {
public:
    std::vector<StatementNode *> mStatementList;

    StatementNodesBlock() : StatementNode() {}

    virtual std::string getNodeTypeName() const { return "StatementsBlock"; }
    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        for (auto it = mStatementList.begin(); it != mStatementList.end();
             it++) {
            root["children"].append((*it)->jsonGen());
        }
        return root;
    }

    void addStatementNode(StatementNode *statementNode) {
        assert(statementNode != nullptr);
        mStatementList.push_back(statementNode);
    }

    // input type expression and multiple name identifiers, create multiple
    // declaration nodes
    void createMultiVarDeclaration(IdentifierNode *type,
                                   IdentifierNodeList *nameList) {
        assert(type != nullptr && nameList != nullptr);
        assert(type->isType());
        std::vector<IdentifierNode *> idenNameList =
            nameList->mIdentifierNodeList; // vector of identifiers, store the
                                           // name of the variables
        for (auto it = idenNameList.begin(); it != idenNameList.end(); it++) {
            // create a variable declaration
            StatementNode *varDecl = new VariableDeclarationNode(type, *it);
            mStatementList.push_back(varDecl);
        }
    }

    // merge two statements block into one same statements block
    void mergeStatements(StatementNodesBlock *to_merge) {
        assert(to_merge != nullptr);
        this->mStatementList.insert(this->mStatementList.end(),
                                    to_merge->mStatementList.begin(),
                                    to_merge->mStatementList.end());
    }

    virtual Value *codeGen() {

        for (auto &iter : mStatementList) {
            iter->codeGen();
        }
        return nullptr;
    }
};

class StructDeclarationNode : public StatementNodesBlock {
protected:
    IdentifierNode *mStructName;
    StatementNodesBlock *mMembers;

public:
    StructDeclarationNode(IdentifierNode *name, StatementNodesBlock *members) {
        mStructName = name;
        mMembers = members;
    }
    void createStructDeclaration(IdentifierNode *structName,
                                 StatementNodesBlock *structMembers) {}
    virtual std::string getNodeTypeName() const {
        return std::string("StructDeclarationBlock") +
               mStructName->getTokenValue();
    }
    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        root["children"].append(mStructName->jsonGen());
        // for(auto it = mStatementList.begin(); it != mStatementList.end();
        // it++){
        root["children"].append(mMembers->jsonGen() /*(*it)->jsonGen()*/);
        //}
        return root;
    }

    virtual Value *codeGen() {
        /*
        TODO:
        */
        return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "Not supported yet");
    }
};

// handle the statement that has only one semicollon
class NullStatementNode : public StatementNode {
public:
    NullStatementNode() : StatementNode() {}
    virtual std::string getNodeTypeName() const { return "NullStatementNode"; }
    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        return root;
    }

    virtual llvm::Value *codeGen() {
        return Builder.CreateAdd(
            ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0, true),
            ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0, true));
    }
};

class DoubleNode : public ExpressionNode {
public:
    double value;
    DoubleNode(std::string _tokenValue) : ExpressionNode(_tokenValue) {
        sscanf(_tokenValue.c_str(), "%lf", &this->value);
    }

    virtual std::string getNodeTypeName() const { return "DoubleNode"; }

    int getValue() { return this->value; }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName() + ":" + std::to_string(value);
        return root;
    };

    virtual llvm::Value *codeGen() {
        return llvm::ConstantFP::get(TheContext, llvm::APFloat(value));
    };
};

class IntNode : public ExpressionNode {
public:
    int value;

    IntNode(std::string _tokenValue) : ExpressionNode(_tokenValue) {
        sscanf(_tokenValue.c_str(), "%d", &this->value);
    }

    double getValue() { return this->value; }

    virtual std::string getNodeTypeName() const { return "IntNode"; }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName() + ":" + std::to_string(value);
        return root;
    };

    virtual llvm::Value *codeGen() {
        return ConstantInt::get(llvm::Type::getInt32Ty(TheContext), this->value,
                                true);
    }
};

class ExpressionStatementNode : public StatementNode {
public:
    ExpressionNode *mExpression;

    ExpressionStatementNode(ExpressionNode *expression) : StatementNode() {
        assert(expression != nullptr);
        this->mExpression = expression;
    }

    virtual std::string getNodeTypeName() const {
        return "ExpressionStatementNode";
    }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        root["children"].append(mExpression->jsonGen());
        return root;
    }

    virtual Value *codeGen() {
        this->mExpression->codeGen();
        return nullptr;
    }
};

// 为了不改变文法.l文件，做的妥协，这个中间文件，只用在函数定义中，
class FuncNameAndArgsNode : public ExpressionNode {
public:
    IdentifierNode *mFuncName;
    VarDeclarationList *parasList; // used for function agrs
                                   // used for function declararion
    FuncNameAndArgsNode(IdentifierNode *nameIdentifier,
                        VarDeclarationList *args)
        : ExpressionNode() {
        assert(nameIdentifier != nullptr);
        this->mFuncName = nameIdentifier;
        this->parasList = args;
    };
};

class FunctionDeclarationNode : public StatementNode {
public:
    IdentifierNode *type;          // return type
    IdentifierNode *id;            // function name
    VarDeclarationList *parasList; // function args, be nullptr if no args
    StatementNodesBlock *body;     // function body

    FunctionDeclarationNode(IdentifierNode *type,
                            FuncNameAndArgsNode *name_and_args,
                            StatementNodesBlock *body)
        : StatementNode() {
        assert(type != nullptr);
        assert(name_and_args != nullptr);
        assert(body != nullptr);
        assert(type->isType());
        this->type = type;
        this->id = name_and_args->mFuncName;
        this->parasList = name_and_args->parasList;
        this->body = body;
    }
    virtual std::string getNodeTypeName() const {
        return "FunctionDeclarationNode";
    }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();

        Json::Value returnType;
        returnType["name"] = std::string("ReturnType");
        returnType["children"].append(type->jsonGen());

        Json::Value funcName;
        funcName["name"] = std::string("FuncName");
        funcName["children"].append(id->jsonGen());

        Json::Value paras;
        paras["name"] = std::string("Paras");
        if (this->parasList != nullptr) {
            for (auto it = parasList->mVarDeclarationList.begin();
                 it != parasList->mVarDeclarationList.end(); it++) {
                paras["children"].append((*it)->jsonGen());
            }
        }

        Json::Value funcBody;
        funcBody["name"] = std::string("Body");
        funcBody["children"].append(body->jsonGen());

        root["children"].append(returnType);
        root["children"].append(funcName);
        root["children"].append(paras);
        root["children"].append(funcBody);

        return root;
    }

    virtual llvm::Value *codeGen() {
        std::vector<llvm::Type *> argTypes;
        if(parasList) {
            auto temp = parasList->mVarDeclarationList;

            for (auto &i: temp) {
                std::string ty = i->id->getSymbolName();
                if (ty == "int" || ty == "char") {
                    argTypes.push_back(llvm::Type::getInt32Ty(TheContext));
                } else if (ty == "float" || ty == "double") {
                    argTypes.push_back(llvm::Type::getDoubleTy(TheContext));
                } else {
                    return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                                      std::to_string(this->getColumnNumber()) + " " +
                                      "A type is not supported in the parameters");
                }
            }
        }
        llvm::Type *ret;

        std::string ty = this->type->getSymbolName();
        if (ty == "int" || ty == "char") {
            ret = (llvm::Type::getInt32Ty(TheContext));
        } else if (ty == "float" || ty == "double") {
            ret = (llvm::Type::getDoubleTy(TheContext));
        } else if (ty == "void") {
            ret = llvm::Type::getVoidTy(TheContext);
        } else {
            return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " + ty +
                             " type is not supported");
        }
        FunctionType *functionType =
            llvm::FunctionType::get(ret, argTypes, false);
        Function *function = llvm::Function::Create(
            functionType, llvm::GlobalValue::ExternalLinkage,
            id->getVariableName(), TheModule.get());
        BasicBlock *basicBlock =
            BasicBlock::Create(TheContext, "func_entry", function, nullptr);
        if(parasList) {
            auto temp = parasList->mVarDeclarationList;
            auto *argTable =
                    new std::unordered_map<std::string, Value *>;
            tableStack.push(argTable);
            variableTables[this->id->getVariableName()] = argTable;
            auto iter_proto = temp.begin();
            for (auto &iter_func: function->args()) {
                iter_func.setName((*iter_proto)->id->getVariableName());
                Value *arg = (*iter_proto)->codeGen();
                Builder.CreateStore(&iter_func, arg, false);
                // (*argTable)[(*iter_proto)->id->getVariableName()] = arg;
                iter_proto++;
            }
        }
        this->body->codeGen();

        tableStack.pop();

        return function;
    }
};

class FunctionCallNode : public ExpressionNode {
public:
    FunctionCallNode(std::string _symbolName, int childrenNumber, ...)
        : ExpressionNode(_symbolName, 0) {
        va_list vl;
        va_start(vl, childrenNumber);
        for (int i = 0; i < childrenNumber; i++) {
            mChildren.push_back(va_arg(vl, Node *));
        }
        mFunctionName = dynamic_cast<IdentifierNode *>(mChildren[0]);
        mArguments = new std::vector<ExpressionNode *>();
        mIsNegligible = (false), mSymbolName = (_symbolName),
        mIsTerminal = (false), mTokenValue = ("I am not a terminal.");
    }
    FunctionCallNode(std::string _tokenValue, bool negligible = false)
        : ExpressionNode(_tokenValue, negligible),
          mArguments(new std::vector<ExpressionNode *>()){};

    std::vector<ExpressionNode *> getArguments() const { return *mArguments; }
    void addArgument(Node *c) {
        assert(dynamic_cast<ExpressionNode *>(c) != NULL);
        mArguments->push_back(dynamic_cast<ExpressionNode *>(c));
    }
    virtual std::string getNodeTypeName() const {
        return std::string("FunctionNode: ") + mFunctionName->getTokenValue();
    }
    virtual Json::Value jsonGen() const {
        Json::Value r;
        r["name"] = getNodeTypeName();
        // r["children"].append(mFunctionName->jsonGen());
        for (auto i : *mArguments) {
            std::cout << "oo\n";
            r["children"].append(i->jsonGen());
        }
        return r;
    }

    virtual llvm::Value *codeGen() {
        Function *CalleeF =
            TheModule->getFunction(mFunctionName->getVariableName());
        if (!CalleeF)
            return LogErrorVV(mFunctionName->getVariableName() + "not declared");
        if (CalleeF->arg_size() != (*mArguments).size()) {
            return LogErrorVV("Incorrect # arguments passed");
        }

        std::vector<Value *> ArgsV;
        for (size_t i = 0; i < mArguments->size(); i++) {
            ArgsV.push_back((*mArguments)[i]->codeGen());
            if (!ArgsV.back())
                return nullptr;
        }

        return Builder.CreateCall(CalleeF, ArgsV, "calltmp");
    }

private:
    IdentifierNode *mFunctionName;
    std::vector<ExpressionNode *> *mArguments;
};

class UnaryOperatorNode : public ExpressionNode {
public:
    UnaryOperatorNode(std::string _symbolName, int childrenNumber, ...)
        : ExpressionNode(_symbolName, 0) {
        va_list vl;
        va_start(vl, childrenNumber);
        for (int i = 0; i < childrenNumber; i++) {
            mChildren.push_back(va_arg(vl, Node *));
        }
        mIsNegligible = (false), mSymbolName = (_symbolName),
        mIsTerminal = (false), mTokenValue = ("I am not a terminal.");
        mHandSide = dynamic_cast<ExpressionNode *>(mChildren[0]);
        op = _symbolName;
        if (mHandSide == NULL)
            throw("castfail");
    }
    UnaryOperatorNode(std::string _tokenValue, bool negligible = false)
        : ExpressionNode(_tokenValue, negligible){};
    virtual std::string getNodeTypeName() const {
        return std::string("UnaryOperatorNode  ") + (getVariableName());
    }

    virtual llvm::Value *codeGen() {
        Value *OperandV = mHandSide->codeGen();
        if (!OperandV)
            return nullptr;
        bool isFloat = false;

        if (OperandV->getType()->getTypeID() == llvm::Type::DoubleTyID) {
            isFloat = true;
        }
        if (op == "pre++" || op == "pre--" || op == "post++" ||
            op == "post--" || op == "~") {
            return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " +
                             "\"" + op + "\" is not supported as an operator");
        } else if (op == "!") {
            if (isFloat) {
                return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                                 std::to_string(this->getColumnNumber()) + " " +
                                 "invalid boolean operation with float number");
            }
            return Builder.CreateNot(OperandV, "notop");
        } else if (op == "-") {
            return isFloat ? Builder.CreateFNeg(OperandV, "fnotop")
                           : Builder.CreateFNeg(OperandV, "notop");
        }
    }

private:
    std::string op;
    ExpressionNode *mHandSide;
};

class ArrayIndexNode : public ExpressionNode {
public:
    ArrayIndexNode(std::string _symbolName, int childrenNumber, ...)
        : ExpressionNode(_symbolName, 0) {
        va_list vl;
        va_start(vl, childrenNumber);
        for (int i = 0; i < childrenNumber; i++) {
            mChildren.push_back(va_arg(vl, Node *));
        }
        mIsNegligible = (false), mSymbolName = (_symbolName),
        mIsTerminal = (false), mTokenValue = ("I am not a terminal.");
        // mLeftHandSide = dynamic_cast<ExpressionNode *>(mChildren[0]);
        // mRightHandSide = dynamic_cast<ExpressionNode *>(mChildren[1]);
        op = _symbolName;
        // if(mLeftHandSide==NULL || mRightHandSide==NULL)throw("castfail");
    }

    ArrayIndexNode(std::string _tokenValue, bool negligible = false)
        : ExpressionNode(_tokenValue, negligible){};

    ArrayIndexNode(std::string opType, ExpressionNode *lhs,
                   std::vector<ExpressionNode *> rhs, bool isArithmetic = false)
        : ExpressionNode() {
        assert(lhs != nullptr);
        // assert(rhs != nullptr);
        assert(opType != "");
        this->setType(Node::TYPE_INT);
        // this->setKind() HERE
        mArrayName = dynamic_cast<IdentifierNode *>(lhs);
        mArrayIndexs = rhs;
        op = opType;
        if (isArithmetic) // + - * / %
        {
            /*if(lhs->getType()==Node::TYPE_DOUBLE ||
            rhs->getType()==Node::TYPE_DOUBLE){
                this->setType(Node::TYPE_DOUBLE);
            }*/
        } else {
            if (lhs->getType() == Node::TYPE_DOUBLE) {
                this->setType(Node::TYPE_DOUBLE);
            } else {
                this->setType(Node::TYPE_INT);
            }
        }
    }

    virtual std::string getNodeTypeName() const { return op; }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        root["children"].append(mArrayName->jsonGen());
        for (auto i : mArrayIndexs) {
            root["children"].append(i->jsonGen());
        }
        return root;
    }
    virtual llvm::Value *codeGen() {
        /*
        TODO:
        */
        return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "Not supported yet");
    }

    // private:
    std::string op;
    // ExpressionNode *mLeftHandSide, *mRightHandSide;
    IdentifierNode *mArrayName;
    std::vector<ExpressionNode *> mArrayIndexs;
};

class ArrayAssignmentNode : public ExpressionNode {
public:
    virtual std::string getNodeTypeName() const {
        return std::string("ArrayAssignmentNode ") + ("=");
    }

    ArrayAssignmentNode(ArrayIndexNode *lhs, ExpressionNode *rhs)
        : ExpressionNode("=", 0) {
        assert(lhs != nullptr);
        assert(rhs != nullptr);
        mLeftHandSide = lhs;
        mRightHandSide = rhs;
    }
    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        root["children"].append(mLeftHandSide->jsonGen());
        root["children"].append(mRightHandSide->jsonGen());
        return root;
    }

    virtual llvm::Value *codeGen() {
        /*
        TODO:
        */
        return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "Not supported yet");
    }

private:
    std::string op;
    ArrayIndexNode *mLeftHandSide;
    ExpressionNode *mRightHandSide;
};

class StructMemberNode : public ExpressionNode {
public:
    StructMemberNode(std::string _tokenValue, bool negligible = false)
        : ExpressionNode(_tokenValue, negligible){};

    StructMemberNode(std::string opType, IdentifierNode *lhs,
                     IdentifierNode *rhs, bool isArithmetic = false)
        : ExpressionNode() {
        assert(lhs != nullptr);
        assert(rhs != nullptr);
        assert(opType != "");
        this->setType(Node::TYPE_INT);
        // this->setKind() HERE
        mVariableName = lhs;
        mMemberName = rhs;
        op = opType;
        if (isArithmetic) // + - * / %
        {
            if (lhs->getType() == Node::TYPE_DOUBLE ||
                rhs->getType() == Node::TYPE_DOUBLE) {
                this->setType(Node::TYPE_DOUBLE);
            }
        } else {
        }
    }

    virtual std::string getNodeTypeName() const { return op; }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        root["children"].append(mVariableName->jsonGen());
        root["children"].append(mMemberName->jsonGen());

        return root;
    }

    virtual llvm::Value *codeGen() {
        /*
        TODO:
        */
        return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "Not supported yet");
    }

    ExpressionNode *getL() { return mVariableName; }
    ExpressionNode *getR() { return mMemberName; }

private:
    std::string op;
    IdentifierNode *mVariableName, *mMemberName;
};

class StructMemberAssignmentNode : public ExpressionNode {
public:
    virtual std::string getNodeTypeName() const {
        return std::string("StructMemberAssignmentNode ") + ("=");
    }

    StructMemberAssignmentNode(StructMemberNode *lhs, ExpressionNode *rhs)
        : ExpressionNode("=", 0) {
        assert(lhs != nullptr);
        assert(rhs != nullptr);
        mLeftHandSide = lhs;
        mRightHandSide = rhs;
    }
    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        root["children"].append(mLeftHandSide->jsonGen());
        root["children"].append(mRightHandSide->jsonGen());
        return root;
    }

    virtual llvm::Value *codeGen() {
        /*
        TODO:
        */
        return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "Not supported yet");
    }

private:
    std::string op;
    StructMemberNode *mLeftHandSide;
    ExpressionNode *mRightHandSide;
};
class BinaryOperatorNode : public ExpressionNode {
public:
    BinaryOperatorNode(std::string _tokenValue, bool negligible = false)
        : ExpressionNode(_tokenValue, negligible){};

    BinaryOperatorNode(std::string opType, ExpressionNode *lhs,
                       ExpressionNode *rhs, bool isArithmetic = true)
        : ExpressionNode() {
        assert(lhs != nullptr);
        assert(rhs != nullptr);
        assert(opType != "");
        this->setType(Node::TYPE_INT);
        // this->setKind() HERE
        mLeftHandSide = lhs;
        mRightHandSide = rhs;
        op = opType;

        if (isArithmetic) // + - * / %
        {
            if (lhs->getType() == Node::TYPE_DOUBLE ||
                rhs->getType() == Node::TYPE_DOUBLE) {
                this->setType(Node::TYPE_DOUBLE);
            }
        }
    }

    

    virtual std::string getNodeTypeName() const { return op; }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        root["children"].append(mLeftHandSide->jsonGen());
        root["children"].append(mRightHandSide->jsonGen());

        return root;
    }

    virtual llvm::Value *codeGen() {
        Value *Left = mLeftHandSide->codeGen();
        Value *Right = mRightHandSide->codeGen();
        if (!Left || !Right)
            return nullptr;
        bool isFloat = false;

        if (Left->getType()->getTypeID() == llvm::Type::DoubleTyID ||
            Right->getType()->getTypeID() == llvm::Type::DoubleTyID) {
            isFloat = true;
            if (!(Left->getType()->getTypeID() == llvm::Type::DoubleTyID)) {
                Left = Builder.CreateSIToFP(
                    Left, llvm::Type::getDoubleTy(TheContext), "ftmp");
            } else if (!(Right->getType()->getTypeID() ==
                         llvm::Type::DoubleTyID)) {
                Right = Builder.CreateSIToFP(
                    Left, llvm::Type::getDoubleTy(TheContext), "ftmp");
            }
        }

        if (op == "&&") { // and operation
            if (isFloat) {
                return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                                 std::to_string(this->getColumnNumber()) + " " +
                                 "invalid boolean operation with float number");
            }
            return Builder.CreateAnd(Left, Right, "andop");
        } else if (op == "||") { // or operation
            if (isFloat) {
                return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                                 std::to_string(this->getColumnNumber()) + " " +
                                 "invalid boolean operation with float number");
            }
            return Builder.CreateOr(Left, Right, "orop");
        } else if (op == "^" || op == "|" ||
                   op == "&") { // bitwise operation, but not supported
            return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " +
                             "bit operation is not supported");
        } else if (op == "==") {
            return isFloat ? Builder.CreateFCmpOEQ(Left, Right, "feqop")
                           : Builder.CreateICmpEQ(Left, Right, "ieqop");
        } else if (op == "!=") {
            return isFloat ? Builder.CreateFCmpONE(Left, Right, "fneop")
                           : Builder.CreateICmpNE(Left, Right, "ineop");
        } else if (op == "<") {
            return isFloat ? Builder.CreateFCmpOLT(Left, Right, "fltop")
                           : Builder.CreateICmpSLT(Left, Right, "iltop");
        } else if (op == ">") {
            return isFloat ? Builder.CreateFCmpOGT(Left, Right, "fgtop")
                           : Builder.CreateICmpSGT(Left, Right, "igtop");
        } else if (op == ">=") {
            return isFloat ? Builder.CreateFCmpOGE(Left, Right, "fgeop")
                           : Builder.CreateICmpSGE(Left, Right, "igeop");
        } else if (op == "<=") {
            return isFloat ? Builder.CreateFCmpOLE(Left, Right, "fleop")
                           : Builder.CreateICmpSLE(Left, Right, "ileop");
        } else if (op == ">>") {
            if (isFloat) {
                return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                                 std::to_string(this->getColumnNumber()) + " " +
                                 "invalid boolean operation with float number");
            }
            return Builder.CreateAShr(Left, Right, "shrop");
        } else if (op == "<<") {
            if (isFloat) {
                return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                                 std::to_string(this->getColumnNumber()) + " " +
                                 "invalid boolean operation with float number");
            }
            return Builder.CreateShl(Left, Right, "shlop");
        } else if (op == "+") {
            return isFloat ? Builder.CreateFAdd(Left, Right, "faddop")
                           : Builder.CreateAdd(Left, Right, "addop");
        } else if (op == "-") {
            return isFloat ? Builder.CreateFSub(Left, Right, "fsubop")
                           : Builder.CreateSub(Left, Right, "subop");
        } else if (op == "*") {
            return isFloat ? Builder.CreateFMul(Left, Right, "fmulop")
                           : Builder.CreateMul(Left, Right, "mulop");
        } else if (op == "/") {
            return isFloat ? Builder.CreateFDiv(Left, Right, "fdivop")
                           : Builder.CreateSDiv(Left, Right, "divop");
        } else if (op == "%") {
            if (isFloat) {
                return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                                 std::to_string(this->getColumnNumber()) + " " +
                                 "invalid \"%\" operation with float number");
            }
            return Builder.CreateSRem(Left, Right, "smodop");
        } else {
            return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " +
                             "\"" + op + "\" is not supported as an operator");
        }
    }

    ExpressionNode *getL() { return mLeftHandSide; }
    ExpressionNode *getR() { return mRightHandSide; }

private:
    std::string op;
    ExpressionNode *mLeftHandSide, *mRightHandSide;
};

class TenaryOperatorNode : public ExpressionNode {
public:
    TenaryOperatorNode(std::string _symbolName, int childrenNumber, ...)
        : ExpressionNode(_symbolName, 0) {
        va_list vl;
        va_start(vl, childrenNumber);
        for (int i = 0; i < childrenNumber; i++) {
            mChildren.push_back(va_arg(vl, Node *));
        }
        mIsNegligible = (false), mSymbolName = (_symbolName),
        mIsTerminal = (false), mTokenValue = ("I am not a terminal.");
        mLeftHandSide = dynamic_cast<ExpressionNode *>(mChildren[0]);
        mMidHandSide = dynamic_cast<ExpressionNode *>(mChildren[1]);
        mRightHandSide = dynamic_cast<ExpressionNode *>(mChildren[2]);
        op = _symbolName;
        if (mLeftHandSide == NULL || mRightHandSide == NULL ||
            mMidHandSide == NULL)
            throw("castfail");
    }
    TenaryOperatorNode(std::string _tokenValue, bool negligible = false)
        : ExpressionNode(_tokenValue, negligible){};
    std::string getNodeTypeName() {
        return std::string("TenaryOperatorNode  ") + (getVariableName());
    }

    virtual llvm::Value *codeGen() {
        return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "? ... : is not supported");
    }

private:
    std::string op;
    ExpressionNode *mLeftHandSide, *mRightHandSide, *mMidHandSide;
};

// central global Node
class GlobalDeclaraionNode : public StatementNode {
public:
    std::vector<StatementNode *> mGlobalStatementList;

    GlobalDeclaraionNode() : StatementNode() {}

    // copy from statements block
    GlobalDeclaraionNode(StatementNodesBlock *toCopy) : StatementNode() {
        for (auto it = toCopy->mStatementList.begin();
             it != toCopy->mStatementList.end(); ++it) {
            mGlobalStatementList.push_back(*it);
        }
    }

    virtual std::string getNodeTypeName() const { return "CentralBlock"; }
    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        for (auto it = mGlobalStatementList.begin();
             it != mGlobalStatementList.end(); it++) {
            root["children"].append((*it)->jsonGen());
        }
        return root;
    }

    virtual llvm::Value *codeGen() {
        Value *ret = nullptr;
        FunctionType* mainFuncType = FunctionType::get(llvm::Type::getVoidTy(TheContext),  false);
        Function* mainFunc = Function::Create(mainFuncType, GlobalValue::ExternalLinkage, "main");
        BasicBlock* block = BasicBlock::Create(TheContext, "entry");
        Builder.SetInsertPoint(block);
        for (auto &iter : mGlobalStatementList) {
            ret = iter->codeGen();
        }
        return ret;
    }

    // merge another global declaration statements block
    void mergeGlobalStatements(StatementNodesBlock *to_merge) {

        assert(to_merge != nullptr);
        if (dynamic_cast<StructDeclarationNode *>(to_merge) == NULL)
            this->mGlobalStatementList.insert(mGlobalStatementList.end(),
                                              to_merge->mStatementList.begin(),
                                              to_merge->mStatementList.end());
        else {
            this->mGlobalStatementList.push_back(to_merge);
        }
    }
};

class ForStatementNode : public StatementNode {
public:
    // for (initialStatement; conditionStatement; progressStatement)
    ExpressionStatementNode *initialStatement;
    ExpressionStatementNode *conditionStatement;
    ExpressionStatementNode *progressStatement;
    StatementNodesBlock *forBody;

    ForStatementNode(ExpressionStatementNode *initial,
                     ExpressionStatementNode *condition,
                     ExpressionStatementNode *progress,
                     StatementNodesBlock *body)
        : StatementNode(), initialStatement(initial),
          conditionStatement(condition), progressStatement(progress),
          forBody(body) {
        assert(initialStatement != nullptr);
        assert(conditionStatement != nullptr);
        assert(progressStatement != nullptr);
        assert(forBody != nullptr);
    }

    virtual std::string getTypeName() const {
        return std::string("ForStatementNode");
    }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getTypeName();

        root["children"].append(initialStatement->jsonGen());
        root["children"].append(conditionStatement->jsonGen());
        root["children"].append(progressStatement->jsonGen());
        root["children"].append(forBody->jsonGen());

        return root;
    }

    virtual llvm::Value *codeGen() {
        Function* theFunction = Builder.GetInsertBlock()->getParent();

        BasicBlock* loopBody = BasicBlock::Create(TheContext, "forbody", theFunction);
        BasicBlock* after = BasicBlock::Create(TheContext, "forcont");

        if(this->initialStatement) {
            this->initialStatement->codeGen();
        }

        Value* cond = this->conditionStatement->codeGen();
        if(!cond) {
            return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " +
                             "lack of condition");
        }

        Builder.CreateCondBr(CastBool(cond), loopBody, after);

        Builder.SetInsertPoint(loopBody);

        auto tempTable = inheritTable();
        tableStack.push(tempTable);

        this->forBody->codeGen();

        tableStack.pop();

        if (this->progressStatement) {
            this->progressStatement->codeGen();
        }

        cond = this->conditionStatement->codeGen();
        Builder.CreateCondBr(CastBool(cond), loopBody, after);

        theFunction->getBasicBlockList().push_back(after);
        Builder.SetInsertPoint(after);

        return nullptr;
    }
};

class WhileStatementNode : public StatementNode {
public:
    // for (initialStatement; conditionStatement; progressStatement)
    ExpressionStatementNode *conditionStatement;
    StatementNodesBlock *whileBody;

    WhileStatementNode(ExpressionStatementNode *condition,
                       StatementNodesBlock *body)
        : StatementNode(), conditionStatement(condition), whileBody(body) {
        assert(conditionStatement != nullptr);
        assert(whileBody != nullptr);
    }

    virtual std::string getTypeName() const {
        return std::string("WhileStatementNode");
    }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getTypeName();

        root["children"].append(conditionStatement->jsonGen());
        root["children"].append(whileBody->jsonGen());

        return root;
    }

    // virtual llvm::Value* codeGen(CodeGenContext& context){return (llvm::Value
    // *)0;}
    virtual llvm::Value *codeGen() {
        Function* theFunction = Builder.GetInsertBlock()->getParent();

        BasicBlock* loopBody = BasicBlock::Create(TheContext, "whilebody", theFunction);
        BasicBlock* after = BasicBlock::Create(TheContext, "whilecont");

        Value* cond = this->conditionStatement->codeGen();
        if(!cond) {
            return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " +
                             "lack of condition");
        }

        Builder.CreateCondBr(CastBool(cond), loopBody, after);

        Builder.SetInsertPoint(loopBody);

        auto tempTable = inheritTable();
        tableStack.push(tempTable);

        this->whileBody->codeGen();

        tableStack.pop();

        cond = this->conditionStatement->codeGen();
        Builder.CreateCondBr(CastBool(cond), loopBody, after);

        theFunction->getBasicBlockList().push_back(after);
        Builder.SetInsertPoint(after);

        return nullptr;
    }
};

class IfStatementNode : public StatementNode {
public:
    ExpressionStatementNode *conditionStatement;
    StatementNodesBlock *trueBody;  // if (True), do this, cannot be null
    StatementNodesBlock *falseBody; // else, do this, can be null

    IfStatementNode(ExpressionStatementNode *condition,
                    StatementNodesBlock *trueStatements,
                    StatementNodesBlock *falseStatements = nullptr)
        : StatementNode(), conditionStatement(condition),
          trueBody(trueStatements), falseBody(falseStatements) {
        assert(conditionStatement != nullptr);
        assert(trueBody != nullptr);
    }
    virtual std::string getTypeName() const { return "NIfStatement"; }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getTypeName();
        root["children"].append(conditionStatement->jsonGen());
        root["children"].append(trueBody->jsonGen());
        if (falseBody != nullptr)
            root["children"].append(falseBody->jsonGen());
        return root;
    }

    virtual llvm::Value *codeGen() {
        auto conditionExpressionValue = conditionStatement->codeGen();
        if (!conditionExpressionValue)
            return LogErrorVV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " +
                             "lack of condition");

        auto theFunction = Builder.GetInsertBlock()->getParent();

        auto trueBlock = llvm::BasicBlock::Create(
            TheContext, "then", Builder.GetInsertBlock()->getParent());
        auto falseBlock = llvm::BasicBlock::Create(TheContext, "else");
        auto mergeBlock = llvm::BasicBlock::Create(TheContext, "ifcont");
        if (this->falseBody) {
            Builder.CreateCondBr(CastBool(conditionExpressionValue), trueBlock,
                                 falseBlock);
        } else {
            Builder.CreateCondBr(CastBool(conditionExpressionValue), trueBlock,
                                 mergeBlock);
        }

        Builder.SetInsertPoint(trueBlock);

        auto tempTable = inheritTable();
        tableStack.push(tempTable);

        this->trueBody->codeGen();

        tableStack.pop();

        trueBlock = Builder.GetInsertBlock();
        if (trueBlock->getTerminator() == nullptr) {
            Builder.CreateBr(mergeBlock);
        }

        if (this->falseBody) {
            theFunction->getBasicBlockList().push_back(falseBlock);
            Builder.SetInsertPoint(falseBlock);

            auto tempTable = inheritTable();
            tableStack.push(tempTable);

            this->falseBody->codeGen();

            tableStack.pop();

            Builder.CreateBr(mergeBlock);
        }

        theFunction->getBasicBlockList().push_back(mergeBlock);
        Builder.SetInsertPoint(mergeBlock);

        return nullptr;
    }
};

class ReturnStatementNode : public StatementNode {
public:
    ExpressionNode *returnValue;

    ReturnStatementNode(ExpressionNode *returnV = nullptr)
        : StatementNode(), returnValue(returnV) {}
    virtual std::string getTypeName() const { return "ReturnStatement"; }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getTypeName();
        if (returnValue != nullptr)
            root["children"].append(returnValue->jsonGen());
        return root;
    }

    virtual llvm::Value *codeGen() {
        Value *ret = returnValue->codeGen();
        Builder.CreateRet(ret);
        return nullptr;
    }
};
class ContinueStatementNode : public StatementNode {
public:
    ContinueStatementNode() : StatementNode() {}

    virtual std::string getTypeName() const { return "ContinueStatement"; }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getTypeName();
        return root;
    }

    // virtual llvm::Value* codeGen(CodeGenContext& context){return (llvm::Value
    // *)0;}
};
class BreakStatementNode : public StatementNode {
public:
    BreakStatementNode() : StatementNode() {}

    virtual std::string getTypeName() const { return "BreakStatement"; }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getTypeName();
        return root;
    }

    // virtual llvm::Value* codeGen(CodeGenContext& context){return (llvm::Value
    // *)0;}
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
          argListStructName(_argListStructName){};
    symAttribute() {}
    symAttribute(Node *p)
        : name(p->getVariableName()), type(p->getType()), kind(p->getKind()),
          argList(p->getArgList()), arraySizes(p->getArraySizes()),
          structTypeName(p->getStructTypeName()),
          lineNumber(p->getLineNumber()), columnNumber(p->getColumnNumber()),
          argListStructName(p->getArgListStructName()){};

    // 将这个属性打印在 stdout 上，用来看的。
    void print();
};

// 符号表。一般不用单个的符号表，而是直接使用符号表栈。
class SymbolTable {
private:
    std::string
        mSymbolTableName; // 表名。表明就是这个表对应的函数名/结构体名等。对匿名作用域来说，表名是用
                          // NameCounter 自动生成的不重复的名字。
    std::map<std::string, symAttribute *> map;       // 符号表本体
    static std::map<std::string, SymbolTable *> set; // 所有的符号表
public:
    SymbolTable();
    SymbolTable(std::string name);
    std::string getName();

    // 向符号表中插入一个符号（符号的名字直接由 t->name
    // 取得）。如果表中原本没有这个符号，则插入成功，返回 true；否则返回 false
    // 并且不插入。
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
    std::vector<SymbolTable *>
        stack; // 栈本体，因为要查表，所以只能做成容器的形式。
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

// std::unique_ptr<ExpressionNode> LogError(const char *str) {
//     fprintf(stderr, "LogError: %s\n", str);
//     return nullptr;
// }

// Value *LogErrorVV(std::string str) { return LogErrorVV(str.c_str()); }

// Value *LogErrorVV(const char *Str) {
//     LogError(Str);
//     return nullptr;
// }

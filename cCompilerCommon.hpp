#pragma once
#include <json/json.h>
// #include <llvm/IR/Value.h>
#include<math.h>
#include<string>
#include <cstring>
#include<iostream>
#include<vector>
#include<map>
#include<cstdarg>
#include<assert.h>


// #include"noError.h"
#include <tr1/memory>

using std::shared_ptr;
using std::make_shared;


class CodeGenContext;


struct Attribute;

/*
    命名器，输入一个字符串，输出它的带编号版本。用于输出parse tree的时候给各个节点命名。
    同时也用于给匿名作用域对应的符号表命名（比如statement block和匿名结构体）。
*/
class NameCounter{
private:
    std::map<std::string, int> map;
public:
    NameCounter(){}
    std::string getNumberedName(std::string name);
};

/*
    语法分析树的结点。（不是抽象语法树）
    为属性文法做了一定的适配，有 AttributivedNode 继承它，负责属性文法的各个功能。
*/
class Node{
public:
    /*
        Type：表明该变量/常量/表达式的数据类型
        Kind：表明该结点/变量/常量的类别
    */
    enum Type{
        TYPE_INT,TYPE_FLOAT,TYPE_DOUBLE,TYPE_CHAR,TYPE_STRING,TYPE_VOID,TYPE_STRUCT
    };
    enum Kind{
        KIND_FUNCTION,KIND_VARIABLE,KIND_ARGUMENT,KIND_ATTRIBUTE,KIND_CONSTANT
    };
protected:
    std::string mSymbolName; // 非终结符的名字，实际使用时会使用 NameCounter 编号，比如“expressionStatement[0]”、“functionDeclaration[3]”等等。
    std::string mTokenValue; // 终结符对应的字符串。这个是不编号的，输入什么就是什么。
    bool mIsTerminal; // 是否是终结符
    bool mIsNegligible; // 是否可以删掉。比如在规则 expressions : expression ',' expression （举个例子）中，中间的逗号对语义分析是无效的，可以直接把他删了，不影响语法分析树的关键结构。
    std::vector<Node *> mChildren; // 树结点的孩子。只有非终结符才有孩子。
    Node::Type NodeType;// 节点的数据类型
    Node::Kind NodeKind;// 节点的类别


    /* 暂时保存 begin */

    std::vector<Node::Type> mTokenArgList;// 参数列表的类型，只有函数能用到
    std::vector<std::string> mTokenArgListStructTypeName;// 和参数列表配合使用，提供参数的结构体名字（如果是结构体的话）
    std::vector<int> mArraySizes;// 数组的各个维度的大小，只有数组能用到。如果不是数组，则这个容器的维度是 0。
    std::string mStructTypeName;// 结构体名字，只有当类型是结构体的时候能用到。注：若类别是 Attribute 但数据类型是结构体，则说明这个节点正在定义一个结构体，此时这个变量就是定义的结构体的名字。
    std::string mVariableName;// 变量的名字。
    int mLineNumber;// 位置（行）
    int mColumnNumber;// 位置（列）
    /* 暂时保存 end */


public:
    Node(){};
    // 建立一个非终结符节点，挂接 childrenNumber 个孩子，分别是 ...
    Node(std::string _symbolName, int childrenNumber, ...); 

    // 建立一个终结符结点，用在 scanner 里面。
    Node(std::string _tokenValue, bool negligible=false):mIsNegligible(negligible),mSymbolName("I am a terminal, valued "+_tokenValue),mIsTerminal(true),mTokenValue(_tokenValue){}
    
	virtual void print(std::string prefix) const{}
	// virtual llvm::Value *codeGen(CodeGenContext &context) { return (llvm::Value *)0; }
	// virtual Json::Value jsonGen() const { return Json::Value(); }

    // 添加一个孩子
    void addChild(Node *newChild);

    // 取得第 i 个孩子
    Node * getChildrenById(int i);

    // 取得孩子的个数
    int getChildrenNumber();

    // 是否是终结符，是 true 否 false
    bool isTerminal()const;


    // 返回名字，终结符就返回终结符对应的字符串，非终结符就返回非终结符的名字。
    std::string getName()const;

    // 打印出以这个节点为根节点的语法分析树。
    void printTree(int depth=0);

    
    // 设定节点的数据类型，不能自适应地一同取得结构体名。
    // virtual void setType(Node::Type _type){}
    virtual void setType(Node::Type _type);


    // 将节点的数据类型设定成和 c 一样。而且如果 c 是结构体，也能一同设定结构体名。
    // virtual void setType(Node * c){}
    virtual void setType(Node * c);

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

    // 设定节点的参数列表。只有函数类型的节点才有可能用到。如果某个参数是结构体的话，需要和 setArgListStructName/getArgListStructName 配合使用，以取得结构体名。
    // virtual void setArgList(std::vector<Node::Type> _argList){}
    virtual void setArgList(std::vector<Node::Type> _argList);

    // 取得节点的参数列表。只有函数类型的节点才有可能用到。如果某个参数是结构体的话，需要和 setArgListStructName/getArgListStructName 配合使用，以取得结构体名。
    // virtual std::vector<Node::Type> getArgList(){}
    virtual std::vector<Node::Type> getArgList();

    // 设定节点的参数列表的结构体名。只有函数类型的节点才有可能用到。和 setArgList/getArgList 配合使用，以确定结构体的名字。
    // virtual void setArgListStructName(std::vector<std::string> _structName){}
    virtual void setArgListStructName(std::vector<std::string> _structName);

    // 取得节点的参数列表的结构体名。只有函数类型的节点才有可能用到。和 setArgList/getArgList 配合使用，以确定结构体的名字。
    // virtual std::vector<std::string> getArgListStructName(){}
    virtual std::vector<std::string> getArgListStructName();

    // 设定数组的维度和各个维度的大小。只有数组类型的节点才可能用到。
    // virtual void setArraySizes(std::vector<int> _sizes){}
    virtual void setArraySizes(std::vector<int> _sizes);



    // 取得数组的维度和各个维度的大小。
    // virtual std::vector<int> getArraySizes(){} // jha
    virtual std::vector<int> getArraySizes(); // jha

    // 判定该节点是不是数组，是 true 否 false
    // virtual bool isArray(){} //jha
    virtual bool isArray() const; //jha


    // 判断改节点是不是double, float等type
    virtual bool isType() const{
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
    virtual void setPosition(int l,int c);


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

    // 将给定的属性复制给这个节点。（包括位置）我承认这个是我写代码写到一半忘记了，又把 setAttribute 拿来重写了一遍...
    virtual void copyFrom(Attribute *c);


    // 返回非终结符的名字。已弃置不用。
    std::string getSymbolName()const;

    // 返回终结符的名字。已弃置不用。
    std::string getTokenValue();



    /* defined by jha begins */
    virtual std::string getNodeTypeName() const{
        return "!!!";
    } ;
    // virtual llvm::Value *codeGen(CodeGenContext &context) { return (llvm::Value *)0;}
	virtual Json::Value jsonGen() const {return Json::Value();}
    /* defined by jha ends */
};


class ExpressionNode : public Node{
public:
    ExpressionNode(){};
    ExpressionNode(std::string _symbolName, int childrenNumber, ...):Node(_symbolName,0){
        va_list vl;
        va_start(vl, childrenNumber);
        for(int i=0; i < childrenNumber; i++){
            mChildren.push_back(va_arg(vl,Node *));
        }
        mIsNegligible=(false),mSymbolName=(_symbolName),mIsTerminal=(false),mTokenValue=("I am not a terminal.");
    }
    ExpressionNode(std::string _tokenValue, bool negligible=false){};
    virtual std::string getNodeTypeName() const {
        return "ExpressionNode";
    }
    virtual Json::Value jsonGen() const{
        Json::Value r;
        r["name"] = getNodeTypeName();
        return r;
    }
};

class StatementNode: public Node {

public:
    StatementNode():Node(){}

    virtual std::string getNodeTypeName() const {
        return "StatementNode";
    }

    virtual Json::Value jsonGen() const {
        Json::Value r;
        r["name"] = getNodeTypeName();
        return r;
    }
};

class IdentifierNode : public ExpressionNode{
public:
    IdentifierNode(std::string name, bool isType=false):ExpressionNode(name){
        assert (name.length() > 0);

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


    bool isType() const{
        return Node::NodeKind == Node::KIND_ATTRIBUTE;
    }
    bool isArray() const{ 
        return Node::isArray();
    }

    virtual std::string getNodeTypeName() const{
        if (isType()) {
            return "TypeNode";
        } else {
            return "IdentifierNode";
        }
    }

    // std::string getName(){
    //     return mSymbolName;
    // }
    // 用getVariableName

    // // virtual llvm::Value* codeGen(CodeGenContext& context){return (llvm::Value *)0;}
    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        return root;
    }

};


class IdentifierNodeList : public ExpressionNode{
public:
    std::vector<IdentifierNode *> mIdentifierNodeList;

    IdentifierNodeList():ExpressionNode("IdentifierNodeList",0){

    }
    void addIdentifierNode(IdentifierNode *identifierNode){
        assert(identifierNode != nullptr);
        mIdentifierNodeList.push_back(identifierNode);
    }

    virtual std::string getNodeTypeName() const{
        return "IdentifierNodeList";
    }
    virtual Json::Value jsonGen() const{
        Json::Value root;
        root["name"] = getNodeTypeName();
        return root;
    }
    // virtual llvm::Value* codeGen(CodeGenContext& context){return (llvm::Value *)0;}

};
class VariableDeclarationNode: public StatementNode  {
public:
    const IdentifierNode *  type;
    IdentifierNode *  id;
	ExpressionNode *  assignmentExpr = nullptr;

    VariableDeclarationNode(const IdentifierNode *  type, IdentifierNode *  id, IdentifierNode *  assignmentExpr = NULL):StatementNode(){
        assert(type != nullptr);
        assert(id != nullptr);

        this->type = type;
        this->id = id;
        this->assignmentExpr = assignmentExpr;
    }


    virtual std::string getNodeTypeName() const{
        return "VariableDeclarationNode";
    }

    virtual Json::Value jsonGen() const{
        Json::Value root;
        root["name"] = getNodeTypeName();
        root["children"].append(type->jsonGen());
        root["children"].append(id->jsonGen());
        /* TODO */
        if( assignmentExpr != nullptr){
            root["children"].append(assignmentExpr->jsonGen());
        }
        return root;
    }

    /* TODO */
    // virtual llvm::Value* codeGen(CodeGenContext& context){return (llvm::Value *)0;}

};

// store all the variable declaration, this is used for function declaration and struct declaraion
class VarDeclarationList : public StatementNode{
public:

    std::vector<VariableDeclarationNode * > mVarDeclarationList;

    VarDeclarationList():StatementNode(){}

    virtual std::string getNodeTypeName() const{
        return "VarDeclarationList";
    }
    virtual Json::Value jsonGen() const{
        Json::Value root;
        root["name"] = getNodeTypeName();
        for(auto it = mVarDeclarationList.begin(); it != mVarDeclarationList.end(); it++){
            root["children"].append((*it)->jsonGen());
        }
        return root;
    }
    // virtual llvm::Value* codeGen(CodeGenContext& context){return (llvm::Value *)0;}

};


// store all statements nodes of the same block
class StatementNodesBlock : public StatementNode{
public:

    std::vector<StatementNode * > mStatementList;

    StatementNodesBlock():StatementNode(){}

    virtual std::string getNodeTypeName() const{
        return "StatementsBlock";
    }
    virtual Json::Value jsonGen() const{
        Json::Value root;
        root["name"] = getNodeTypeName();
        for(auto it = mStatementList.begin(); it != mStatementList.end(); it++){
            root["children"].append((*it)->jsonGen());
        }
        return root;
    }

    void addStatementNode(StatementNode *statementNode){
        assert(statementNode != nullptr);
        mStatementList.push_back(statementNode);
    }

    // virtual llvm::Value* codeGen(CodeGenContext& context){return (llvm::Value *)0;}


    // input type expression and multiple name identifiers, create multiple declaration nodes
    void createMultiVarDeclaration(const IdentifierNode* type, IdentifierNodeList* nameList) {
        assert(type != nullptr && nameList != nullptr);
        assert(type->isType());
        std::vector<IdentifierNode * > idenNameList = nameList->mIdentifierNodeList; // vector of identifiers, store the name of the variables
        for (auto it = idenNameList.begin(); it != idenNameList.end(); it++) {
            // create a variable declaration
            StatementNode * varDecl  = new VariableDeclarationNode(type, *it);
            mStatementList.push_back(varDecl);
        }
    }

    // merge two statements block into one same statements block
    void mergeStatements(StatementNodesBlock * to_merge) {
        assert(to_merge != nullptr);
        this->mStatementList.insert(this->mStatementList.end(), to_merge->mStatementList.begin(), to_merge->mStatementList.end());
    }

    

};


// handle the statement that has only one semicollon
class NullStatementNode: public StatementNode {
public:
    NullStatementNode():StatementNode(){}
    virtual std::string getNodeTypeName() const {
        return "NullStatementNode";
    }
    virtual Json::Value jsonGen() const{
        Json::Value root;
        root["name"] = getNodeTypeName();
        return root;
    }

    // virtual llvm::Value* codeGen(CodeGenContext& context){return (llvm::Value *)0;}
};



class DoubleNode : public ExpressionNode{
public:
	double value;
    DoubleNode(std::string _tokenValue, bool negligible=false):ExpressionNode(_tokenValue, negligible){
        sscanf(_tokenValue.c_str(), "%lf", &this->value);

    }

	virtual std::string getNodeTypeName() const{
		return "DoubleNode";
	}

    int getValue(){
        return this->value;
    }
    
    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName() + ":" + std::to_string(value);
        return root;
    };

	// virtual llvm::Value* codeGen(CodeGenContext& context){return (llvm::Value *)0;};

};

class IntNode : public ExpressionNode{
public:
    int value;

    IntNode(std::string _tokenValue, bool negligible=false):ExpressionNode(_tokenValue, negligible){
        sscanf(_tokenValue.c_str(), "%d", &this->value);

    }

    double getValue(){
        return this->value;
    }

    virtual std::string getNodeTypeName() const  {
        return "IntNode";
    }

    
    virtual Json::Value jsonGen() const{
        Json::Value root;
        root["name"] = getNodeTypeName() + ":" + std::to_string(value);
        return root;
    };


    // virtual llvm::Value* codeGen(CodeGenContext& context){return (llvm::Value *)0;}
};


class ExpressionStatementNode : public StatementNode{
public:
    ExpressionNode * mExpression;

    ExpressionStatementNode(ExpressionNode * expression):StatementNode(){
        assert(expression != nullptr);
        this->mExpression = expression;
    }

    virtual std::string getNodeTypeName() const{
        return "ExpressionStatementNode";
    }

    virtual Json::Value jsonGen() const{
        Json::Value root;
        root["name"] = getNodeTypeName();
        root["children"].append(mExpression->jsonGen());
        return root;
    }

    // virtual llvm::Value* codeGen(CodeGenContext& context){return (llvm::Value *)0;}
};



// 为了不改变文法.l文件，做的妥协，这个中间文件，只用在函数定义中，
class FuncNameAndArgsNode : public ExpressionNode {
public:
    IdentifierNode *  mFuncName;
    VarDeclarationList *  parasList; // used for function agrs
        // used for function declararion
    FuncNameAndArgsNode(IdentifierNode * nameIdentifier, VarDeclarationList * args): ExpressionNode(){
        assert (nameIdentifier != nullptr);
        this->mFuncName = nameIdentifier;
        this->parasList = args;

    };
};


class FunctionDeclarationNode : public StatementNode{
public:
    IdentifierNode *  type; // return type
    IdentifierNode *  id; // function name
    VarDeclarationList *  parasList; // function args, be nullptr if no args
    StatementNodesBlock *  body; // function body


    FunctionDeclarationNode(IdentifierNode *  type, FuncNameAndArgsNode *  name_and_args, StatementNodesBlock *  body):StatementNode(){
        assert (type != nullptr);
        assert (name_and_args != nullptr);
        assert (body != nullptr);
        assert (type->isType());
        this->type = type;
        this->id = name_and_args->mFuncName;
        this->parasList = name_and_args->parasList;
        this->body = body;
    }
    virtual std::string getNodeTypeName() const{
        return "FunctionDeclarationNode";
    }


    virtual Json::Value jsonGen() const{
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
            for (auto it = parasList->mVarDeclarationList.begin(); it != parasList->mVarDeclarationList.end(); it++){
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
    // virtual llvm::Value* codeGen(CodeGenContext& context){return (llvm::Value *)0;}

};




class FunctionCallNode : public ExpressionNode{
public:
    FunctionCallNode(std::string _symbolName, int childrenNumber, ...):ExpressionNode(_symbolName,0){
        va_list vl;
        va_start(vl, childrenNumber);
        for(int i=0; i < childrenNumber; i++){
            mChildren.push_back(va_arg(vl,Node *));
        }
        mArguments = new std::vector<ExpressionNode *>();
        mIsNegligible = (false), mSymbolName = (_symbolName), mIsTerminal = (false), mTokenValue = ("I am not a terminal.");
    }
    FunctionCallNode(std::string _tokenValue, bool negligible=false):ExpressionNode(_tokenValue,negligible){};

    virtual std::string getNodeTypeName() const{
        return std::string("FunctionCallNode  ") + (mFunctionName->getName());
    }
    std::vector<ExpressionNode *> getArguments()const{
        return *mArguments;
    }
    void addArgument(Node *c){
        mArguments->push_back(dynamic_cast<ExpressionNode *>(c));
    }
    // virtual llvm::Value* codeGen(CodeGenContext& context){return (llvm::Value *)0;}
private:
    IdentifierNode *mFunctionName;
    std::vector<ExpressionNode *> *mArguments;
};

class UnaryOperatorNode : public ExpressionNode{
public:
    UnaryOperatorNode(std::string _symbolName, int childrenNumber, ...):ExpressionNode(_symbolName,0){
        va_list vl;
        va_start(vl, childrenNumber);
        for(int i=0; i < childrenNumber; i++){
            mChildren.push_back(va_arg(vl,Node *));
        }
        mIsNegligible = (false), mSymbolName = (_symbolName), mIsTerminal = (false), mTokenValue = ("I am not a terminal.");
        mHandSide = dynamic_cast<ExpressionNode *>(mChildren[0]);
        op = _symbolName;
        if(mHandSide==NULL)throw("castfail");
    }
    UnaryOperatorNode(std::string _tokenValue, bool negligible=false):ExpressionNode(_tokenValue,negligible){};
    virtual std::string getNodeTypeName() const{
        return std::string("UnaryOperatorNode  ")+(getVariableName());
    }
    // virtual llvm::Value* codeGen(CodeGenContext& context){return (llvm::Value *)0;}
private:
    std::string op;
    ExpressionNode *mHandSide;
};

class BinaryOperatorNode : public ExpressionNode{
public:
    BinaryOperatorNode(std::string _symbolName, int childrenNumber, ...):ExpressionNode(_symbolName,0){
        va_list vl;
        va_start(vl, childrenNumber);
        for(int i=0;i<childrenNumber;i++){
            mChildren.push_back(va_arg(vl,Node *));
        }
        mIsNegligible=(false),mSymbolName=(_symbolName),mIsTerminal=(false),mTokenValue=("I am not a terminal.");
        mLeftHandSide = dynamic_cast<ExpressionNode *>(mChildren[0]);
        mRightHandSide = dynamic_cast<ExpressionNode *>(mChildren[1]);
        op = _symbolName;
        if(mLeftHandSide==NULL || mRightHandSide==NULL)throw("castfail");
    }
    
    BinaryOperatorNode(std::string _tokenValue, bool negligible=false):ExpressionNode(_tokenValue,negligible){};
    
    BinaryOperatorNode(std::string opType, ExpressionNode *lhs, ExpressionNode *rhs, bool isArithmetic=true):ExpressionNode() {
        assert(lhs != nullptr);
        assert(rhs != nullptr);
        assert(opType != "");
        this->setType(Node::TYPE_INT);
        mLeftHandSide = lhs;
        mRightHandSide = rhs;
        op = opType;


        if (isArithmetic) // + - * / %
        {
            if(lhs->getType()==Node::TYPE_DOUBLE || rhs->getType()==Node::TYPE_DOUBLE){
                this->setType(Node::TYPE_DOUBLE);
            }
        }



    }
    
    virtual std::string getNodeTypeName() const{
        return op;
    }

    virtual Json::Value jsonGen() const{
        Json::Value root;
        root["name"] = getNodeTypeName();
        root["children"].append(mLeftHandSide->jsonGen());
        root["children"].append(mRightHandSide->jsonGen());

        return root;
    }
    // virtual llvm::Value* codeGen(CodeGenContext& context){return (llvm::Value *)0;}
private:
    std::string op;
    ExpressionNode *mLeftHandSide, *mRightHandSide;
};

class TenaryOperatorNode : public ExpressionNode{
public:
    TenaryOperatorNode(std::string _symbolName, int childrenNumber, ...):ExpressionNode(_symbolName,0){
        va_list vl;
        va_start(vl, childrenNumber);
        for(int i=0;i<childrenNumber;i++){
            mChildren.push_back(va_arg(vl, Node *));
        }
        mIsNegligible=(false),mSymbolName=(_symbolName),mIsTerminal=(false),mTokenValue=("I am not a terminal.");
        mLeftHandSide = dynamic_cast<ExpressionNode *>(mChildren[0]);
        mMidHandSide = dynamic_cast<ExpressionNode *>(mChildren[1]);
        mRightHandSide = dynamic_cast<ExpressionNode *>(mChildren[2]);
        op = _symbolName;
        if(mLeftHandSide==NULL || mRightHandSide==NULL || mMidHandSide==NULL)throw("castfail");
    }
    TenaryOperatorNode(std::string _tokenValue, bool negligible=false):ExpressionNode(_tokenValue,negligible){};
    virtual std::string getNodeTypeName() const{
        return std::string("TenaryOperatorNode  ")+(getVariableName());
    }
    // virtual llvm::Value* codeGen(CodeGenContext& context){return (llvm::Value *)0;}
private:
    std::string op;
    ExpressionNode *mLeftHandSide, *mRightHandSide, *mMidHandSide;
};

class AssignmentNode : public ExpressionNode{
public:
    AssignmentNode(std::string _symbolName, int childrenNumber, ...):ExpressionNode(_symbolName,0){
        va_list vl;
        va_start(vl, childrenNumber);
        for(int i=0; i < childrenNumber; i++){
            mChildren.push_back(va_arg(vl,ExpressionNode *));
        }
        mIsNegligible=(false),mSymbolName=(_symbolName),mIsTerminal=(false),mTokenValue=("I am not a terminal.");
        mLeftHandSide = dynamic_cast<ExpressionNode *>(mChildren[0]);
        mRightHandSide = dynamic_cast<ExpressionNode *>(mChildren[1]);
        this->op = _symbolName;
        if(mLeftHandSide==NULL || mRightHandSide==NULL)throw("castfail");
    }

    virtual std::string getNodeTypeName() const{
        return std::string("AssignmentNode ")+("=");
    }
    // virtual llvm::Value* codeGen(CodeGenContext& context){return (llvm::Value *)0;}
private:
    std::string op;
    ExpressionNode *mLeftHandSide, *mRightHandSide;
};



// central global Node 
class GlobalDeclaraionNode : public StatementNode{
public:

    std::vector<StatementNode * > mGlobalStatementList;

    GlobalDeclaraionNode():StatementNode(){}

    // copy from statements block 
    GlobalDeclaraionNode(StatementNodesBlock* toCopy):StatementNode(){
        for (auto it = toCopy->mStatementList.begin(); it != toCopy->mStatementList.end(); ++it){
            mGlobalStatementList.push_back(*it);
        }
    } 

    virtual std::string getNodeTypeName() const {
        return "CentralBlock";
    }
    virtual Json::Value jsonGen() const{
        Json::Value root;
        root["name"] = getNodeTypeName();
        for(auto it = mGlobalStatementList.begin(); it != mGlobalStatementList.end(); it++){
            root["children"].append((*it)->jsonGen());
        }
        return root;
    }
    // virtual llvm::Value* codeGen(CodeGenContext& context){return (llvm::Value *)0;}


    // merge another global declaration statements block
    void mergeGlobalStatements(StatementNodesBlock *  to_merge) {

        assert(to_merge != nullptr);
        this->mGlobalStatementList.insert(mGlobalStatementList.end(), to_merge->mStatementList.begin(), to_merge->mStatementList.end());
    }

};






// 属性。这个是变量的属性，是存在符号表里的，不是语法分析树的属性，它们会有细微的差别。
struct Attribute{
    std::string name;
    Node::Type type;
    Node::Kind kind;
    std::vector<Node::Type> argList;
    std::vector<std::string> argListStructName;
    std::vector<int> arraySizes;
    std::string structTypeName;
    int lineNumber;
    int columnNumber;
    Attribute(std::string _name, Node::Type _type, Node::Kind _kind, std::vector<Node::Type> _argList, std::vector<std::string> _argListStructName, std::vector<int> _arraySizes, std::string _structTypeName, int l, int c)
        : name(_name),type(_type),kind(_kind),argList(_argList),arraySizes(_arraySizes),structTypeName(_structTypeName),lineNumber(l),columnNumber(c),argListStructName(_argListStructName){};
    Attribute(){}
    Attribute(Node *p)
        : name(p->getVariableName()),type(p->getType()),kind(p->getKind()),argList(p->getArgList()),arraySizes(p->getArraySizes()),
          structTypeName(p->getStructTypeName()),lineNumber(p->getLineNumber()),columnNumber(p->getColumnNumber()),argListStructName(p->getArgListStructName()){};
    
    // 将这个属性打印在 stdout 上，用来看的。
    void print();
};

// 符号表。一般不用单个的符号表，而是直接使用符号表栈。
class SymbolTable{
private:
    std::string mSymbolTableName;// 表名。表明就是这个表对应的函数名/结构体名等。对匿名作用域来说，表名是用 NameCounter 自动生成的不重复的名字。
    std::map<std::string, Attribute*> map;// 符号表本体
    static std::map<std::string, SymbolTable*> set;// 所有的符号表
public:
    SymbolTable();
    SymbolTable(std::string name);
    std::string getName();

    // 向符号表中插入一个符号（符号的名字直接由 t->name 取得）。如果表中原本没有这个符号，则插入成功，返回 true；否则返回 false 并且不插入。
    bool insert(Attribute* t);

    // 查表。依据给定的 name 从表中取得对应的属性。没查到的话返回 NULL
    Attribute *lookUp(std::string name);

    // 打印表，用来看的。
    void print();

    // 根据表名取得符号表。
    static SymbolTable *getSymbolTableByName(std::string symbolTableName);

    // 查看所有出现过的符号表。
    static void viewAllSymbolTable();
};

// 符号表栈。用于维护变量生命周期。
class SymbolTableStack{
private:
    std::vector<SymbolTable*> stack;// 栈本体，因为要查表，所以只能做成容器的形式。
public:
    SymbolTableStack(SymbolTable *globalSymbolTable);

    // 压栈
    void push(SymbolTable* t);

    // 出栈
    void pop();

    // 访问栈顶
    SymbolTable *top();

    // 查表，从栈顶开始查，查不到就一层层往下查。全都查不到的话返回 NULL
    Attribute *lookUp(std::string name);

    // 将符号插入栈顶的符号表。
    bool insert(Attribute* t);
};

extern int csLineCnt;
extern int csColumnCnt;
extern SymbolTableStack *symbolTableStack;

bool checkType(Node *p, Node::Type type);
bool checkKind(Node *p, Node::Kind kind);
bool typeMatch(Node *a, Node *b);
bool typeMatch(std::vector<Node::Type> a, std::vector<Node::Type> b);
bool typeMatch(std::vector<Node::Type> a,Node *c , std::vector<std::string> s);
bool typeMatch(Attribute *a, Node * b);
std::string type_to_string(Attribute *t);



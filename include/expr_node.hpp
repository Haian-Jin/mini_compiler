#pragma once

#include "ast_node.hpp"
#include "stat_node.hpp"

class Node;

class ExpressionNode : public Node {
public:

    ExpressionNode() = default;;


    std::string getNodeTypeName() const override;

    /* getTypeAddress():
            get the type and address of the variable form the symbol table
            return error type and nullptr if not inherited by other nodes
     */
    virtual Type_and_Address getTypeAddress();

    /* addrGen():
            get the address of the variable form the symbol table
            return error type and nullptr if the function was not called by a variable node
     */
    virtual llvm::Value *addrGen(int ind = 0);

    Json::Value jsonGen() const override;
};

class IdentifierNode : public ExpressionNode {
    /*
      This node is used represent an identifier, could be variable or type of variable
     */
public:
    IdentifierNode(std::string name, bool isType = false);

    /* isType():
            return if this identifier is variable type's name
            for example: "int", "char", "double"
     */
    bool isType() const;

    /* isArray():
            return if this identifier is the name of an array
            implement as an interface for public access to Node::isType()
            seems to be redundant
            may be useful in TAC pattern
     */
    bool isArray() const override;

    /* getNodeTypeName():
            used to generate Json Tree for AST Tree
     */
    std::string getNodeTypeName() const override;

    Json::Value jsonGen() const override;

    /* getTypeAddress():
            get the type and address of the variable form the symbol table
     */
    Type_and_Address getTypeAddress();

    /* addrGen():
            get the address of the variable form the symbol table
     */
    llvm::Value *addrGen(int ind = 0) override;

    /* codeGen():
            generate IR code to load the value form the address gotten form the addrGen()
            return that value's register
     */
    llvm::Value *codeGen() override;
};

class IdentifierNodeList : public ExpressionNode {
    /*
      This node is used to pass value to declare multiple variables in a line
     */
public:

    std::vector<IdentifierNode *> mIdentifierNodeList;

    IdentifierNodeList() : ExpressionNode() {}

    void addIdentifierNode(IdentifierNode *identifierNode);

    std::string getNodeTypeName() const override;

    Json::Value jsonGen() const override;

    /*codeGen():
            a virtual codeGen for this node's codeGen() would never be called
     */
    llvm::Value *codeGen() override;
};

class AssignmentNode : public ExpressionNode {
    /*
        used to represent assignment
        only "=" is supported in our program, "+=", "-=" is not supported
     */
public:

    std::string getNodeTypeName() const override;

    AssignmentNode(IdentifierNode *lhs, ExpressionNode *rhs);

    virtual Json::Value jsonGen() const;

    /*codeGen():
            generate IR codes to create store of the right value
     */
    llvm::Value *codeGen() override;

private:
    std::string op;
    IdentifierNode *mLeftHandSide;
    ExpressionNode *mRightHandSide;
};

class DoubleNode : public ExpressionNode {
    //represent a double value in the user's code
public:
    double value;

    DoubleNode(std::string _tokenValue);

    std::string getNodeTypeName() const override;

    int getValue() const;

    Json::Value jsonGen() const override;

    /*codeGen():
            generate a right value of the double type in llvm
     */
    llvm::Value *codeGen() override;
};

class IntNode : public ExpressionNode {
    //represent an int value in the user's code
public:
    int value;

    IntNode(std::string _tokenValue);

    IntNode(int v);;

    double getValue() const;

    std::string getNodeTypeName() const override;

    Json::Value jsonGen() const override;

    /*codeGen():
            generate a right value of the int type in llvm
     */
    llvm::Value *codeGen() override;
};

class FuncNameAndArgsNode : public ExpressionNode {
    //only used for function declaration
    //not a terminal symbol
public:
    IdentifierNode *mFuncName;
    VarDeclarationList *parasList; // used for function agrs
    // used for function declararion
    FuncNameAndArgsNode(IdentifierNode *nameIdentifier,
                        VarDeclarationList *args);;
};

class UnaryOperatorNode : public ExpressionNode {
    //Unary Operator such as "++", "-", "!"
public:
    UnaryOperatorNode(std::string type, ExpressionNode * operand);

    std::string getNodeTypeName() const override;

    /*codeGen():
            generate IR codes of the operator
     */
    llvm::Value *codeGen() override;

private:
    std::string op;
    ExpressionNode *mHandSide;
};

class BinaryOperatorNode : public ExpressionNode {
    //binary Operator such as "+", "-", "&&"
public:

    BinaryOperatorNode(std::string opType, ExpressionNode *lhs,
                       ExpressionNode *rhs, bool isArithmetic = true);


    std::string getNodeTypeName() const override;

    Json::Value jsonGen() const override;

    /*codeGen():
            generate IR codes of the operator
     */
    llvm::Value *codeGen() override;

    ExpressionNode *getL() { return mLeftHandSide; }

    ExpressionNode *getR() { return mRightHandSide; }

private:
    std::string op;
    ExpressionNode *mLeftHandSide, *mRightHandSide;
};

class TenaryOperatorNode : public ExpressionNode {
    //binary Operator such as "...?...:..."
public:
    TenaryOperatorNode(std::string op,ExpressionNode * LeftHandSide, 
        ExpressionNode * MidHandSide, ExpressionNode * RightHandSide);


    std::string getNodeTypeName();

    //not finished
    llvm::Value *codeGen() override;

private:
    std::string op;
    ExpressionNode *mLeftHandSide, *mRightHandSide, *mMidHandSide;
};
#pragma once
#include "ast_node.hpp"
#include "expr_node.hpp"

class Node;
class ExpressionNode;
class IdentifierNode;
class IdentifierNodeList;
class AssignmentNode;

class StatementNode : public Node {
    //node for instructions not generating r value
public:
    StatementNode();

    std::string getNodeTypeName() const override;

    Json::Value jsonGen() const override;

    //return nullptr if not inherited
    llvm::Value *codeGen() override;
};

class VariableDeclarationNode : public StatementNode {
    //node for variable's declaration, such as "int a;"
public:
    const IdentifierNode *type;
    IdentifierNode *id;
    AssignmentNode *assignmentExpr = nullptr;

    VariableDeclarationNode(IdentifierNode *inType, IdentifierNode *id,
                            AssignmentNode *assignmentExpr = nullptr);

    std::string getNodeTypeName() const override;

    Json::Value jsonGen() const override;

    /*codeGen:
        generate IR codes to create alloca for the variable
        store to symbol table
     */
    llvm::Value *codeGen() override;
};

class VarDeclarationList : public StatementNode {
    /*
     store all the variable declaration, this is used for function declaration and
     struct declaraion.
     Not a terminal AST Node
     */
public:
    std::vector<VariableDeclarationNode *> mVarDeclarationList;

    VarDeclarationList() : StatementNode() {}

    std::string getNodeTypeName() const override;

    Json::Value jsonGen() const override;

    Value *codeGen() override;
};

class StatementNodesBlock : public StatementNode {
    /*
        represent a series of codes in a block
        for example: codes in "{}"
     */
public:
    std::vector<StatementNode *> mStatementList;

    StatementNodesBlock() : StatementNode() {}

    std::string getNodeTypeName() const override;

    Json::Value jsonGen() const override;

    void addStatementNode(StatementNode *statementNode);

    // input type expression and multiple name identifiers, create multiple
    // declaration nodes
    void createMultiVarDeclaration(IdentifierNode *type,
                                   IdentifierNodeList *nameList);

    // merge two statements block into one same statements block
    void mergeStatements(StatementNodesBlock *to_merge);

    /* codeGen():
        call evert statement's codeGen() in this block
        to generate the IR codes of this block
     */
    Value *codeGen() override;
};

class NullStatementNode : public StatementNode {
    // handle the statement that has only one semicolon
public:
    NullStatementNode() : StatementNode() {}

    std::string getNodeTypeName() const override;

    Json::Value jsonGen() const override;

    /* codeGen():
        generate IR code of 0+0 to generate null statement
     */
    llvm::Value *codeGen() override;
};

class ExpressionStatementNode : public StatementNode {
    //expressions with semicolon
public:
    ExpressionNode *mExpression;

    ExpressionStatementNode(ExpressionNode *expression);

    std::string getNodeTypeName() const override;

    Json::Value jsonGen() const override;

    /* codeGen():
        run codeGen of the expression node
     */
    Value *codeGen() override;
};




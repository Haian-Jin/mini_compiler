#pragma once
#include "cCompilerCommon.hpp"
#include "exprNode.hpp"

class Node;
class ExpressionNode;
class IdentifierNode;
class IdentifierNodeList;
class AssignmentNode;

class StatementNode : public Node {

public:
    StatementNode() : Node() {}

    std::string getNodeTypeName() const override { return "StatementNode"; }

    Json::Value jsonGen() const override {
        Json::Value r;
        r["name"] = getNodeTypeName();
        return r;
    }

    llvm::Value *codeGen() override {
        return nullptr;
    }
};

class VariableDeclarationNode : public StatementNode {
public:
    const IdentifierNode *type;
    IdentifierNode *id;
    AssignmentNode *assignmentExpr = nullptr;

    VariableDeclarationNode(IdentifierNode *inType, IdentifierNode *id,
                            AssignmentNode *assignmentExpr = nullptr);

    virtual std::string getNodeTypeName() const {
        return "VariableDeclarationNode";
    }

    Json::Value jsonGen() const override;
    llvm::Value *codeGen() override;
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
        /* This node is used for func declaration, no need to codeGen() */
        return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "No need to codeGen this");
    }
};

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
                                   IdentifierNodeList *nameList);

    // merge two statements block into one same statements block
    void mergeStatements(StatementNodesBlock *to_merge) {
        assert(to_merge != nullptr);
        this->mStatementList.insert(this->mStatementList.end(),
                                    to_merge->mStatementList.begin(),
                                    to_merge->mStatementList.end());
    }

    Value *codeGen() override;
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

    llvm::Value *codeGen() override;
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

    Json::Value jsonGen() const override;

    Value *codeGen() override;
};




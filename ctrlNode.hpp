#pragma once
#include "cCompilerCommon.hpp"
#include "statNode.hpp"

class StatementNode;
class StatementNodesBlock;
class ExpressionStatementNode;

class GlobalDeclaraionNode : public StatementNode {
public:
    std::vector<StatementNode *> mGlobalStatementList;

    GlobalDeclaraionNode() : StatementNode() {}

    // copy from statements block
    GlobalDeclaraionNode(StatementNodesBlock *toCopy);

    virtual std::string getNodeTypeName() const { return "CentralBlock"; }

    Json::Value jsonGen() const override;

    llvm::Value *codeGen() override;

    void mergeGlobalStatements(StatementNodesBlock *to_merge);
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

    Json::Value jsonGen() const override;

    llvm::Value *codeGen() override;
};

class WhileStatementNode : public StatementNode {
public:
    // for (initialStatement; conditionStatement; progressStatement)
    ExpressionStatementNode *conditionStatement;
    StatementNodesBlock *whileBody;

    WhileStatementNode(ExpressionStatementNode *condition,
                       StatementNodesBlock *body);

    virtual std::string getTypeName() const {
        return std::string("WhileStatementNode");
    }

    Json::Value jsonGen() const override;

    llvm::Value *codeGen() override;
};

class IfStatementNode : public StatementNode {
public:
    ExpressionStatementNode *conditionStatement;
    StatementNodesBlock *trueBody;  // if (True), do this, cannot be null
    StatementNodesBlock *falseBody; // else, do this, can be null

    IfStatementNode(ExpressionStatementNode *condition,
                    StatementNodesBlock *trueStatements,
                    StatementNodesBlock *falseStatements = nullptr);



    virtual std::string getTypeName() const { return "NIfStatement"; }

    Json::Value jsonGen() const override;

    llvm::Value *codeGen() override;
};

class ReturnStatementNode : public StatementNode {
public:
    ExpressionNode *returnValue;

    ReturnStatementNode(ExpressionNode *returnV = nullptr);

    virtual std::string getTypeName() const { return "ReturnStatement"; }

    Json::Value jsonGen() const override;

    llvm::Value *codeGen() override;
};

class ContinueStatementNode : public StatementNode {
public:
    ContinueStatementNode() : StatementNode() {}

    virtual std::string getTypeName() const { return "ContinueStatement"; }

    virtual Json::Value jsonGen() const;
};

class BreakStatementNode : public StatementNode {
public:
    BreakStatementNode() : StatementNode() {}

    virtual std::string getTypeName() const { return "BreakStatement"; }

    virtual Json::Value jsonGen() const;
};

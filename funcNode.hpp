#pragma once
#include "cCompilerCommon.hpp"

class StatementNode;
class IdentifierNode;
class ExpressionNode;
class VarDeclarationList;
class StatementNodesBlock;
class FuncNameAndArgsNode;
class StatementNodesBlock;

class FunctionDeclarationNode : public StatementNode {
public:
    IdentifierNode *type;          // return type
    IdentifierNode *id;            // function name
    VarDeclarationList *parasList; // function args, be nullptr if no args
    StatementNodesBlock *body;     // function body

    FunctionDeclarationNode(IdentifierNode *type,
                            FuncNameAndArgsNode *name_and_args,
                            StatementNodesBlock *body);

    virtual std::string getNodeTypeName() const {
        return "FunctionDeclarationNode";
    }

    Json::Value jsonGen() const override;

    llvm::Value *codeGen() override;
};

class FunctionCallNode : public ExpressionNode {
public:
    FunctionCallNode(std::string _symbolName, int childrenNumber, ...);

    FunctionCallNode(std::string _tokenValue, bool negligible = false)
            : ExpressionNode(_tokenValue, negligible),
              mArguments(new std::vector<ExpressionNode *>()) {};

    std::vector<ExpressionNode *> getArguments() const { return *mArguments; }

    void addArgument(Node *c) {
        assert(dynamic_cast<ExpressionNode *>(c) != NULL);
        mArguments->push_back(dynamic_cast<ExpressionNode *>(c));
    }

    virtual std::string getNodeTypeName() const;

    Json::Value jsonGen() const override;

    llvm::Value* codeGen_p();

    llvm::Value* codeGen_s();

    llvm::Value *codeGen() override;

private:
    IdentifierNode *mFunctionName;
    std::vector<ExpressionNode *> *mArguments;
};


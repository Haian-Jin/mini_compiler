#pragma once
#include "exprNode.hpp"
#include "cCompilerCommon.hpp"
#include "statNode.hpp"

class StructDeclarationNode : public StatementNode {
protected:
    IdentifierNode *mStructName;
    StatementNodesBlock *mMembers;

public:
    StructDeclarationNode(IdentifierNode *name, StatementNodesBlock *members) {
        assert(name != nullptr);
        assert(members != nullptr);
        mStructName = name;
        mMembers = members;
    }


    std::string getNodeTypeName() const override;

    Json::Value jsonGen() const override;

    Value *codeGen() override;
};

class StructMemberNode : public ExpressionNode {
public:
    StructMemberNode(std::string _tokenValue, bool negligible = false);

    StructMemberNode(std::string opType, IdentifierNode *lhs,
                     IdentifierNode *rhs, bool isArithmetic = false);

    std::string getNodeTypeName() const override;

    Json::Value jsonGen() const override;

    llvm::Value *codeGen() override;

    ExpressionNode *getL() { return mVariableName; }

    ExpressionNode *getR() { return mMemberName; }

private:
    std::string op;
    IdentifierNode *mVariableName, *mMemberName;
};

class StructMemberAssignmentNode : public ExpressionNode {
public:
    std::string getNodeTypeName() const override;

    StructMemberAssignmentNode(StructMemberNode *lhs, ExpressionNode *rhs);

    Json::Value jsonGen() const override;

    llvm::Value *codeGen() override;

private:
    std::string op;
    StructMemberNode *mLeftHandSide;
    ExpressionNode *mRightHandSide;
};

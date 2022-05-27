#pragma once
#include "cCompilerCommon.hpp"
#include "exprNode.hpp"

class ExpressionNode;
class IdentifierNode;

llvm::Value *calcArrayIndex(std::vector<int> arraySizes, std::vector<ExpressionNode *> mArrayIndexs);

class ArrayIndexNode : public ExpressionNode {
public:
    ArrayIndexNode(std::string _symbolName, int childrenNumber, ...);


    ArrayIndexNode(std::string _tokenValue, bool negligible = false)
            : ExpressionNode(_tokenValue, negligible) {};

    ArrayIndexNode(std::string opType, ExpressionNode *lhs,
                   std::vector<ExpressionNode *> rhs, bool isArithmetic = false);

    std::string getVariableName();

    virtual std::string getNodeTypeName() const { return op; }

    virtual Json::Value jsonGen() const;

    Type_and_Address getTypeAddress() override;

    llvm::Value *addrGen(int ind = 0) override;

    llvm::Value *codeGen() override;


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

    ArrayAssignmentNode(ArrayIndexNode *lhs, ExpressionNode *rhs);


    virtual Json::Value jsonGen() const;

    llvm::Value *codeGen() override;

private:
    std::string op;
    ArrayIndexNode *mLeftHandSide;
    ExpressionNode *mRightHandSide;
};

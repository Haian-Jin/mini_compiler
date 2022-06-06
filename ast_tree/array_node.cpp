//
// Created by Administrator on 5/28/2022.
//
#include "include/ast_node.hpp"
#include "include/array_node.hpp"
#include "include/expr_node.hpp"
#include "include/func_node.hpp"
#include "include/ctrl_node.hpp"
#include "include/stat_node.hpp"
#include "include/struct_node.hpp"

llvm::Value *calcArrayIndex(std::vector<int> arraySizes, std::vector<ExpressionNode *> mArrayIndexs) {
    ExpressionNode *expression = *(mArrayIndexs.begin());
    int postMul = 1;
    for (int i = 1; i < arraySizes.size(); i++) {
        BinaryOperatorNode *te = new BinaryOperatorNode("*", new IntNode(arraySizes[i]), expression);
        expression = te;
        if (i < mArrayIndexs.size()) {
            BinaryOperatorNode *temp = new BinaryOperatorNode("+", mArrayIndexs[i], expression);
            expression = temp;
        }
    }
    if (arraySizes.size() == 1) {
        return (expression)->codeGen();
    } else
        return dynamic_cast<BinaryOperatorNode *>(expression)->codeGen();
}

//--------------------------ArrayIndexNode----------------------------------
ArrayIndexNode::ArrayIndexNode(std::string _symbolName, int childrenNumber, ...)  : ExpressionNode(_symbolName, 0) {
    va_list vl;
    va_start(vl, childrenNumber);
    for (int i = 0; i < childrenNumber; i++) {
        mChildren.push_back(va_arg(vl, Node *));
    }
    mIsNegligible = (false), mSymbolName = (_symbolName),
    mIsTerminal = (false), mTokenValue = ("I am not a terminal.");
    op = _symbolName;
}

ArrayIndexNode::ArrayIndexNode(std::string opType, ExpressionNode *lhs, std::vector<ExpressionNode *> rhs,
                               bool isArithmetic)
        : ExpressionNode() {
    assert(lhs != nullptr);
    assert(opType != "");
    this->setType(Node::TYPE_INT);
    // this->setKind() HERE
    mArrayName = dynamic_cast<IdentifierNode *>(lhs);
    mArrayIndexs = rhs;
    op = opType;
    if (isArithmetic) // + - * / %
    {
    } else {
        if (lhs->getType() == Node::TYPE_DOUBLE) {
            this->setType(Node::TYPE_DOUBLE);
        } else {
            this->setType(Node::TYPE_INT);
        }
    }
}

std::string ArrayIndexNode::getVariableName() {
    return this->mArrayName->getSymbolName();
}

Json::Value ArrayIndexNode::jsonGen() const {
    Json::Value root;
    root["name"] = getNodeTypeName();
    root["children"].append(mArrayName->jsonGen());
    for (auto i: mArrayIndexs) {
        root["children"].append(i->jsonGen());
    }
    return root;
}

ArrayIndexNode::ArrayIndexNode(std::string _tokenValue, bool negligible)
        : ExpressionNode(_tokenValue, negligible) {}

std::string ArrayIndexNode::getNodeTypeName() const { return op; }

Type_and_Address ArrayIndexNode::getTypeAddress() {
    llvm::Value *value = nullptr;
    llvm::Type::TypeID type;
    bool isArray = false;
    std::string name = mArrayName->getSymbolName();
    std::vector<int> arraySizes;
    if (tableStack.empty()) { /* if the stack is empty, find it only in the global table */
        if (variableTable.find(name) != (variableTable.end())) {
            value = variableTable[name].address;
            type = variableTable[name].type;
            isArray = variableTable[name].isPtr;
            arraySizes = variableTable[name].arraySizes;
        } else {
            value = nullptr;
        }
    } else { /* otherwise, find it on both stack top and the global table */
        if (tableStack.top()->find(name) != tableStack.top()->end()) {
            value = (*tableStack.top())[name].address;
            type = (*tableStack.top())[name].type;
            isArray = (*tableStack.top())[name].isPtr;
            arraySizes = (*tableStack.top())[name].arraySizes;
        } else if (variableTable.find(name) != (variableTable.end())) {
            value = variableTable[name].address;
            type = variableTable[name].type;
            isArray = variableTable[name].isPtr;
            arraySizes = variableTable[name].arraySizes;
        } else {
            value = nullptr;
        }
    }
    return {type, value, isArray, arraySizes};
}

llvm::Value *ArrayIndexNode::addrGen(int ind) {
    llvm::Value *value = nullptr;
    llvm::Type::TypeID type;
    bool isArray = false;
    auto ta = getTypeAddress();
    type = ta.type;
    value = ta.address;
    isArray = ta.isPtr;
    std::string name = mArrayName->getSymbolName();
    std::vector<int> arraySizes = ta.arraySizes;
    if (!value) {
        LogErrorV(std::to_string(this->getLineNumber()) + ":" + std::to_string(this->getColumnNumber()) +
                  " array " + std::string(name) + " is not declared");
    }
    if (isArray) { /* this is an array, normally codegen */
        llvm::ArrayRef<Value *> indexs;
        std::vector<ExpressionNode *> Ind = std::vector<ExpressionNode *>(mArrayIndexs);
        Ind.push_back(new IntNode(ind));
        indexs = {llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0),
                  calcArrayIndex(arraySizes, Ind)};
        auto ptr = Builder.CreateInBoundsGEP(value, indexs, "elementPtr");
        return ptr;
    } else {
        return LogErrorV(std::to_string(mArrayName->getLineNumber()) + ":" + std::to_string(mArrayName->getColumnNumber()) +
                         " variable " + std::string(name) + " is not an array!");
    }
}

llvm::Value *ArrayIndexNode::codeGen() {
    Type_and_Address t = getTypeAddress();
    if (t.type!=llvm::Type::LabelTyID || t.arraySizes.size()==mArrayIndexs.size()) {
        auto ptr = addrGen();
        return Builder.CreateLoad(ptr, false, "");
    } else {
        return this->addrGen();
    }
}

//----------------------------ArrayAssignmentNode------------------------------
ArrayAssignmentNode::ArrayAssignmentNode(ArrayIndexNode *lhs, ExpressionNode *rhs) : ExpressionNode("=", 0) {
    assert(lhs != nullptr);
    assert(rhs != nullptr);
    mLeftHandSide = lhs;
    mRightHandSide = rhs;
}

Json::Value ArrayAssignmentNode::jsonGen() const {
    Json::Value root;
    root["name"] = getNodeTypeName();
    root["children"].append(mLeftHandSide->jsonGen());
    root["children"].append(mRightHandSide->jsonGen());
    return root;
}

std::string ArrayAssignmentNode::getNodeTypeName() const {
    return std::string("ArrayAssignmentNode ") + ("=");
}

llvm::Value *ArrayAssignmentNode::codeGen() {
    ArrayIndexNode *&arrayIndex = mLeftHandSide;
    ExpressionNode *&expression = mRightHandSide;
    auto ta = mLeftHandSide->getTypeAddress();
    Value *res = nullptr;
    llvm::Value *value = ta.address;
    llvm::Type::TypeID type = ta.type;
    bool isArray = ta.isPtr;
    std::string name = arrayIndex->getVariableName();
    std::vector<int> arraySizes = ta.arraySizes;

    if (!value) {
        res = LogErrorV(std::to_string(mLeftHandSide->mArrayName->getLineNumber()) + ":" + std::to_string(mLeftHandSide->mArrayName->getColumnNumber()) +
                        " array " + std::string(name) + " is not declared");

    } else if (!isArray) {
        res = LogErrorV(std::to_string(mLeftHandSide->mArrayName->getLineNumber()) + ":" + std::to_string(mLeftHandSide->mArrayName->getColumnNumber()) +
                        " variable " + std::string(name) + " is not an array");

    } else {
        auto arrayPointer = Builder.CreateLoad(value, "arrayPointer");
        auto arrayIndexValue = calcArrayIndex(arraySizes, arrayIndex->mArrayIndexs);

        llvm::ArrayRef<llvm::Value *> ga{llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0),
                                         arrayIndexValue};

        if (type == llvm::Type::IntegerTyID)
            res = Builder.CreateAlignedStore(expression->codeGen(),
                                             Builder.CreateInBoundsGEP(value, ga, "elementPointer"), 4);

        else if (type == llvm::Type::DoubleTyID)
            res = Builder.CreateAlignedStore(expression->codeGen(),
                                             Builder.CreateInBoundsGEP(value, ga, "elementPointer"), 8);

        else if (type == llvm::Type::LabelTyID)
            res = Builder.CreateAlignedStore(expression->codeGen(),
                                             Builder.CreateInBoundsGEP(value, ga, "elementPointer"), 1);

    }
    return res;
}

//
// Created by Administrator on 5/28/2022.
//
#include "cCompilerCommon.hpp"
#include "arrayNode.hpp"
#include "exprNode.hpp"
#include "funcNode.hpp"
#include "ctrlNode.hpp"
#include "statNode.hpp"

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
        return LogErrorV(std::to_string(this->getLineNumber()) + ":" + std::to_string(this->getColumnNumber()) +
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

ArrayIndexNode::ArrayIndexNode(std::string _symbolName, int childrenNumber, ...)  : ExpressionNode(_symbolName, 0) {
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

ArrayIndexNode::ArrayIndexNode(std::string opType, ExpressionNode *lhs, std::vector<ExpressionNode *> rhs,
                               bool isArithmetic)
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


llvm::Value *ArrayAssignmentNode::codeGen() {
    ArrayIndexNode *&arrayIndex = mLeftHandSide;
    ExpressionNode *&expression = mRightHandSide;
    Value *res = nullptr;
    llvm::Value *value = nullptr;
    llvm::Type::TypeID type;
    bool isArray = false;
    std::string name = arrayIndex->getVariableName();
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
    if (!value) {
        res = LogErrorV(std::to_string(this->getLineNumber()) + ":" + std::to_string(this->getColumnNumber()) +
                        " array " + std::string(name) + " is not declared");
    } else if (!isArray) {
        res = LogErrorV(std::to_string(this->getLineNumber()) + ":" + std::to_string(this->getColumnNumber()) +
                        " array " + std::string(name) + " is not an array");
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

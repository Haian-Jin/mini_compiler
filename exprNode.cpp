//
// Created by Administrator on 5/28/2022.
//

#include"./cCompilerCommon.hpp"
#include "arrayNode.hpp"
#include "exprNode.hpp"
#include "ctrlNode.hpp"
#include "funcNode.hpp"
#include "statNode.hpp"

Type_and_Address IdentifierNode::getTypeAddress() {
    llvm::Value *value = nullptr;
    llvm::Type::TypeID type;
    bool isArray = false;
    std::string name = this->getSymbolName();
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

llvm::Value *IdentifierNode::addrGen(int ind) {
    std::string name = this->getSymbolName();
    llvm::Value* value = nullptr;
    if (tableStack.empty()) { /* if the stack is empty, find it only in the global table */
        if (variableTable.find(name) != (variableTable.end())) {
            value = variableTable[name].address;
        } else {
            value = nullptr;
            return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " + name +
                             "not declared");
        }
    } else { /* otherwise, find it on both stack top and the global table */
        if (tableStack.top()->find(name) != tableStack.top()->end()) {
            value = (*tableStack.top())[name].address;
        } else if (variableTable.find(name) != (variableTable.end())) {
            value = variableTable[name].address;
        } else {
            value = nullptr;
            return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " + name +
                             "not declared");
        }
    }
    return value;
}

llvm::Value *IdentifierNode::codeGen() {
    if (!isType()) {
        auto t = getTypeAddress();
        if (t.type == llvm::Type::LabelTyID) {
            return addrGen();
        }
        return Builder.CreateLoad(addrGen(), false, "");
    } else {
        return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "Keywords can\'t be used as identifier's name");
    }
}


llvm::Value *AssignmentNode::codeGen() {
    Value *dst = nullptr;
    llvm::Type::TypeID type_l;
    if (tableStack.empty()) {
        dst = variableTable[mLeftHandSide->getSymbolName()].address;
        type_l = variableTable[mLeftHandSide->getSymbolName()].type;
    } else {
        dst = (tableStack.top()->find(mLeftHandSide->getSymbolName()) !=
               tableStack.top()->end())
              ? ((*(tableStack.top()))[mLeftHandSide->getSymbolName()].address)
              : (variableTable[mLeftHandSide->getSymbolName()].address);
        type_l = (tableStack.top()->find(mLeftHandSide->getSymbolName()) !=
                  tableStack.top()->end())
                 ? ((*(tableStack.top()))[mLeftHandSide->getSymbolName()].type)
                 : (variableTable[mLeftHandSide->getSymbolName()].type);
    }
    if (!dst)
        return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "undeclared variable");
    Value *R = mRightHandSide->codeGen();

    auto type_r = R->getType()->getTypeID();
    if (type_r == type_l) {
        Builder.CreateStore(R, dst);
        return R;
    } else if (type_r == llvm::Type::DoubleTyID) {
        return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "Can't assign double to int");
    } else {
        R = Builder.CreateSIToFP(R, llvm::Type::getDoubleTy(TheContext));
        Builder.CreateStore(R, dst);
        return R;
    }
}

llvm::Value *UnaryOperatorNode::codeGen() {
    Value *OperandV = mHandSide->codeGen();
    if (!OperandV)
        return nullptr;
    bool isFloat = false;

    if (OperandV->getType()->getTypeID() == llvm::Type::DoubleTyID) {
        isFloat = true;
    }
    if (op == "pre++" || op == "pre--" || op == "post++" ||
        op == "post--" || op == "~") {
        return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "\"" + op + "\" is not supported as an operator");
    } else if (op == "!") {
        if (isFloat) {
            return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " +
                             "invalid boolean operation with float number");
        }
        return Builder.CreateNot(OperandV, "notop");
    } else if (op == "-") {
        return isFloat ? Builder.CreateFNeg(OperandV, "fnotop")
                       : Builder.CreateFNeg(OperandV, "notop");
    }
}


llvm::Value *BinaryOperatorNode::codeGen() {
    Value *Left = mLeftHandSide->codeGen();
    Value *Right = mRightHandSide->codeGen();

    if(Left->getType()->getTypeID()==llvm::Type::PointerTyID||Right->getType()->getTypeID()==llvm::Type::PointerTyID) {
        if(Left->getType()->getTypeID()!=Right->getType()->getTypeID() || op!= "==") {
            return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " +
                             "invalid operation");
        } else {
            Type_and_Address l = mLeftHandSide->getTypeAddress();
            Type_and_Address r = mRightHandSide->getTypeAddress();
            int e = std::min(*l.arraySizes.rbegin(), *r.arraySizes.rbegin());
            auto ret = Builder.CreateICmpEQ(Builder.CreateLoad(Left, false, ""), Builder.CreateLoad(Right, false, ""));
            for (int i = 1; i < e; ++i) {
                auto ptr_l = mLeftHandSide->addrGen(i);
                auto ptr_r = mRightHandSide->addrGen(i);
                auto temp = Builder.CreateICmpEQ(Builder.CreateLoad(ptr_l, false, ""), Builder.CreateLoad(ptr_r, false, ""));
                ret = Builder.CreateAnd(temp, ret);
            }
            return ret;
        }
    }

    if (!Left || !Right)
        return nullptr;
    bool isFloat = false;

    if (Left->getType()->getTypeID() == llvm::Type::DoubleTyID ||
        Right->getType()->getTypeID() == llvm::Type::DoubleTyID) {
        isFloat = true;
        if (!(Left->getType()->getTypeID() == llvm::Type::DoubleTyID)) {
            Left = Builder.CreateSIToFP(
                    Left, llvm::Type::getDoubleTy(TheContext), "ftmp");
        } else if (!(Right->getType()->getTypeID() ==
                     llvm::Type::DoubleTyID)) {
            Right = Builder.CreateSIToFP(
                    Right, llvm::Type::getDoubleTy(TheContext), "ftmp");
        }
    } else if (Left->getType()->getIntegerBitWidth()==8 || Right->getType()->getIntegerBitWidth()==8) {
        Left = Builder.CreateIntCast(Left, llvm::Type::getInt32Ty(TheContext), false, "8castl");
        Right = Builder.CreateIntCast(Right, llvm::Type::getInt32Ty(TheContext), false, "8castr");
    }

    if (op == "&&") { // and operation
        if (isFloat) {
            return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " +
                             "invalid boolean operation with float number");
        }
        return Builder.CreateAnd(Left, Right, "andop");
    } else if (op == "||") { // or operation
        if (isFloat) {
            return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " +
                             "invalid boolean operation with float number");
        }
        return Builder.CreateOr(Left, Right, "orop");
    } else if (op == "^" || op == "|" ||
               op == "&") { // bitwise operation, but not supported
        return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "bit operation is not supported");
    } else if (op == "==") {
        return isFloat ? Builder.CreateFCmpOEQ(Left, Right, "feqop")
                       : Builder.CreateICmpEQ(Left, Right, "ieqop");
    } else if (op == "!=") {
        return isFloat ? Builder.CreateFCmpONE(Left, Right, "fneop")
                       : Builder.CreateICmpNE(Left, Right, "ineop");
    } else if (op == "<") {
        return isFloat ? Builder.CreateFCmpOLT(Left, Right, "fltop")
                       : Builder.CreateICmpSLT(Left, Right, "iltop");
    } else if (op == ">") {
        return isFloat ? Builder.CreateFCmpOGT(Left, Right, "fgtop")
                       : Builder.CreateICmpSGT(Left, Right, "igtop");
    } else if (op == ">=") {
        return isFloat ? Builder.CreateFCmpOGE(Left, Right, "fgeop")
                       : Builder.CreateICmpSGE(Left, Right, "igeop");
    } else if (op == "<=") {
        return isFloat ? Builder.CreateFCmpOLE(Left, Right, "fleop")
                       : Builder.CreateICmpSLE(Left, Right, "ileop");
    } else if (op == ">>") {
        if (isFloat) {
            return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " +
                             "invalid boolean operation with float number");
        }
        return Builder.CreateAShr(Left, Right, "shrop");
    } else if (op == "<<") {
        if (isFloat) {
            return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " +
                             "invalid boolean operation with float number");
        }
        return Builder.CreateShl(Left, Right, "shlop");
    } else if (op == "+") {
        return isFloat ? Builder.CreateFAdd(Left, Right, "faddop")
                       : Builder.CreateAdd(Left, Right, "addop");
    } else if (op == "-") {
        return isFloat ? Builder.CreateFSub(Left, Right, "fsubop")
                       : Builder.CreateSub(Left, Right, "subop");
    } else if (op == "*") {
        return isFloat ? Builder.CreateFMul(Left, Right, "fmulop")
                       : Builder.CreateMul(Left, Right, "mulop");
    } else if (op == "/") {
        return isFloat ? Builder.CreateFDiv(Left, Right, "fdivop")
                       : Builder.CreateSDiv(Left, Right, "divop");
    } else if (op == "%") {
        if (isFloat) {
            return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " +
                             "invalid \"%\" operation with float number");
        }
        return Builder.CreateSRem(Left, Right, "smodop");
    } else {
        return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "\"" + op + "\" is not supported as an operator");
    }
}

//
// Created by Administrator on 5/28/2022.
//

#include"include/ast_node.hpp"
#include "include/array_node.hpp"
#include "include/expr_node.hpp"
#include "include/ctrl_node.hpp"
#include "include/func_node.hpp"
#include "include/stat_node.hpp"
#include "include/struct_node.hpp"

// -----------------------ExpressionNode-----------------------------
ExpressionNode::ExpressionNode(std::string _symbolName, int childrenNumber, ...)
        : Node(_symbolName, 0) {
    va_list vl;
    va_start(vl, childrenNumber);
    for (int i = 0; i < childrenNumber; i++) {
        mChildren.push_back(va_arg(vl, Node *));
    }
    mSymbolName = (_symbolName),
    mIsTerminal = (false), mTokenValue = ("I am not a terminal.");
}

Type_and_Address ExpressionNode::getTypeAddress() {
    return {llvm::Type::TypeID::VoidTyID, nullptr};
}

llvm::Value *ExpressionNode::addrGen(int ind) {
    return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                     std::to_string(this->getColumnNumber()) + " " + "This should not be Gen");
}

Json::Value ExpressionNode::jsonGen() const {
    Json::Value r;
    r["name"] = getNodeTypeName();
    return r;
}

ExpressionNode::ExpressionNode(std::string _tokenValue, bool negligible) {}

std::string ExpressionNode::getNodeTypeName() const { return "ExpressionNode"; }

// -----------------------IdentifierNode-----------------------------
IdentifierNode::IdentifierNode(std::string name, bool isType)
        : ExpressionNode(name) {
    assert(name.length() > 0);

    this->mSymbolName = name;
    if (isType) {
        this->setKind(Node::KIND_ATTRIBUTE);
        if (name == "int") {
            this->setType(Node::TYPE_INT);
        } else if (name == "float") {
            this->setType(Node::TYPE_FLOAT);
        } else if (name == "double") {
            this->setType(Node::TYPE_DOUBLE);
        } else if (name == "char") {
            this->setType(Node::TYPE_CHAR);
        } else if (name == "void") {
            this->setType(Node::TYPE_VOID);
        }
    }
}

bool IdentifierNode::isType() const { return Node::NodeKind == Node::KIND_ATTRIBUTE; }

bool IdentifierNode::isArray() const { return Node::isArray(); }

std::string IdentifierNode::getNodeTypeName() const {

    if (isType()) {
        return std::string("TypeNode: ") + getTokenValue();
    } else {
        return std::string("IdentifierNode: ") + getTokenValue();
    }
}

Json::Value IdentifierNode::jsonGen() const {
    Json::Value root;
    root["name"] = getNodeTypeName();
    return root;
}

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
    auto res = getTypeAddress();
    if (res.address == nullptr) {
        return LogErrorV(std::to_string(Node::getLineNumber()) + ":" +
                         std::to_string(Node::getLineNumber()) + " " +
                         "This identifier is not defined");
    }
    return res.address;
}

llvm::Value *IdentifierNode::codeGen() {
    if (!isType()) {
        auto t = getTypeAddress();
        if (t.type == llvm::Type::LabelTyID) {
            return addrGen();
        }
        return Builder.CreateLoad(addrGen(), false, "");
    } else {
        return LogErrorV(std::to_string(Node::getLineNumber()) + ":" +
                         std::to_string(Node::getLineNumber()) + " " +
                         "Keywords can\'t be used as identifier's name");
    }
}

// -----------------------AssignmentNode-----------------------------
std::string AssignmentNode::getNodeTypeName() const {
    return std::string("AssignmentNode ") + ("=");
}

AssignmentNode::AssignmentNode(IdentifierNode *lhs, ExpressionNode *rhs)
        : ExpressionNode("=", 0) {
    assert(lhs != nullptr);
    assert(rhs != nullptr);
    mLeftHandSide = lhs;
    mRightHandSide = rhs;
}

Json::Value AssignmentNode::jsonGen() const {
    Json::Value root;
    root["name"] = getNodeTypeName();
    root["children"].append(mLeftHandSide->jsonGen());
    root["children"].append(mRightHandSide->jsonGen());
    return root;
}

llvm::Value *AssignmentNode::codeGen() {
    auto res = mLeftHandSide->getTypeAddress();
    Value *dst = res.address;
    if (!dst)
        return LogErrorV(std::to_string(mLeftHandSide->getLineNumber()) + ":" +
                         std::to_string(mLeftHandSide->getColumnNumber()) + " "+ " undeclared variable: " +
                                                                                 mLeftHandSide->getSymbolName());
    Value *R = mRightHandSide->codeGen();
    auto type_l = res.type;
    auto type_r = R->getType()->getTypeID();
    if (type_r == type_l) {
        Builder.CreateStore(R, dst);
        return R;
    } else if (type_r == llvm::Type::DoubleTyID) {
        return LogErrorV(std::to_string(mLeftHandSide->getLineNumber()) + ":" +
                         std::to_string(mLeftHandSide->getColumnNumber()) + " " +
                         "Can't assign double to int");
    } else {
        R = Builder.CreateSIToFP(R, llvm::Type::getDoubleTy(TheContext));
        Builder.CreateStore(R, dst);
        return R;
    }
}

// -----------------------IdentifierNodeList-----------------------------
void IdentifierNodeList::addIdentifierNode(IdentifierNode *identifierNode) {
    assert(identifierNode != nullptr);
    mIdentifierNodeList.push_back(identifierNode);
}

std::string IdentifierNodeList::getNodeTypeName() const { return "IdentifierNodeList"; }

Json::Value IdentifierNodeList::jsonGen() const {
    Json::Value root;
    root["name"] = getNodeTypeName();
    return root;
}

llvm::Value *IdentifierNodeList::codeGen() {
    /* 用于为函数传递参数，并不会真的被调用codeGen */
    return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                     std::to_string(this->getColumnNumber()) + " " +
                     "I'm not sure this should be made a codeGen");
}

// -----------------------DoubleNode-----------------------------
DoubleNode::DoubleNode(std::string _tokenValue) : ExpressionNode(_tokenValue) {
    sscanf(_tokenValue.c_str(), "%lf", &this->value);
}

std::string DoubleNode::getNodeTypeName() const { return "DoubleNode"; }

int DoubleNode::getValue() const { return this->value; }

Json::Value DoubleNode::jsonGen() const {
    Json::Value root;
    root["name"] = getNodeTypeName() + ":" + std::to_string(value);
    return root;
}

llvm::Value *DoubleNode::codeGen() {
    return llvm::ConstantFP::get(TheContext, llvm::APFloat(value));
}

// -----------------------IntNode-----------------------------
IntNode::IntNode(std::string _tokenValue) : ExpressionNode(_tokenValue) {
    sscanf(_tokenValue.c_str(), "%d", &this->value);
}

IntNode::IntNode(int v) : value(v) {}

double IntNode::getValue() const { return this->value; }

std::string IntNode::getNodeTypeName() const { return "IntNode"; }

Json::Value IntNode::jsonGen() const {
    Json::Value root;
    root["name"] = getNodeTypeName() + ":" + std::to_string(value);
    return root;
}

llvm::Value *IntNode::codeGen() {
    return ConstantInt::get(llvm::Type::getInt32Ty(TheContext), this->value,
                            true);
}

// -----------------------FuncNameAndArgsNode-----------------------------
FuncNameAndArgsNode::FuncNameAndArgsNode(IdentifierNode *nameIdentifier, VarDeclarationList *args)
        : ExpressionNode() {
    assert(nameIdentifier != nullptr);
    this->mFuncName = nameIdentifier;
    this->parasList = args;
}

// -----------------------UnaryOperatorNode-----------------------------
UnaryOperatorNode::UnaryOperatorNode(std::string _symbolName, int childrenNumber, ...)
        : ExpressionNode(_symbolName, 0) {
    va_list vl;
    va_start(vl, childrenNumber);
    for (int i = 0; i < childrenNumber; i++) {
        mChildren.push_back(va_arg(vl, Node *));
    }
    mSymbolName = (_symbolName),
    mIsTerminal = (false), mTokenValue = ("I am not a terminal.");
    mHandSide = dynamic_cast<ExpressionNode *>(mChildren[0]);
    op = _symbolName;
    if (mHandSide == NULL)
        throw ("castfail");
}

UnaryOperatorNode::UnaryOperatorNode(std::string _tokenValue, bool negligible)
        : ExpressionNode(_tokenValue, negligible) {}

std::string UnaryOperatorNode::getNodeTypeName() const {
    return std::string("UnaryOperatorNode  ") + (getSymbolName());
}

llvm::Value *UnaryOperatorNode::codeGen() {
    if (op == "~") {
        return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "\"" + op + "\" is not supported as an operator");
    } else if (op == "post++" || op == "post--" || op == "pre++" || op == "pre--") {
        int delta = 0;
        if (op == "post++" || op == "pre++") {
            delta = 1;
        } else {
            delta = -1;
        }
        auto res = mHandSide->getTypeAddress();
        Value *dst = res.address;
        if (!dst) {
            return LogErrorV(std::to_string(mHandSide->getLineNumber()) + ":" +
                             std::to_string(mHandSide->getColumnNumber()) + " " +
                             "\"" + mHandSide->getSymbolName() + "\" is not declared");
        }
        if (res.type != llvm::Type::IntegerTyID) {
            return LogErrorV(std::to_string(mHandSide->getLineNumber()) + ":" +
                             std::to_string(mHandSide->getColumnNumber()) + " " +
                             "only integer's ++/-- is supported");
        }
        Value *bef = mHandSide->codeGen();
        Value *aft = Builder.CreateAdd(bef, ConstantInt::get(llvm::Type::getInt32Ty(TheContext), delta,
                                                             true), "PPorMM");
        Builder.CreateStore(aft, dst);
        if (op == "post++" || op == "post--") {
            return bef;
        } else {
            return aft;
        }
    } else if (op == "!") {
        Value *OperandV = mHandSide->codeGen();
        if (!OperandV)
            return nullptr;
        bool isFloat = false;

        if (OperandV->getType()->getTypeID() == llvm::Type::DoubleTyID) {
            isFloat = true;
        }
        if (isFloat) {
            return LogErrorV(std::to_string(mHandSide->getLineNumber()) + ":" +
                             std::to_string(mHandSide->getColumnNumber()) + " " +
                             "invalid boolean operation with float number");
        }
        return Builder.CreateNot(OperandV, "notop");
    } else if (op == "-") {
        Value *OperandV = mHandSide->codeGen();
        if (!OperandV)
            return nullptr;
        bool isFloat = false;

        if (OperandV->getType()->getTypeID() == llvm::Type::DoubleTyID) {
            isFloat = true;
        }
        return isFloat ? Builder.CreateFNeg(OperandV, "fnotop")
                       : Builder.CreateFNeg(OperandV, "notop");
    }
}

// -----------------------BinaryOperatorNode-----------------------------
BinaryOperatorNode::BinaryOperatorNode(std::string _tokenValue, bool negligible)
        : ExpressionNode(_tokenValue, negligible) {}

BinaryOperatorNode::BinaryOperatorNode(std::string opType, ExpressionNode *lhs, ExpressionNode *rhs, bool isArithmetic)
        : ExpressionNode() {
    assert(lhs != nullptr);
    assert(rhs != nullptr);
    assert(opType != "");
    this->setType(Node::TYPE_INT);
    this->setKind(Node::KIND_CONSTANT); //defualt for non-arithmetic operation
    mLeftHandSide = lhs;
    mRightHandSide = rhs;
    op = opType;

    if (isArithmetic) // + - * / %
    {
        if (lhs->getType() == Node::TYPE_DOUBLE || rhs->getType() == Node::TYPE_DOUBLE) 
        {
            this->setType(Node::TYPE_DOUBLE);
        }
    }
}

std::string BinaryOperatorNode::getNodeTypeName() const { return op; }

Json::Value BinaryOperatorNode::jsonGen() const {
    Json::Value root;
    root["name"] = getNodeTypeName();
    root["children"].append(mLeftHandSide->jsonGen());
    root["children"].append(mRightHandSide->jsonGen());

    return root;
}

llvm::Value *BinaryOperatorNode::codeGen() {
    Value *Left = mLeftHandSide->codeGen();
    Value *Right = mRightHandSide->codeGen();

    if (Left->getType()->getTypeID() == llvm::Type::PointerTyID ||
        Right->getType()->getTypeID() == llvm::Type::PointerTyID) {
        if (Left->getType()->getTypeID() != Right->getType()->getTypeID() || op != "==") {
            return LogErrorV(std::to_string(mRightHandSide->getLineNumber()) + ":" +
                             std::to_string(mRightHandSide->getColumnNumber() - 1) + " " +
                             "invalid operation");
        } else {
            Type_and_Address l = mLeftHandSide->getTypeAddress();
            Type_and_Address r = mRightHandSide->getTypeAddress();
            int e = std::min(*l.arraySizes.rbegin(), *r.arraySizes.rbegin());
            auto ret = Builder.CreateICmpEQ(Builder.CreateLoad(Left, false, ""), Builder.CreateLoad(Right, false, ""));
            for (int i = 1; i < e; ++i) {
                auto ptr_l = mLeftHandSide->addrGen(i);
                auto ptr_r = mRightHandSide->addrGen(i);
                auto temp = Builder.CreateICmpEQ(Builder.CreateLoad(ptr_l, false, ""),
                                                 Builder.CreateLoad(ptr_r, false, ""));
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
    } else if (Left->getType()->getIntegerBitWidth() == 8 || Right->getType()->getIntegerBitWidth() == 8) {
        Left = Builder.CreateIntCast(Left, llvm::Type::getInt32Ty(TheContext), false, "8castl");
        Right = Builder.CreateIntCast(Right, llvm::Type::getInt32Ty(TheContext), false, "8castr");
    }

    if (op == "&&") { // and operation
        if (isFloat) {
            return LogErrorV((mRightHandSide->getLineNumber()) + ":" +
                             std::to_string(mRightHandSide->getColumnNumber() - 1) + " " +
                             "invalid boolean operation with float number");
        }
        return Builder.CreateAnd(Left, Right, "andop");
    } else if (op == "||") { // or operation
        if (isFloat) {
            return LogErrorV((mRightHandSide->getLineNumber()) + ":" +
                             std::to_string(mRightHandSide->getColumnNumber() - 1) + " " +
                             "invalid boolean operation with float number");
        }
        return Builder.CreateOr(Left, Right, "orop");
    } else if (op == "^" || op == "|" ||
               op == "&") { // bitwise operation, but not supported
        return LogErrorV((mRightHandSide->getLineNumber()) + ":" +
                         std::to_string(mRightHandSide->getColumnNumber() - 1) + " " +
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
            return LogErrorV((mRightHandSide->getLineNumber()) + ":" +
                             std::to_string(mRightHandSide->getColumnNumber() - 1) + " " +
                             "invalid boolean operation with float number");
        }
        return Builder.CreateAShr(Left, Right, "shrop");
    } else if (op == "<<") {
        if (isFloat) {
            return LogErrorV((mRightHandSide->getLineNumber()) + ":" +
                             std::to_string(mRightHandSide->getColumnNumber() - 1) + " " +
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
            return LogErrorV((mRightHandSide->getLineNumber()) + ":" +
                             std::to_string(mRightHandSide->getColumnNumber() - 1) + " " +
                             "invalid \"%\" operation with float number");
        }
        return Builder.CreateSRem(Left, Right, "smodop");
    } else {
        return LogErrorV((mRightHandSide->getLineNumber()) + ":" +
                         std::to_string(mRightHandSide->getColumnNumber() - 1) + " " +
                         "\"" + op + "\" is not supported as an operator");
    }
}

// -----------------------TenaryOperatorNode-----------------------------
TenaryOperatorNode::TenaryOperatorNode(std::string _symbolName, int childrenNumber, ...)
        : ExpressionNode(_symbolName, 0) {
    va_list vl;
    va_start(vl, childrenNumber);
    for (int i = 0; i < childrenNumber; i++) {
        mChildren.push_back(va_arg(vl, Node *));
    }
    mSymbolName = (_symbolName),
    mIsTerminal = (false), mTokenValue = ("I am not a terminal.");
    mLeftHandSide = dynamic_cast<ExpressionNode *>(mChildren[0]);
    mMidHandSide = dynamic_cast<ExpressionNode *>(mChildren[1]);
    mRightHandSide = dynamic_cast<ExpressionNode *>(mChildren[2]);
    op = _symbolName;
    if (mLeftHandSide == NULL || mRightHandSide == NULL ||
        mMidHandSide == NULL)
        throw ("castfail");
}

TenaryOperatorNode::TenaryOperatorNode(std::string _tokenValue, bool negligible)
        : ExpressionNode(_tokenValue, negligible) {}

std::string TenaryOperatorNode::getNodeTypeName() {
    return std::string("TenaryOperatorNode  ") + (getSymbolName());
}

llvm::Value *TenaryOperatorNode::codeGen() {
    return LogErrorV(std::to_string(mMidHandSide->getLineNumber()) + ":" +
                     std::to_string(mMidHandSide->getColumnNumber()-1) + " " +
                     "? ... : is not supported");
}

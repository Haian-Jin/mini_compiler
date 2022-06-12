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

std::unordered_map<std::string, std::unordered_map<std::string, Index_Type>*> structMap;


//---------------------------StructDeclarationNode------------------------------

std::string StructDeclarationNode::getNodeTypeName() const {
    return std::string("StructDeclarationBlock") +
           mStructName->getTokenValue();
}

Json::Value StructDeclarationNode::jsonGen() const {
    Json::Value root;
    root["name"] = getNodeTypeName();
    root["children"].append(mStructName->jsonGen());

    root["children"].append(mMembers->jsonGen());

    return root;
}

Value *StructDeclarationNode::codeGen() {
    std::vector<llvm::Type *> memberTypes;
    std::unordered_map<std::string, Index_Type>* memberMap = new std::unordered_map<std::string, Index_Type>;
    auto structType = StructType::create(TheContext, this->mStructName->getSymbolName());
    int i = 0;
    for (auto &member: mMembers->mStatementList) {
        auto v = (VariableDeclarationNode *) member;
        std::string ty = v->type->getSymbolName();
        std::string memberName = v->id->getSymbolName();
        llvm::Type::TypeID tor;
        Index_Type IT;
        if (!v->isArray()) {
            if (ty == "int") {
                memberTypes.push_back(llvm::Type::getInt32Ty(TheContext));
                tor = llvm::Type::IntegerTyID;
            } else if (ty == "float" || ty == "double") {
                memberTypes.push_back(llvm::Type::getDoubleTy(TheContext));
                tor = llvm::Type::DoubleTyID;
            } else if (ty == "char") {
                memberTypes.push_back(llvm::Type::getInt8Ty(TheContext));
                tor = llvm::Type::IntegerTyID;
            } else {
                return LogErrorV(
                        std::to_string(this->getLineNumber()) + ":" + std::to_string(this->getColumnNumber()) +
                        "type not supported");
            }
            IT.type = tor;
            IT.index = i;
            i++;
            (*memberMap)[memberName] = IT;
        } else {
            if (ty == "int") {
                memberTypes.push_back(llvm::Type::getInt32PtrTy(TheContext));
                tor = llvm::Type::IntegerTyID;
            } else if (ty == "float" || ty == "double") {
                memberTypes.push_back(llvm::Type::getDoublePtrTy(TheContext));
                tor = llvm::Type::DoubleTyID;
            } else if (ty == "char") {
                memberTypes.push_back(llvm::Type::getInt8PtrTy(TheContext));
                tor = llvm::Type::LabelTyID;
            } else {
                return LogErrorV(
                        std::to_string(this->getLineNumber()) + ":" + std::to_string(this->getColumnNumber()) +
                        "type not supported");
            }
            auto dimSize = v->getArraySizes();
            IT.type = tor;
            IT.index = i++;
            IT.isPtr = true;
            IT.arraySizes = dimSize;
            (*memberMap)[memberName] = IT;
        }
    }
    structTable[this->mStructName->getSymbolName()] = structType;
    structMap[this->mStructName->getSymbolName()] = memberMap;
    structType->setBody(memberTypes);
    return nullptr;
}

StructMemberNode::StructMemberNode(std::string _tokenValue, bool negligible)
        : ExpressionNode(_tokenValue, negligible) {}

StructMemberNode::StructMemberNode(std::string opType, IdentifierNode *lhs, IdentifierNode *rhs, bool isArithmetic)
        : ExpressionNode() {
    assert(lhs != nullptr);
    assert(rhs != nullptr);
    assert(opType != "");
    this->setType(Node::TYPE_INT);
    // this->setKind() HERE
    mVariableName = lhs;
    mMemberName = rhs;
    op = opType;
    if (isArithmetic) // + - * / %
    {
        if (lhs->getType() == Node::TYPE_DOUBLE ||
            rhs->getType() == Node::TYPE_DOUBLE) {
            this->setType(Node::TYPE_DOUBLE);
        }
    } else {
    }
}

std::string StructMemberNode::getNodeTypeName() const { return op; }

Json::Value StructMemberNode::jsonGen() const {
    Json::Value root;
    root["name"] = getNodeTypeName();
    root["children"].append(mVariableName->jsonGen());
    root["children"].append(mMemberName->jsonGen());

    return root;
}

llvm::Value *StructMemberNode::addrGen(int ind) {
    std::string name = mVariableName->getSymbolName();
    if(tableStack.top()->find(name) == tableStack.top()->end()) {
        return LogErrorV(std::to_string(mVariableName->getLineNumber()) + ":" +
                         std::to_string(mVariableName->getColumnNumber()) + " struct \'" + name +
                         "\' not declared");
    }
    Type_and_Address st = (*tableStack.top())[name];
    if (!st.isStruct) {
        if (tableStack.top()->find(name) == tableStack.top()->end()) {
            return LogErrorV(std::to_string(mVariableName->getLineNumber()) + ":" +
                             std::to_string(mVariableName->getColumnNumber()) + " variable \'" + name +
                             "\' is not a struct");
        }
    }
    std::string stName = st.stName;
    std::string rName = mMemberName->getSymbolName();
    auto map = structMap[stName];
    if(map->find(rName) == map->end()) {
        return LogErrorV(std::to_string(mVariableName->getLineNumber()) + ":" +
                         std::to_string(mVariableName->getColumnNumber()) + " \'" + rName +
                         "\' is not a member of \'" + stName + "\'");
    }
    auto stInd = (*map)[rName];
    std::vector<Value*> idx;
    idx.push_back(ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0, false));
    idx.push_back(ConstantInt::get(llvm::Type::getInt32Ty(TheContext), stInd.index, false));

    auto res = Builder.CreateInBoundsGEP(st.address, idx, "memberAddr");
    return res;
}

llvm::Value *StructMemberNode::codeGen() {
    auto ptr = this->addrGen();
    return Builder.CreateLoad(ptr, "memberValue");
}

ExpressionNode *StructMemberNode::getL() { return mVariableName; }

ExpressionNode *StructMemberNode::getR() { return mMemberName; }

std::string StructMemberAssignmentNode::getNodeTypeName() const {
    return std::string("StructMemberAssignmentNode ") + ("=");
}

StructMemberAssignmentNode::StructMemberAssignmentNode(StructMemberNode *lhs, ExpressionNode *rhs)
        : ExpressionNode("=", 0) {
    assert(lhs != nullptr);
    assert(rhs != nullptr);
    mLeftHandSide = lhs;
    mRightHandSide = rhs;
}

Json::Value StructMemberAssignmentNode::jsonGen() const {
    Json::Value root;
    root["name"] = getNodeTypeName();
    root["children"].append(mLeftHandSide->jsonGen());
    root["children"].append(mRightHandSide->jsonGen());
    return root;
}

llvm::Value *StructMemberAssignmentNode::codeGen() {
    auto ptr = mLeftHandSide->addrGen();
    auto rValue = mRightHandSide->codeGen();
    return Builder.CreateStore(rValue, ptr);
}

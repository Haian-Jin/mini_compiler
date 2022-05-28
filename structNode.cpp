//
// Created by Administrator on 5/28/2022.
//

#include"./cCompilerCommon.hpp"
#include "arrayNode.hpp"
#include "exprNode.hpp"
#include "ctrlNode.hpp"
#include "funcNode.hpp"
#include "statNode.hpp"
#include "structNode.hpp"


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
    auto structType = StructType::create(TheContext, this->mStructName->getSymbolName());
    for (auto &member: mMembers->mStatementList) {
        auto v = (VariableDeclarationNode *) member;
        std::string ty = v->type->getSymbolName();
        if (!v->isArray()) {
            if (ty == "int") {
                memberTypes.push_back(llvm::Type::getInt32Ty(TheContext));
            } else if (ty == "float" || ty == "double") {
                memberTypes.push_back(llvm::Type::getDoubleTy(TheContext));
            } else if (ty == "char") {
                memberTypes.push_back(llvm::Type::getInt8Ty(TheContext));
            } else {
                return LogErrorV(
                        std::to_string(this->getLineNumber()) + ":" + std::to_string(this->getColumnNumber()) +
                        "type not supported");
            }
        } else {
            if (ty == "int") {
                memberTypes.push_back(llvm::Type::getInt32PtrTy(TheContext));
            } else if (ty == "float" || ty == "double") {
                memberTypes.push_back(llvm::Type::getDoublePtrTy(TheContext));
            } else if (ty == "char") {
                memberTypes.push_back(llvm::Type::getInt8PtrTy(TheContext));
            } else {
                return LogErrorV(
                        std::to_string(this->getLineNumber()) + ":" + std::to_string(this->getColumnNumber()) +
                        "type not supported");
            }

        }
    }
    structTable[this->mStructName->getSymbolName()] = structType;
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

llvm::Value *StructMemberNode::codeGen() {
    /*
    TODO:
    */
    return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                     std::to_string(this->getColumnNumber()) + " " +
                     "Not supported yet");
}

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
    /*
    TODO:
    */
    return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                     std::to_string(this->getColumnNumber()) + " " +
                     "Not supported yet");
}

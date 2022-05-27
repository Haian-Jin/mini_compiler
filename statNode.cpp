//
// Created by Administrator on 5/28/2022.
//
#include "cCompilerCommon.hpp"
#include "arrayNode.hpp"
#include "exprNode.hpp"
#include "funcNode.hpp"
#include "ctrlNode.hpp"
#include "statNode.hpp"

Value *StatementNodesBlock::codeGen() {
    for (auto &iter: mStatementList) {
        iter->codeGen();
    }
    return nullptr;
}

void StatementNodesBlock::createMultiVarDeclaration(IdentifierNode *type, IdentifierNodeList *nameList) {
    assert(type != nullptr && nameList != nullptr);
    assert(type->isType());
    std::vector<IdentifierNode *> idenNameList =
            nameList->mIdentifierNodeList; // vector of identifiers, store the
    // name of the variables
    for (auto it = idenNameList.begin(); it != idenNameList.end(); it++) {
        // create a variable declaration
        StatementNode *varDecl = new VariableDeclarationNode(type, *it);
        mStatementList.push_back(varDecl);
    }
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
            if (!v->isArray()) {
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
    }
    structTable[this->mStructName->getSymbolName()] = structType;
    structType->setBody(memberTypes);
    return nullptr;
}

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

llvm::Value *NullStatementNode::codeGen() {
    return Builder.CreateAdd(
            ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0, true),
            ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0, true));
}

VariableDeclarationNode::VariableDeclarationNode(IdentifierNode *inType, IdentifierNode *id,
                                                 AssignmentNode *assignmentExpr): StatementNode()  {
    assert(inType != nullptr);
    assert(id != nullptr);
    this->type = inType;
    this->id = id;
    this->assignmentExpr = assignmentExpr;
    this->setKind(Node::KIND_VARIABLE);
    id->setType(inType->getType());
    this->setType(id/*inType->getType()*/);
}

Json::Value VariableDeclarationNode::jsonGen() const {
    Json::Value root;
    root["name"] = getNodeTypeName();
    root["children"].append(type->jsonGen());
    root["children"].append(id->jsonGen());

    if (assignmentExpr != nullptr) {
        root["children"].append(assignmentExpr->jsonGen());
    }
    return root;
}

llvm::Value *VariableDeclarationNode::codeGen() {
    if (!type->isType()) {
        return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "This type is not supported");
    }
    std::string ty = type->getSymbolName();
    //std::cout<<"typeName: "<<ty<<std::endl;
    Value *res;
    llvm::Type::TypeID tor;
    if (!this->id->isArray()) {
        if (tableStack.empty()) {
            if (ty == "int" || ty == "short") {
                res = new llvm::GlobalVariable(*TheModule, llvm::Type::getInt32Ty(TheContext), false,
                                               llvm::GlobalValue::PrivateLinkage, con_0(), id->getSymbolName());
                tor = llvm::Type::IntegerTyID;
            } else if (ty == "float" || ty == "double") {
                res = new llvm::GlobalVariable(*TheModule, llvm::Type::getDoubleTy(TheContext), false,
                                               llvm::GlobalValue::PrivateLinkage, con_0(), id->getSymbolName());
                tor = llvm::Type::DoubleTyID;
            } else if (ty == "char") {
                res = new llvm::GlobalVariable(*TheModule, llvm::Type::getInt8Ty(TheContext), false,
                                               llvm::GlobalValue::PrivateLinkage, con_0(), id->getSymbolName());
                tor = llvm::Type::IntegerTyID;
            } else {
                return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                                 std::to_string(this->getColumnNumber()) + " " +
                                 "This type is not supported");
            }
            Type_and_Address ret = {tor, res};
            variableTable[this->id->getSymbolName()] = ret;
        } else {
            if (ty == "int") {
                res = Builder.CreateAlloca(llvm::Type::getInt32Ty(TheContext));
                tor = llvm::Type::IntegerTyID;
            } else if (ty == "float" || ty == "double") {
                res = Builder.CreateAlloca(llvm::Type::getDoubleTy(TheContext));
                tor = llvm::Type::DoubleTyID;
            } else if (ty=="char") {
                res = Builder.CreateAlloca(llvm::Type::getInt8Ty(TheContext));
                tor = llvm::Type::IntegerTyID;
            } else {
                return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                                 std::to_string(this->getColumnNumber()) + " " +
                                 "This type is not supported");
            }
            Type_and_Address ret = {tor, res};
            (*(tableStack.top()))[this->id->getSymbolName()] = ret;

            if (this->assignmentExpr != nullptr) {
                this->assignmentExpr->codeGen();
            }
        }
        return res;
    } else { /* is array */
        auto dimsize = this->getArraySizes();
        int array_size = 1;
        for (int a: dimsize) {
            array_size *= a;
        }
        llvm::ArrayType *array_type = nullptr;
//            Value *ArraySize = ConstantInt::get(llvm::Type::getInt32Ty(TheContext), array_size, false);
        if (tableStack.empty()) {
            if (ty == "int") {
                array_type = llvm::ArrayType::get(llvm::Type::getInt32Ty(TheContext), array_size);

                tor = llvm::Type::IntegerTyID;
            } else if (ty == "float" || ty == "double") {
                array_type = llvm::ArrayType::get(llvm::Type::getDoubleTy(TheContext), array_size);
                tor = llvm::Type::DoubleTyID;
            } else if (ty == "char") {
                array_type = llvm::ArrayType::get(llvm::Type::getInt8Ty(TheContext), array_size);
                tor = llvm::Type::LabelTyID; //I didn't find a type for char, so I use Label for it
            } else {
                return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                                 std::to_string(this->getColumnNumber()) + " " +
                                 "This type is not supported");
            }
            res = new llvm::GlobalVariable(*TheModule, array_type, false, llvm::GlobalValue::PrivateLinkage, 0,
                                           id->getSymbolName());
            std::vector<llvm::Constant*> const_array_elems;
            for (int i = 0; i < array_size; ++i) {
                const_array_elems.push_back(con_0());
            }
            llvm::Constant* const_array = llvm::ConstantArray::get(array_type, const_array_elems);
            ((llvm::GlobalVariable*)res)->setInitializer(const_array);
            Type_and_Address ret = {tor, res, true, dimsize};
            variableTable[this->id->getSymbolName()] = ret;
        } else {
            Value *ArraySize = ConstantInt::get(llvm::Type::getInt32Ty(TheContext), array_size, false);
            if (ty == "int") {
                auto arrayType = llvm::ArrayType::get(llvm::Type::getInt32Ty(TheContext), array_size);
                res = Builder.CreateAlloca(arrayType,
                                           ArraySize, id->getSymbolName());
                tor = llvm::Type::IntegerTyID;
            } else if (ty == "float" || ty == "double") {
                auto arrayType = llvm::ArrayType::get(llvm::Type::getDoubleTy(TheContext), array_size);
                res = Builder.CreateAlloca(arrayType,
                                           ArraySize, id->getSymbolName());
                tor = llvm::Type::DoubleTyID;
            } else if (ty == "char") {
                auto arrayType = llvm::ArrayType::get(llvm::Type::getInt8Ty(TheContext), array_size);
//                    std::vector<llvm::Constant*> const_array_elems;
//                    for (int i = 0; i < array_size; ++i) {
//                        const_array_elems.push_back(con_0());
//                    }
//                    llvm::Constant* const_array = llvm::ConstantArray::get(array_type, const_array_elems);
                res = Builder.CreateAlloca(arrayType,
                                           ArraySize, id->getSymbolName());
                tor = llvm::Type::LabelTyID; //for char
                for (int i = 0; i < array_size; ++i) {
                    llvm::ArrayRef<llvm::Value *> ga{llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0),
                                                     ConstantInt::get(llvm::Type::getInt32Ty(TheContext), i, false)};
                    Builder.CreateAlignedStore(ConstantInt::get(llvm::Type::getInt8Ty(TheContext), 0, true),
                                               Builder.CreateInBoundsGEP(res, ga, "elementPointer"), 1);
                }
            } else {
                res = LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                                std::to_string(this->getColumnNumber()) + " " +
                                "This type is not supported");
                tor = llvm::Type::VoidTyID;
            }
            (*tableStack.top())[this->id->getSymbolName()] = {tor, res, true, dimsize};
        }
        return res;
    }
}

Value *ExpressionStatementNode::codeGen() {
    return this->mExpression->codeGen();
}

Json::Value ExpressionStatementNode::jsonGen() const {
    Json::Value root;
    root["name"] = getNodeTypeName();
    root["children"].append(mExpression->jsonGen());
    return root;
}

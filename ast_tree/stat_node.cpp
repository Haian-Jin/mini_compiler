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

// ------------------------------StatementNode----------------------------------------
StatementNode::StatementNode() : Node() {}

std::string StatementNode::getNodeTypeName() const { return "StatementNode"; }

Json::Value StatementNode::jsonGen() const {
    Json::Value r;
    r["name"] = getNodeTypeName();
    return r;
}

llvm::Value *StatementNode::codeGen() {
    return nullptr;
}

// ------------------------------VariableDeclarationNode----------------------------------------
VariableDeclarationNode::VariableDeclarationNode(IdentifierNode *inType, IdentifierNode *id,
                                                 AssignmentNode *assignmentExpr) : StatementNode() {
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
    std::string name = id->getSymbolName();
    if(tableStack.empty()) {
        if(variableTable.find(name)!=variableTable.end()) {
            return LogErrorV(std::to_string(id->getLineNumber()) + ":" +
                             std::to_string(id->getColumnNumber()) + " " +
                             "Redefinition of" + "\'"+ name + "\'");
        }
    } else {
        if(tableStack.top()->find(name)!=tableStack.top()->end()) {
            return LogErrorV(std::to_string(id->getLineNumber()) + ":" +
                             std::to_string(id->getColumnNumber()) + " " +
                             "Redefinition of" + "\'" + name + "\'");
        }
    }
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
                if (structTable.find(ty)!=structTable.end()) {
                    return LogErrorV(std::to_string(id->getLineNumber()) + ":" +
                                     std::to_string(id->getColumnNumber()) + " " +
                                     "Global structure is not supported");
                } else {
                    return LogErrorV(std::to_string(id->getLineNumber()) + ":" +
                                     std::to_string(id->getColumnNumber()) + " " +
                                     "This type is not supported");
                }
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
            } else if (ty == "char") {
                res = Builder.CreateAlloca(llvm::Type::getInt8Ty(TheContext));
                tor = llvm::Type::IntegerTyID;
            } else {
                if (structTable.find(ty)!=structTable.end()) {
                    res = Builder.CreateAlloca(structTable[ty]);
                    tor = llvm::Type::StructTyID;

                    for (auto & item: *(structMap[ty])) {
                        if (item.second.isPtr) {
                            return LogErrorV(std::to_string(id->getLineNumber()) + ":" +
                                             std::to_string(id->getColumnNumber()) + " " +
                                             "This type is not supported");
//                            llvm::Value* addr = nullptr;
//                            auto dimSize = item.second.arraySizes;
//                            int array_size = 1;
//                            for (int a: dimSize) {
//                                array_size *= a;
//                            }
//                            Value *ArraySize = ConstantInt::get(llvm::Type::getInt32Ty(TheContext), array_size, false);
//                            if (item.second.type == llvm::Type::IntegerTyID) {
//                                auto arrayType = llvm::ArrayType::get(llvm::Type::getInt32Ty(TheContext), array_size);
//                                addr = Builder.CreateAlloca(arrayType,
//                                                           ArraySize, id->getSymbolName()+"."+item.first);
//                            } else if (item.second.type == llvm::Type::DoubleTyID) {
//                                auto arrayType = llvm::ArrayType::get(llvm::Type::getDoubleTy(TheContext), array_size);
//                                addr = Builder.CreateAlloca(arrayType,
//                                                            ArraySize, id->getSymbolName()+"."+item.first);
//                            } else if (item.second.type == llvm::Type::LabelTyID) {
//                                auto arrayType = llvm::ArrayType::get(llvm::Type::getInt8Ty(TheContext), array_size);
//                                addr = Builder.CreateAlloca(arrayType,
//                                                            ArraySize, id->getSymbolName()+"."+item.first);
//
//                            }
//
//                          Builder.CreateStore(addr, )
                        }
                        Type_and_Address ret = {tor, res};
                        ret.isStruct = true;
                        ret.stName = ty;
                        (*tableStack.top())[this->id->getSymbolName()] = ret;
                    }

                } else {
                    return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                                     std::to_string(this->getColumnNumber()) + " " +
                                     "This type is not supported");
                }
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
            std::vector<llvm::Constant *> const_array_elems;
            for (int i = 0; i < array_size; ++i) {
                const_array_elems.push_back(con_0());
            }
            llvm::Constant *const_array = llvm::ConstantArray::get(array_type, const_array_elems);
            ((llvm::GlobalVariable *) res)->setInitializer(const_array);
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

std::string VariableDeclarationNode::getNodeTypeName() const {
    return "VariableDeclarationNode";
}

// ------------------------------VarDeclarationList----------------------------------------
std::string VarDeclarationList::getNodeTypeName() const { return "VarDeclarationList"; }

Json::Value VarDeclarationList::jsonGen() const {
    Json::Value root;
    root["name"] = getNodeTypeName();
    for (auto it = mVarDeclarationList.begin();
         it != mVarDeclarationList.end(); it++) {
        root["children"].append((*it)->jsonGen());
    }
    return root;
}

Value *VarDeclarationList::codeGen() {
    /* This node is used for func declaration, no need to codeGen() */
    return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                     std::to_string(this->getColumnNumber()) + " " +
                     "No need to codeGen this");
}


// ------------------------------StatementNodesBlock----------------------------------------
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

std::string StatementNodesBlock::getNodeTypeName() const { return "StatementsBlock"; }

Json::Value StatementNodesBlock::jsonGen() const {
    Json::Value root;
    root["name"] = getNodeTypeName();
    for (auto it = mStatementList.begin(); it != mStatementList.end();
         it++) {
        root["children"].append((*it)->jsonGen());
    }
    return root;
}

void StatementNodesBlock::addStatementNode(StatementNode *statementNode) {
    assert(statementNode != nullptr);
    mStatementList.push_back(statementNode);
}

void StatementNodesBlock::mergeStatements(StatementNodesBlock *to_merge) {
    assert(to_merge != nullptr);
    this->mStatementList.insert(this->mStatementList.end(),
                                to_merge->mStatementList.begin(),
                                to_merge->mStatementList.end());
}

Value *StatementNodesBlock::codeGen() {
    for (auto &iter: mStatementList) {
        iter->codeGen();
    }
    return nullptr;
}

// ------------------------------NullStatementNode----------------------------------------
llvm::Value *NullStatementNode::codeGen() {
    return Builder.CreateAdd(
            ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0, true),
            ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0, true));
}

std::string NullStatementNode::getNodeTypeName() const { return "NullStatementNode"; }

Json::Value NullStatementNode::jsonGen() const {
    Json::Value root;
    root["name"] = getNodeTypeName();
    return root;
}

// ------------------------------ExpressionStatementNode----------------------------------------
Value *ExpressionStatementNode::codeGen() {
    return this->mExpression->codeGen();
}

Json::Value ExpressionStatementNode::jsonGen() const {
    Json::Value root;
    root["name"] = getNodeTypeName();
    root["children"].append(mExpression->jsonGen());
    return root;
}

ExpressionStatementNode::ExpressionStatementNode(ExpressionNode *expression) : StatementNode() {
    assert(expression != nullptr);
    this->mExpression = expression;
}

std::string ExpressionStatementNode::getNodeTypeName() const {
    return "ExpressionStatementNode";
}




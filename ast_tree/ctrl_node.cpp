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

//--------------------------GlobalDeclarationNode--------------------------------

GlobalDeclarationNode::GlobalDeclarationNode() : StatementNode() {}

GlobalDeclarationNode::GlobalDeclarationNode(StatementNodesBlock *toCopy) : StatementNode() {
    for (auto it = toCopy->mStatementList.begin();
         it != toCopy->mStatementList.end(); ++it) {
        mGlobalStatementList.push_back(*it);
    }
}

std::string GlobalDeclarationNode::getNodeTypeName() const { return "CentralBlock"; }

Json::Value GlobalDeclarationNode::jsonGen() const {
    Json::Value root;
    root["name"] = getNodeTypeName();
    for (auto it = mGlobalStatementList.begin();
         it != mGlobalStatementList.end(); it++) {
        root["children"].append((*it)->jsonGen());
    }
    return root;
}

llvm::Value *GlobalDeclarationNode::codeGen() {
    Value *ret = nullptr;
    TheModule = new Module("test", TheContext);
    for (auto &iter: mGlobalStatementList) {
        ret = iter->codeGen();
    }
    return ret;
}

void GlobalDeclarationNode::mergeGlobalStatements(StatementNodesBlock *to_merge) {
    assert(to_merge != nullptr);
    this->mGlobalStatementList.insert(mGlobalStatementList.end(), to_merge->mStatementList.begin(),
                                      to_merge->mStatementList.end());
}

//---------------------------ReturnStatementNode----------------------------------

ReturnStatementNode::ReturnStatementNode(ExpressionNode *returnV)
        : StatementNode(), returnValue(returnV) {}

std::string ReturnStatementNode::getTypeName() const { return "ReturnStatement"; }

Json::Value ReturnStatementNode::jsonGen() const {
    Json::Value root;
    root["name"] = getTypeName();
    if (returnValue != nullptr)
        root["children"].append(returnValue->jsonGen());
    return root;
}

llvm::Value *ReturnStatementNode::codeGen() {
    Value *ret = returnValue->codeGen();
    Builder.CreateRet(ret);
    return nullptr;
}

//----------------------------IfStatementNode-------------------------------------------

IfStatementNode::IfStatementNode(ExpressionStatementNode *condition, StatementNodesBlock *trueStatements,
                                 StatementNodesBlock *falseStatements) : StatementNode(), conditionStatement(condition),
                                                                         trueBody(trueStatements),
                                                                         falseBody(falseStatements) {
    assert(conditionStatement != nullptr);
    assert(trueBody != nullptr);
}

Json::Value IfStatementNode::jsonGen() const {
    Json::Value root;
    root["name"] = getTypeName();
    root["children"].append(conditionStatement->jsonGen());
    root["children"].append(trueBody->jsonGen());
    if (falseBody != nullptr)
        root["children"].append(falseBody->jsonGen());
    return root;
}

std::string IfStatementNode::getTypeName() const { return "NIfStatement"; }

llvm::Value *IfStatementNode::codeGen() {
    auto conditionExpressionValue = conditionStatement->codeGen();
    if (!conditionExpressionValue)
        return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "lack of condition");

    auto theFunction = Builder.GetInsertBlock()->getParent();

    auto trueBlock = llvm::BasicBlock::Create(
            TheContext, "then", theFunction);
    auto falseBlock = llvm::BasicBlock::Create(TheContext, "else");
    auto mergeBlock = llvm::BasicBlock::Create(TheContext, "ifcont");
    if (this->falseBody) {
        Builder.CreateCondBr(CastBool(conditionExpressionValue), trueBlock,
                             falseBlock);
    } else {
        Builder.CreateCondBr(CastBool(conditionExpressionValue), trueBlock,
                             mergeBlock);
    }

    Builder.SetInsertPoint(trueBlock);

    auto tempTable = inheritTable();
    tableStack.push(tempTable);

    this->trueBody->codeGen();

    tableStack.pop();

    trueBlock = Builder.GetInsertBlock();
    if (trueBlock->getTerminator() == nullptr) {
        Builder.CreateBr(mergeBlock);
    }

    if (this->falseBody) {
        theFunction->getBasicBlockList().push_back(falseBlock);
        Builder.SetInsertPoint(falseBlock);

        auto tempTable = inheritTable();
        tableStack.push(tempTable);

        this->falseBody->codeGen();

        tableStack.pop();

        Builder.CreateBr(mergeBlock);
    }

    theFunction->getBasicBlockList().push_back(mergeBlock);
    Builder.SetInsertPoint(mergeBlock);

    return nullptr;
}

//----------------------------WhileStatementNode----------------------------------------

WhileStatementNode::WhileStatementNode(ExpressionStatementNode *condition, StatementNodesBlock *body)
        : StatementNode(), conditionStatement(condition), whileBody(body) {
    assert(conditionStatement != nullptr);
    assert(whileBody != nullptr);
}

Json::Value WhileStatementNode::jsonGen() const {
    Json::Value root;
    root["name"] = getTypeName();

    root["children"].append(conditionStatement->jsonGen());
    root["children"].append(whileBody->jsonGen());

    return root;
}

std::string WhileStatementNode::getTypeName() const {
    return std::string("WhileStatementNode");
}

llvm::Value *WhileStatementNode::codeGen() {
    Function *theFunction = Builder.GetInsertBlock()->getParent();

    BasicBlock *loopBody = BasicBlock::Create(TheContext, "whilebody", theFunction);
    BasicBlock *after = BasicBlock::Create(TheContext, "whilecont");

    Value *cond = this->conditionStatement->codeGen();
    if (!cond) {
        return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "lack of condition");
    }

    Builder.CreateCondBr(CastBool(cond), loopBody, after);

    Builder.SetInsertPoint(loopBody);

    auto tempTable = inheritTable();
    tableStack.push(tempTable);

    this->whileBody->codeGen();

    tableStack.pop();

    cond = this->conditionStatement->codeGen();
    Builder.CreateCondBr(CastBool(cond), loopBody, after);

    theFunction->getBasicBlockList().push_back(after);
    Builder.SetInsertPoint(after);

    return nullptr;
}

//-------------------------------ForStatementNode--------------------------------------

ForStatementNode::ForStatementNode(ExpressionStatementNode *initial, ExpressionStatementNode *condition,
                                   ExpressionStatementNode *progress, StatementNodesBlock *body)
        : StatementNode(), initialStatement(initial),
          conditionStatement(condition), progressStatement(progress),
          forBody(body) {
    assert(initialStatement != nullptr);
    assert(conditionStatement != nullptr);
    assert(progressStatement != nullptr);
    assert(forBody != nullptr);
}

std::string ForStatementNode::getTypeName() const {
    return std::string("ForStatementNode");
}

llvm::Value *ForStatementNode::codeGen() {
    Function *theFunction = Builder.GetInsertBlock()->getParent();

    BasicBlock *loopBody = BasicBlock::Create(TheContext, "forbody", theFunction);
    BasicBlock *after = BasicBlock::Create(TheContext, "forcont");

    if (this->initialStatement) {
        this->initialStatement->codeGen();
    }

    Value *cond = this->conditionStatement->codeGen();
    if (!cond) {
        return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "lack of condition");
    }

    Builder.CreateCondBr(CastBool(cond), loopBody, after);

    Builder.SetInsertPoint(loopBody);

    auto tempTable = inheritTable();
    tableStack.push(tempTable);

    this->forBody->codeGen();

    tableStack.pop();

    if (this->progressStatement) {
        this->progressStatement->codeGen();
    }

    cond = this->conditionStatement->codeGen();
    Builder.CreateCondBr(CastBool(cond), loopBody, after);

    theFunction->getBasicBlockList().push_back(after);
    Builder.SetInsertPoint(after);

    return nullptr;
}

Json::Value ForStatementNode::jsonGen() const {
    Json::Value root;
    root["name"] = getTypeName();

    root["children"].append(initialStatement->jsonGen());
    root["children"].append(conditionStatement->jsonGen());
    root["children"].append(progressStatement->jsonGen());
    root["children"].append(forBody->jsonGen());

    return root;
}

//-----------------------------------ContinueStatementNode---------------------

Json::Value ContinueStatementNode::jsonGen() const {
    Json::Value root;
    root["name"] = getTypeName();
    return root;
}

ContinueStatementNode::ContinueStatementNode() : StatementNode() {}

std::string ContinueStatementNode::getTypeName() const { return "ContinueStatement"; }

//-----------------------------------BreakStatementNode---------------------------

Json::Value BreakStatementNode::jsonGen() const {
    Json::Value root;
    root["name"] = getTypeName();
    return root;
}

BreakStatementNode::BreakStatementNode() : StatementNode() {}

std::string BreakStatementNode::getTypeName() const { return "BreakStatement"; }

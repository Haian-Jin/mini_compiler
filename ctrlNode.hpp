#pragma once
#include "cCompilerCommon.hpp"
#include "statNode.hpp"

class StatementNode;
class StatementNodesBlock;
class ExpressionStatementNode;

class GlobalDeclarationNode : public StatementNode {
    /*
        this node represents the whole entity of user's code
        the root Node of the AST
        the beginning of the DFS of the codeGen()
    */
public:
    std::vector<StatementNode *> mGlobalStatementList;

    GlobalDeclarationNode();

    // copy from statements block
    GlobalDeclarationNode(StatementNodesBlock *toCopy);

    std::string getNodeTypeName() const override;

    Json::Value jsonGen() const override;

    /* codeGen():
        call codeGen of all its sons in mGlobalStatementList in order
        equals to a DSF in AST to generate IR codes
     */
    llvm::Value *codeGen() override;

    void mergeGlobalStatements(StatementNodesBlock *to_merge);
};

class ForStatementNode : public StatementNode {
    //This node is used to represent the for structure
public:
    ExpressionStatementNode *initialStatement;
    ExpressionStatementNode *conditionStatement;
    ExpressionStatementNode *progressStatement;
    StatementNodesBlock *forBody;

    ForStatementNode(ExpressionStatementNode *initial,
                     ExpressionStatementNode *condition,
                     ExpressionStatementNode *progress,
                     StatementNodesBlock *body);

    virtual std::string getTypeName() const;

    Json::Value jsonGen() const override;

    /* codeGen():
        generate 2 insert blocks
        generate IR code of the body block
        the for body should have its own symbol table
        which is copied form the symbol table now
        the progress statement should be right after the body
        generate IR codes to judge and jump based on the condition statement
    */
    llvm::Value *codeGen() override;
};

class WhileStatementNode : public StatementNode {
    //This node is used to represent the while structure
public:
    ExpressionStatementNode *conditionStatement;
    StatementNodesBlock *whileBody;

    WhileStatementNode(ExpressionStatementNode *condition,
                       StatementNodesBlock *body);

    virtual std::string getTypeName() const;

    Json::Value jsonGen() const override;

    /* codeGen():
        generate 2 insert blocks
        generate IR code of the body block
        the while body should have its own symbol table
        which is copied form the symbol table now
        generate IR codes to judge and jump based on the condition statement
    */
    llvm::Value *codeGen() override;
};

class IfStatementNode : public StatementNode {
    //This node is used to represent the if structure
public:
    ExpressionStatementNode *conditionStatement;
    StatementNodesBlock *trueBody;  // if (True), do this, cannot be null
    StatementNodesBlock *falseBody; // else, do this, can be null

    IfStatementNode(ExpressionStatementNode *condition,
                    StatementNodesBlock *trueStatements,
                    StatementNodesBlock *falseStatements = nullptr);



    virtual std::string getTypeName() const;

    Json::Value jsonGen() const override;

    /* codeGen():
        generate 2 or 3 insert blocks (based on "else")
        generate IR codes of each block except for the after block
        those blocks should have their own symbol tables
        which are copied form the symbol table now
        generate IR codes to judge and jump
    */
    llvm::Value *codeGen() override;
};

class ReturnStatementNode : public StatementNode {
    //Node for instructions that return some value for function
public:
    ExpressionNode *returnValue;

    ReturnStatementNode(ExpressionNode *returnV = nullptr);

    virtual std::string getTypeName() const;

    Json::Value jsonGen() const override;

    /* codeGen():
        generate the r value should be returned
        call function of llvm's llvm::builder<>::CreateRet() to return that r value
    */
    llvm::Value *codeGen() override;
};

class ContinueStatementNode : public StatementNode {
    // Not implemented yet
public:
    ContinueStatementNode();

    virtual std::string getTypeName() const;

    Json::Value jsonGen() const override;
};

class BreakStatementNode : public StatementNode {
    // Not implemented yet
public:
    BreakStatementNode();

    virtual std::string getTypeName() const;

    Json::Value jsonGen() const override;
};

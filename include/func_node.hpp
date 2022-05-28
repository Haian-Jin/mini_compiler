#pragma once
#include "ast_node.hpp"

class StatementNode;
class IdentifierNode;
class ExpressionNode;
class VarDeclarationList;
class StatementNodesBlock;
class FuncNameAndArgsNode;
class StatementNodesBlock;

class FunctionDeclarationNode : public StatementNode {
    //declare a function
    //declaration and definition of functions must be in the same place
    //function can't be defined in another function
public:
    IdentifierNode *type;          // return type
    IdentifierNode *id;            // function name
    VarDeclarationList *parasList; // function args, be nullptr if no args
    StatementNodesBlock *body;     // function body

    FunctionDeclarationNode(IdentifierNode *type,
                            FuncNameAndArgsNode *name_and_args,
                            StatementNodesBlock *body);

    std::string getNodeTypeName() const override;

    Json::Value jsonGen() const override;

    //create the prototype of the function and store it in the module
    llvm::Value *codeGen() override;
};

class FunctionCallNode : public ExpressionNode {
    //calling function
public:
    FunctionCallNode(std::string _symbolName, int childrenNumber, ...);

    FunctionCallNode(std::string _tokenValue, bool negligible = false);

    std::vector<ExpressionNode *> getArguments() const;

    void addArgument(Node *c);

    std::string getNodeTypeName() const override;

    Json::Value jsonGen() const override;

    /* codeGen_p():
        call C's printf as an external function
    */
    llvm::Value* codeGen_p();

    /* codeGen_s():
        call C's scanf as an external function
    */
    llvm::Value* codeGen_s();

    /* codeGen():
        judge if it is calling to printf or scanf or other user-defined function
        generate IR codes to call that function
    */
    llvm::Value *codeGen() override;

private:
    IdentifierNode *mFunctionName;
    std::vector<ExpressionNode *> *mArguments;
};


//
// Created by Administrator on 5/28/2022.
//
#include "include/ast_node.hpp"
#include "include/expr_node.hpp"
#include "include/ctrl_node.hpp"
#include "include/stat_node.hpp"
#include "include/array_node.hpp"
#include "include/func_node.hpp"
#include "include/struct_node.hpp"

//-----------------------FunctionDeclarationNode------------------------------------------------------

FunctionDeclarationNode::FunctionDeclarationNode(IdentifierNode *type, FuncNameAndArgsNode *name_and_args,
                                                 StatementNodesBlock *body)
        : StatementNode() {
    assert(type != nullptr);
    assert(name_and_args != nullptr);
    assert(body != nullptr);
    assert(type->isType());
    this->type = type;
    this->id = name_and_args->mFuncName;
    this->parasList = name_and_args->parasList;
    this->body = body;
}

Json::Value FunctionDeclarationNode::jsonGen() const {

    Json::Value root;
    root["name"] = getNodeTypeName();

    Json::Value returnType;
    returnType["name"] = std::string("ReturnType");
    returnType["children"].append(type->jsonGen());

    Json::Value funcName;
    funcName["name"] = std::string("FuncName");
    funcName["children"].append(id->jsonGen());

    Json::Value paras;
    paras["name"] = std::string("Paras");
    if (this->parasList != nullptr) {
        for (auto it = parasList->mVarDeclarationList.begin();
             it != parasList->mVarDeclarationList.end(); it++) {
            paras["children"].append((*it)->jsonGen());
        }
    }

    Json::Value funcBody;
    funcBody["name"] = std::string("Body");
    funcBody["children"].append(body->jsonGen());

    root["children"].append(returnType);
    root["children"].append(funcName);
    root["children"].append(paras);
    root["children"].append(funcBody);

    return root;
}

std::string FunctionDeclarationNode::getNodeTypeName() const {
    return "FunctionDeclarationNode";
}

llvm::Value *FunctionDeclarationNode::codeGen() {
    std::vector<llvm::Type *> argTypes;
    if (parasList) {
        auto temp = parasList->mVarDeclarationList;

        for (auto &i: temp) {
            std::string ty = i->type->getSymbolName();
            if (ty == "int" || ty == "char") {
                argTypes.push_back(llvm::Type::getInt32Ty(TheContext));
            } else if (ty == "float" || ty == "double") {
                argTypes.push_back(llvm::Type::getDoubleTy(TheContext));
            } else {
                return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                                 std::to_string(this->getColumnNumber()) + " " +
                                 "A type is not supported in the parameters");
            }
        }
    }
    llvm::Type *ret;

    std::string ty = this->type->getSymbolName();
    if (ty == "int" || ty == "char") {
        ret = (llvm::Type::getInt32Ty(TheContext));
    } else if (ty == "float" || ty == "double") {
        ret = (llvm::Type::getDoubleTy(TheContext));
    } else if (ty == "void") {
        ret = llvm::Type::getVoidTy(TheContext);
    } else {
        return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " + ty +
                         " type is not supported");
    }
    FunctionType *functionType =
            llvm::FunctionType::get(ret, argTypes, false);
    // std::cout<<"functionName: "<<id->getSymbolName()<<'\n';

    Function *function = NULL;
    if (id->getSymbolName() == "main") {
        function = llvm::Function::Create(
                functionType, llvm::GlobalValue::ExternalLinkage,
                "Main", TheModule);
    } else {
        function = llvm::Function::Create(
                functionType, llvm::GlobalValue::ExternalLinkage,
                id->getSymbolName(), TheModule);
    }
    BasicBlock *basicBlock =
            BasicBlock::Create(TheContext, id->getSymbolName(), function, nullptr);
    Builder.SetInsertPoint(basicBlock);
    auto *argTable =
            new std::unordered_map<std::string, Type_and_Address>;
    tableStack.push(argTable);
    if (parasList) {
        auto temp = parasList->mVarDeclarationList;

        auto iter_proto = temp.begin();
        for (auto &iter_func: function->args()) {
            iter_func.setName((*iter_proto)->id->getSymbolName());
            Value *arg = (*iter_proto)->codeGen();
            Builder.CreateStore(&iter_func, arg, false);
            iter_proto++;
        }
    }

    this->body->codeGen();

    tableStack.pop();

    return function;
}

//-----------------------FunctionCallNode------------------------------------------------------

FunctionCallNode::FunctionCallNode(std::string _symbolName, int childrenNumber, ...) : ExpressionNode() {
    va_list vl;
    va_start(vl, childrenNumber);
    for (int i = 0; i < childrenNumber; i++) {
        mChildren.push_back(va_arg(vl, Node *));
    }
    mFunctionName = dynamic_cast<IdentifierNode *>(mChildren[0]);
    mArguments = new std::vector<ExpressionNode *>();
    mSymbolName = (_symbolName),
    mIsTerminal = (false), mTokenValue = ("I am not a terminal.");
}

std::string FunctionCallNode::getNodeTypeName() const {
    return std::string("FunctionNode: ") + mFunctionName->getTokenValue();
}

Json::Value FunctionCallNode::jsonGen() const {
    Json::Value r;
    r["name"] = getNodeTypeName();
    // r["children"].append(mFunctionName->jsonGen());
    for (auto i: *mArguments) {
        std::cout << "oo\n";
        r["children"].append(i->jsonGen());
    }
    return r;
}

FunctionCallNode::FunctionCallNode(std::string _tokenValue, bool negligible)
        : ExpressionNode(),mArguments(new std::vector<ExpressionNode *>()) {}

std::vector<ExpressionNode *> FunctionCallNode::getArguments() const { return *mArguments; }

void FunctionCallNode::addArgument(Node *c) {
    assert(dynamic_cast<ExpressionNode *>(c) != NULL);
    mArguments->push_back(dynamic_cast<ExpressionNode *>(c));
}

llvm::Value *FunctionCallNode::codeGen_s() {
    Value *res = nullptr;
    if (mArguments) {
        Function *func_scanf = TheModule->getFunction("scanf");
        if (!func_scanf) {
            PointerType *Pty = PointerType::get(IntegerType::get(TheContext, 8), 0);
            FunctionType *FuncTy9 = FunctionType::get(IntegerType::get(TheContext, 32), true);

            func_scanf = Function::Create(FuncTy9, GlobalValue::ExternalLinkage, "scanf", TheModule);
            func_scanf->setCallingConv(CallingConv::C);

            AttributeList func_printf_PAL;
            func_scanf->setAttributes(func_printf_PAL);
        }
        std::string format = (*((*mArguments)[0])).getTokenValue();
        format = format.substr(1, format.size() - 2);
        std::regex pattern_n("\\\\n");
        format = std::regex_replace(format, pattern_n, "\n");
        std::regex pattern_r("\\\\r");
        format = std::regex_replace(format, pattern_r, "\r");
        std::regex pattern_t("\\\\t");
        format = std::regex_replace(format, pattern_t, "\t");
        Value *str = Builder.CreateGlobalStringPtr(format);
        std::vector<Value *> int32_call_params;
        int32_call_params.push_back(str);
        for (int i = 1; i < (*mArguments).size(); i++) {
            llvm::Value *value = (*mArguments)[i]->addrGen();
            int32_call_params.push_back(value);
        }

        res = Builder.CreateCall(func_scanf, int32_call_params, "call_scanf");
    }
    return res;
}

llvm::Value *FunctionCallNode::codeGen_p() {
    Value *res = nullptr;
    if (mArguments) {


        Function *func_printf = TheModule->getFunction("printf");
        if (!func_printf) {
            PointerType *Pty = PointerType::get(IntegerType::get(TheContext, 8), 0);
            FunctionType *FuncTy9 = FunctionType::get(IntegerType::get(TheContext, 32), true);

            func_printf = Function::Create(FuncTy9, GlobalValue::ExternalLinkage, "printf", TheModule);
            func_printf->setCallingConv(CallingConv::C);

            AttributeList func_printf_PAL;
            func_printf->setAttributes(func_printf_PAL);
        }
        std::string format = (*((*mArguments)[0])).getTokenValue();
        format = format.substr(1, format.size() - 2);
        std::regex pattern_n("\\\\n");
        format = std::regex_replace(format, pattern_n, "\n");
        std::regex pattern_r("\\\\r");
        format = std::regex_replace(format, pattern_r, "\r");
        std::regex pattern_t("\\\\t");
        format = std::regex_replace(format, pattern_t, "\t");
        Value *str = Builder.CreateGlobalStringPtr(format);
        std::vector<Value *> int32_call_params;
        int32_call_params.push_back(str);
        for (int i = 1; i < (*mArguments).size(); i++) {
            int32_call_params.push_back((*mArguments)[i]->codeGen());
        }

        res = Builder.CreateCall(func_printf, int32_call_params, "call_printf");
    }
    return res;
}

llvm::Value *FunctionCallNode::codeGen() {
    if (mFunctionName->getSymbolName() == "printf") {
        return codeGen_p();
    } else if (mFunctionName->getSymbolName() == "scanf") {
        return codeGen_s();
    } else {
        Function *CalleeF =
                TheModule->getFunction(mFunctionName->getSymbolName());
        if (!CalleeF)
            return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " +"function: " + mFunctionName->getSymbolName() + " not defined");
        if (CalleeF->arg_size() != (*mArguments).size()) {
            return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                             std::to_string(this->getColumnNumber()) + " " +"Incorrect arguments passed");
        }

        std::vector<Value *> ArgsV;
        for (auto &mArgument: *mArguments) {
            ArgsV.push_back(mArgument->codeGen());
            if (!ArgsV.back())
                return nullptr;
        }

        return Builder.CreateCall(CalleeF, ArgsV, "calltmp");
    }
}


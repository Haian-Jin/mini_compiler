#pragma once
#include "cCompilerCommon.hpp"
#include "statNode.hpp"

class Node;

class ExpressionNode : public Node {
public:
    ExpressionNode() = default;;

    ExpressionNode(std::string _symbolName, int childrenNumber, ...)
            : Node(_symbolName, 0) {
        va_list vl;
        va_start(vl, childrenNumber);
        for (int i = 0; i < childrenNumber; i++) {
            mChildren.push_back(va_arg(vl, Node *));
        }
        mIsNegligible = (false), mSymbolName = (_symbolName),
        mIsTerminal = (false), mTokenValue = ("I am not a terminal.");
    }

    ExpressionNode(std::string _tokenValue, bool negligible = false) {};

    std::string getNodeTypeName() const override { return "ExpressionNode"; }

    virtual Type_and_Address getTypeAddress() {
        return {llvm::Type::TypeID::VoidTyID, nullptr};
    }

    virtual llvm::Value* addrGen(int ind = 0) {
        return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " + "This should not be Gen");
    }

    Json::Value jsonGen() const override {
        Json::Value r;
        r["name"] = getNodeTypeName();
        return r;
    }
};

class IdentifierNode : public ExpressionNode {
public:
    IdentifierNode(std::string name, bool isType = false)
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
    };

    bool isType() const { return Node::NodeKind == Node::KIND_ATTRIBUTE; }

    bool isArray() const { return Node::isArray(); }

    virtual std::string getNodeTypeName() const {

        if (isType()) {
            return std::string("TypeNode: ") + getTokenValue();
        } else {
            return std::string("IdentifierNode: ") + getTokenValue();
        }
    }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        return root;
    }

    Type_and_Address getTypeAddress();

    llvm::Value *addrGen(int ind = 0) override;
    llvm::Value *codeGen() override;
};

class IdentifierNodeList : public ExpressionNode {
public:
    std::vector<IdentifierNode *> mIdentifierNodeList;

    IdentifierNodeList() : ExpressionNode("IdentifierNodeList", 0) {}

    void addIdentifierNode(IdentifierNode *identifierNode) {
        assert(identifierNode != nullptr);
        mIdentifierNodeList.push_back(identifierNode);
    }

    virtual std::string getNodeTypeName() const { return "IdentifierNodeList"; }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        return root;
    }

    virtual llvm::Value *codeGen() {
        /* 用于为函数传递参数，并不会真的被调用codeGen */
        return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "I'm not sure this should be made a codeGen");
    }
};

class AssignmentNode : public ExpressionNode {
public:
    virtual std::string getNodeTypeName() const {
        return std::string("AssignmentNode ") + ("=");
    }

    AssignmentNode(IdentifierNode *lhs, ExpressionNode *rhs)
            : ExpressionNode("=", 0) {
        assert(lhs != nullptr);
        assert(rhs != nullptr);
        mLeftHandSide = lhs;
        mRightHandSide = rhs;
    }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        root["children"].append(mLeftHandSide->jsonGen());
        root["children"].append(mRightHandSide->jsonGen());
        return root;
    }

    llvm::Value *codeGen() override;

private:
    std::string op;
    IdentifierNode *mLeftHandSide;
    ExpressionNode *mRightHandSide;
};

class DoubleNode : public ExpressionNode {
public:
    double value;

    DoubleNode(std::string _tokenValue) : ExpressionNode(_tokenValue) {
        sscanf(_tokenValue.c_str(), "%lf", &this->value);
    }

    virtual std::string getNodeTypeName() const { return "DoubleNode"; }

    int getValue() { return this->value; }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName() + ":" + std::to_string(value);
        return root;
    };

    llvm::Value *codeGen() override {
        return llvm::ConstantFP::get(TheContext, llvm::APFloat(value));
    };
};

class IntNode : public ExpressionNode {
public:
    int value;

    IntNode(std::string _tokenValue) : ExpressionNode(_tokenValue) {
        sscanf(_tokenValue.c_str(), "%d", &this->value);
    }

    IntNode(int v) : value(v) {};

    double getValue() { return this->value; }

    virtual std::string getNodeTypeName() const { return "IntNode"; }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName() + ":" + std::to_string(value);
        return root;
    };

    llvm::Value *codeGen() override {
        return ConstantInt::get(llvm::Type::getInt32Ty(TheContext), this->value,
                                true);
    }
};

// 为了不改变文法.l文件，做的妥协，这个中间文件，只用在函数定义中，
class FuncNameAndArgsNode : public ExpressionNode {
public:
    IdentifierNode *mFuncName;
    VarDeclarationList *parasList; // used for function agrs
    // used for function declararion
    FuncNameAndArgsNode(IdentifierNode *nameIdentifier,
                        VarDeclarationList *args)
            : ExpressionNode() {
        assert(nameIdentifier != nullptr);
        this->mFuncName = nameIdentifier;
        this->parasList = args;
    };
};

class UnaryOperatorNode : public ExpressionNode {
public:
    UnaryOperatorNode(std::string _symbolName, int childrenNumber, ...)
            : ExpressionNode(_symbolName, 0) {
        va_list vl;
        va_start(vl, childrenNumber);
        for (int i = 0; i < childrenNumber; i++) {
            mChildren.push_back(va_arg(vl, Node *));
        }
        mIsNegligible = (false), mSymbolName = (_symbolName),
        mIsTerminal = (false), mTokenValue = ("I am not a terminal.");
        mHandSide = dynamic_cast<ExpressionNode *>(mChildren[0]);
        op = _symbolName;
        if (mHandSide == NULL)
            throw ("castfail");
    }

    UnaryOperatorNode(std::string _tokenValue, bool negligible = false)
            : ExpressionNode(_tokenValue, negligible) {};

    virtual std::string getNodeTypeName() const {
        return std::string("UnaryOperatorNode  ") + (getSymbolName());
    }

    llvm::Value *codeGen() override;

private:
    std::string op;
    ExpressionNode *mHandSide;
};

class BinaryOperatorNode : public ExpressionNode {
public:
    BinaryOperatorNode(std::string _tokenValue, bool negligible = false)
            : ExpressionNode(_tokenValue, negligible) {};

    BinaryOperatorNode(std::string opType, ExpressionNode *lhs,
                       ExpressionNode *rhs, bool isArithmetic = true)
            : ExpressionNode() {
        assert(lhs != nullptr);
        assert(rhs != nullptr);
        assert(opType != "");
        this->setType(Node::TYPE_INT);
        // this->setKind() HERE
        mLeftHandSide = lhs;
        mRightHandSide = rhs;
        op = opType;

        if (isArithmetic) // + - * / %
        {
            if (lhs->getType() == Node::TYPE_DOUBLE ||
                rhs->getType() == Node::TYPE_DOUBLE) {
                this->setType(Node::TYPE_DOUBLE);
            }
        }
    }


    virtual std::string getNodeTypeName() const { return op; }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        root["children"].append(mLeftHandSide->jsonGen());
        root["children"].append(mRightHandSide->jsonGen());

        return root;
    }

    llvm::Value *codeGen() override;

    ExpressionNode *getL() { return mLeftHandSide; }

    ExpressionNode *getR() { return mRightHandSide; }

private:
    std::string op;
    ExpressionNode *mLeftHandSide, *mRightHandSide;
};

class TenaryOperatorNode : public ExpressionNode {
public:
    TenaryOperatorNode(std::string _symbolName, int childrenNumber, ...)
            : ExpressionNode(_symbolName, 0) {
        va_list vl;
        va_start(vl, childrenNumber);
        for (int i = 0; i < childrenNumber; i++) {
            mChildren.push_back(va_arg(vl, Node *));
        }
        mIsNegligible = (false), mSymbolName = (_symbolName),
        mIsTerminal = (false), mTokenValue = ("I am not a terminal.");
        mLeftHandSide = dynamic_cast<ExpressionNode *>(mChildren[0]);
        mMidHandSide = dynamic_cast<ExpressionNode *>(mChildren[1]);
        mRightHandSide = dynamic_cast<ExpressionNode *>(mChildren[2]);
        op = _symbolName;
        if (mLeftHandSide == NULL || mRightHandSide == NULL ||
            mMidHandSide == NULL)
            throw ("castfail");
    }

    TenaryOperatorNode(std::string _tokenValue, bool negligible = false)
            : ExpressionNode(_tokenValue, negligible) {};

    std::string getNodeTypeName() {
        return std::string("TenaryOperatorNode  ") + (getSymbolName());
    }

    virtual llvm::Value *codeGen() {
        return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "? ... : is not supported");
    }

private:
    std::string op;
    ExpressionNode *mLeftHandSide, *mRightHandSide, *mMidHandSide;
};

class StructMemberNode : public ExpressionNode {
public:
    StructMemberNode(std::string _tokenValue, bool negligible = false)
            : ExpressionNode(_tokenValue, negligible) {};

    StructMemberNode(std::string opType, IdentifierNode *lhs,
                     IdentifierNode *rhs, bool isArithmetic = false)
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

    virtual std::string getNodeTypeName() const { return op; }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        root["children"].append(mVariableName->jsonGen());
        root["children"].append(mMemberName->jsonGen());

        return root;
    }

    virtual llvm::Value *codeGen() {
        /*
        TODO:
        */
        return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "Not supported yet");
    }

    ExpressionNode *getL() { return mVariableName; }

    ExpressionNode *getR() { return mMemberName; }

private:
    std::string op;
    IdentifierNode *mVariableName, *mMemberName;
};

class StructMemberAssignmentNode : public ExpressionNode {
public:
    virtual std::string getNodeTypeName() const {
        return std::string("StructMemberAssignmentNode ") + ("=");
    }

    StructMemberAssignmentNode(StructMemberNode *lhs, ExpressionNode *rhs)
            : ExpressionNode("=", 0) {
        assert(lhs != nullptr);
        assert(rhs != nullptr);
        mLeftHandSide = lhs;
        mRightHandSide = rhs;
    }

    virtual Json::Value jsonGen() const {
        Json::Value root;
        root["name"] = getNodeTypeName();
        root["children"].append(mLeftHandSide->jsonGen());
        root["children"].append(mRightHandSide->jsonGen());
        return root;
    }

    virtual llvm::Value *codeGen() {
        /*
        TODO:
        */
        return LogErrorV(std::to_string(this->getLineNumber()) + ":" +
                         std::to_string(this->getColumnNumber()) + " " +
                         "Not supported yet");
    }

private:
    std::string op;
    StructMemberNode *mLeftHandSide;
    ExpressionNode *mRightHandSide;
};

#include "include/ast_node.hpp"
#include "include/array_node.hpp"
#include "include/expr_node.hpp"
#include "include/ctrl_node.hpp"
#include "include/func_node.hpp"
#include "include/stat_node.hpp"
#include "include/struct_node.hpp"

// 用于记录行数和列数 
int csLineCnt = 0;
int csColumnCnt = 0;

llvm::LLVMContext TheContext;
llvm::IRBuilder<> Builder(TheContext);
Module *TheModule = new Module(llvm::StringRef(), TheContext);
std::unordered_map<std::string, Type_and_Address> variableTable;
std::unordered_map<std::string, StructType *> structTable;
std::unordered_map<std::string,std::unordered_map<std::string, Type_and_Address> *> variableTables;
std::stack<std::unordered_map<std::string, Type_and_Address> *> tableStack;

// 用于记录所有的符号表。按照 <表名字, 表> 存储；表名字就是当前的函数名/结构体名。
std::map<std::string, SymbolTable *> SymbolTable::set;

// 符号表栈，用于实现变量的生命周期。
SymbolTableStack *symbolTableStack = new SymbolTableStack(new SymbolTable("Global_SymbolTable"));

std::string NameCounter::getNumberedName(std::string name) {
    if (map.find(name) == map.end()) {
        map.insert({name, 0});
    }
    return name + "[" + std::to_string(map[name]++) + "]";
}

Node::Node(std::string _symbolName, int childrenNumber, ...) : mSymbolName(_symbolName),
                                                               mIsTerminal(false), mTokenValue("I am not a terminal.") {
    va_list vl;
    va_start(vl, childrenNumber);
    for (int i = 0; i < childrenNumber; i++) {
        mChildren.push_back(va_arg(vl, Node *));
    }
}


bool Node::isTerminal() const {
    return mIsTerminal;
}


std::string Node::getName() const {
    return mIsTerminal ? mTokenValue : mSymbolName;
}



Node::Type Node::getType() {
    return this->NodeType;
}

void Node::setType(Node::Type type) {
    this->NodeType = type;
}

void Node::setType(Node *c) {
    this->setType(c->getType());
    if (c->getType() == Node::TYPE_STRUCT) {
        this->setStructTypeName(c->getStructTypeName());
    }
    if (c->isArray()) {
        this->setArraySizes(c->getArraySizes());
    }
}

Node::Kind Node::getKind() {
    return this->NodeKind;
}

void Node::setKind(Node::Kind _kind) {
    this->NodeKind = _kind;
}

std::string Node::getSymbolName() const {
    return this->mSymbolName;
}

std::string Node::getTokenValue() const {
    if (!(this->mIsTerminal)) {
        return this->getSymbolName();
    }
    return this->mTokenValue;
}



std::vector<Node::Type> Node::getArgList() {
    return this->mTokenArgList;
}


void Node::setArraySizes(std::vector<int> _sizes) {
    mArraySizes.assign(_sizes.begin(), _sizes.end());
}

std::vector<std::string> Node::getArgListStructName() {
    return mTokenArgListStructTypeName;
}

std::vector<int> Node::getArraySizes() {
    return mArraySizes;
}

bool Node::isArray() const {
    return mArraySizes.size() > 0;
}


void Node::setStructTypeName(std::string _name) {
    mStructTypeName = _name;
}

std::string Node::getStructTypeName() {
    return mStructTypeName;
}

void Node::setVariableName(std::string _name) {
    this->mVariableName = _name;
}

void Node::setPosition(int l, int c) {
    mLineNumber = l;
    mColumnNumber = c;
}

int Node::getLineNumber() {
    return mLineNumber;
}

int Node::getColumnNumber() {
    return mColumnNumber;
}

void Node::setPosition(Node *c) {
    mLineNumber = c->getLineNumber();
    mColumnNumber = c->getColumnNumber();
}

void symAttribute::print() {
    std::cout << name << ' ';
    switch (type) {
        case Node::TYPE_INT:
            std::cout << "int ";
            break;
        case Node::TYPE_DOUBLE:
            std::cout << "double ";
            break;
        case Node::TYPE_STRUCT:
            std::cout << "struct " << structTypeName << ' ';
            break;
        default:
            std::cout << type << ' ';
    }
    switch (kind) {
        case Node::KIND_ARGUMENT:
            std::cout << "augument ";
            break;
        case Node::KIND_ATTRIBUTE:
            std::cout << "attribute ";
            break;
        case Node::KIND_CONSTANT:
            std::cout << "constant ";
            break;
        case Node::KIND_FUNCTION:
            std::cout << "function ";
            break;
        case Node::KIND_VARIABLE:
            std::cout << "variable ";
            break;
        default:
            std::cout << kind << ' ';
    }
    if (kind == Node::KIND_FUNCTION) {
        std::cout << '(';
        for (int i = 0; i < argList.size(); i++) {
            auto string = argList[i];
            switch (string) {
                case Node::TYPE_INT:
                    std::cout << "int";
                    break;
                case Node::TYPE_DOUBLE:
                    std::cout << "double";
                    break;
                case Node::TYPE_STRUCT:
                    std::cout << "struct " << argListStructName[i];
                    break;
                default:
                    std::cout << type;
            }
            if (i != argList.size() - 1)std::cout << ",";
        }
        std::cout << ") ";
    }
    if (arraySizes.size() > 0) {
        for (auto size: arraySizes) {
            std::cout << "[" << size << "]";
        }
        std::cout << ' ';
    }
    printf(" --pos:l%dc%d\n", lineNumber, columnNumber);
}

SymbolTable::SymbolTable() : mSymbolTableName({"Unamed Symbol Table"}) {
    set.insert({mSymbolTableName, this});
}

SymbolTable::SymbolTable(std::string name) : mSymbolTableName(name) {
    set.insert({mSymbolTableName, this});
}

std::string SymbolTable::getName() {
    return mSymbolTableName;
}

bool SymbolTable::insert(symAttribute *t) {
    if (map.find(t->name) != map.end()) {
        return false;
    } else {
        map.insert({t->name, t});
        return true;
    }
}

symAttribute *SymbolTable::lookUp(std::string name) {
    if (map.find(name) == map.end()) {
        return NULL;
    } else {
        return map[name];
    }
}

void SymbolTable::print() {
    std::cout << "Symbol Table Name: " << mSymbolTableName << std::endl;
    int i = 1;
    for (auto pair: map) {
        printf("No.%03d ", i++);
        //std::cout<<pair.first<<' ';
        pair.second->print();
    }
}

SymbolTable *SymbolTable::getSymbolTableByName(std::string symbolTableName) {
    return set[symbolTableName];
}

void SymbolTable::viewAllSymbolTable() {
    std::cout << "Printing All Symbol Tables attended...\n";
    for (auto pair: set) {
        //std::cout<<"Symbol Table Name: "<<pair.first()<<std::endl;
        std::cout << "----------------------------------------------\n";
        pair.second->print();
        std::cout << "----------------------------------------------\n";
    }
}

SymbolTableStack::SymbolTableStack(SymbolTable *globalSymbolTable) {
    stack.push_back(globalSymbolTable);
}

void SymbolTableStack::push(SymbolTable *t) {
    stack.push_back(t);
}

void SymbolTableStack::pop() {
    if (stack.size() == 1) {
        throw ("You cannot pop the global symbol table.");
    }
    stack.pop_back();
}

SymbolTable *SymbolTableStack::top() {
    return stack[stack.size() - 1];
}

symAttribute *SymbolTableStack::lookUp(std::string name) {
    for (int i = stack.size() - 1; i >= 0; i--) {
        if (stack[i]->lookUp(name)) {
            return stack[i]->lookUp(name);
        }
    }
    return NULL;
}

bool SymbolTableStack::insert(symAttribute *t) {
    return stack[stack.size() - 1]->insert(t);
}

bool checkType(Node *p, Node::Type type) {
    return p->getType() == type;
}

bool checkKind(Node *p, Node::Kind kind) {
    return p->getKind() == kind;
}

bool typeMatch(Node *a, Node *b) {
    if (a->isArray() || b->isArray()) {
        return false;
    }
    if (a->getType() == b->getType()) {
        if (a->getType() != Node::TYPE_STRUCT)return true;
        else return a->getStructTypeName().compare(b->getStructTypeName()) == 0;
    }
    if (a->getType() == Node::TYPE_INT) {
        return b->getType() == Node::TYPE_DOUBLE;
    }
    if (a->getType() == Node::TYPE_DOUBLE) {
        return b->getType() == Node::TYPE_INT;
    }
    return false;
}

bool typeMatch(std::vector<Node::Type> a, std::vector<Node::Type> b) {
    if (a.size() != b.size())return false;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[i])continue;
        if (a[i] == Node::TYPE_INT && b[i] == Node::TYPE_DOUBLE)continue;
        if (b[i] == Node::TYPE_INT && a[i] == Node::TYPE_DOUBLE)continue;
        return false;
    }

    return true;
}

bool typeMatch(std::vector<Node::Type> a, Node *c, std::vector<std::string> s) {
    auto b = c->getArgList();
    if (a.size() != b.size())return false;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[i]) {
            if (a[i] != Node::TYPE_STRUCT)continue;
            else if (c->getArgListStructName()[i].compare(s[i]) != 0)return false;
            else continue;
        }
        if (a[i] == Node::TYPE_INT && b[i] == Node::TYPE_DOUBLE)continue;
        if (b[i] == Node::TYPE_INT && a[i] == Node::TYPE_DOUBLE)continue;
        return false;
    }

    return true;
}

bool typeMatch(symAttribute *a, Node *b) {
    if (b->isArray())return false;
    if (a->type == b->getType()) {
        if (a->type == Node::TYPE_STRUCT) {
            return a->structTypeName.compare(b->getStructTypeName()) == 0;
        } else return true;
    }
    if ((a->type == Node::TYPE_INT && b->getType() == Node::TYPE_DOUBLE) ||
        (a->type == Node::TYPE_DOUBLE && b->getType() == Node::TYPE_INT))
        return true;
    return false;
}





std::string type_to_string(symAttribute *t) {
    switch (t->type) {
        case (Node::TYPE_VOID):
            return "void";
        case (Node::TYPE_INT):
            return "int";
        case (Node::TYPE_DOUBLE):
            return "double";
        case (Node::TYPE_STRUCT):
            return std::string("struct ") + t->structTypeName;
    }
}


std::unique_ptr<ExpressionNode> LogError(const char *str) {
    fprintf(stderr, "LogError: %s\n", str);
    return nullptr;
}

Value *LogErrorV(std::string str) { return LogErrorV(str.c_str()); }

Value *LogErrorV(const char *Str) {
    LogError(Str);
    exit(1);
    return nullptr;
}


llvm::Constant *con_0() {
    return llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0);
}

Value *CastBool(Value *cond) {
    if (cond->getType()->getTypeID() == Type::IntegerTyID) {
        cond = Builder.CreateIntCast(cond, Type::getInt1Ty(TheContext), true);
        return Builder.CreateICmpNE(
                cond, ConstantInt::get(Type::getInt1Ty(TheContext), 0, true));
    } else if (cond->getType()->getTypeID() == Type::DoubleTyID) {
        return Builder.CreateFCmpONE(cond,
                                     ConstantFP::get(TheContext, APFloat(0.0)));
    } else {
        return cond;
    }
}

std::unordered_map<std::string, Type_and_Address> *inheritTable() {
    std::unordered_map<std::string, Type_and_Address> *codeTable;
    if (tableStack.empty()) {
        codeTable = new std::unordered_map<std::string, Type_and_Address>(variableTable);
    } else {
        codeTable =
                new std::unordered_map<std::string, Type_and_Address>(*(tableStack.top()));
    }
    return codeTable;
}




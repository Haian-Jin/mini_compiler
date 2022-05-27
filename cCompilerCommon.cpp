#include "./cCompilerCommon.hpp"

// 用于记录行数和列数 
int csLineCnt = 0;
int csColumnCnt = 0;

// 用于记录所有的符号表。按照 <表名字, 表> 存储；表名字就是当前的函数名/结构体名。
std::map<std::string, SymbolTable*> SymbolTable::set;

// 符号表栈，用于实现变量的生命周期。
SymbolTableStack *symbolTableStack = new SymbolTableStack(new SymbolTable("Global_SymbolTable"));

std::string NameCounter::getNumberedName(std::string name){
    if(map.find(name) == map.end()){
        map.insert({name,0});
    }
    return name+"["+std::to_string(map[name]++)+"]";
}

Node::Node(std::string _symbolName, int childrenNumber, ...):mIsNegligible(false),mSymbolName(_symbolName),mIsTerminal(false),mTokenValue("I am not a terminal."){
    va_list vl;
    va_start(vl, childrenNumber);
    for(int i=0;i<childrenNumber;i++){
        mChildren.push_back(va_arg(vl,Node *));
    }
}
void Node::addChild(Node *newChild){
    mChildren.push_back(newChild);
}
Node * Node::getChildrenById(int i){
    return mChildren[i];
}
int Node::getChildrenNumber(){
    return mChildren.size();
}
bool Node::isTerminal()const{
    return mIsTerminal;
}


std::string Node::getName()const{
    return mIsTerminal?mTokenValue:mSymbolName;
}
void Node::printTree(int depth/*=0*/){
    for(int i=0; i < depth; i++){
        std::cout<<"\t";
    }
    std::cout << this->getName() << std::endl;
    for(int i=0; i<mChildren.size(); i++){
        mChildren[i]->printTree(depth + 1);
    }
}
void Node::copyFromChild(){
    this->setType(mChildren[0]->getType());
    this->setKind(mChildren[0]->getKind());
    this->setArgList(mChildren[0]->getArgList());
    this->setArgListStructName(mChildren[0]->getArgListStructName());
    this->setArraySizes(mChildren[0]->getArraySizes());
    this->setStructTypeName(mChildren[0]->getStructTypeName());
    this->setVariableName(mChildren[0]->getSymbolName());
    this->setPosition(mChildren[0]->getLineNumber(), mChildren[0]->getColumnNumber());
}
void Node::copyFrom(Node *c){
    this->setType(c); // setType() has been overloaded early. here is fine
    this->setKind(c->getKind());
    this->setArgList(c->getArgList());
    this->setArgListStructName(c->getArgListStructName());
    this->setArraySizes(c->getArraySizes());
    this->setStructTypeName(c->getStructTypeName());
    this->setVariableName(c->getSymbolName());
    this->setPosition(c->getLineNumber(), c->getColumnNumber());
}

Node::Type Node::getType(){
    return this->NodeType;
}
void Node::setType(Node::Type type){
    this->NodeType = type;
}

void Node::setType(Node *c){
    this->setType(c->getType());
    if(c->getType()==Node::TYPE_STRUCT){
        this->setStructTypeName(c->getStructTypeName());
    }
    if(c->isArray()){
        this->setArraySizes(c->getArraySizes());
    }
}

Node::Kind Node::getKind(){
    return this->NodeKind;
}

void Node::setKind(Node::Kind _kind){
    this->NodeKind = _kind;
}

std::string Node::getTypeString(){
    std::string string;
    switch(this->NodeType){
        case(Node::TYPE_DOUBLE):
            string+={"double"};
            break;
        case(Node::TYPE_INT):
            string+={"int"};
            break;
        case(Node::TYPE_STRUCT):
            string+=(std::string("struct ")+this->mStructTypeName);
            break;
        default :
            string+=std::to_string(this->NodeType);
    }
    for(int i=0; i < this->mArraySizes.size(); i++){
        string+="[]";
    }
    return string;
}



void Node::setArgList(std::vector<Node::Type> _argList){
    mTokenArgList.assign(_argList.begin(),_argList.end());
}
std::vector<Node::Type> Node::getArgList(){
    return this->mTokenArgList;
}
void Node::setArgListStructName(std::vector<std::string> _structName){
    mTokenArgListStructTypeName.assign(_structName.begin(), _structName.end());
}
void Node::setArraySizes(std::vector<int> _sizes){
    mArraySizes.assign(_sizes.begin(),_sizes.end());
}
std::vector<std::string> Node::getArgListStructName(){
    return mTokenArgListStructTypeName;
}
std::vector<int> Node::getArraySizes(){
    return mArraySizes;
}
bool Node::isArray() const{
    return mArraySizes.size() > 0;
}
int Node::getArrayDimension(){
    return mArraySizes.size();
}
void Node::setStructTypeName(std::string _name){
    mStructTypeName = _name;
}
std::string Node::getStructTypeName(){
        return mStructTypeName;
}
void Node::setVariableName(std::string _name){
    this->mVariableName = _name;
}/*
std::string Node::getSymbolName() const{
    return mVariableName;
}*/
void Node::setPosition(int l, int c) {
    mLineNumber = l;
    mColumnNumber = c;
}
int Node::getLineNumber(){
    return mLineNumber;
}
int Node::getColumnNumber(){
    return mColumnNumber;
}
void Node::setPosition(Node *c){
    mLineNumber = c->getLineNumber();
    mColumnNumber = c->getColumnNumber();
}

void symAttribute::print(){
    std::cout<<name<<' ';
    switch(type){
        case Node::TYPE_INT:
            std::cout<<"int ";
            break;
        case Node::TYPE_DOUBLE:
            std::cout<<"double ";
            break;
        case Node::TYPE_STRUCT:
            std::cout<<"struct "<<structTypeName<<' ';
            break;
        default:
            std::cout<<type<<' ';
    }
    switch(kind){
        case Node::KIND_ARGUMENT:
            std::cout<<"augument ";
            break;
        case Node::KIND_ATTRIBUTE:
            std::cout<<"attribute ";
            break;
        case Node::KIND_CONSTANT:
            std::cout<<"constant ";
            break;
        case Node::KIND_FUNCTION:
            std::cout<<"function ";
            break;
        case Node::KIND_VARIABLE:
            std::cout<<"variable ";
            break;
        default:
            std::cout<<kind<<' ';
    }
    if(kind==Node::KIND_FUNCTION){
        std::cout<<'(';
        for(int i=0;i<argList.size();i++){
            auto string = argList[i];
            switch(string){
                case Node::TYPE_INT:
                    std::cout<<"int";
                    break;
                case Node::TYPE_DOUBLE:
                    std::cout<<"double";
                    break;
                case Node::TYPE_STRUCT:
                    std::cout<<"struct "<<argListStructName[i];
                    break;
                default:
                    std::cout<<type;
            }
            if(i!=argList.size()-1)std::cout<<",";
        }
        std::cout<<") ";
    }
    if(arraySizes.size()>0){
        for(auto size : arraySizes){
            std::cout<<"["<<size<<"]";
        }
        std::cout<<' ';
    }
    printf(" --pos:l%dc%d\n", lineNumber, columnNumber);
}

SymbolTable::SymbolTable():mSymbolTableName({"Unamed Symbol Table"}){
    set.insert({mSymbolTableName, this});
}
SymbolTable::SymbolTable(std::string name):mSymbolTableName(name){
    set.insert({mSymbolTableName, this});
}
std::string SymbolTable::getName(){
    return mSymbolTableName;
}
bool SymbolTable::insert(symAttribute* t){
    if(map.find(t->name)!=map.end()){
        return false;
    }else{
        map.insert({t->name,t});
        return true;
    }
}
symAttribute *SymbolTable::lookUp(std::string name){
    if(map.find(name)==map.end()){
        return NULL;
    }else{
        return map[name];
    }
}
void SymbolTable::print(){
    std::cout<<"Symbol Table Name: "<<mSymbolTableName<<std::endl;
    int i=1;
    for(auto pair : map){
        printf("No.%03d ",i++);
        //std::cout<<pair.first<<' ';
        pair.second->print();
    }
}
SymbolTable *SymbolTable::getSymbolTableByName(std::string symbolTableName){
    return set[symbolTableName];
}
void SymbolTable::viewAllSymbolTable(){
    std::cout<<"Printing All Symbol Tables attended...\n";
    for(auto pair : set){
        //std::cout<<"Symbol Table Name: "<<pair.first()<<std::endl;
        std::cout<<"----------------------------------------------\n";
        pair.second->print();
        std::cout<<"----------------------------------------------\n";
    }
}

SymbolTableStack::SymbolTableStack(SymbolTable *globalSymbolTable){
    stack.push_back(globalSymbolTable);
}
void SymbolTableStack::push(SymbolTable* t){
    stack.push_back(t);
}
void SymbolTableStack::pop(){
    if(stack.size()==1){
        throw("You cannot pop the global symbol table.");
    }
    stack.pop_back();
}
SymbolTable *SymbolTableStack::top(){
    return stack[stack.size()-1];
}
symAttribute *SymbolTableStack::lookUp(std::string name){
    for(int i=stack.size()-1;i>=0;i--){
        if(stack[i]->lookUp(name)){
            return stack[i]->lookUp(name);
        }
    }
    return NULL;
}
bool SymbolTableStack::insert(symAttribute* t){
    return stack[stack.size()-1]->insert(t);
}

bool checkType(Node *p, Node::Type type){
    return p->getType()==type;
}
bool checkKind(Node *p, Node::Kind kind){
    return p->getKind()==kind;
}
bool typeMatch(Node *a, Node *b){
    if(a->isArray()||b->isArray()){
        return false;
    }
    if(a->getType()==b->getType()){
        if(a->getType()!=Node::TYPE_STRUCT)return true;
        else return a->getStructTypeName().compare(b->getStructTypeName())==0;
    }
    if(a->getType()==Node::TYPE_INT){
        return b->getType()==Node::TYPE_DOUBLE;
    }
    if(a->getType()==Node::TYPE_DOUBLE){
        return b->getType()==Node::TYPE_INT;
    }
    return false;
}
bool typeMatch(std::vector<Node::Type> a, std::vector<Node::Type> b){
    if(a.size()!=b.size())return false;
    for(int i=0;i<a.size();i++){
        if(a[i]==b[i])continue;
        if(a[i]==Node::TYPE_INT && b[i]==Node::TYPE_DOUBLE)continue;
        if(b[i]==Node::TYPE_INT && a[i]==Node::TYPE_DOUBLE)continue;
        return false;
    }

    return true;
}
bool typeMatch(std::vector<Node::Type> a,Node *c , std::vector<std::string> s){
    auto b=c->getArgList();
    if(a.size()!=b.size())return false;
    for(int i=0;i<a.size();i++){
        if(a[i]==b[i]){
            if(a[i]!=Node::TYPE_STRUCT)continue;
            else if(c->getArgListStructName()[i].compare(s[i])!=0)return false;
            else continue;
        }
        if(a[i]==Node::TYPE_INT && b[i]==Node::TYPE_DOUBLE)continue;
        if(b[i]==Node::TYPE_INT && a[i]==Node::TYPE_DOUBLE)continue;
        return false;
    }

    return true;
}
bool typeMatch(symAttribute *a, Node* b){
    if(b->isArray())return false;
    if(a->type==b->getType()){
        if(a->type==Node::TYPE_STRUCT){
            return a->structTypeName.compare(b->getStructTypeName())==0;
        }else return true;
    }
    if((a->type==Node::TYPE_INT && b->getType()==Node::TYPE_DOUBLE)||(a->type==Node::TYPE_DOUBLE && b->getType()==Node::TYPE_INT))return true;
    return false;
}

void Node::setAttribute(void *p){
    auto c = (symAttribute*)p;
    this->setType(c->type);
    this->setKind(c->kind);
    this->setArgList(c->argList);
    this->setArgListStructName(c->argListStructName);
    this->setArraySizes(c->arraySizes);
    this->setStructTypeName(c->structTypeName);
    this->setVariableName(c->name);
    this->setPosition(c->lineNumber, c->columnNumber);
}

void Node::copyFrom(symAttribute *c){
    if(!c) return;
    this->setType(c->type);
    this->setKind(c->kind);
    this->setArgList(c->argList);
    this->setArraySizes(c->arraySizes);
    this->setStructTypeName(c->structTypeName);
    this->setVariableName(c->name);
    this->setPosition(c->lineNumber, c->columnNumber);
}

std::string type_to_string(symAttribute *t){
    switch(t->type){
        case(Node::TYPE_VOID):
            return "void";
        case(Node::TYPE_INT):
            return "int";
        case(Node::TYPE_DOUBLE):
            return "double";
        case(Node::TYPE_STRUCT):
            return std::string("struct ")+t->structTypeName;
    }
}
std::string Node::getSymbolName()const{
    return this->mSymbolName;
}

std::string Node::getTokenValue()const{
    if(!(this->mIsTerminal)){
        return getSymbolName();
    }
    return this->mTokenValue;
}
Value *LogErrorVV(std::string str) {
    std::cout << str << std::endl;
    return nullptr;
}

llvm::LLVMContext TheContext;
llvm::IRBuilder<> Builder(TheContext);
Module *TheModule = new Module(llvm::StringRef(),TheContext);
std::unordered_map<std::string, Type_and_Address> variableTable;
std::unordered_map<std::string, StructType*> structTable;
std::unordered_map<std::string,
        std::unordered_map<std::string, Type_and_Address> *>
        variableTables;
std::stack<std::unordered_map<std::string, Type_and_Address> *> tableStack;
//std::map<std::string,symAttribute *> originalSymbolTable;


llvm::Value* calcArrayIndex(std::vector<int> arraySizes, std::vector<ExpressionNode *> mArrayIndexs){
     ExpressionNode* expression = *(mArrayIndexs.begin());
    int postMul = 1;
//    for(int i=mArrayIndexs.size()-1; i>=1; i--){
//        BinaryOperatorNode* temp = new BinaryOperatorNode("*", new IntNode(postMul), mArrayIndexs[i-1]);
//        postMul *= arraySizes[i-1];
//        BinaryOperatorNode* te = new BinaryOperatorNode("+", temp, expression);
//        expression = te;
//    }
    for (int i = 1;i<arraySizes.size();i++) {
        BinaryOperatorNode* te = new BinaryOperatorNode("*", new IntNode(arraySizes[i]), expression);
        expression = te;
        if(i<mArrayIndexs.size()) {
            BinaryOperatorNode *temp = new BinaryOperatorNode("+", mArrayIndexs[i], expression);
            expression = temp;
        }
//        if (i>mArrayIndexs.size()-1) {
//            postMul *= arraySizes[i];
//            expression = nullptr;
//        } else {
//            BinaryOperatorNode* temp = new BinaryOperatorNode("*", new IntNode(postMul), mArrayIndexs[i]);
//            postMul *= arraySizes[i];
//            if(!expression)
//                expression = temp;
//            else {
//                BinaryOperatorNode *te = new BinaryOperatorNode("+", temp, expression);
//                expression = te;
//            }
//        }
    }
    if(arraySizes.size()==1){
        return (expression)->codeGen();
    }else
        return dynamic_cast<BinaryOperatorNode*>(expression)->codeGen();
}

llvm::Constant* con_0() {
    return llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0);
}



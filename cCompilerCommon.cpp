#include"./cCompilerCommon.hpp"
#include"runner.hpp"
int csLineCnt = 0;
//Node *cout=0;
int csColumnCnt = 0;
AddressCounter* addressCounter = new AddressCounter();

std::map<std::string, SymbolTable*> SymbolTable::set;

SymbolTableStack *symbolTableStack = new SymbolTableStack(new SymbolTable("Global_SymbolTable"));

bool checkType(Node *p, Node::Type type){
    return p->getType()==type;
}
bool checkKind(Node *p, Node::Kind kind){
    return p->getKind()==kind;
}
bool typeMatch(Node *a, Node *b){
    if(a->isArray()||b->isArray()){
        /*if(a->isArray()&&b->isArray())return false;
        if(a->isArray()){
            return b->getType()==Node::TYPE_INT;
        }else{
            return a->getType()==Node::TYPE_INT;
        }*/
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
        //if(a[i]!=b[i])return false;
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
    //return false;
    for(int i=0;i<a.size();i++){
        //if(a[i]!=b[i])return false;
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
bool typeMatch(Attribute *a, Node* b){
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
    auto c = (Attribute*)p;
    this->setType(c->type);
    this->setKind(c->kind);
    this->setArgList(c->argList);
    this->setArgListStructName(c->argListStructName);
    this->setArraySizes(c->arraySizes);
    this->setStructTypeName(c->structTypeName);
    this->setVariableName(c->name);
    this->setPosition(c->lineNumber, c->columnNumber);
}

void Node::copyFrom(Attribute *c){
    if(!c)return;
    this->setType(c->type);
    this->setKind(c->kind);
    this->setArgList(c->argList);
    this->setArraySizes(c->arraySizes);
    this->setStructTypeName(c->structTypeName);
    this->setVariableName(c->name);
    this->setPosition(c->lineNumber, c->columnNumber);
}

std::string type_to_string(Attribute *t){
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

ProgramRam program;
NameCounter programNameCounter;

int VariableDeclarationNode::getSize(){
    if(this->mTokenType==Node::TYPE_VOID){
        return 1;
    }
    int arraySize = 1;
    if(isArray()){
        for(int i : this->getArraySizes()){
            arraySize *= i;
        }
    }
    int singleSize = 1;
    if(getType()==Node::TYPE_STRUCT){
        singleSize = symbolTableStack->lookUp(this->getStructTypeName())->size;
    }
    return arraySize * singleSize;
}

int StructDeclarationNode::getSize(){
    if(mSizeSum!=-1)return mSizeSum;
    int sizeSum = 0;
    for(auto record : (SymbolTable::getSymbolTableByName(mChildren[1]->getStructTypeName()))->getTable()){
        /**/
        auto attribute = record.second;
        std::cout<<"building struct member: "<<attribute->name<<std::endl;
        attribute->offset = sizeSum;
        if(attribute->type == Node::TYPE_STRUCT){
            attribute->size = symbolTableStack->lookUp(attribute->structTypeName)->size;
        }else{
            attribute->size = 1;
        }
        if(attribute->arraySizes.size()!=0){
            for(int i:attribute->arraySizes){
                attribute->size *= i;
            }
        }
        sizeSum += attribute->size;
    }
    return mSizeSum=sizeSum;
}

std::string StructDeclarationNode::codeGen(){
std::cout<<"StructDeclarationNode::codeGen\n";
    //symbolTableStack->push(SymbolTable::getSymbolTableByName(getStructTypeName()));
    auto attribute = symbolTableStack->lookUp(mChildren[1]->getStructTypeName());

    if(attribute==NULL){
        std::cout<<mChildren[1]->getStructTypeName()<<" not found.";
        exit(1);
    }
    attribute->size = getSize();
    std::cout<<"StructDeclarationNode::codeGen finished\n";
    //symbolTableStack->pop();
}

std::string VariableDeclarationStatementNode::codeGen(){
    std::cout<<"VariableDeclarationStatementNode::codeGen\n";
    auto variables = mChildren[1]->getChildren();
    std::stringstream ss;
    for(auto variable : variables){
        dynamic_cast<VariableDeclarationNode*>(variable)->codeGen();
    }
    return "`";
}

std::string VariableDeclarationNode::codeGen(){
    std::cout<<"VariableDeclarationNode::codeGen\n";
    auto attribute = symbolTableStack->lookUp(this->getVariableName());
    assert(attribute!=NULL);
    attribute->size = getSize();
    attribute->addr = addressCounter->getNextNAddr(getSize());
    return "`";
}

int FunctionDeclarationNode::getSize(){
    VariableDeclarationNode t(this);
    return t.getSize();
}

std::string FunctionDeclarationNode::codeGen(){
    std::cout<<"FunctionDeclarationNode::codeGen\n";
    auto attribute = symbolTableStack->lookUp(this->getVariableName());
    assert(attribute!=NULL);
    attribute->size = getSize();
    attribute->addr = addressCounter->getNextNAddr(getSize());
    auto table = SymbolTable::getSymbolTableByName(this->getVariableName());
    for(auto record : table->getTable()){
        AttributivedNode s("t",0);
        s.copyFrom(record.second);
        VariableDeclarationNode t(&s);
        record.second->size = t.getSize();
        record.second->addr = addressCounter->getNextNAddr(t.getSize());
    }
    program.labelNextLine(this->getVariableName());
    symbolTableStack->push(SymbolTable::getSymbolTableByName(this->getVariableName()));
    return "`";
}

void Node::fullCopyFrom(Node *c){
    //std::cout<<"Wrong copy\n";
    //this->setType(c->getType());
    //this->mChildren.assign(c->mChildren.begin(),c->mChildren.end());
    mSymbolName = c->mSymbolName;
    mTokenValue = c->mTokenValue; //(token string)
    mIsTerminal = c->mIsTerminal;
    mIsNegligible = c->mIsNegligible;
    mChildren = c->mChildren;
    if(dynamic_cast<AttributivedNode*>(c)!=NULL){
        this->setType(c);
        this->setKind(c->getKind());
        this->setArgList(c->getArgList());
        this->setArgListStructName(c->getArgListStructName());
        this->setArraySizes(c->getArraySizes());
        this->setStructTypeName(c->getStructTypeName());
        this->setVariableName(c->getVariableName());
        this->setPosition(c->getLineNumber(), c->getColumnNumber());
    }
}

std::string getAddr(Node *c){
    std::stringstream ss;
    while(c->getName().compare("[]")==0)c=c->getChildrenById(0);
    if(c->getChildrenNumber()==0){
        auto attribute = symbolTableStack->lookUp(c->getVariableName());
        assert(attribute!=NULL);
        ss<<attribute->addr;
        return ss.str();
    }else if(c->getName().compare(".")){
        std::string res = c->codeGen();
        return res.substr(1,res.length()-2);// TODO
    }else if(c->getName().compare("[]")){
        std::string res = c->codeGen();
        return res.substr(1,res.length()-2);// TODO
    }
}

std::string computeArrayOffset(ExpressionNode *c);
std::string getOffsetAddr(std::string symbolTableName, Node *c){
    std::string res;
    Node *p=c;
    while(p->getChildrenNumber()!=0)p=p->getChildrenById(0);
    auto attribute = SymbolTable::getSymbolTableByName(symbolTableName)->lookUp(p->getTokenValue());
    //std::cout<<symbolTableName<<":"<<c->getVariableName()<<'\n';
    assert(attribute!=NULL);
    std::stringstream ss;
    ss<<attribute->offset;
    if(c->getName().compare("[]")==0){
        std::string offset = computeArrayOffset(dynamic_cast<ExpressionNode*>(c));
        program.push({"ADD", ss.str(), offset, res=programNameCounter.getNumberedName("`t")});
        return res;
    }else if(c->getName().compare(".")==0){
        res = c->codeGen();
        return res.substr(1,res.length()-2);
    }
    return ss.str();
}

std::string computeArrayOffset(ExpressionNode *c){
    ExpressionNode *p = c;
    while(p->getChildrenNumber()!=0){
        p = dynamic_cast<ExpressionNode*>(p->getChildrenById(0));
        assert(p!=NULL);
    }
    auto attribute = symbolTableStack->lookUp(p->getVariableName());
    assert(attribute!=NULL);
    auto &arraySizes = attribute->arraySizes;

    std::string res, t;
    res = c->getChildrenById(1)->codeGen();
    c=dynamic_cast<ExpressionNode*>(c->getChildrenById(0));
    int sizeMul = arraySizes[arraySizes.size()-1];
    for(int i=arraySizes.size()-2; i>=0; i--){
        std::string midRes;
        std::stringstream ss;
        ss<<sizeMul;
        program.push({"MUL", ss.str(), c->getChildrenById(1)->codeGen(), midRes=programNameCounter.getNumberedName("`t")});
        program.push({"ADD", midRes, res, t=programNameCounter.getNumberedName("`t")});
        res = t;
        sizeMul *= arraySizes[i];
        c=dynamic_cast<ExpressionNode*>(c->getChildrenById(0));
    }
    std::stringstream ss;
    ss<<(attribute->size/sizeMul);
    program.push({"MUL", ss.str(), res, t=programNameCounter.getNumberedName("`t")}); /* for struct. */
    return t;
}

std::string ExpressionNode::codeGen(){
    std::string res;
    std::cout<<"ExpressionNode::codeGen: "<<this->getName()<<"\n";
    if(mChildren.size()==0){ // is terminal
        if(this->getKind()==Node::KIND_VARIABLE){
            auto attribute = symbolTableStack->lookUp(this->getVariableName());
            assert(attribute!=NULL);
            std::stringstream ss;
            ss<<"["<<attribute->addr<<"]";
            return ss.str();
        }else if(this->getType()==Node::TYPE_INT){
            sscanf(mTokenValue.c_str(),"%d",&this->intValue);
            return {mTokenValue};
        }else if(this->getType()==Node::TYPE_DOUBLE){
            sscanf(mTokenValue.c_str(),"%lf",&this->doubleValue);
            return {mTokenValue};
        }else if(this->getType()==Node::TYPE_CHAR){
            this->intValue = (int)mTokenValue.c_str()[1];
            if(mTokenValue.c_str()[1]=='\\'){
                this->intValue = '\n';
            }
            std::stringstream ss;
            ss<<this->intValue;
            return ss.str();
        }
    }else if(this->getName().length()==1){ /*            + - * / % = > < .         */
        switch(this->getName()[0]){
            case '+':
                program.push({"ADD", this->mChildren[0]->codeGen(), this->mChildren[1]->codeGen(), res=programNameCounter.getNumberedName("`t")});
                return res;
            case '-':
                program.push({"SUB", this->mChildren[0]->codeGen(), this->mChildren[1]->codeGen(), res=programNameCounter.getNumberedName("`t")});
                return res;
            case '*':
                program.push({"MUL", this->mChildren[0]->codeGen(), this->mChildren[1]->codeGen(), res=programNameCounter.getNumberedName("`t")});
                return res;
            case '/':
                program.push({"DIV", this->mChildren[0]->codeGen(), this->mChildren[1]->codeGen(), res=programNameCounter.getNumberedName("`t")});
                return res;
            case '%':
                program.push({"REM", this->mChildren[0]->codeGen(), this->mChildren[1]->codeGen(), res=programNameCounter.getNumberedName("`t")});
                return res;
            case '>':
                program.push({"SLT", this->mChildren[1]->codeGen(), this->mChildren[0]->codeGen(), res=programNameCounter.getNumberedName("`t")});
                return res;
            case '<':
                program.push({"SLT", this->mChildren[0]->codeGen(), this->mChildren[1]->codeGen(), res=programNameCounter.getNumberedName("`t")});
                return res;
            case '=':
                program.push({"ADD", "0", this->mChildren[1]->codeGen(), this->mChildren[0]->codeGen()});
                return "`";
                //return programNameCounter.getNumberedName("`t");
            case '.':
                if(mChildren[0]->getName().compare("[]")){
                    std::string baseAddr = getAddr(mChildren[0]);
                    std::string offsetAddr = getOffsetAddr(mChildren[0]->getStructTypeName(), mChildren[1]);
                    
                    program.push({"ADD", baseAddr, offsetAddr, res=programNameCounter.getNumberedName("`t")});
                    return std::string("[")+res+std::string("]");
                }else{
                    std::string baseAddr = mChildren[0]->codeGen();
                    baseAddr=baseAddr.substr(1,baseAddr.length()-2);
                    std::string offsetAddr = getOffsetAddr(mChildren[0]->getStructTypeName(), mChildren[1]);
                    program.push({"ADD", baseAddr, offsetAddr, res=programNameCounter.getNumberedName("`t")});
                    return std::string("[")+res+std::string("]");
                }
        }
    }else if(this->getName().length()==2){/*      != == >= <= ++ --  []   || &&  ()                          */
        if(this->getName().compare({"=="}) == 0){
            std::string subRes;
            res=programNameCounter.getNumberedName("`t");
            program.push({"SUB", this->mChildren[0]->codeGen(), this->mChildren[1]->codeGen(), subRes=programNameCounter.getNumberedName("`t")});
            program.push({"ADD", "0", "0", res});
            program.push({"BNE", subRes, "0", "1"});
            program.push({"ADD", "1", "0", res});
            return res;
        }else if(this->getName().compare({">="})==0){
            std::string subRes;
            res=programNameCounter.getNumberedName("`t");
            program.push({"SUB", this->mChildren[0]->codeGen(), this->mChildren[1]->codeGen(), subRes=programNameCounter.getNumberedName("`t")});
            program.push({"SLT", "-1", subRes, res});
            return res;
        }else if(this->getName().compare({"<="})==0){
            std::string subRes;
            res=programNameCounter.getNumberedName("`t");
            program.push({"SUB", this->mChildren[1]->codeGen(), this->mChildren[0]->codeGen(), subRes=programNameCounter.getNumberedName("`t")});
            program.push({"SLT", "-1", subRes, res});
            return res;
        }else if(this->getName().compare({"||"})==0){
            std::string subRes;
            res=programNameCounter.getNumberedName("`t");
            program.push({"ADD", this->mChildren[1]->codeGen(), this->mChildren[0]->codeGen(), subRes=programNameCounter.getNumberedName("`t")});
            program.push({"ADD", "0", "0", res});
            program.push({"BEQ", subRes, "0", "1"});
            program.push({"ADD", "1", "0", res});
            return res;
        }else if(this->getName().compare({"&&"})==0){
            std::string subRes;
            res=programNameCounter.getNumberedName("`t");
            program.push({"ADD", this->mChildren[1]->codeGen(), this->mChildren[0]->codeGen(), subRes=programNameCounter.getNumberedName("`t")});
            program.push({"ADD", "0", "0", res});
            program.push({"BNE", subRes, "2", "1"});
            program.push({"ADD", "1", "0", res});
            return res;
        }else if(this->getName().compare({"!="})==0){
            std::string subRes;
            res=programNameCounter.getNumberedName("`t");
            program.push({"SUB", this->mChildren[0]->codeGen(), this->mChildren[1]->codeGen(), subRes=programNameCounter.getNumberedName("`t")});
            program.push({"ADD", "0", "0", res});
            program.push({"BEQ", subRes, "0", "1"});
            program.push({"ADD", "1", "0", res});
            return res;
        }else if(this->getName().compare({"[]"})==0){
            std::string subRes;
            std::string baseAddr = getAddr(mChildren[0]);
            //std::stringstream ss;
            //ss<<baseAddr;
            program.push({"ADD", baseAddr, computeArrayOffset(this)/*this->mChildren[1]->codeGen()*/, res=programNameCounter.getNumberedName("`t")});
            return std::string("[") + res + std::string("]");
        }else if(this->getName().compare({"()"})==0){
            auto table = SymbolTable::getSymbolTableByName(this->mChildren[0]->getVariableName())->getTable();
            int retAddr = symbolTableStack->lookUp(this->mChildren[0]->getVariableName())->addr;
            // symbolTableStack->push(SymbolTable::getSymbolTableByName(this->mChildren[0]->getVariableName()));
            if(this->mChildren.size()==1){
                program.push({"CALL", this->mChildren[0]->getVariableName(), "NULL", "NULL"});
                std::stringstream ss;
                ss<<"["<<retAddr<<"]";
                return ss.str();
            }else{
                auto argValueExpressions = this->mChildren[1]->getChildren();
                int argCnt = 0;
                std::stack<std::string> s;
                while(true){
                    int f=true;
                    for(auto i : table){
                        if(i.second->offset == argCnt){
                            f=false;
                            std::stringstream ss;
                            ss<<"["<<i.second->addr<<"]";
                            program.push({"PUSH", ss.str(), "", ""});
                            s.push(ss.str());
                            argCnt++;
                            break;
                        }
                    }
                    if(f)break;
                }
                argCnt=0;
                /* chuan can shu */
                for(auto expression : argValueExpressions){
                    std::string argValue;
                    argValue = expression->codeGen();
                    for(auto i : table){
                        if(i.second->offset == argCnt){
                            std::stringstream ss;
                            ss<<"["<<i.second->addr<<"]";
                            // program.push({"PUSH", ss.str(), "", ""});
                            program.push({"ADD", "0", argValue, ss.str()});
                            argCnt++;
                            break;
                        }
                    }
                }
                program.push({"CALL", this->mChildren[0]->getVariableName(), "NULL", "NULL"});
                while(!s.empty()){
                    program.push({"POP", s.top(), "", ""});
                    s.pop();
                }
                std::stringstream ss;
                ss<<"["<<retAddr<<"]";
                return ss.str();
            }
        }
    }
}

std::string IfNode::codeGen(){
    Node *condition = this->mChildren[1];
    Node *thenBlock = this->mChildren[2];
    Node *elseBlock = this->getChildrenById(4);
    std::string conditionResult;
    std::string thenBlockLabel = programNameCounter.getNumberedName("IfConditionIsTrue");
    std::string elseBlockLabel = programNameCounter.getNumberedName("IfConditionIsFalse");
    std::string arterBlockLabel = programNameCounter.getNumberedName("IfStatementEnd");
    /*condition*/
    conditionResult=this->mChildren[1]->codeGen();
    program.push({"BEQ", "0", conditionResult, elseBlockLabel});
    /*then*/
    thenBlock->codeGen();
    program.push({"BEQ", "0", "0", arterBlockLabel});
    /*else*/
    program.labelNextLine(elseBlockLabel);
    if(elseBlock){
        elseBlock->codeGen();
    }
    program.labelNextLine(arterBlockLabel);
    return "`";
}

std::string ForNode::codeGen(){
    Node *initialExpressions = this->mChildren[1];
    Node *conditionExpresstion = this->mChildren[2]->getChildrenById(0);
    Node *tailExpression = this->mChildren[3];
    Node *loopBody = this->mChildren[4];

    std::string conditionResult;
    std::string loopStartLabel = programNameCounter.getNumberedName("LoopStart");
    std::string afterLoopLabel = programNameCounter.getNumberedName("LoopEnd");

    initialExpressions->codeGen();

    program.labelNextLine(loopStartLabel);
    conditionResult = conditionExpresstion->codeGen();
    program.push({"BEQ", "0", conditionResult, afterLoopLabel});

    loopBody->codeGen();
    tailExpression->codeGen();
    program.push({"BEQ", "0", "0", loopStartLabel});
    program.labelNextLine(afterLoopLabel);
    return "`";
}

std::string RetNode::codeGen(){
    std::cout<<"RerNode::codeGen(): "<<this->mChildren.size()<<"\n";
    auto table = SymbolTable::getSymbolTableByName(symbolTableStack->top()->getName())->getTable();
    /*int cnt = 0;
    std::stack<std::string> s;
    while(true){
        bool f=true;
        for(auto a : table){
            if(a.second->offset==cnt){
                f = false;
                cnt++;
                std::stringstream ss;
                ss<<"["<<a.second->addr<<"]";
                s.push(ss.str());
            }
        }
        if(f)break;
    }
    while(!s.empty()){
        program.push({"POP",s.top(),"",""});
        s.pop();
    }*/
    if(this->mChildren.size()==1){
        program.push({"RET","","",""});
    }else{
        std::stringstream ss;
        std::cout<<"using symbol table: "<<symbolTableStack->top()->getName()<<"\n";
        ss<<"["<<symbolTableStack->lookUp(symbolTableStack->top()->getName())->addr<<"]";
        program.push({"ADD", "0", mChildren[1]->codeGen(), ss.str()});
        program.push({"RET","","",""});
    }
    symbolTableStack->pop();
    return "0";
}

std::string ReadNode::codeGen(){
    std::string dst;
    dst = this->mChildren[0]->codeGen();
    program.push({"READ", dst, "", ""});
    return "`";

}

std::string WriteNode::codeGen(){
    std::string dst;
    dst = this->mChildren[0]->codeGen();
    program.push({"WRITE", dst, "", ""});
    return "`";
}


std::string StringNode::codeGen(){
    return this->mTokenValue;
}
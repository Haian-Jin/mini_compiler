%{
#include"./cCompilerCommon.hpp"
extern int yylex();
extern char *yytext;
static bool noError = true;
static Node *treeRoot;
static NameCounter nameCounter;
int yyerror(std::string);
static void error_missingSemicolon();
static void error_missingInitializations();
static void error_wrongStatement();
static void error_wrongExpression();
static void error_missingRightBrancket();
static void error_missingRightBrancket2();
static void error_elseWithNoIf();
static void eatToNewLine();
static void error_duplicatedVariable(Node *);
static void error_variableNotDeclared(std::string);
static void error_illegalArraySize(Node *);
static void error_expressionTypeError(Node *,Node *,Node *);
static void error_expressionTypeError(Node *,Node *);
static void error_typeMismatch(Node *);
static void error_variableNotDeclaredInStruct(Node *,Node *);
static void error_argumentNumberNotMatch(Node *,int);
static void error_argumentTypeNotMatch(std::vector<Node::Type>&,Node *,std::vector<std::string>&);
static void error_structNotDeclared(std::string);
static void error_notArray(Node *);
static void error_returnValueTypeMismatch(symAttribute* need, Node::Type give);
static void error_returnValueTypeMismatch(symAttribute* need, Node * give);
static void error_functionReturnsArray();
%}
%code requires {
#include"./cCompilerCommon.hpp"
}

%union{
    Node * nodePtr;
    DoubleNode * doubleNodePtr;
    IntNode * intNodePtr;
    IdentifierNodeList* identifierNodeListPtr;
    IdentifierNode* identifierNodePtr;
    VarDeclarationList* varDeclarationListPtr;
    StatementNodesBlock* statementNodesBlockPtr;
    GlobalDeclaraionNode * globalDeclaraionNodePtr;
    std::vector<VarDeclarationList*> * structMemberListPtr;
    std::vector<ExpressionNode*> * ExpressionNodeListPtr;
}

%token GOTO ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN LOGICAL_OR LOGICAL_AND EQ NE GE LE SL SR INC DEC IDENTIFIER DOUBLE_NUMBER INT_NUMBER STRING 
%token FOR DO WHILE CONTINUE BREAK IF ELSE SWITCH CASE RETURN
%token STRUCT INT DOUBLE CHAR PTR CONST DEFAULT FLOAT STATIC UNSIGNED VOID 



%type<identifierNodeListPtr> initializations structMembers
%type<identifierNodePtr> initialization IDENTIFIER  typeName type
%type<varDeclarationListPtr> paramTypes 
%type<statementNodesBlockPtr>  globalDeclaration declaration statementBlock statements statement structMemberDeclarations structMemberDeclaration
%type<nodePtr> GOTO ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN LOGICAL_OR LOGICAL_AND EQ NE GE LE SL SR INC DEC DOUBLE_NUMBER INT_NUMBER STRING FOR DO WHILE CONTINUE BREAK IF ELSE SWITCH CASE RETURN STRUCT INT DOUBLE CHAR PTR CONST DEFAULT FLOAT STATIC UNSIGNED VOID 
%type<globalDeclaraionNodePtr> cCode0 cCode 
%type<nodePtr> structTypeName pointerSpecifier 
%type<nodePtr> variable variableName  paramTypeName variableWithNoName variableWithNoNameCore initialValue initialValues functionDeclaration localDeclarations 
%type<nodePtr>  expressionStatement loopStatement branchStatement caseBlock caseStatements jumpStatement expression assignmentExpression tenaryConditionExpression
%type<nodePtr> logicalOrExpression logicalAndExpression bitwiseOrExpression bitwiseExclusiveOrExpression bitwiseAndExpression equalityComparisonExpression 
%type<nodePtr> shiftExpression arithmeticAddExpression arithmeticMulExpression castedExpression unaryExpression prefixUnaryExpression postfixUnaryExpression 
%type<nodePtr> atomicExpression relationComparisonExpression
%type<nodePtr> '+' '-' '(' ')' '[' ']' '{' '}' '~' '%' '^' '&' '*' '=' ';' '<' '>' ',' '?' '/' ':' '!' '|' '.'
%type<ExpressionNodeListPtr> paramList 





%start cCode0


%%

/* Always start from declaration of a variable or a function */
/* Generally, there are two types of C code lines: declarations(along with the initializations) and (what we called)statements */

cCode0 :
        cCode {
            treeRoot = $1;
        }
    ;

cCode :
        globalDeclaration {
            $$ = new GlobalDeclaraionNode(dynamic_cast<StatementNodesBlock*>($1));
        }
    |   cCode globalDeclaration {
            $$ = $1;
            $$->mergeGlobalStatements(dynamic_cast<StatementNodesBlock*>($2));
    }
    ;

/* declaration 用于定义变量或者定义结构体；functionDeclaration 用于定义函数 */
/* 在我们的语言中，定义分为全局和局部两种。全局定义是放在任何 statement block（语句块）之外的。 */

globalDeclaration :
        declaration { /* 全局的变量定义，兼定义结构。 */
            $$ = $1;
        }
    |   functionDeclaration { /* 语法上，所有的函数都必须要定义在全局。 */
            $$ = new StatementNodesBlock(); 
            $$->addStatementNode(dynamic_cast<StatementNode*>($1));
        }

    
    /* |   statement { // 不允许在全局范围内出现不是定义的语句。 
            yyerror("syntax error");
            std::cout<<"C-- only supports statements within a function.\n";
        }
    |   '}' {
            yyerror("syntax error");
            std::cout<<"a '}' without its '{'.\n";
        } */
    ;


declaration :
        type initializations ';' { /* 定义变量 */
            $$ = new StatementNodesBlock();
            $$->createMultiVarDeclaration(dynamic_cast<IdentifierNode *>($1), dynamic_cast<IdentifierNodeList *>($2));

        }
    // TODO
     |   STRUCT IDENTIFIER { // 定义结构体
            // 取得结构体名之后，即使为该结构体构建符号表
            $2->setType(Node::TYPE_STRUCT);
            $2->setKind(Node::KIND_ATTRIBUTE);
            $2->setStructTypeName($2->getTokenValue());
            $2->setVariableName($2->getTokenValue());
            symbolTableStack->insert(new symAttribute($2));
            symbolTableStack->push(new SymbolTable($2->getStructTypeName()));
        } '{' structMemberDeclarations '}' ';' { 
            //$$ = new Node(nameCounter.getNumberedName("declaration"), 6, $1, $2, $4, $5, $6, $7);
            $$ = new StructDeclarationNode(dynamic_cast<IdentifierNode *>($2), dynamic_cast<StatementNodesBlock *>($5));
            // $$->createStructDeclaration(dynamic_cast<IdentifierNode *>($2), dynamic_cast<StatementNodesBlock *>($5));
            symbolTableStack->pop();
        }
    /* |   type initializations error  {
            error_missingSemicolon(); 
        } */
    ;

type :
        typeName {$$ = $1;}          /* int */
    |   CONST typeName {$$ = $2;}     /* const int, 不实现这一条。 */     
    |   STATIC typeName {$$ = $2;}   /* static int, 不实现这一条。 */
    ;

typeName :
        INT { 
            $$ = new IdentifierNode($1->getTokenValue(), true);
            $$->setPosition(csLineCnt, csColumnCnt);
        }               
    |   UNSIGNED INT { /* 不实现这一条 */}  
    |   CHAR { 
            $$ = new IdentifierNode($1->getTokenValue(), true);
            $$->setPosition(csLineCnt, csColumnCnt);
        }  
    |   FLOAT { /* 不实现这一条, 只支持double */
            $$ = new IdentifierNode($1->getTokenValue(), true);
            $$->setPosition(csLineCnt, csColumnCnt);
        }  
    |   DOUBLE { 
            $$ = new IdentifierNode($1->getTokenValue(), true);
            $$->setPosition(csLineCnt, csColumnCnt);
        }  
    |   VOID { 
            $$ = new IdentifierNode($1->getTokenValue(), true);
            $$->setPosition(csLineCnt, csColumnCnt);
        }  
    |   structTypeName { /* TODO */
            $$ = new IdentifierNode($1->getStructTypeName(), true);
            $$->setType(Node::TYPE_STRUCT);
            $$->setKind(Node::KIND_ATTRIBUTE);
            $$->setStructTypeName($1->getStructTypeName());
            $$->setPosition($1);
        }  
    ;

/* 定义结构体。注：在定义有名结构体的同时定义该结构体的变量，对应的产生式移到 declaration 里面去了。 */
/* （这是我设计产生式时候的失误） */
structTypeName : 
        STRUCT '{' {
            /* 为该匿名结构体维护符号表 */
            std::string name = nameCounter.getNumberedName("`Unamed_Structure");
            symbolTableStack->insert(new symAttribute(name, Node::TYPE_STRUCT, Node::KIND_ATTRIBUTE, std::vector<Node::Type>(), std::vector<std::string>(), 
                                     std::vector<int>(), name, csLineCnt, csColumnCnt-1));
            symbolTableStack->push(new SymbolTable(name));
        } structMemberDeclarations '}' {
            $$ = new Node(nameCounter.getNumberedName("structTypeName"), 4, $1, $2, $4, $5);
            $$->setType(Node::TYPE_STRUCT);
            $$->setKind(Node::KIND_ATTRIBUTE);
            $$->setStructTypeName(symbolTableStack->top()->getName());
            $$->setPosition($1);
            symbolTableStack->pop();
        }
    |   STRUCT IDENTIFIER { /* 一个之前已经定义过的结构体名字。 */
            $$ = new Node(nameCounter.getNumberedName("structTypeName"), 2, $1, $2);
            $$->setType(Node::TYPE_STRUCT);
            $$->setKind(Node::KIND_ATTRIBUTE);
            $$->setStructTypeName($2->getTokenValue()/*nameCounter.getNumberedName($2->getTokenValue())*/);
            $$->setPosition($1);
            if(symbolTableStack->lookUp($2->getTokenValue())==0){
                error_structNotDeclared($2->getTokenValue());
            }
        }
    ;

/* 定义结构体的成员变量。这个和 declarations 的不同在于，这里不能定义函数，也不能做初始化。 */
structMemberDeclarations :
        structMemberDeclaration {
            $$ = $1;
        }
    |   structMemberDeclarations structMemberDeclaration {
            $$ = $1;
            $$->mergeStatements($2);
        }
    ;

structMemberDeclaration :
        type structMembers ';' {
            // $$ = new Node(nameCounter.getNumberedName("structMemberDeclarations"), 3, $1, $2, $3);
            $$ = new StatementNodesBlock();
            for(int i=0;i<$2->getChildrenNumber();i++){
                $2->getChildrenById(i)->setType($1);
            }
            for(int i=0;i<$2->getChildrenNumber();i++){
                if($2->getChildrenById(i)->isTerminal() && $2->getChildrenById(i)->getTokenValue().compare(",")==0) continue;
                if(symbolTableStack->insert(new symAttribute($2->getChildrenById(i))) == false){
                    error_duplicatedVariable($2->getChildrenById(i));
                }else{

                }
            }
            $$->createMultiVarDeclaration($1,$2);
        }
    ;

structMembers : /* 注：结构体的成员变量不能做初始化 */
        variable {
            $$ = new IdentifierNodeList();
            $$->addIdentifierNode(dynamic_cast<IdentifierNode*>($1));
        }
    |   structMembers ',' variable {
            $$ = $1;
            $$->addIdentifierNode(dynamic_cast<IdentifierNode*>($3));
        }
    ;

/* 初始化，负责在定义变量的同时赋予初始值。当然也可以不赋予初始值。 */
/* 有时间的话就实现一下初始值，没时间就算了。 */
initializations :
        initialization {
            $$ = new IdentifierNodeList();
            $$->addIdentifierNode(dynamic_cast<IdentifierNode*>($1));
        }
    |   initializations ',' initialization {
            $$ = $1;
            $$->addIdentifierNode(dynamic_cast<IdentifierNode*>($3));
        }
    ;

initialization :
        variable {                       /* int a; 没有初始值 */
            $$ = dynamic_cast<IdentifierNode*>($1);
        }
    |   variable '=' initialValue {   /* int a=10; 有初始值 暂时不实现 */
        }
    ;

variable :
        pointerSpecifier variableName {  /* int *a; 指针变量，这里不打算实现。 */
           // $$ = new Node(nameCounter.getNumberedName("variable"), 2, $1, $2);
        }
    |   variableName { /* 不是指针的变量 */
            $$ = $1;
        }
    ;

/* 我们不打算实现指针。 */
pointerSpecifier :
        '*' { /* a simple pointer */
            $$ = new Node(nameCounter.getNumberedName("pointerSpecifier"), 1, $1);
        }
    |   pointerSpecifier '*' { /* a pointer to another pointer variable */
            $$ = new Node(nameCounter.getNumberedName("pointerSpecifier"), 2, $1, $2);
        }
    |   '*' CONST { /* a pointer to a const variable */
            $$ = new Node(nameCounter.getNumberedName("pointerSpecifier"), 2, $1, $2);
        }
    |   pointerSpecifier '*' CONST { /* a pointer to another pointer which is a pointer to a const value */
            $$ = new Node(nameCounter.getNumberedName("pointerSpecifier"), 3, $1, $2, $3);
        }
    ;

variableName :
        IDENTIFIER { /* 一个普通的变量 */
            $$ = $1;
            $$ = new IdentifierNode($1->getTokenValue(), false);
            $$->setKind(Node::KIND_VARIABLE);
        }
    |   variableName '[' INT_NUMBER ']' {    /* 数组，可以是多维度的。其中 NUMBER 必须是整数。 */
            // $$ = new IdentifierNode(nameCounter.getNumberedName("variableName"), 4, $1, $2, $3, $4);
            if(!(checkType($3,Node::TYPE_INT) && checkKind($3,Node::KIND_CONSTANT))){
                error_illegalArraySize($3);
            }else{
                $$ = $1;
                auto arraySizes = $$->getArraySizes();
                int newSize = dynamic_cast<IntNode*>($3)->value;
                //sscanf($3->getTokenValue().c_str(),"%d",&newSize);
                arraySizes.push_back(newSize);
                $$->setArraySizes(arraySizes);
                auto a = $$->getArraySizes();
                //assert(a!=NULL);
//                std::cout<<"array: ";std::cout<<a.size()<<std::endl;
            }
        }
    |   '(' variable ')' {              /* 这一条弃之不用，太复杂了 */
            $$ = new Node(nameCounter.getNumberedName("variableName"), 3, $1, $2, $3);
        }
    |   variableName '(' ')' {           /* 函数定义 */
           $$ = new FuncNameAndArgsNode(dynamic_cast<IdentifierNode *>($1), nullptr);
        }
    |   variableName '(' paramTypes ')' {    /* 函数定义 */
            $$ = new FuncNameAndArgsNode(dynamic_cast<IdentifierNode *>($1), dynamic_cast<VarDeclarationList *>($3));
        }
    ;

paramTypes :    /* 参数可以没有名字、只有类型。但是我们的参数必须给名字。 */
        paramTypeName {
            $$ = new VarDeclarationList();
            $$->mVarDeclarationList.push_back(dynamic_cast<VariableDeclarationNode *>($1));
        }
    |   paramTypes ',' paramTypeName {
            $$ = $1;
            $$->mVarDeclarationList.push_back(dynamic_cast<VariableDeclarationNode *>($3));
        }
    ;

paramTypeName :
    /*
        type {   // int (*f)(double,char); 不实现这一条，太复杂 
            $$ = new Node(nameCounter.getNumberedName("paramTypeName"), 1, $1);
        }
    |   type variableWithNoName { // 无名字的指针变量。不实现这一条，天复杂 
            $$ = new Node(nameCounter.getNumberedName("paramTypeName"), 2, $1, $2);
        }
    |   */
        type variable {      // 这一条是要正常实现的，定义函数用的 
            $$ = new VariableDeclarationNode(dynamic_cast<IdentifierNode *>($1), dynamic_cast<IdentifierNode *>($2));

        }
    ;

/* 不用管这个，都不实现的。 */
variableWithNoName :        /* !! 如果要阅读这个的话，请和 variable 相关的产生式一起阅读 !!*/
        pointerSpecifier {       /* 不实现指针 */
            $$ = new Node(nameCounter.getNumberedName("variableWithNoName"), 1, $1);
        }
    |   variableWithNoNameCore { 
            $$ = new Node(nameCounter.getNumberedName("variableWithNoName"), 1, $1);
        }
    ;

/* 不用管这个，都不实现的。 */
variableWithNoNameCore :    /* !! read this along with 'variableName' !!*/
        variableWithNoNameCore '[' INT_NUMBER ']' {
            $$ = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 4, $1, $2, $3, $4);
        }
    |   '(' variableWithNoName ')' {
            $$ = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 3, $1, $2, $3);
        }
    |   variableWithNoNameCore '(' ')' {  /* a function taking another function as param... */
            $$ = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 3, $1, $2, $3);
        }
    |   variableWithNoNameCore '(' paramTypes ')' { /* a function taking another function as param... */
            $$ = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 4, $1, $2, $3, $4);
        }
    |   '[' ']' {            /* because it has no name, it must stop some way. Below is some terminators */
            $$ = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 2, $1, $2);
        }
    |   '(' ')' {
            $$ = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 2, $1, $2);
        }
    |   '(' paramTypes ')' { /* a function taking another function as param... */
            $$ = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 3, $1, $2, $3);
        }
    ;

/* 初始值，如果要在定义的时候初始化的话，initialValue 就是跟在 = 后面的部分。有时间的话就实现一下初始值，没时间就算了。 */
initialValue :
        '{' initialValues '}' {          /* int a[10]={1}; 初始化列表 */
            $$ = new Node(nameCounter.getNumberedName("initialValue"), 3, $1, $2, $3);
        }
    |   assignmentExpression {          /* int a=5+6; int b=a=3; 普通的初始值 */
            $$ = new Node(nameCounter.getNumberedName("initialValue"), 1, $1);
    }
    ;

/* 初始化列表 */
initialValues :
        initialValue {
            $$ = new Node(nameCounter.getNumberedName("initialValues"), 1, $1);
        }
    |   initialValues ',' initialValue { /* int a[10]={1,2,3} */
            $$ = $1;
            $$->addChild($2);
            $$->addChild($3);
        }
    ;

/* 函数定义 */
functionDeclaration :   
        type variable  statementBlock {
            $$ = new FunctionDeclarationNode(dynamic_cast<IdentifierNode *>($1), dynamic_cast<FuncNameAndArgsNode *>($2), dynamic_cast<StatementNodesBlock*>($3));
        }
    ;

/* 语句块，即“{...}” */
statementBlock : 
        '{' '}' { /* 可以 {} 这样而不必 {;} 这样 */
            $$ = new StatementNodesBlock();
            $$->addStatementNode(dynamic_cast<StatementNode *>(new NullStatementNode()));
        }
    |   '{' statements '}' {
            $$ = $2;
        }

    /* 暂时先不管
    |   '{' localDeclarations '}' {
            $$ = new Node(nameCounter.getNumberedName("statementBlock"), 3, $1, $2, $3);
        }
    |   '{' localDeclarations statements '}' { // 如果要定义局部变量，必须要把所有的定义语句语句块的最前面。
            $$ = new Node(nameCounter.getNumberedName("statementBlock"), 4, $1, $2, $3, $4);
        }
    |   '{' localDeclarations statements error '}' {
            yyerror("Declaration after statements");
        }
    */
        
    ;

/* 局部变量定义。和全局定义的区别在于，局部不能定义函数。 */
localDeclarations :
        declaration {
            $$ = new Node(nameCounter.getNumberedName("localDeclarations"), 1, $1);
        }
    |   localDeclarations declaration {
            $$ = $1;
            $$->addChild($2);
        }
    ;

statements :    /* 一串语句 */
        statement {
            $$ = $1;
        }
    |   statements statement {
            $$ = $1;
            $$->mergeStatements(dynamic_cast<StatementNodesBlock *>($2));
        }
    ;

statement :     /* 一个语句，以封号“;”结尾。（但是语句块可以不以封号结尾） */
        declaration {
            $$ = $1;
        }
    |   expressionStatement { // 表达式，也是最常见的语句
            $$ = new StatementNodesBlock();
            $$->addStatementNode(dynamic_cast<StatementNode *>($1));
        }
    |   loopStatement { // 循环
            $$ = new StatementNodesBlock();
            $$->addStatementNode(dynamic_cast<StatementNode *>($1));
        }
    |   { symbolTableStack->push(new SymbolTable(nameCounter.getNumberedName("NestedBlock"))); } statementBlock { // 语句块
            // 注：非函数体的语句块是管变量的生命周期的，所以这里要维护符号表。 
            // 不能把这个维护放在 statementBlock:'{'...'}' 这个产生式里面，因为这样的话函数体语句块会维护两次符号表。 
            // $$ = new Node(nameCounter.getNumberedName("statement"), 1, $2);
            $$ = $2;
            symbolTableStack->pop();
        }     
    |   branchStatement {
            $$ = new StatementNodesBlock();
            $$->addStatementNode(dynamic_cast<StatementNode *>($1));
        }
    |   jumpStatement {
            $$ = new StatementNodesBlock();
            $$->addStatementNode(dynamic_cast<StatementNode *>($1));
        }
    |   error ';' {
        error_wrongStatement();
    } 
    ;

expressionStatement :
        ';' { /* 注：空语句是一个 expressionStatement */
            $$ = new NullStatementNode();
        }
    |   expression ';' {
            $$ = new ExpressionStatementNode(dynamic_cast<ExpressionNode *>($1));
        }
    |   expression error {
            error_missingSemicolon();
        }
    ;

loopStatement : /* for, while, do-while */
        FOR '(' expressionStatement expressionStatement expression ')' statement { /* 不允许 for(int i;i<10;i++) 这样 */
            $5 = new ExpressionStatementNode(dynamic_cast<ExpressionNode *>($5));
            $$ = new ForStatementNode(dynamic_cast<ExpressionStatementNode *>($3), dynamic_cast<ExpressionStatementNode *>($4), dynamic_cast<ExpressionStatementNode *>($5), dynamic_cast<StatementNodesBlock *>($7));
        }
    |   WHILE '(' expression ')' statement {
            $3 = new ExpressionStatementNode(dynamic_cast<ExpressionNode *>($3));
            $$ = new WhileStatementNode(dynamic_cast<ExpressionStatementNode *>($3), dynamic_cast<StatementNodesBlock *>($5));
        }
    // do-while暂不实现
    |   DO statement WHILE '(' expression ')' ';' {
            $$ = new Node(nameCounter.getNumberedName("loopStatement"), 7, $1, $2, $3, $4, $5, $6, $7);
        }
    
    |   WHILE '(' expression error { error_missingRightBrancket(); } ')' statement /* error recovery */
    |   WHILE '(' error { error_wrongExpression; } ')' statement { 

        }
    ;

/* 分支跳转语句 */
branchStatement :
        IF '(' expression ')' statement {
            $3 = new ExpressionStatementNode(dynamic_cast<ExpressionNode *>($3));
            $$ = new IfStatementNode(dynamic_cast<ExpressionStatementNode *>($3), dynamic_cast<StatementNodesBlock *>($5));  
        }
    |   IF '(' expression ')' statement ELSE statement { /* （else悬挂问题）这一条和上一条不能颠倒。 */
            $3 = new ExpressionStatementNode(dynamic_cast<ExpressionNode *>($3));
            $$ = new IfStatementNode(dynamic_cast<ExpressionStatementNode *>($3), dynamic_cast<StatementNodesBlock *>($5), dynamic_cast<StatementNodesBlock *>($7));
        }
    |   SWITCH '(' expression ')' caseBlock /* 我们不打算实现 SWITCH-CASE，因为太复杂了 */
    |   error  ELSE statement {
            { error_elseWithNoIf(); }
        }
    ;   /* too complex, SWITCH is not supported yet */

/* 不实现 */
caseBlock :
        '{' caseStatements '}'
    ;

/* 不实现 */
caseStatements :
        CASE tenaryConditionExpression ':' statement
    |   DEFAULT ':' statement
    ;

/* 无条件跳转语句 */
jumpStatement :
        RETURN ';' { /* 函数返回，这里要检查返回类型 */
            $$ = new ReturnStatementNode();
        }
    |   RETURN expression ';' { /* 函数返回，这里要检查返回类型 */
            $$ = new ReturnStatementNode(dynamic_cast<ExpressionNode *>($2));
        }
    |   CONTINUE ';' { /* 循环控制 */
            $$ = new ContinueStatementNode();
        }
    |   BREAK ';' { /* 循环控制 */
            $$ = new BreakStatementNode();
        }
    /*
    |   GOTO IDENTIFIER ';' { // 太复杂了，不实现 
            $$ = new Node(nameCounter.getNumberedName("jumpStatement"), 3, $1, $2, $3);
        }
    */
    ; 


/* 表达式，有十六个优先级（大大小小加起来大概有十九个） */

/* PRIORITY 15: "," */

expression : 
        assignmentExpression {
            $$ = $1;
        }
    // 暂时先不实现 TODO
    /* 
    |   expression ',' assignmentExpression {
            $$ = $1;
            $$->addChild($2);
            $$->addChild($3);
            // 一串逗号分隔的表达式的值，是最后一个表达式的值。
            $$->copyFrom($$->getChildrenById($$->getChildrenNumber()-1));
        }
    */
    ;

/* PRIORITY 14: "=, +=, -=, ..." assignment */

assignmentExpression :
        tenaryConditionExpression {
            $$ = $1;
        }
    |   unaryExpression '=' assignmentExpression {
            if(dynamic_cast<IdentifierNode*>($1)!=NULL)
                $$ = new AssignmentNode(dynamic_cast<IdentifierNode*>($1), dynamic_cast<ExpressionNode*>($3));
            else if(dynamic_cast<ArrayIndexNode*>($1)!=NULL){
                $$ = new ArrayAssignmentNode(dynamic_cast<ArrayIndexNode*>($1), dynamic_cast<ExpressionNode*>($3));// here??
            }else if(dynamic_cast<StructMemberNode*>($1)!=NULL){
                $$ = new StructMemberAssignmentNode(dynamic_cast<StructMemberNode*>($1), dynamic_cast<ExpressionNode*>($3));
            }else{
                std::cout<<"Some thing wrong at line "<<csLineCnt<<std::endl;
            }
            /* if(!(checkKind($1, Node::KIND_VARIABLE)) || $1->isArray()){
                if (!(checkKind($1, Node::KIND_VARIABLE))) {
                    printf("hhhhh");
                }
                error_expressionTypeError($1,$2,$3);
            } */
            if(!typeMatch($1, $3)){
                error_typeMismatch($1);
            }

        }
    // 暂时只实现= TODO
    /* |   unaryExpression ADD_ASSIGN assignmentExpression {
            $2 = new AssignmentNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFromChild();
            if(!(checkKind($1, Node::KIND_VARIABLE))){
                error_expressionTypeError($1,$2,$3);
            }
            if(!typeMatch($1, $3)){
                error_typeMismatch($1);
            }
        }
    |   unaryExpression SUB_ASSIGN assignmentExpression {
            $2 = new AssignmentNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFromChild();
            if(!(checkKind($1,Node::KIND_VARIABLE))){
                error_expressionTypeError($1,$2,$3);
            }
            if(!typeMatch($1,$3)){
                error_typeMismatch($1);
            }
        }
    |   unaryExpression MUL_ASSIGN assignmentExpression {
            $2 = new AssignmentNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFromChild();
            if(!(checkKind($1,Node::KIND_VARIABLE))){
                error_expressionTypeError($1,$2,$3);
            }
            if(!typeMatch($1,$3)){
                error_typeMismatch($1);
            }
        }
    |   unaryExpression DIV_ASSIGN assignmentExpression {
            $2 = new AssignmentNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFromChild();
            if(!(checkKind($1,Node::KIND_VARIABLE))){
                error_expressionTypeError($1,$2,$3);
            }
            if(!typeMatch($1,$3)){
                error_typeMismatch($1);
            }
        } */
    ;

/* PRIORITY 13: "?:" tenary conditional operator */

tenaryConditionExpression :
        logicalOrExpression {
            $$ = $1;
        }
    |   logicalOrExpression '?' expression ':' tenaryConditionExpression {/* Hint: right hand of ':' cannot be expression because no '=' should appear at the right hand of ':'. */
            $$ = new TenaryOperatorNode({"?:"}, 3, $1, $3, $5);
            $$->copyFromChild();
            $$->setType(Node::TYPE_INT);
            if($3->getType()==Node::TYPE_DOUBLE||$5->getType()==Node::TYPE_DOUBLE)$$->setType(Node::TYPE_DOUBLE);
            $$->setKind(Node::KIND_CONSTANT);
            if(!(checkType($1,Node::TYPE_INT))){
                error_expressionTypeError($1,$$);
            }
            if($1->isArray()){
                error_expressionTypeError($1,$$);
            }
        }
    ;

/* PRIORITY 12: "||" logical OR */

logicalOrExpression :
        logicalAndExpression {
            $$ = $1;
        }
    |   logicalOrExpression LOGICAL_OR logicalAndExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3), false);
            $$->setPosition($2);

            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            if(!(checkType($1,Node::TYPE_INT)&&checkType($3,Node::TYPE_INT)) || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    ;

/* PRIORITY 11: "&&" logical AND */

logicalAndExpression :
        bitwiseOrExpression {
            $$ = $1;
        }
    |   logicalAndExpression LOGICAL_AND bitwiseOrExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3), false);
            $$->setPosition($2);

            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            if(!(checkType($1,Node::TYPE_INT)&&checkType($3,Node::TYPE_INT)) || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    ;

/* PRIORITY 10: "|" bitwise OR */

bitwiseOrExpression :
        bitwiseExclusiveOrExpression {
            $$ = $1;
        }
    |   bitwiseOrExpression '|' bitwiseExclusiveOrExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3), false);
            $$->setPosition($2);

            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            if(!(checkType($1,Node::TYPE_INT)&&checkType($3,Node::TYPE_INT)) || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    ;

/* PRIORITY 9: "^" bitwise EXCLUSIVE OR */

bitwiseExclusiveOrExpression :
        bitwiseAndExpression {
            $$ = $1;
        }
    |   bitwiseExclusiveOrExpression '^' bitwiseAndExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3), false);
            $$->setPosition($2);

            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            if(!(checkType($1,Node::TYPE_INT)&&checkType($3,Node::TYPE_INT)) || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    ;

/* PRIORITY 8: "&" bitwise AND */

bitwiseAndExpression :
        equalityComparisonExpression {
            $$ = $1;
        }
    |   bitwiseAndExpression '&' equalityComparisonExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3), false);
            $$->setPosition($2);

            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            if(!(checkType($1,Node::TYPE_INT)&&checkType($3,Node::TYPE_INT)) || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    ;

/* PRIORITY 7: "==, !=" compare equality */

equalityComparisonExpression :
        relationComparisonExpression {
            $$ = $1;
        }
    |   equalityComparisonExpression EQ relationComparisonExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3), false);
            $$->setPosition($2);

            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            /*if(checkType($1,Node::TYPE_STRUCT)||checkType($1,Node::TYPE_VOID)||checkType($1,Node::TYPE_STRING)||checkType($3,Node::TYPE_STRUCT)||checkType($3,Node::TYPE_VOID)||checkType($3,Node::TYPE_STRING)){
                error_expressionTypeError($1,$2,$3);
            }*/
            if(!typeMatch($1,$3) || $1->getType()==Node::TYPE_VOID || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    |   equalityComparisonExpression NE relationComparisonExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3), false);
            $$->setPosition($2);

            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            if(!typeMatch($1,$3) || $1->getType()==Node::TYPE_VOID || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    ;

/* PRIORITY 6: "<, >, <=, >=" compare relation */

relationComparisonExpression :
        shiftExpression {
            $$ = $1;
        }
    |   relationComparisonExpression '<' shiftExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3), false);
            $$->setPosition($2);

            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            if(checkType($1,Node::TYPE_STRUCT)||checkType($1,Node::TYPE_VOID)||checkType($1,Node::TYPE_STRING)||checkType($3,Node::TYPE_STRUCT)||checkType($3,Node::TYPE_VOID)||checkType($3,Node::TYPE_STRING)){
                error_expressionTypeError($1,$2,$3);
            }
            if($1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    |   relationComparisonExpression '>' shiftExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3), false);
            $$->setPosition($2);

            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            if(checkType($1,Node::TYPE_STRUCT)||checkType($1,Node::TYPE_VOID)||checkType($1,Node::TYPE_STRING)||checkType($3,Node::TYPE_STRUCT)||checkType($3,Node::TYPE_VOID)||checkType($3,Node::TYPE_STRING)){
                error_expressionTypeError($1,$2,$3);
            }
            if($1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    |   relationComparisonExpression LE shiftExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3), false);
            $$->setPosition($2);

            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            if(checkType($1,Node::TYPE_STRUCT)||checkType($1,Node::TYPE_VOID)||checkType($1,Node::TYPE_STRING)||checkType($3,Node::TYPE_STRUCT)||checkType($3,Node::TYPE_VOID)||checkType($3,Node::TYPE_STRING)){
                error_expressionTypeError($1,$2,$3);
            }
            if($1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    |   relationComparisonExpression GE shiftExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3), false);
            $$->setPosition($2);

            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            if(checkType($1,Node::TYPE_STRUCT)||checkType($1,Node::TYPE_VOID)||checkType($1,Node::TYPE_STRING)||checkType($3,Node::TYPE_STRUCT)||checkType($3,Node::TYPE_VOID)||checkType($3,Node::TYPE_STRING)){
                error_expressionTypeError($1,$2,$3);
            }
            if($1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    ;

/* PRIORITY 5: ">>, <<" shift operator */

shiftExpression :
        arithmeticAddExpression {
            $$ = $1;
        }
    |   shiftExpression SL arithmeticAddExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3), false);
            $$->setPosition($2);

            if(!(checkType($1,Node::TYPE_INT)&&checkType($3,Node::TYPE_INT)) || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    |   shiftExpression SR arithmeticAddExpression  {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3), false);
            $$->setPosition($2);

            if(!(checkType($1,Node::TYPE_INT)&&checkType($3,Node::TYPE_INT)) || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    ;

/* PRIORITY 4: "+, -" arithmetic add */

arithmeticAddExpression :
        arithmeticMulExpression {
            $$ = $1;
        }
    |   arithmeticAddExpression '+' arithmeticMulExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3));
            $$->setPosition($2);

            // 不知道要不要留
            if($1->getType()==Node::TYPE_STRUCT || $3->getType()==Node::TYPE_STRUCT || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    |   arithmeticAddExpression '-' arithmeticMulExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3));
            $$->setPosition($2);

            // 不知道要不要留
            if($1->getType()==Node::TYPE_STRUCT || $3->getType()==Node::TYPE_STRUCT || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    ;

/* PRIORITY 3: "*, /, %" arithmetic mul */

arithmeticMulExpression :
        unaryExpression {
            $$ = $1;
        }
    |   arithmeticMulExpression '*' castedExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3));
            $$->setPosition($2);

            // 不知道要不要留
            if($1->getType()==Node::TYPE_STRUCT || $3->getType()==Node::TYPE_STRUCT || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    |   arithmeticMulExpression '/' castedExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3));
            $$->setPosition($2);

            // 不知道要不要留
            if($1->getType()==Node::TYPE_STRUCT || $3->getType()==Node::TYPE_STRUCT || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    |   arithmeticMulExpression '%' castedExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3));
            $$->setPosition($2);

            // 不知道要不要留
            if($1->getType()==Node::TYPE_STRUCT || $3->getType()==Node::TYPE_STRUCT || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    ;

/* PRIORITY 2: typecasting */
/* 类型转换这个我们不实现。只用第一个产生式。 */

castedExpression :
       unaryExpression {
            $$ = $1;
        }
    ;

/* PRIORITY 1: "++, --, !, ~" unary operator, and ". ->" */
/* 前++比后++优先的。原因是 ++a[i] 的意思是 ++(a[i]) 而不是 (++a)[i] */

unaryExpression :
        prefixUnaryExpression {
            $$ = $1;
        }
    |   postfixUnaryExpression {
            $$ = $1;
        }
    ;

prefixUnaryExpression :
        INC postfixUnaryExpression {/* ++a, especially ++a[i] is ++(a[i]) but not (++a)[i] */
            $1 = new UnaryOperatorNode(std::string("pre")+$1->getName(), 1, $2);
            $$ = $1;
            $$->copyFromChild();
            if(!checkKind($2, Node::KIND_VARIABLE) || $2->isArray() || $2->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError($2,$1);
            }
        }
    |   DEC postfixUnaryExpression {/* --a, the same as ++a[i] */
            $1 = new UnaryOperatorNode(std::string("pre")+$1->getName(), 1, $2);
            $$ = $1;
            $$->copyFromChild();
            if(!checkKind($2, Node::KIND_VARIABLE) || $2->isArray() || $2->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError($2,$1);
            }
        }
    |   '!' postfixUnaryExpression {/* logical NOT */
            $1 = new UnaryOperatorNode($1->getName(), 1, $2);
            $$ = $1;
            $$->copyFromChild();
            if(!checkType($2, Node::TYPE_INT)){
                error_expressionTypeError($2,$1);
            }
        }
    |   '~' postfixUnaryExpression {/* bitwise NOT */
            $1 = new UnaryOperatorNode($1->getName(), 1, $2);
            $$ = $1;
            $$->copyFromChild();
            if(!checkType($2, Node::TYPE_INT)){
                error_expressionTypeError($2,$1);
            }
        }
    |   '-' postfixUnaryExpression {/* negative */
            $1 = new UnaryOperatorNode($1->getName(), 1, $2);
            $$ = $1;
            if(checkType($2, Node::TYPE_STRUCT)){
                error_expressionTypeError($2,$1);
            }
        }
    ;

postfixUnaryExpression :
        atomicExpression {
            $$ = $1;
        }
    |   postfixUnaryExpression INC {/* a++, espetially a[i]++ is allowed, (a[i])++ is not necessary */
            $2 = new UnaryOperatorNode(std::string("post")+$2->getName(), 1, $1);
            $$ = $2;
            $$->copyFromChild();
            if(!checkKind($1, Node::KIND_VARIABLE) || $1->isArray() || $1->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError($1,$2);
            }
        }
    |   postfixUnaryExpression DEC {/* a-- */
            $2 = new UnaryOperatorNode(std::string("post")+$2->getName(), 1, $1);
            $$ = $2;
            $$->copyFromChild();
            if(!checkKind($1, Node::KIND_VARIABLE) || $1->isArray() || $1->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError($1,$2);
            }
        }
    |   postfixUnaryExpression '[' assignmentExpression ']' {/* array a[10], corresponding to prefix ++ */
            if(dynamic_cast<IdentifierNode*>($1)!=NULL){
                std::vector<ExpressionNode*> indexList;
                indexList.push_back(dynamic_cast<ExpressionNode*>($3));
                $$ = new ArrayIndexNode({"[]"}, dynamic_cast<ExpressionNode*>($1), indexList);
            }else{
                std::vector<ExpressionNode*> indexList = dynamic_cast<ArrayIndexNode*>($1)->mArrayIndexs;
                indexList.push_back(dynamic_cast<ExpressionNode*>($3));
                $$ = new ArrayIndexNode({"[]"}, dynamic_cast<ExpressionNode*>(dynamic_cast<ArrayIndexNode*>($1)->mArrayName), indexList);
            }
            /*
            $$ = new BinaryOperatorNode({"[]"}, 2, $1, $3);
            $$->copyFromChild();
            if(!$1->isArray()){
                error_notArray($1);
            }else {
                if(!checkType($3, Node::TYPE_INT)){
                    error_expressionTypeError($3,$$);
                }
                /* 减少一个维度 *//*
                auto arraySizes = $$->getArraySizes();
                arraySizes.erase(arraySizes.begin(),arraySizes.begin()+1);
                $$->setArraySizes(arraySizes);
                Node *p = $$;
                std::vector<ExpressionNode*> indexList;
                int dontDead = 0;
                while(dynamic_cast<IdentifierNode*>(p)==NULL){
                    dontDead++;
                    indexList.push_back(dynamic_cast<ExpressionNode*>(p->getChildrenById(1)));
                    p = p->getChildrenById(0);
                    if(dontDead>=100){
                        throw("dead loop");
                    }
                }
                for(int i=0;i<indexList.size()/2;i++){
                    auto t = indexList[i];
                    indexList[i] = indexList[indexList.size()-i-1];
                    indexList[indexList.size()-i-1] = t;
                }
                std::cout<<"ChangedIntoArray\n";
                $$ = new ArrayIndexNode({"[]"}, dynamic_cast<ExpressionNode*>(p), indexList);
            }*/
        }
    |   postfixUnaryExpression '(' paramList ')' {/* function, f()[i], f[i](), f[i]()[j] are all allowed，但我们不=实现它。 */
            $$ = new FunctionCallNode({"()"}, 2, $1, $3);
            $$->copyFromChild();
            for(auto i : *$3){
                dynamic_cast<FunctionCallNode *>($$)->addArgument(i);
            }
            /*if(!(checkKind($1, Node::KIND_FUNCTION))){
                error_expressionTypeError($1,$2);
            }else{
                std::vector<Node::Type> argList;
                std::vector<std::string> argListStructName;
                for(int i=0; i<$3->getChildrenNumber(); i++){
                    auto child = $3->getChildrenById(i);
                    if(child->isTerminal() && child->getTokenValue().compare(",")==0)continue;
                    argList.push_back(child->getType());
                    if(child->getType()==Node::TYPE_STRUCT){
                        argListStructName.push_back(child->getStructTypeName());
                    }else{
                        argListStructName.push_back({""});
                    }
                    (dynamic_cast<FunctionCallNode *>($$))->addArgument(child);
                }
                if(argList.size()!=$1->getArgList().size()){
                    //std::cout<<"~";
                    error_argumentNumberNotMatch($1,argList.size());
                }else{
                    if(!typeMatch(argList,$1,argListStructName)){
                        error_argumentTypeNotMatch(argList,$1,argListStructName);
                    }
                }
            }*/
        }
    |   postfixUnaryExpression '(' ')'           {/* function with no params. */
            $$ = new FunctionCallNode({"()"}, 1, $1);
            $$->copyFromChild();
            /*if(!(checkKind($1, Node::KIND_FUNCTION))){
                error_expressionTypeError($1,$$);
            }else {
                if($1->getArgList().size()!=0){
                    error_argumentNumberNotMatch($1,0);
                }
            }*/
        }
    |   postfixUnaryExpression '.' IDENTIFIER    {/* struct's member (a.val) */
            $$ = new StructMemberNode($2->getTokenValue(), dynamic_cast<IdentifierNode *>($1), dynamic_cast<IdentifierNode *>($3));
            $$->setPosition($2);
            if(checkKind($1, Node::KIND_ATTRIBUTE) || !(checkType($1, Node::TYPE_STRUCT)) || $1->isArray())
                error_expressionTypeError($1,$2);
            else {
                auto symbolTable = SymbolTable::getSymbolTableByName($1->getStructTypeName());
            
                if(symbolTable->lookUp($3->getTokenValue()) == NULL)
                    error_variableNotDeclaredInStruct($1,$3);
                
                $$->copyFrom(symbolTable->lookUp($3->getTokenValue()));
            }
        }
    |   postfixUnaryExpression '[' expression error  {
            error_missingRightBrancket2();
        }
    ;

paramList :
        assignmentExpression {
            // $$ = new Node(nameCounter.getNumberedName("paramList"), 1, $1);
            $$ = new std::vector<ExpressionNode*>();
            $$->push_back(dynamic_cast<ExpressionNode*>($1));
        }
    |   paramList ',' assignmentExpression {/* 这里面不能填 expression，因为 expression 也是用逗号隔开的一串表达式 */
            $$ = $1;
            //$$->addChild($2);
            //$$->addChild($3);
            $$->push_back(dynamic_cast<ExpressionNode*>($3));
        }
    ;

/* PRIORITY 0: branckets */

atomicExpression :
        IDENTIFIER {
            $$ = $1;
            $$ = new IdentifierNode($1->getTokenValue(), false);
            if(symbolTableStack->lookUp($1->getTokenValue())==NULL){
                error_variableNotDeclared($1->getTokenValue());
            }else{
                $$->setAttribute(symbolTableStack->lookUp($1->getTokenValue()));
            }
            $$->setPosition(csLineCnt, csColumnCnt);

        }
    |   DOUBLE_NUMBER {
            $$ = $1;
            $$->setPosition(csLineCnt, csColumnCnt);
        }
    |   INT_NUMBER {
            $$ = $1;
            $$->setPosition(csLineCnt, csColumnCnt);
        }
    |   STRING {
            $$ = $1;
            $$ = new IdentifierNode($1->getTokenValue(), false);
            $$->setType(Node::TYPE_STRING);
            $$->setPosition(csLineCnt, csColumnCnt);
        }
    |   '(' expression ')' {
            $$ = $2;
        }
    ;


%%
int yyerror(std::string s){
    noError = false;
    printf("syntax error at line %d, column %d.\n", csLineCnt, csColumnCnt);
}
static void error_missingSemicolon(){
    std::cout<<"[ERROR] ";
    printf("Missing \';\' at line %d, after column %d\n", csLineCnt, csColumnCnt-(int)strlen(yytext));
}
static void error_wrongStatement(){
    std::cout<<"[ERROR] ";
    printf("a statement near line %d is illeagal. ", csLineCnt);
    printf("maybe you\'re putting a declaration after a statement.\n");//'
}
static void error_wrongExpression(){
    std::cout<<"[ERROR] ";
    printf("an expression near line %d is illeagal.\n", csLineCnt);
}
static void error_missingRightBrancket(){
    std::cout<<"[ERROR] ";
    printf("expect \')\' at line %d, after column %d .\n", csLineCnt, csColumnCnt-(int)strlen(yytext));
}
static void error_missingRightBrancket2(){
    std::cout<<"[ERROR] ";
    printf("expect \']\' at line %d, after column %d .\n", csLineCnt, csColumnCnt-(int)strlen(yytext));
}
static void error_elseWithNoIf(){
    std::cout<<"[ERROR] ";
    printf("expect \"if\" for the \"else\", at line %d, near column %d .\n", csLineCnt, csColumnCnt-(int)strlen(yytext));
}
static void error_duplicatedVariable(Node *c){
    std::cout<<"[ERROR] ";
    std::cout<<"variable \""<<c->getSymbolName()<<"\" at line "<<c->getLineNumber()<<" near column "<<c->getColumnNumber()<<""<<" has been declared before.\n";
    std::cout<<" Hint: first declaraed at line "<<symbolTableStack->lookUp(c->getSymbolName())->lineNumber<<", near column "<<symbolTableStack->lookUp(c->getSymbolName())->columnNumber<<std::endl;
}
static void error_variableNotDeclared(std::string name){
//    std::cout<<"[ERROR] ";
//    std::cout<<"variable \""<<name<<"\" was not declared.\n";
//    std::cout<<" Hint: first used at line "<<csLineCnt<<", near column "<<csColumnCnt<<std::endl;
}
static void error_structNotDeclared(std::string name){
//    std::cout<<"[ERROR] ";
//    std::cout<<"struct type name \""<<name<<"\" was not declared.\n";
//    std::cout<<" Hint: first used at line "<<csLineCnt<<", near column "<<csColumnCnt<<std::endl;
}
static void error_illegalArraySize(Node * c){
    std::cout<<"[ERROR] ";
    std::cout<<"Size of array at line "<<c->getLineNumber()<<" near column "<<c->getColumnNumber()<<" must be a integer and must be a constant.\n";
}
static void error_expressionTypeError(Node *exp1, Node *op, Node *exp2){
    std::cout<<"[ERROR] ";
    std::cout<<"Type error at line "<<op->getLineNumber()<<" near column "<<op->getColumnNumber()<<":\n";
    std::cout<<" Type "<<exp1->getTypeString()<<" and type "<<exp2->getTypeString()<<" are not match for the operator \""<<op->getTokenValue()<<"\"\n";
}
static void error_expressionTypeError(Node *exp1, Node *op){
    std::cout<<"[ERROR] ";
    std::cout<<"Type error at line "<<op->getLineNumber()<<" near column "<<op->getColumnNumber()<<":\n";
    std::cout<<" Type "<<exp1->getTypeString()<<" is not supported for the operator \""<<op->getTokenValue()<<"\"\n";
}
static void error_typeMismatch(Node *c){
    std::cout<<"[ERROR] ";
    std::cout<<"Type mismatch at line "<<c->getLineNumber()<<" near column "<<c->getColumnNumber()<<"\n";
    std::cout<<" Hint: are you putting an array at the left hand of \'=\', or using \'=\' to connect two mismatched type?\n";
}
static void error_variableNotDeclaredInStruct(Node *v, Node *m){
    std::cout<<"[ERROR] variable \""<<v->getSymbolName()<<"\" dose not has member \""<<m->getTokenValue()<<"\"\n";
    auto symattribute = symbolTableStack->lookUp(v->getSymbolName());
    if(symattribute){
        std::cout<<" Hint: you declared this variable at line "<<symattribute->lineNumber<<" near column "<<symattribute->columnNumber<<std::endl;
    }
}
static void error_argumentNumberNotMatch(Node *f,int an){
    std::cout<<"[ERROR] function's argument number not match at line "<<f->getLineNumber()<<" near column "<<f->getColumnNumber()<<"\n";//'
    std::cout<<" Hint: function \""<<f->getSymbolName()<<"\" needs "<<f->getArgList().size()<<" arguments but you gave "<<an<<".\n";
}
static void error_notArray(Node *c){
    std::cout<<"[ERROR] \""<<c->getSymbolName()<<"\" at line "<<c->getLineNumber()<<" near column "<<c->getColumnNumber()<<" is not an array.\n";
    std::cout<<" Hint: are you using too many \"[]\"\'s to access an array?\n";//'
}
static void error_returnValueTypeMismatch(symAttribute* need, Node::Type give){
    std::cout<<"[ERROR] return value type mismatch at line "<<csLineCnt<<std::endl;
    std::cout<<" Hint: the function returns "<<type_to_string(need)<<" but you gave nothing\n"; 
}
static void error_returnValueTypeMismatch(symAttribute* need, Node * give){
    std::cout<<"[ERROR] return value type mismatch at line "<<csLineCnt<<std::endl;
    std::cout<<" Hint: the function returns "<<type_to_string(need)<<" but you gave "<<give->getTypeString()<<std::endl;
}
static void error_functionReturnsArray(){
    std::cout<<"[ERROR] at line "<<csLineCnt<<": function cannot return an array\n";
}
static void error_argumentTypeNotMatch(std::vector<Node::Type>& userGave,Node *function,std::vector<std::string>& structTypeName){
    std::cout<<"[ERROR] function's argument type not match at line "<<function->getLineNumber()<<" near column "<<function->getColumnNumber()<<"\n";//'
    std::cout<<" Hint: function \""<<function->getSymbolName()<<"\" needs parameters of (";
    auto fa = function->getArgList();
    for(int i=0;i<fa.size();i++){
        switch(fa[i]){
            case Node::TYPE_INT:
                std::cout<<"int";
                break;
            case Node::TYPE_DOUBLE:
                std::cout<<"double";
                break;
            case Node::TYPE_STRUCT:
                std::cout<<"struct "<<function->getArgListStructName()[i];
                break;
            default:
                std::cout<<userGave[i]<<' ';
        }
        if(i<fa.size()-1)std::cout<<",";
    }
    std::cout<<") but you gave (";
    for(int i=0;i<userGave.size();i++){
        switch(userGave[i]){
            case Node::TYPE_INT:
                std::cout<<"int";
                break;
            case Node::TYPE_DOUBLE:
                std::cout<<"double";
                break;
            case Node::TYPE_STRUCT:
                std::cout<<"struct "<<structTypeName[i];
                break;
            default:
                std::cout<<userGave[i]<<' ';
        }
        if(i<userGave.size()-1)std::cout<<",";
    }
    std::cout<<")\n";
}
static void eatToNewLine(){ /* 该函数已弃置不用 */
    std::cout<<"eating:\n";
    char c;
    while((c=getchar())!=EOF && c!='\n'){
        //std::cout<<c;
    }
    std::cout<<"last eaten: \\"<<(int)c<<std::endl;
    if(c=='\n'){
        csLineCnt++;
        csColumnCnt=0;
    }
}
Node *makeParseTree(){
    yyparse();
    if(!noError){
        std::cout<<"The compiling cannot continue due to errors above.";
        return NULL;
    }
    return treeRoot;
}
/*
int main(){
    yyparse();
    if(!noError){
        std::cout<<"The compiling cannot continue due to errors above.";
        return 0;
    }
    std::cout<<"Parse complete, no error was found.\n";
    //treeRoot->printTree();
}
*/

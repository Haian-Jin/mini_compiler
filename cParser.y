%{
#include"./include/ast_node.hpp"
extern int yylex();
extern char *yytext;
static bool noError = true;
static Node *treeRoot;
static NameCounter nameCounter;
int yyerror(std::string);
static void error_missingSemicolon();
static void error_wrongExpression();
static void error_missingRightBrancket();
static void error_missingRightBrancket2();
static void error_elseWithNoIf();
static void error_illegalArraySize(Node *);
%}
%code requires {
#include "./include/ast_node.hpp"
#include "./include/array_node.hpp"
#include "./include/expr_node.hpp"
#include "./include/ctrl_node.hpp"
#include "./include/func_node.hpp"
#include "./include/stat_node.hpp"
#include "./include/struct_node.hpp"
}

%union{
    Node * nodePtr;
    DoubleNode * doubleNodePtr;
    IntNode * intNodePtr;
    IdentifierNodeList* identifierNodeListPtr;
    IdentifierNode* identifierNodePtr;
    VarDeclarationList* varDeclarationListPtr;
    StatementNodesBlock* statementNodesBlockPtr;
    GlobalDeclarationNode * globalDeclarationNodePtr;
    std::vector<VarDeclarationList*> * structMemberListPtr;
    std::vector<ExpressionNode*> * ExpressionNodeListPtr;
}

%token GOTO ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN LOGICAL_OR LOGICAL_AND EQ NE GE LE SL SR INC DEC IDENTIFIER DOUBLE_NUMBER INT_NUMBER STRING 
%token FOR DO WHILE CONTINUE BREAK IF ELSE SWITCH CASE RETURN
%token STRUCT INT DOUBLE CHAR PTR CONST DEFAULT FLOAT STATIC UNSIGNED VOID 


%type<identifierNodeListPtr> initializations structMembers
%type<identifierNodePtr> initialization IDENTIFIER typeName type
%type<varDeclarationListPtr> paramTypes 
%type<statementNodesBlockPtr>  globalDeclaration declaration statementBlock statements statement structMemberDeclarations structMemberDeclaration
%type<nodePtr> GOTO ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN LOGICAL_OR LOGICAL_AND EQ NE GE LE SL SR INC DEC DOUBLE_NUMBER INT_NUMBER STRING FOR DO WHILE CONTINUE BREAK IF ELSE SWITCH CASE RETURN STRUCT INT DOUBLE CHAR PTR CONST DEFAULT FLOAT STATIC UNSIGNED VOID 
%type<globalDeclarationNodePtr> cCode0 cCode
%type<nodePtr> structTypeName pointerSpecifier 
%type<nodePtr> variable variableName  paramTypeName variableWithNoName variableWithNoNameCore initialValue initialValues functionDeclaration 
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
            $$ = new GlobalDeclarationNode(dynamic_cast<StatementNodesBlock*>($1));
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
    ;

declaration :
        type initializations ';' { /* 定义变量 */
            $$ = new StatementNodesBlock();
            $$->createMultiVarDeclaration(dynamic_cast<IdentifierNode *>($1), dynamic_cast<IdentifierNodeList *>($2));

        }
    |   STRUCT IDENTIFIER '{' structMemberDeclarations '}' ';' { // 定义结构体
            $2->setType(Node::TYPE_STRUCT);
            $2->setKind(Node::KIND_ATTRIBUTE);
            $2->setStructTypeName($2->getTokenValue());
            $2->setVariableName($2->getTokenValue()); 
            $$ = new StatementNodesBlock();
            StructDeclarationNode * structDecTemp = new StructDeclarationNode(dynamic_cast<IdentifierNode *>($2), dynamic_cast<StatementNodesBlock *>($4));
            $$->addStatementNode(dynamic_cast<StatementNode *>(structDecTemp));
        }
    |   type initializations error  {
            error_missingSemicolon();
        } 
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
    |   structTypeName {
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
        }
    ;

/* 定义结构体的成员变量。这个和 declarations 的不同在于，这里不能定义函数，也不能做初始化。 */
structMemberDeclarations :
        structMemberDeclaration {
            $$ = $1;
        }
    |   structMemberDeclarations structMemberDeclaration {
            $$ = $1;
            $$->mergeStatements(dynamic_cast<StatementNodesBlock*>($2));
        }
    ;

structMemberDeclaration :
        type structMembers ';' {
            $$ = new StatementNodesBlock();
            $$->createMultiVarDeclaration($1, $2);
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
        pointerSpecifier variableName {  /* int *a; 指针变量，这里不打算实现。 */}
    |   variableName { /* 不是指针的变量 */
            $$ = $1;
        }
    ;

/* 我们不打算实现指针。 */
pointerSpecifier :
        '*' { /* a simple pointer */}
    |   pointerSpecifier '*' { /* a pointer to another pointer variable */ }
    |   '*' CONST { /* a pointer to a const variable */ }
    |   pointerSpecifier '*' CONST { /* a pointer to another pointer which is a pointer to a const value */ }
    ;

variableName :
        IDENTIFIER { /* 一个普通的变量 */
            $$ = new IdentifierNode($1->getTokenValue(), false);
            $$->setKind(Node::KIND_VARIABLE);
            $$->setPosition(csLineCnt, csColumnCnt);

        }
    |   variableName '[' INT_NUMBER ']' {    /* 数组，可以是多维度的。其中 NUMBER 必须是整数。 */
            if(!(checkType($3,Node::TYPE_INT) && checkKind($3,Node::KIND_CONSTANT))){
                error_illegalArraySize($3);
            }else{
                $$ = $1;
                auto arraySizes = $$->getArraySizes();
                int newSize = dynamic_cast<IntNode*>($3)->value;
                arraySizes.push_back(newSize);
                $$->setArraySizes(arraySizes);
                auto a = $$->getArraySizes();
            }
        }
    |   '(' variable ')' { /* 这一条弃之不用，太复杂了 */}
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
        type {   // int (*f)(double,char); 不实现这一条，太复杂 }
    |   type variableWithNoName { // 无名字的指针变量。不实现这一条，天复杂 }
    |   */
        type variable {      // 这一条是要正常实现的，定义函数用的 
            $$ = new VariableDeclarationNode(dynamic_cast<IdentifierNode *>($1), dynamic_cast<IdentifierNode *>($2));
        }
    ;

/* 不用管这个，都不实现的。 */
variableWithNoName :        /* !! 如果要阅读这个的话，请和 variable 相关的产生式一起阅读 !!*/
        pointerSpecifier {       /* 不实现指针 */}
    |   variableWithNoNameCore {}
    ;

/* 不用管这个，都不实现的。 */
variableWithNoNameCore :    /* !! read this along with 'variableName' !!*/
        variableWithNoNameCore '[' INT_NUMBER ']' {}
    |   '(' variableWithNoName ')' {}
    |   variableWithNoNameCore '(' ')' {  /* a function taking another function as param... */}
    |   variableWithNoNameCore '(' paramTypes ')' { /* a function taking another function as param... */}
    |   '[' ']' { /* because it has no name, it must stop some way. Below is some terminators */}
    |   '(' ')' {}
    |   '(' paramTypes ')' { /* a function taking another function as param... */}
    ;

/* 初始值，如果要在定义的时候初始化的话，initialValue 就是跟在 = 后面的部分。有时间的话就实现一下初始值，没时间就算了。 */
initialValue :
        '{' initialValues '}' { /* int a[10]={1}; 初始化列表 */}
    |   assignmentExpression { /* int a=5+6; int b=a=3; 普通的初始值 */}
    ;

/* 初始化列表 */
initialValues :
        initialValue {} // TODO
    |   initialValues ',' initialValue { /* int a[10]={1,2,3}  TODO  */}
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
    |   statementBlock { // 语句块
            $$ = $1;
        }     
    |   branchStatement {
            $$ = new StatementNodesBlock();
            $$->addStatementNode(dynamic_cast<StatementNode *>($1));
        }
    |   jumpStatement {
            $$ = new StatementNodesBlock();
            $$->addStatementNode(dynamic_cast<StatementNode *>($1));
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
    |   DO statement WHILE '(' expression ')' ';' {}
    |   WHILE '(' expression error { error_missingRightBrancket(); } ')' statement /* error recovery */
    |   WHILE '(' error { error_wrongExpression; } ')' statement {}
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
    ; 


/* 表达式，有十六个优先级（大大小小加起来大概有十九个） */

/* PRIORITY 15: "," */
expression : 
        assignmentExpression {
            $$ = $1;
        }
    /* // 暂时先不实现 TODO
    |   expression ',' assignmentExpression {}
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

        }
    /* 暂时未实现, TODO
    |   unaryExpression ADD_ASSIGN assignmentExpression {}
    |   unaryExpression SUB_ASSIGN assignmentExpression {}
    |   unaryExpression MUL_ASSIGN assignmentExpression {}
    |   unaryExpression DIV_ASSIGN assignmentExpression {} /*
    ;

/* PRIORITY 13: "?:" tenary conditional operator */
tenaryConditionExpression :
        logicalOrExpression {
            $$ = $1;
        }
    |   logicalOrExpression '?' expression ':' tenaryConditionExpression {/* Hint: right hand of ':' cannot be expression because no '=' should appear at the right hand of ':'. */
            $$ = new TenaryOperatorNode({"?:"}, 3, $1, $3, $5);
            $$->setType(Node::TYPE_INT);
            if($3->getType()==Node::TYPE_DOUBLE||$5->getType()==Node::TYPE_DOUBLE)$$->setType(Node::TYPE_DOUBLE);
            $$->setKind(Node::KIND_CONSTANT);
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

        }
    |   equalityComparisonExpression NE relationComparisonExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3), false);
            $$->setPosition($2);
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
        }
    |   relationComparisonExpression '>' shiftExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3), false);
            $$->setPosition($2);
        }
    |   relationComparisonExpression LE shiftExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3), false);
            $$->setPosition($2);
        }
    |   relationComparisonExpression GE shiftExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3), false);
            $$->setPosition($2);
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
        }
    |   shiftExpression SR arithmeticAddExpression  {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3), false);
            $$->setPosition($2);
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
        }
    |   arithmeticAddExpression '-' arithmeticMulExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3));
            $$->setPosition($2);
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
        }
    |   arithmeticMulExpression '/' castedExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3));
            $$->setPosition($2);
        }
    |   arithmeticMulExpression '%' castedExpression {
            $$ = new BinaryOperatorNode($2->getTokenValue(), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3));
            $$->setPosition($2);
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
            $$ = new UnaryOperatorNode(std::string("pre")+$1->getName(), 1, $2);
        }
    |   DEC postfixUnaryExpression {/* --a, the same as ++a[i] */
            $$ = new UnaryOperatorNode(std::string("pre")+$1->getName(), 1, $2);
        }
    |   '!' postfixUnaryExpression {/* logical NOT */
            $$ = new UnaryOperatorNode($1->getName(), 1, $2);
        }
    |   '~' postfixUnaryExpression {/* bitwise NOT */
            $$ = new UnaryOperatorNode($1->getName(), 1, $2);
        }
    |   '-' postfixUnaryExpression {/* negative */
            $$ = new UnaryOperatorNode($1->getName(), 1, $2);
        }
    ;

postfixUnaryExpression :
        atomicExpression {
            $$ = $1;
        }
    |   postfixUnaryExpression INC {/* a++, espetially a[i]++ is allowed, (a[i])++ is not necessary */
            $$ = new UnaryOperatorNode(std::string("post")+$2->getName(), 1, $1);
        }
    |   postfixUnaryExpression DEC {/* a-- */
            $$ = new UnaryOperatorNode(std::string("post")+$2->getName(), 1, $1);
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
        }
    |   postfixUnaryExpression '(' paramList ')' {/* function, f()[i], f[i](), f[i]()[j] are all allowed，但我们不=实现它。 */
            $$ = new FunctionCallNode({"()"}, 2, $1, $3);
            for(auto i : *$3) {
                dynamic_cast<FunctionCallNode *>($$)->addArgument(i);
            }
        }
    |   postfixUnaryExpression '(' ')'           {/* function with no params. */
            $$ = new FunctionCallNode({"()"}, 1, $1);
        }
    |   postfixUnaryExpression '.' IDENTIFIER    {/* struct's member (a.val) */
            $$ = new StructMemberNode($2->getTokenValue(), dynamic_cast<IdentifierNode *>($1), dynamic_cast<IdentifierNode *>($3));
            $$->setPosition($2);
        }
    |   postfixUnaryExpression '[' expression error  {
            error_missingRightBrancket2();
        }
    ;

paramList :
        assignmentExpression {
            $$ = new std::vector<ExpressionNode*>();
            $$->push_back(dynamic_cast<ExpressionNode*>($1));
        }
    |   paramList ',' assignmentExpression {/* 这里面不能填 expression，因为 expression 也是用逗号隔开的一串表达式 */
            $$ = $1;
            $$->push_back(dynamic_cast<ExpressionNode*>($3));
        }
    ;

/* PRIORITY 0: branckets */
atomicExpression :
        IDENTIFIER {
            $$ = new IdentifierNode($1->getTokenValue(), false);
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
    // printf("syntax error at line %d, column %d.\n", csLineCnt, csColumnCnt);
}
static void error_missingSemicolon(){
    LogErrorV("Missing \';\' at line" +  std::to_string(csLineCnt) + ", after column" + std::to_string(csColumnCnt-(int)strlen(yytext)));
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
static void error_illegalArraySize(Node * c){
    std::cout<<"[ERROR] ";
    std::cout<<"Size of array at line "<<c->getLineNumber()<<" near column "<<c->getColumnNumber()<<" must be a integer and must be a constant.\n";
}


Node *makeParseTree(){
    yyparse();
    if(!noError){
        std::cout<<"The compiling cannot continue due to errors above.";
        return NULL;
    }
    return treeRoot;
}
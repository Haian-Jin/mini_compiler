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

/* declaration ??????????????????????????????????????????functionDeclaration ?????????????????? */
/* ??????????????????????????????????????????????????????????????????????????????????????? statement block??????????????????????????? */

globalDeclaration :
        declaration { /* ?????????????????????????????????????????? */
            $$ = $1;
        }
    |   functionDeclaration { /* ????????????????????????????????????????????????????????? */
            $$ = new StatementNodesBlock(); 
            $$->addStatementNode(dynamic_cast<StatementNode*>($1));
        }
    ;

declaration :
        type initializations ';' { /* ???????????? */
            $$ = new StatementNodesBlock();
            $$->createMultiVarDeclaration(dynamic_cast<IdentifierNode *>($1), dynamic_cast<IdentifierNodeList *>($2));
        }
    |   STRUCT IDENTIFIER '{' structMemberDeclarations '}' ';' { // ???????????????
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
    |   CONST typeName {$$ = $2;}     /* const int, ????????????????????? */     
    |   STATIC typeName {$$ = $2;}   /* static int, ????????????????????? */
    ;

typeName :
        INT { 
            $$ = new IdentifierNode($1->getTokenValue(), true);
            $$->setPosition(csLineCnt, csColumnCnt);
        }               
    |   UNSIGNED INT { /* ?????????????????? */}  
    |   CHAR { 
            $$ = new IdentifierNode($1->getTokenValue(), true);
            $$->setPosition(csLineCnt, csColumnCnt);
        }  
    |   FLOAT { /* ??????????????????, ?????????double */
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

/* ??????????????????????????????????????????????????????????????????????????????????????????????????????????????? declaration ??????????????? */
/* ????????????????????????????????????????????? */
structTypeName : 
        STRUCT '{' {
            /* ???????????????????????????????????? */
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
    |   STRUCT IDENTIFIER { /* ???????????????????????????????????????????????? */
            $$ = new Node(nameCounter.getNumberedName("structTypeName"), 2, $1, $2);
            $$->setType(Node::TYPE_STRUCT);
            $$->setKind(Node::KIND_ATTRIBUTE);
            $$->setStructTypeName($2->getTokenValue()/*nameCounter.getNumberedName($2->getTokenValue())*/);
            $$->setPosition($1);
        }
    ;

/* ?????????????????????????????????????????? declarations ????????????????????????????????????????????????????????????????????? */
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

structMembers : /* ???????????????????????????????????????????????? */
        variable {
            $$ = new IdentifierNodeList();
            $$->addIdentifierNode(dynamic_cast<IdentifierNode*>($1));
        }
    |   structMembers ',' variable {
            $$ = $1;
            $$->addIdentifierNode(dynamic_cast<IdentifierNode*>($3));
        }
    ;

/* ???????????????????????????????????????????????????????????????????????????????????????????????? */
/* ??????????????????????????????????????????????????????????????? */
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
        variable {                       /* int a; ??????????????? */
            $$ = dynamic_cast<IdentifierNode*>($1);
        }
    |   variable '=' initialValue {   /* int a=10; ???????????? ??????????????? */
        }
    ;

variable :
        pointerSpecifier variableName {  /* int *a; ??????????????????????????????????????? */}
    |   variableName { /* ????????????????????? */
            $$ = $1;
        }
    ;

/* ?????????????????????????????? */
pointerSpecifier :
        '*' { /* a simple pointer */}
    |   pointerSpecifier '*' { /* a pointer to another pointer variable */ }
    |   '*' CONST { /* a pointer to a const variable */ }
    |   pointerSpecifier '*' CONST { /* a pointer to another pointer which is a pointer to a const value */ }
    ;

variableName :
        IDENTIFIER { /* ????????????????????? */
            $$ = new IdentifierNode($1->getTokenValue(), false);
            $$->setKind(Node::KIND_VARIABLE);
            $$->setPosition(csLineCnt, csColumnCnt);
        }
    |   variableName '[' INT_NUMBER ']' {    /* ??????????????????????????????????????? NUMBER ?????????????????? */
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
    |   variableName '[' DOUBLE_NUMBER ']' {    /* ??????????????????????????????????????? NUMBER ?????????????????? */
            error_illegalArraySize($3);
        }
    |   '(' variable ')' { /* ???????????????????????????????????? */}
    |   variableName '(' ')' {   /* ???????????? */
           $$ = new FuncNameAndArgsNode(dynamic_cast<IdentifierNode *>($1), nullptr);
        }
    |   variableName '(' paramTypes ')' {    /* ???????????? */
            $$ = new FuncNameAndArgsNode(dynamic_cast<IdentifierNode *>($1), dynamic_cast<VarDeclarationList *>($3));
        }
    ;

paramTypes :    /* ????????????????????????????????????????????????????????????????????????????????? */
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
        type {   // int (*f)(double,char); ?????????????????????????????? }
    |   type variableWithNoName { // ????????????????????????????????????????????????????????? }
    |   */
        type variable {      // ??????????????????????????????????????????????????? 
            $$ = new VariableDeclarationNode(dynamic_cast<IdentifierNode *>($1), dynamic_cast<IdentifierNode *>($2));
        }
    ;

/* ???????????????????????????????????? */
variableWithNoName :        /* !! ???????????????????????????????????? variable ?????????????????????????????? !!*/
        pointerSpecifier {       /* ??????????????? */}
    |   variableWithNoNameCore {}
    ;

/* ???????????????????????????????????? */
variableWithNoNameCore :    /* !! read this along with 'variableName' !!*/
        variableWithNoNameCore '[' INT_NUMBER ']' {}
    |   '(' variableWithNoName ')' {}
    |   variableWithNoNameCore '(' ')' {  /* a function taking another function as param... */}
    |   variableWithNoNameCore '(' paramTypes ')' { /* a function taking another function as param... */}
    |   '[' ']' { /* because it has no name, it must stop some way. Below is some terminators */}
    |   '(' ')' {}
    |   '(' paramTypes ')' { /* a function taking another function as param... */}
    ;

/* ?????????????????????????????????????????????????????????initialValue ???????????? = ????????????????????????????????????????????????????????????????????????????????? */
initialValue :
        '{' initialValues '}' { /* int a[10]={1}; ??????????????? */}
    |   assignmentExpression { /* int a=5+6; int b=a=3; ?????????????????? */}
    ;

/* ??????????????? */
initialValues :
        initialValue {} // TODO
    |   initialValues ',' initialValue { /* int a[10]={1,2,3}  TODO  */}
    ;

/* ???????????? */
functionDeclaration :   
        type variable  statementBlock {
            $$ = new FunctionDeclarationNode(dynamic_cast<IdentifierNode *>($1), dynamic_cast<FuncNameAndArgsNode *>($2), dynamic_cast<StatementNodesBlock*>($3));
        }
    ;

/* ??????????????????{...}??? */
statementBlock : 
        '{' '}' { /* ?????? {} ??????????????? {;} ?????? */
            $$ = new StatementNodesBlock();
            $$->addStatementNode(dynamic_cast<StatementNode *>(new NullStatementNode()));
        }
    |   '{' statements '}' {
            $$ = $2;
        }
    ;

statements :    /* ???????????? */
        statement {
            $$ = $1;
        }
    |   statements statement {
            $$ = $1;
            $$->mergeStatements(dynamic_cast<StatementNodesBlock *>($2));
        }
    ;

statement :     /* ???????????????????????????;????????????????????????????????????????????????????????? */
        declaration {
            $$ = $1;
        }
    |   expressionStatement { // ????????????????????????????????????
            $$ = new StatementNodesBlock();
            $$->addStatementNode(dynamic_cast<StatementNode *>($1));
        }
    |   loopStatement { // ??????
            $$ = new StatementNodesBlock();
            $$->addStatementNode(dynamic_cast<StatementNode *>($1));
        }
    |   statementBlock { // ?????????
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
        ';' { /* ???????????????????????? expressionStatement */
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
        FOR '(' expressionStatement expressionStatement expression ')' statement { /* ????????? for(int i;i<10;i++) ?????? */
            $5 = new ExpressionStatementNode(dynamic_cast<ExpressionNode *>($5));
            $$ = new ForStatementNode(dynamic_cast<ExpressionStatementNode *>($3), dynamic_cast<ExpressionStatementNode *>($4), dynamic_cast<ExpressionStatementNode *>($5), dynamic_cast<StatementNodesBlock *>($7));
        }
    |   WHILE '(' expression ')' statement {
            $3 = new ExpressionStatementNode(dynamic_cast<ExpressionNode *>($3));
            $$ = new WhileStatementNode(dynamic_cast<ExpressionStatementNode *>($3), dynamic_cast<StatementNodesBlock *>($5));
        }
    // do-while????????????
    |   DO statement WHILE '(' expression ')' ';' {}
    |   WHILE '(' expression error { error_missingRightBrancket(); } ')' statement /* error recovery */
    |   WHILE '(' error { error_wrongExpression; } ')' statement {}
    ;

/* ?????????????????? */
branchStatement :
        IF '(' expression ')' statement {
            $3 = new ExpressionStatementNode(dynamic_cast<ExpressionNode *>($3));
            $$ = new IfStatementNode(dynamic_cast<ExpressionStatementNode *>($3), dynamic_cast<StatementNodesBlock *>($5));  
        }
    |   IF '(' expression ')' statement ELSE statement { /* ???else??????????????????????????????????????????????????? */
            $3 = new ExpressionStatementNode(dynamic_cast<ExpressionNode *>($3));
            $$ = new IfStatementNode(dynamic_cast<ExpressionStatementNode *>($3), dynamic_cast<StatementNodesBlock *>($5), dynamic_cast<StatementNodesBlock *>($7));
        }
    |   SWITCH '(' expression ')' caseBlock /* ????????????????????? SWITCH-CASE????????????????????? */
    |   error  ELSE statement {
            { error_elseWithNoIf(); }
        }
    ;   /* too complex, SWITCH is not supported yet */

/* ????????? */
caseBlock :
        '{' caseStatements '}'
    ;

/* ????????? */
caseStatements :
        CASE tenaryConditionExpression ':' statement
    |   DEFAULT ':' statement
    ;

/* ????????????????????? */
jumpStatement :
        RETURN ';' { /* ?????????????????????????????????????????? */
            $$ = new ReturnStatementNode();
        }
    |   RETURN expression ';' { /* ?????????????????????????????????????????? */
            $$ = new ReturnStatementNode(dynamic_cast<ExpressionNode *>($2));
        }
    |   CONTINUE ';' { /* ???????????? */
            $$ = new ContinueStatementNode();
        }
    |   BREAK ';' { /* ???????????? */
            $$ = new BreakStatementNode();
        }
    ; 


/* ?????????????????????????????????????????????????????????????????????????????? */

/* PRIORITY 15: "," */
expression : 
        assignmentExpression {
            $$ = $1;
        }
    /* // ?????????????????? TODO
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
                $$ = new ArrayAssignmentNode(dynamic_cast<ArrayIndexNode*>($1), dynamic_cast<ExpressionNode*>($3));
            }else if(dynamic_cast<StructMemberNode*>($1)!=NULL){
                $$ = new StructMemberAssignmentNode(dynamic_cast<StructMemberNode*>($1), dynamic_cast<ExpressionNode*>($3));
            }else{
                std::cout<<"Some thing wrong at line "<<csLineCnt<<std::endl;
            }
        }
    /* ???????????????, TODO
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
            $$ = new TenaryOperatorNode(std::string("?:"), dynamic_cast<ExpressionNode *>($1), dynamic_cast<ExpressionNode *>($3), dynamic_cast<ExpressionNode *>($5));
            $$->setPosition($1);
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
/* ??????????????????????????????????????????????????????????????? */
castedExpression :
       unaryExpression {
            $$ = $1;
        }
    ;

/* PRIORITY 1: "++, --, !, ~" unary operator, and ". ->" */
/* ???++??????++????????????????????? ++a[i] ???????????? ++(a[i]) ????????? (++a)[i] */
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
            $$ = new UnaryOperatorNode(std::string("pre")+$1->getName(), dynamic_cast<ExpressionNode*>($2));
        }
    |   DEC postfixUnaryExpression {/* --a, the same as ++a[i] */
            $$ = new UnaryOperatorNode(std::string("pre")+$1->getName(), dynamic_cast<ExpressionNode*>($2));
        }
    |   '!' postfixUnaryExpression {/* logical NOT */
            $$ = new UnaryOperatorNode($1->getName(), dynamic_cast<ExpressionNode*>($2));
        }
    |   '~' postfixUnaryExpression {/* bitwise NOT */
            $$ = new UnaryOperatorNode($1->getName(), dynamic_cast<ExpressionNode*>($2));
        }
    |   '-' postfixUnaryExpression {/* negative */
            $$ = new UnaryOperatorNode($1->getName(), dynamic_cast<ExpressionNode*>($2));
        }
    ;

postfixUnaryExpression :
        atomicExpression {
            $$ = $1;
        }
    |   postfixUnaryExpression INC {/* a++, espetially a[i]++ is allowed, (a[i])++ is not necessary */
            $$ = new UnaryOperatorNode(std::string("post")+$2->getName(), dynamic_cast<ExpressionNode*>($1));
        }
    |   postfixUnaryExpression DEC {/* a-- */
            $$ = new UnaryOperatorNode(std::string("post")+$2->getName(), dynamic_cast<ExpressionNode*>($1));
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
    |   postfixUnaryExpression '(' paramList ')' {/* function, f()[i], f[i](), f[i]()[j] are all allowed???????????????=???????????? */
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
    |   paramList ',' assignmentExpression {/* ?????????????????? expression????????? expression ??????????????????????????????????????? */
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
    LogErrorV("Missing \';\' at line " +  std::to_string(csLineCnt) + ", after column" + std::to_string(csColumnCnt-(int)strlen(yytext)));
}

static void error_wrongExpression(){
    LogErrorV("an expression near line " + std::to_string(csLineCnt) +" is illeagal.\n");
}
static void error_missingRightBrancket(){
    LogErrorV("expect \')\' at line " +  std::to_string(csLineCnt) + ", after column" + std::to_string(csColumnCnt-(int)strlen(yytext)));    
}
static void error_missingRightBrancket2(){
    LogErrorV("expect \']\' at line " +  std::to_string(csLineCnt) + ", after column" + std::to_string(csColumnCnt-(int)strlen(yytext)));  
}
static void error_elseWithNoIf(){
    LogErrorV("expect \"if\" for the \"else\", at line " +  std::to_string(csLineCnt) + ", after column" + std::to_string(csColumnCnt-(int)strlen(yytext)));  
}
static void error_illegalArraySize(Node * c){
    LogErrorV("Size of array at line " +  std::to_string(csLineCnt) + ", after column" + std::to_string(csColumnCnt-(int)strlen(yytext)));  
}


Node *makeParseTree(){
    yyparse();
    if(!noError){
        std::cout<<"The compiling cannot continue due to errors above.";
        return NULL;
    }
    return treeRoot;
}
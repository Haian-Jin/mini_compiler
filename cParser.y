%{
#include"./cCompilerCommon.hpp"
extern int yylex();
extern char *yytext;
static bool noError = true;
static Node *treeRoot;
static NameCounter nameCounter;
int yyerror(std::string);
void error_missingSemicolon();
void error_missingInitializations();
void error_wrongStatement();
void error_wrongExpression();
void error_missingRightBrancket();
void error_elseWithNoIf();
void eatToNewLine();
%}
%code requires {
#include"./cCompilerCommon.hpp"
}
%token GOTO ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN LOGICAL_OR LOGICAL_AND EQ NE GE LE SL SR INC DEC IDENTIFIER NUMBER STRING
%token FOR DO WHILE CONTINUE BREAK IF ELSE SWITCH CASE RETURN
%token STRUCT INT DOUBLE CHAR PTR CONST DEFAULT FLOAT STATIC UNSIGNED VOID 

/* TODO: give nonterminals a type. */
%union{
    Node* nodePtr;
}
%type<nodePtr> GOTO ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN LOGICAL_OR LOGICAL_AND EQ NE GE LE SL SR INC DEC IDENTIFIER NUMBER STRING FOR DO WHILE CONTINUE BREAK IF ELSE SWITCH CASE RETURN STRUCT INT DOUBLE CHAR PTR CONST DEFAULT FLOAT STATIC UNSIGNED VOID 
%type<nodePtr> cCode0 cCode globalDeclaration declaration type
%type<nodePtr> typeName structTypeName structMemberDeclarations structMemberDeclaration structMembers initializations initialization variable pointerSpecifier variableName
%type<nodePtr> paramTypes paramTypeName variableWithNoName variableWithNoNameCore initialValue initialValues functionDeclaration statementBlock localDeclarations statements
%type<nodePtr> statement expressionStatement loopStatement branchStatement caseBlock caseStatements jumpStatement expression assignmentExpression tenaryConditionExpression
%type<nodePtr> logicalOrExpression logicalAndExpression bitwiseOrExpression bitwiseExclusiveOrExpression bitwiseAndExpression equalityComparisonExpression 
%type<nodePtr> shiftExpression arithmeticAddExpression arithmeticMulExpression castedExpression unaryExpression prefixUnaryExpression postfixUnaryExpression 
%type<nodePtr> paramList atomicExpression relationComparisonExpression
%type<nodePtr> '+' '-' '(' ')' '[' ']' '{' '}' '~' '%' '^' '&' '*' '=' ';' '<' '>' ',' '?' '/' ':' '!'
%start cCode0
%%

/* Always start from declaration of a variable or a function*/
/* Generally, there are two types of C code lines: declarations(along with the initializations) and (what we called)statements */

cCode0 :
        cCode {
            treeRoot = $1;
        }
    ;

cCode :
        globalDeclaration {
            $$ = new Node(nameCounter.getNumberedName("cCode"), 1, $1);
        }
    |   cCode globalDeclaration {
            $$ = $1;
            $$->addChild($2);
    }
    ;

/* A declaration declares a variable, constant, or a function, and their values. */
/* As we all known, in C, a declaration can be global or local. A global declaration is outside any function or statement block. */

globalDeclaration :
        declaration { /* A global declaration has the same form as a local declaration. */
            $$ = new Node(nameCounter.getNumberedName("globalDeclaration"), 1, $1);
        }
    |   functionDeclaration { /* In C, all functions must be declared global (grammatically). */ 
            $$ = new Node(nameCounter.getNumberedName("globalDeclaration"), 1, $1);
        }
    |   statement {
            yyerror("syntax error");
            std::cout<<"C only supports statements within a function.\n";
        }
    |   '}' {
            yyerror("syntax error");
            std::cout<<"a '}' without its '{'.\n";
        }
    ;

/* In C, a declaration is part from statement, treated specially */
/* ...because a declaration can be outside any function, but statement must be in a function */
/*
declarations :  
        declaration
    |   declarations declaration
    ;
*/
declaration :
        type initializations ';' {
            $$ = new Node(nameCounter.getNumberedName("declaration"), 3, $1, $2, $3);
        }
    |   STRUCT IDENTIFIER '{' structMemberDeclarations '}' ';' {
            $$ = new Node(nameCounter.getNumberedName("declaration"), 6, $1, $2, $3, $4, $5, $6);
        }
    |   type initializations error  {
        error_missingSemicolon();
    } 
    /*
    |   STRUCT IDENTIFIER '{' structMemberDeclarations '}' error ';' {
        error_missingSemicolon();
    }*/
    ;

type :
        typeName {           /* int */
            $$ = new Node(nameCounter.getNumberedName("type"), 1, $1);
        }
    |   CONST typeName {     /* const int */
            $$ = new Node(nameCounter.getNumberedName("type"), 2, $1, $2);
        }
    |   STATIC typeName {    /* static int */
            $$ = new Node(nameCounter.getNumberedName("type"), 2, $1, $2);
        }
    ;

typeName :
        INT { 
            $$ = new Node(nameCounter.getNumberedName("typeName"), 1, $1);
        }               
    |   UNSIGNED INT { 
            $$ = new Node(nameCounter.getNumberedName("typeName"), 2, $1, $2);
        }  
    |   CHAR { 
            $$ = new Node(nameCounter.getNumberedName("typeName"), 1, $1);
        }  
    |   FLOAT { 
            $$ = new Node(nameCounter.getNumberedName("typeName"), 1, $1);
        }  
    |   DOUBLE { 
            $$ = new Node(nameCounter.getNumberedName("typeName"), 1, $1);
        }  
    |   VOID { 
            $$ = new Node(nameCounter.getNumberedName("typeName"), 1, $1);
        }  
    |   structTypeName { 
            $$ = new Node(nameCounter.getNumberedName("typeName"), 1, $1);
        }  
    ;

structTypeName : 
        STRUCT IDENTIFIER '{' structMemberDeclarations '}' {
            $$ = new Node(nameCounter.getNumberedName("structTypeName"), 5, $1, $2, $3, $4, $5);
        }
    |   STRUCT '{' structMemberDeclarations '}' {
            $$ = new Node(nameCounter.getNumberedName("structTypeName"), 4, $1, $2, $3, $4);
        }
    |   STRUCT IDENTIFIER {
            $$ = new Node(nameCounter.getNumberedName("structTypeName"), 2, $1, $2);
        }
    ;

structMemberDeclarations :
        structMemberDeclaration {
            $$ = new Node(nameCounter.getNumberedName("structMemberDeclarations"), 1, $1);
        }
    |   structMemberDeclarations structMemberDeclaration {
            $$ = $1;
            $$->addChild($2);
        }
    ;

structMemberDeclaration :
        type structMembers ';' {
            $$ = new Node(nameCounter.getNumberedName("structMemberDeclarations"), 3, $1, $2, $3);
        }
    /*|   type structMembers error {
        error_missingSemicolon();
    }*/
    ;

structMembers : /* notice: initialization is not allowed within a struct */
        variable {
            $$ = new Node(nameCounter.getNumberedName("structMembers"), 1, $1);
        }
    |   structMembers ',' variable {
            $$ = $1;
            $$->addChild($2);
            $$->addChild($3);
        }
    ;

initializations :
        initialization {
            $$ = new Node(nameCounter.getNumberedName("initializations"), 1, $1);
        }
    |   initializations ',' initialization {
            $$ = $1;
            $$->addChild($2);
            $$->addChild($3);
        }
    ;

/* called 'initialization', a declaration of a variable can have no initial value. */

initialization :
        variable {                       /* int a; */
            $$ = new Node(nameCounter.getNumberedName("initialization"), 1, $1);
        }
    |   variable '=' initialValue {   /* int a=10; */
            $$ = new Node(nameCounter.getNumberedName("initialization"), 3, $1, $2, $3);
        }
    ;

variable :
        pointerSpecifier variableName {  /* int *a; */
            $$ = new Node(nameCounter.getNumberedName("variable"), 2, $1, $2);
        }
    |   variableName {
            $$ = new Node(nameCounter.getNumberedName("variable"), 1, $1);
        }
    ;

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
        IDENTIFIER {
            $$ = new Node(nameCounter.getNumberedName("variableName"), 1, $1);
        }
    |   variableName '[' NUMBER ']' {    /* int a[10][10]; only constant int number is allowed */
            $$ = new Node(nameCounter.getNumberedName("variableName"), 4, $1, $2, $3, $4);
        }
    |   '(' variable ')' {              /* used for pointer to an multi-div array, a function, etc. */
            $$ = new Node(nameCounter.getNumberedName("variableName"), 3, $1, $2, $3);
        }
    |   variableName '(' ')' {           /* declaration of a function, but no implementation yet. */
            $$ = new Node(nameCounter.getNumberedName("variableName"), 3, $1, $2, $3);
        }
    |   variableName '(' paramTypes ')' {    /* declaration of a function having parameters, not implementint yet*/
            $$ = new Node(nameCounter.getNumberedName("variableName"), 4, $1, $2, $3, $4);
        }
    ;

paramTypes :    /* param can have no name, so I have to rewrite it to distinguish it from others. Really dull yeah? */
        paramTypeName {
            $$ = new Node(nameCounter.getNumberedName("paramTypes"), 1, $1);
        }
    |   paramTypes ',' paramTypeName {
            $$ = $1;
            $$->addChild($2);
            $$->addChild($3);
        }
    ;

paramTypeName :
        type {   /* int (*f)(double,char); */
            $$ = new Node(nameCounter.getNumberedName("paramTypeName"), 1, $1);
        }
    |   type variableWithNoName { /* if the param is a pointer or something else */
            $$ = new Node(nameCounter.getNumberedName("paramTypeName"), 2, $1, $2);
        }
    |   type variable {      /* int (*f)(double a,char *b); */
            $$ = new Node(nameCounter.getNumberedName("paramTypeName"), 2, $1, $2);
        }
    ;

variableWithNoName :        /* !! read this along with 'variable' !!*/
        pointerSpecifier {       /* int (*f)(double *,char **); */
            $$ = new Node(nameCounter.getNumberedName("variableWithNoName"), 1, $1);
        }
    |   variableWithNoNameCore {
            $$ = new Node(nameCounter.getNumberedName("variableWithNoName"), 1, $1);
        }
    ;

variableWithNoNameCore :    /* !! read this along with 'variableName' !!*/
        variableWithNoNameCore '[' NUMBER ']' {
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

initialValue :
        '{' initialValues '}' {          /* int a[10]={1}; */
            $$ = new Node(nameCounter.getNumberedName("initialValue"), 3, $1, $2, $3);
        }
    |   assignmentExpression {          /* int a=5+6; int b=a=3; */
            $$ = new Node(nameCounter.getNumberedName("initialValue"), 1, $1);
    }
    ;

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

/*
functionDeclaration :
        type variable '(' ')' statementBlock
    |   type variable '(' params ')' statementBlock
    ;

params : 
        paramDeclaration
    |   params ',' paramDeclaration
    ;

paramDeclaration :
        type '*' IDENTIFIER
    |   type IDENTIFIER
    |   type IDENTIFIER '[' ']'
    ;
*/

functionDeclaration :   /* rule above has something wrong, we can not recognize if a identifier is a function or a regular variable. Besides, it brings more conflicts */
        type variable statementBlock {
            //std::cout<<"a function found\n";
            $$ = new Node(nameCounter.getNumberedName("functionDeclaration"), 3, $1, $2, $3);
        }
    ;

/* a implementation of a function is a statement block. A statement block is {statements} */

statementBlock :
        '{' '}' { /* {} is supported. {;} is not necessary. */
            $$ = new Node(nameCounter.getNumberedName("statementBlock"), 2, $1, $2);
        }
    |   '{' statements '}' {
            $$ = new Node(nameCounter.getNumberedName("statementBlock"), 3, $1, $2, $3);
        }
    |   '{' localDeclarations '}' {
            $$ = new Node(nameCounter.getNumberedName("statementBlock"), 3, $1, $2, $3);
        }
    |   '{' localDeclarations statements '}' { /* our C only supports declarations before all statements */
            $$ = new Node(nameCounter.getNumberedName("statementBlock"), 4, $1, $2, $3, $4);
        }
    ;

localDeclarations :
        declaration {
            $$ = new Node(nameCounter.getNumberedName("localDeclarations"), 1, $1);
        }
    |   localDeclarations declaration {
            $$ = $1;
            $$->addChild($2);
        }
    ;

statements :    /* some statements */
        statement {
            $$ = new Node(nameCounter.getNumberedName("statements"), 1, $1);
        }
    |   statements statement {
            $$ = $1;
            $$->addChild($2);
        }
    ;

statement :     /* a single statement, ended with (or block without) a ';'*/
        expressionStatement {
            $$ = new Node(nameCounter.getNumberedName("statement"), 1, $1);
        }
    |   loopStatement {
            $$ = new Node(nameCounter.getNumberedName("statement"), 1, $1);
        }
    |   statementBlock { /* nested blocks is supported. But we are not going to support a block that is not body of loop, branch or function. */
            $$ = new Node(nameCounter.getNumberedName("statement"), 1, $1);
        }    
    |   branchStatement {
            $$ = new Node(nameCounter.getNumberedName("statement"), 1, $1);
        }
    |   jumpStatement {
            $$ = new Node(nameCounter.getNumberedName("statement"), 1, $1);
        }
    |   error ';' {
        error_wrongStatement();
    }
    |   error '}' {
        error_wrongStatement();
    }
    ;

expressionStatement :
        ';' {
            //std::cout<<"a empty expression statement found\n";
            $$ = new Node(nameCounter.getNumberedName("expressionStatement"), 1, $1);
        }
    |   expression ';' {
            $$ = new Node(nameCounter.getNumberedName("expressionStatement"), 2, $1, $2);
        }
    |   expression error {
        error_missingSemicolon();
    }
    ;

loopStatement : /* for, while, do-while*/
        FOR '(' expressionStatement expressionStatement expression ')' statement { /* Our C does NOT support "for(int i=0;i<10;i++)" */
            $$ = new Node(nameCounter.getNumberedName("loopStatement"), 7, $1, $2, $3, $4, $5, $6, $7);
        }
    |   WHILE '(' expression ')' statement {
            $$ = new Node(nameCounter.getNumberedName("loopStatement"), 5, $1, $2, $3, $4, $5);
        }
    |   DO statement WHILE '(' expression ')' ';' {
            $$ = new Node(nameCounter.getNumberedName("loopStatement"), 7, $1, $2, $3, $4, $5, $6, $7);
        }
    |   WHILE '(' expression error { error_missingRightBrancket(); } ')' statement /* error recovery */
    |   WHILE '(' error { error_wrongExpression; } ')' statement { 

    }
    ;

branchStatement :
        IF '(' expression ')' statement {
            $$ = new Node(nameCounter.getNumberedName("branchStatement"), 5, $1, $2, $3, $4, $5);
        }
    |   IF '(' expression ')' statement ELSE statement { /* (Hanging-ELSE problem) DON'T move this line to the first rule. YACC handle this conflict the same as we hope. */
            $$ = new Node(nameCounter.getNumberedName("branchStatement"), 7, $1, $2, $3, $4, $5, $6, $7);
        }
    |   SWITCH '(' expression ')' caseBlock
    |   error { error_elseWithNoIf(); } ELSE statement {

    }
    ;   /* too complex, SWITCH is not supported yet */

caseBlock :
        '{' caseStatements '}'
    ;

caseStatements :
        CASE tenaryConditionExpression ':' statement
    |   DEFAULT ':' statement
    ;

jumpStatement :
        RETURN ';' {
            $$ = new Node(nameCounter.getNumberedName("jumpStatement"), 2, $1, $2);
        }
    |   RETURN expression ';' {
            $$ = new Node(nameCounter.getNumberedName("jumpStatement"), 3, $1, $2, $3);
        }
    |   CONTINUE ';' {
            $$ = new Node(nameCounter.getNumberedName("jumpStatement"), 2, $1, $2);
        }
    |   BREAK ';' {
            $$ = new Node(nameCounter.getNumberedName("jumpStatement"), 2, $1, $2);
        }
    |   GOTO IDENTIFIER ';' {
            $$ = new Node(nameCounter.getNumberedName("jumpStatement"), 3, $1, $2, $3);
        }
    ; 


/* The formula expressions, with priorities from LOW to HIGH*/

/* PRIORITY 15: "," */

expression : 
        assignmentExpression {
            //$$ = new Node(nameCounter.getNumberedName("expression"), 1, $1);
            $1 = new Node(nameCounter.getNumberedName("assignmentExpression"));
            $$ = new Node(nameCounter.getNumberedName("expression"), 1, $1);
        }
    |   expression ',' assignmentExpression {
            $3 = new Node(nameCounter.getNumberedName("assignmentExpression"));
            $$ = $1;
            $$->addChild($2);
            $$->addChild($3);
        }
    /*|   error ',' {
        error_wrongExpression();
    }*/
    ;

/* PRIORITY 14: "=, +=, -=, ..." assignment */

assignmentExpression :
        tenaryConditionExpression
    |   unaryExpression '=' assignmentExpression
    |   unaryExpression ADD_ASSIGN assignmentExpression
    |   unaryExpression SUB_ASSIGN assignmentExpression
    |   unaryExpression MUL_ASSIGN assignmentExpression
    |   unaryExpression DIV_ASSIGN assignmentExpression
    /*|   error ')' {
        error_wrongExpression();
    }*/
    ;

/* PRIORITY 13: "?:" tenary conditional operator */

tenaryConditionExpression :
        logicalOrExpression
    |   logicalOrExpression '?' expression ':' tenaryConditionExpression /* Hint: right hand of ':' cannot be expression because no '=' should appear at the right hand of ':'. */
    ;

/* PRIORITY 12: "||" logical OR */

logicalOrExpression :
        logicalAndExpression
    |   logicalOrExpression LOGICAL_OR logicalAndExpression
    ;

/* PRIORITY 11: "&&" logical AND */

logicalAndExpression :
        bitwiseOrExpression
    |   logicalAndExpression LOGICAL_AND bitwiseOrExpression
    ;

/* PRIORITY 10: "|" bitwise OR */

bitwiseOrExpression :
        bitwiseExclusiveOrExpression
    |   bitwiseOrExpression '|' bitwiseExclusiveOrExpression
    ;

/* PRIORITY 9: "^" bitwise EXCLUSIVE OR */

bitwiseExclusiveOrExpression :
        bitwiseAndExpression
    |   bitwiseExclusiveOrExpression '^' bitwiseAndExpression
    ;

/* PRIORITY 8: "&" bitwise AND */

bitwiseAndExpression :
        equalityComparisonExpression
    |   bitwiseAndExpression '&' equalityComparisonExpression
    ;

/* PRIORITY 7: "==, !=" compare equality */

equalityComparisonExpression :
        relationComparisonExpression
    |   equalityComparisonExpression EQ relationComparisonExpression
    |   equalityComparisonExpression NE relationComparisonExpression
    ;

/* PRIORITY 6: "<, >, <=, >=" compare relation */

relationComparisonExpression :
        shiftExpression
    |   relationComparisonExpression '<' shiftExpression
    |   relationComparisonExpression '>' shiftExpression
    |   relationComparisonExpression LE shiftExpression /* neglecting signed/unsigned */
    |   relationComparisonExpression GE shiftExpression /* neglecting signed/unsigned */
    ;

/* PRIORITY 5: ">>, <<" shift operator */

shiftExpression :
        arithmeticAddExpression
    |   shiftExpression SL arithmeticAddExpression
    |   shiftExpression SR arithmeticAddExpression /* neglecting signed/unsigned*/
    ;

/* PRIORITY 4: "+, -" arithmetic add */

arithmeticAddExpression :
        arithmeticMulExpression
    |   arithmeticAddExpression '+' arithmeticMulExpression
    |   arithmeticAddExpression '-' arithmeticMulExpression
    ;

/* PRIORITY 3: "*, /, %" arithmetic mul */

arithmeticMulExpression :
        unaryExpression
    |   arithmeticMulExpression '*' castedExpression
    |   arithmeticMulExpression '/' castedExpression
    |   arithmeticMulExpression '%' castedExpression
    ;

/* PRIORITY 2: typecasting */

castedExpression :
       unaryExpression
    |   '(' typeName ')' castedExpression
    ;

/* PRIORITY 1: "++, --, !, ~" unary operator, and ". ->" */

unaryExpression :
        prefixUnaryExpression
    |   postfixUnaryExpression
    ;

prefixUnaryExpression :
        INC postfixUnaryExpression /* ++a, especially ++a[i] is ++(a[i]) but not (++a)[i] */
    |   DEC postfixUnaryExpression /* --a, the same as ++a[i] */
    |   '!' postfixUnaryExpression /* logical NOT */
    |   '~' postfixUnaryExpression /* bitwise NOT */
    |   '-' postfixUnaryExpression /* negative */
    ;

postfixUnaryExpression :
        atomicExpression
    |   postfixUnaryExpression INC /* a++, espetially a[i]++ is allowed, (a[i])++ is not necessary */
    |   postfixUnaryExpression DEC /* a-- */
    |   postfixUnaryExpression '[' expression ']' /* array a[10], corresponding to prefix ++ */
    |   postfixUnaryExpression '(' paramList ')' /* function, f()[i], f[i](), f[i]()[j] are all allowed */
    |   postfixUnaryExpression '(' ')'           /* function with no params. */
    |   postfixUnaryExpression '.' IDENTIFIER    /* struct's member (a.val)*/
    |   postfixUnaryExpression PTR IDENTIFIER    /* struct's member, pointer (a->val) */
    ;

paramList :
        assignmentExpression
    |   paramList ',' assignmentExpression /* Don't mess up with "expression"!!! */
    ;

/* PRIORITY 0: branckets*/

atomicExpression :
        IDENTIFIER
    |   NUMBER
    |   STRING
    |   '(' expression ')'
    /*|   '(' expression error {
        error_missingRightBrancket();
    }*/
    ;

/* --------------The formula expressions---------------- */


%%
int yyerror(std::string s){
    noError = false;
    //printf("%s\n",s.c_str());
    printf("syntax error at line %d, column %d.\n", csLineCnt, csColumnCnt);
    //return 0;
}
void error_missingSemicolon(){
    printf("Missing \';\' at line %d, after column %d\n", csLineCnt, csColumnCnt-1);
    eatToNewLine();
}
void error_wrongStatement(){
    printf("a statement near line %d is illeagal.\n", csLineCnt);
}
void error_wrongExpression(){
    printf("an expression near line %d is illeagal.\n", csLineCnt);
}
void error_missingRightBrancket(){
    printf("expect \')\' at line %d, after column %d .\n", csLineCnt, csColumnCnt-1);
    eatToNewLine();
}
void error_elseWithNoIf(){
    printf("expect \"if\" for the \"else\", at line %d, near column %d .\n", csLineCnt, csColumnCnt-1);
}
void eatToNewLine(){
    std::cout<<"eating:\n";
    char c;
    while((c=getchar())!=EOF && c!='\n'){
        //std::cout<<c;
    }
    std::cout<<"last eaten: "<<c<<std::endl;
    if(c=='\n'){
        csLineCnt++;
        csColumnCnt=0;
    }
}
int main(){
    yyparse();
    if(noError){
        std::cout<<"Parse complete, no error was found.\n";
        treeRoot->printTree();
    }
}

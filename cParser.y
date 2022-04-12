%{
#include<stdlib.h>
#include<math.h>
%}
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN LOGICAL_OR LOGICAL_AND EQ NE SL SR INC DEC IDENTIFIER NUMBER STRING
%token FOR DO WHILE CONTINUE BREAK IF ELSE SWITCH CASE RETURN
%token STRUCT INT DOUBLE CHAR
%%

/* The formula expressions, with priorities from LOW to HIGH*/

/* PRIORITY 15: "," */

expression : 
        assignmentExpression
    |   expression ',' assignmentExpression
    ;

/* PRIORITY 14: "=, +=, -=, ..." assignment */

assignmentExpression :
        tenaryConditionExpression
    |   unaryExpression '=' assignmentExpression
    |   unaryExpression ADD_ASSIGN assignmentExpression
    |   unaryExpression SUB_ASSIGN assignmentExpression
    |   unaryExpression MUL_ASSIGN assignmentExpression
    |   unaryExpression DIV_ASSIGN assignmentExpression
    ;

/* PRIORITY 13: "?:" tenary conditional operator */

tenaryConditionExpression :
        logicalOrExpression
    |   logicalOrExpression '?' expression ':' tenaryConditionExpression /*Hint: right hand of ':' cannot be expression because no '=' should appear at the right hand of ':'.*/
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
    |   arithmeticMulExpression '*' unaryExpression
    |   arithmeticMulExpression '/' unaryExpression
    |   arithmeticMulExpression '%' unaryExpression
    ;

/* PRIORITY 2: typecasting */

castedExpression :
       unaryExpression
    |   '(' typeName ')' castedExpression
    ;

/* PRIORITY 1: "++, --, !, ~" unary operator*/

unaryExpression :
        prefixUnaryExpression
    |   postfixUnaryExpression
    ;

prefixUnaryExpression :
        INC postfixExpression /* ++a, especially ++a[i] is ++(a[i]) but not (++a)[i] */
    |   DEC postfixExpression /* --a, the same as ++a[i] */
    |   '!' postfixExpression /* logical NOT */
    |   '~' postfixExpression /* bitwise NOT */
    |   '-' postfixExpression /* negative */
    ;

postfixUnaryExpression :
        postfixExpression INC /* a++, espetially a[i]++ is allowed, (a[i])++ is not necessary */
    |   postfixExpression DEC /* a-- */
    |   postfixExpression '[' expression ']' /* array a[10], corresponding to prefix ++ */
    |   postfixExpression '(' paramList ')' /*function, f()[i], f[i](), f[i]()[j] are all allowed */
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
    ;

/*--------------The formula expressions----------------*/

/* In C, every sentence is a statement */

statements :    /* some statements */
        statement
    |   statements statement
    ;

statement :     /* a single statement, ended with (or block without) a ';'*/
        expressionStatement
    |   loopStatement
    |   statementBlock
    |   branchStatement 
    |   jumpStatement
    ;

expressionStatement :
        ';'
    |   expression ';'
    ;

loopStatement : /* for, while, do-while*/
        FOR '(' expressionStatement expressionStatement expression ')' statement /* Our C does NOT support "for(int i=0;i<10;i++)" */
    |   WHILE '(' expression ')' statement
    |   DO statement WHILE '(' expression ')' ';'
    ;

statementBlock :
        '{' '}' /* {} is supported. {;} is not necessary. */
    |   '{' statements '}'
    ;

branchStatement :
        IF '(' expression ')' statement
    |   IF '(' expression ')' statement ELSE statement /* (Hanging-ELSE problem) DON'T move this line to the first rule. YACC handle this conflict the same as we think.*/
    ;

jumpStatement :
        RETURN ';'
    |   RETURN expression ';'
    |   CONTINUE ';'
    |   BREAK ';'
    ;

/* In C, a declaration is part from statement, threated specially */
/* ...because a declaration can be outside any function, but statement must be in a function */

declarations :
        declaration
    |   declarations declaration
    ;

declaration :
        type initializations ';'
    ;

type :
        typeName            /* int */
    |   CONST typeName      /* const int */
    |   STATIC typeName     /* static int */
    ;

typeName :
        INT
    |   DOUBLE
    |   CHAR
    ;

initializations :
        initialization
    |   initializations ',' initialization
    ;

initialization :
        variable                        /* int a; */
    |   variable '=' initializeValue    /* int a=10; */
    ;

variable :
        '*' variableName                /* int *a; */
    |   variableName
    ;

variableName :
        IDENTIFIER  
    |   variableName '[' NUMBER ']'     /* int a[10][10]; */
    ;

initializeValue :
        '{' initialValues '}'           /* int a[10]={1}; */
    |   assignmentExpression;           /* int a=5+6; */
    ;

initialValues :
        initializeValue                 
        initializeValues ',' initializeValue /*int a[10]={1,2,3}*/
    ;

/* The declaration of function is different from others */

functionDeclaration :
        type IDENTIFIER '(' ')' statementBlock
    |   type IDENTIFIER '(' params ')' statementBlock
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

/* Always start from declaration of a variable or a function*/

cCode :
        globalDeclaration
    |   cCode globalDeclaration
    ;

globalDeclaration :
        functionDeclaration
    |   declaration
    ;

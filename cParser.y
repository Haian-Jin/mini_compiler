%{
#include<stdlib.h>
#include<math.h>
#include"./cCompilerCommon.h"
%}
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN LOGICAL_OR LOGICAL_AND EQ NE SL SR INC DEC IDENTIFIER NUMBER STRING
%token FOR DO WHILE CONTINUE BREAK IF ELSE SWITCH CASE RETURN
%token STRUCT INT DOUBLE CHAR PTR 
%%

/* Always start from declaration of a variable or a function*/
/* Generally, there are two types of C code lines: declarations(along with the initializations) and (what we called)statements */

cCode :
        globalDeclaration
    |   cCode globalDeclaration
    ;

/* A declaration declares a variable, constant, or a function, and their values. */
/* As we all known, in C, a declaration can be global or local. A global declaration is outside any function or statement block. */

globalDeclaration :
       declaration /* A global declaration has the same form as a local declaration. */
    |  functionDeclaration /* In C, all functions must be declared global (grammatically). */
    ;

/* In C, a declaration is part from statement, treated specially */
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
        INT                 /* unsigned is not supported yet*/
    |   UNSIGNED INT
    |   CHAR
    |   FLOAT
    |   DOUBLE
    |   VOID 
    |   structTypeName
    ;

structTypeName : 
        STRUCT IDENTIFIER '{' structMemberDeclarations '}'
    |   STRUCT '{' structMemberDeclarations '}'
    |   STRUCT IDENTIFIER
    ;

structMemberDeclarations :
        structMemberDeclaration
    |   structMemberDeclarations structMemberDeclaration
    ;

structMemberDeclaration :
        type structMembers ';'
    ;

structMembers : /* notice: initialization is not allowed within a struct */
        variable
    |   structMembers ',' variable
    ;

initializations :
        initialization
    |   initializations ',' initialization
    ;

/* called 'initialization', a declaration of a variable can have no initial value. */

initialization :
        variable                        /* int a; */
    |   variable '=' initializeValue    /* int a=10; */
    ;

variable :
        pointerSpecifier variableName   /* int *a; */
    |   variableName
    ;

pointerSpecifier :
        '*' /* a simple pointer */
    |   pointer '*' /* a pointer to another pointer variable */
    |   '*' CONST /* a pointer to a const variable */
    |   pointer '*' CONST /* a pointer to another pointer which is a pointer to a const value */
    ;

variableName :
        IDENTIFIER  
    |   variableName '[' NUMBER ']'     /* int a[10][10]; only constant int number is allowed */
    |   '(' variable ')'                /* used for pointer to an multi-div array, a function, etc. */
    |   variableName '(' ')'            /* declaration of a function, but no implementation yet. */
    |   variableName '(' paramTypes ')'     /* declaration of a function having parameters, not implementint yet*/
    ;

paramTypes :    /* param can have no name, so I have to rewrite it to distinguish it from others. Really dull yeah? */
        paramTypeName
    |   paramTypes ',' paramTypeName
    ;

paramTypeName :
        type    /* int (*f)(double,char); */
    |   type variableWithNoName /* if the param is a pointer or something else */
    |   type variable       /* int (*f)(double a,char *b); */
    ;

variableWithNoName :        /* !! read this along with 'variable' !!*/
        pointerSpecifier        /* int (*f)(double *,char **); */
    |   variableWithNoNameCore
    ;

variableWithNoNameCore :    /* !! read this along with 'variableName' !!*/
        variableWithNoNameCore '[' NUMBER ']'
    |   '(' variableWithNoName ')' 
    |   variableWithNoNameCore '(' ')'  /* a function taking another function as param... */
    |   variableWithNoNameCore '(' paramTypes ')' /* a function taking another function as param... */
    |   '[' ']'             /* because it has no name, it must stop some way. Below is some terminators */
    |   '(' ')'
    |   '(' paramTypes ')'  /* a function taking another function as param... */
    ;

initializeValue :
        '{' initialValues '}'           /* int a[10]={1}; */
    |   assignmentExpression;           /* int a=5+6; int b=a=3; */
    ;

initialValues :
        initializeValue                 
        initializeValues ',' initializeValue /* int a[10]={1,2,3} */
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
        type variable statementBlock
    ;

/* a implementation of a function is a statement block. A statement block is {statements} */

statementBlock :
        '{' '}' /* {} is supported. {;} is not necessary. */
    |   '{' statements '}'
    |   '{' localDeclarations '}'
    |   '{' localDeclarations statements '}' /* our C only supports declarations before all statements */
    ;

localDeclarations :
        declaration
    |   localDeclarations declaration
    ;

statements :    /* some statements */
        statement
    |   statements statement
    ;

statement :     /* a single statement, ended with (or block without) a ';'*/
        expressionStatement 
    |   loopStatement
    |   statementBlock      /* nested blocks is supported. But we are not going to support a block that is not body of loop, branch or function. */
    |   branchStatement     /*  */
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

branchStatement :
        IF '(' expression ')' statement
    |   IF '(' expression ')' statement ELSE statement /* (Hanging-ELSE problem) DON'T move this line to the first rule. YACC handle this conflict the same as we hope. */
    |   SWITCH '(' expression ')' caseBlock
    ;   /* too complex, SWITCH is not supported yet */

caseBlock :
        '{' caseStatements '}'
    ;

caseStatements :
        CASE tenaryConditionExpression ':' statement
    |   DEFAULT ':' statement
    ;

jumpStatement :
        RETURN ';'
    |   RETURN expression ';'
    |   CONTINUE ';'
    |   BREAK ';'
    ;


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
    |   arithmeticMulExpression '*' unaryExpression
    |   arithmeticMulExpression '/' unaryExpression
    |   arithmeticMulExpression '%' unaryExpression
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
    |   postfixExpression '(' paramList ')' /* function, f()[i], f[i](), f[i]()[j] are all allowed */
    |   postfixExpression '.' IDENTIFIER    /* struct's member (a.val)*/
    |   postfixExpression PTR IDENTIFIER    /* struct's member, pointer (a->val) */
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

/* --------------The formula expressions---------------- */



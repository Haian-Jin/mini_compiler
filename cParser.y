%{
#include<stdlib.h>
#include<math.h>
%}

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
    |   logicalOrExpression '?' expression ':' tenaryConditionExpression /*Hint: right hand of ':' cannot be expresion because no '=' should appear at the right hand of ':'.*/
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


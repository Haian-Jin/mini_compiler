## 序言

### 1.1 概述



### 1.2 开发环境

Ubuntu 18.04

### 1.3 文件说明



### 1.4 组员分工

|      |      |
| :--- | :--- |
|      |      |
|      |      |
|      |      |



## 第二章 词法分析



### 2.1 Lex

Lex是Lexical Analyzer Generator（取前三个字母）的缩写，是Unix环境下非常著名的工具，主要功能是生成一个词法分析器(scanner)的[C](https://baike.baidu.com/item/C/7252092)源码，描述规则采用正则表达式(regular expression)。



### 2.2 正则表达式

正则表达式是通过单个字符串描述，匹配一系列符合某个句法规则的字符串。在实际应用中，常用到的语法规则如下（摘录自[维基百科]([https://zh.wikipedia.org/wiki/%E6%AD%A3%E5%88%99%E8%A1%A8%E8%BE%BE%E5%BC%8F](https://zh.wikipedia.org/wiki/正则表达式)))

|   字符   |                             描述                             |
| :------: | :----------------------------------------------------------: |
|   `\`    | 将下一个字符标记为一个特殊字符（File Format Escape，清单见本表）、或一个原义字符（Identity Escape，有^$()*+?.[\{\|共计12个)、或一个向后引用（backreferences）、或一个八进制转义符。例如，“`n`”匹配字符“`n`”。“`\n`”匹配一个换行符。序列“`\\`”匹配“`\`”而“`\(`”则匹配“`(`”。 |
|   `^`    | 匹配输入字符串的开始位置。如果设置了RegExp对象的Multiline属性，^也匹配“`\n`”或“`\r`”之后的位置。 |
|   `$`    | 匹配输入字符串的结束位置。如果设置了RegExp对象的Multiline属性，$也匹配“`\n`”或“`\r`”之前的位置。 |
|   `*`    | 匹配前面的子表达式零次或多次。例如，zo*能匹配“`z`”、“`zo`”以及“`zoo`”。*等价于{0,}。 |
|   `+`    | 匹配前面的子表达式一次或多次。例如，“`zo+`”能匹配“`zo`”以及“`zoo`”，但不能匹配“`z`”。+等价于{1,}。 |
|   `?`    | 匹配前面的子表达式零次或一次。例如，“`do(es)?`”可以匹配“`does`”中的“`do`”和“`does`”。?等价于{0,1}。 |
|  `{n}`   | *n*是一个非负整数。匹配确定的*n*次。例如，“`o{2}`”不能匹配“`Bob`”中的“`o`”，但是能匹配“`food`”中的两个o。 |
|  `{n,}`  | *n*是一个非负整数。至少匹配*n*次。例如，“`o{2,}`”不能匹配“`Bob`”中的“`o`”，但能匹配“`foooood`”中的所有o。“`o{1,}`”等价于“`o+`”。“`o{0,}`”则等价于“`o*`”。 |
| `{n,m}`  | *m*和*n*均为非负整数，其中*n*<=*m*。最少匹配*n*次且最多匹配*m*次。例如，“`o{1,3}`”将匹配“`fooooood`”中的前三个o。“`o{0,1}`”等价于“`o?`”。请注意在逗号和两个数之间不能有空格。 |
|   `?`    | 非贪心量化（Non-greedy quantifiers）：当该字符紧跟在任何一个其他重复修饰符（*,+,?，{*n*}，{*n*,}，{*n*,*m*}）后面时，匹配模式是**非**贪婪的。非贪婪模式尽可能少的匹配所搜索的字符串，而默认的贪婪模式则尽可能多的匹配所搜索的字符串。例如，对于字符串“`oooo`”，“`o+?`”将匹配单个“`o`”，而“`o+`”将匹配所有“`o`”。 |
|   `.`    | 匹配除“`\r`”“`\n`”之外的任何单个字符。要匹配包括“`\r`”“`\n`”在内的任何字符，请使用像“`(.|\r|\n)`”的模式。 |
|  `x|y`   | 没有包围在()里，其范围是整个正则表达式。例如，“`z|food`”能匹配“`z`”或“`food`”。“`(?:z|f)ood`”则匹配“`zood`”或“`food`”。 |
| `[xyz]`  | 字符集合（character class）。匹配所包含的任意一个字符。例如，“`[abc]`”可以匹配“`plain`”中的“`a`”。特殊字符仅有反斜线\保持特殊含义，用于转义字符。其它特殊字符如星号、加号、各种括号等均作为普通字符。脱字符^如果出现在首位则表示负值字符集合；如果出现在字符串中间就仅作为普通字符。连字符 - 如果出现在字符串中间表示字符范围描述；如果如果出现在首位（或末尾）则仅作为普通字符。右方括号应转义出现，也可以作为首位字符出现。 |
| `[^xyz]` | 排除型字符集合（negated character classes）。匹配未列出的任意字符。例如，“`[^abc]`”可以匹配“`plain`”中的“`plin`”。 |
| `[a-z]`  | 字符范围。匹配指定范围内的任意字符。例如，“`[a-z]`”可以匹配“`a`”到“`z`”范围内的任意小写字母字符。 |
| `[^a-z]` | 排除型的字符范围。匹配任何不在指定范围内的任意字符。例如，“`[^a-z]`”可以匹配任何不在“`a`”到“`z`”范围内的任意字符。 |
|   `\d`   | 匹配一个数字字符。等价于[0-9]。注意Unicode正则表达式会匹配全角数字字符。 |
|   `\D`   |              匹配一个非数字字符。等价于[^0-9]。              |
|   `\n`   |              匹配一个换行符。等价于\x0a和\cJ。               |
|   `\r`   |              匹配一个回车符。等价于\x0d和\cM。               |
|   `\s`   | 匹配任何空白字符，包括空格、制表符、换页符等等。等价于[ \f\n\r\t\v]。注意Unicode正则表达式会匹配全角空格符。 |
|   `\S`   |          匹配任何非空白字符。等价于[^ \f\n\r\t\v]。          |
|   `\w`   | 匹配包括下划线的任何单词字符。等价于“`[A-Za-z0-9_]`”。注意Unicode正则表达式会匹配中文字符。 |
|   `\W`   |        匹配任何非单词字符。等价于“`[^A-Za-z0-9_]`”。         |

### 2.3 具体实现

#### 2.3.1 定义区

```
%{
#include "./cCompilerCommon.hpp"
#include "./cParser.hpp"

void echo(bool negligible=false);
void echoint();
void echodouble();
void echochar();
void errecho();
void echoidentifier();
inline void mkNode(bool negligible);
extern YYSTYPE yylval;
static YYSTYPE tempYylval;
%}

%option noyywrap

intNumber (([1-9][0-9]*)|[0-9])|(0x[0-9a-fA-F]+)|(0[0-7]*)
identifier [a-zA-Z_][a-zA-Z0-9_]*
doubleNumber {intNumber}\.{intNumber}
emptyChar [ \t\n\r]
char \'.\'|\'\\.\' 
string \"[^\"]*\"

commentLine (\/\/.*\n)|(\/\*(.|\n)*\*\/)
```



#### 2.3.2 规则区

```
{emptyChar} {
    if(yytext[0] == '\n'){
        csColumnCnt = 0;
        csLineCnt++;
    }else{
        csColumnCnt++;
    }
}
{commentLine} {
    csColumnCnt=0;
    for(int i=0; yytext[i]; i++)
        csLineCnt += (yytext[i]=='\n');
}

int {
    echo();
    csColumnCnt+=3;
    return INT;
}
float {
    echo();
    csColumnCnt+=5;
    return FLOAT;
}
double {
    echo();
    csColumnCnt+=6;
    return DOUBLE;
}
char {
    echo();
    csColumnCnt+=4;
    return CHAR;
}
for {
    echo();
    csColumnCnt+=3;
    return FOR;
}
do {
    echo();
    csColumnCnt+=2;
    return DO;
}
while {
    echo();
    csColumnCnt+=5;
    return WHILE;
}
continue {
    echo();
    csColumnCnt+=8;
    return CONTINUE;
}
break {
    echo();
    csColumnCnt+=5;
    return BREAK;
}
switch {
    echo();
    csColumnCnt+=6;
    return SWITCH;
}
case {
    echo();
    csColumnCnt+=4;
    return CASE;
}
default {
    echo();
    csColumnCnt+=7;
    return DEFAULT;
}
if {
    echo();
    csColumnCnt+=2;
    return IF;
}
else {
    echo();
    csColumnCnt+=4;
    return ELSE;
}
return {
    echo();
    csColumnCnt+=6;
    return RETURN;
}
struct {
    echo();
    csColumnCnt+=5;
    return STRUCT;
}
unsigned {
    echo();
    csColumnCnt+=8;
    return UNSIGNED;
}
const {
    echo();
    csColumnCnt+=5;
    return CONST;
}
static {
    echo();
    csColumnCnt+=6;
    return STATIC;
}
void {
    echo();
    csColumnCnt+=4;
    return VOID;
}
goto {
    echo();
    csColumnCnt+=4;
    return GOTO;
}



{intNumber} {
    echoint();
    csColumnCnt+=strlen(yytext);
    return INT_NUMBER;
}
{doubleNumber} {
    echodouble();
    csColumnCnt+=strlen(yytext);
    return DOUBLE_NUMBER;
}
{char} {
    echochar();
    csColumnCnt+=strlen(yytext);
    return INT_NUMBER;
}
\+\= {
    echo();
    csColumnCnt+=strlen(yytext);
    return ADD_ASSIGN;
}
\-\= {
    echo();
    csColumnCnt+=strlen(yytext);
    return SUB_ASSIGN;
}
\*\= {
    echo();
    csColumnCnt+=strlen(yytext);
    return MUL_ASSIGN;
}
\/\= {
    echo();
    csColumnCnt+=strlen(yytext);
    return DIV_ASSIGN;
}
\&\& {
    echo();
    csColumnCnt+=strlen(yytext);
    return LOGICAL_AND;
}
\|\| {
    echo();
    csColumnCnt+=strlen(yytext);
    return LOGICAL_OR;
}
\=\= {
    echo();
    csColumnCnt+=strlen(yytext);
    return EQ;
}
\!\= {
    echo();
    csColumnCnt+=strlen(yytext);
    return NE;
}
\<\= {
    echo();
    csColumnCnt+=strlen(yytext);
    return LE;
}
\>\= {
    echo();
    csColumnCnt+=strlen(yytext);
    return GE;
}
\<\< {
    echo();
    csColumnCnt+=strlen(yytext);
    return SL;
}
\>\> {
    echo();
    csColumnCnt+=strlen(yytext);
    return SR;
}
\+\+ {
    echo();
    csColumnCnt+=strlen(yytext);
    return INC;
}
\-\- {
    echo();
    csColumnCnt+=strlen(yytext);
    return DEC;
}
\-\> {
    echo();
    csColumnCnt+=strlen(yytext);
    return PTR;
}


{identifier} {
    echoidentifier();
    csColumnCnt+=strlen(yytext);
    return IDENTIFIER;
}
{string} {
    echo();
    csColumnCnt+=strlen(yytext);
    return STRING;
}
[\)\(\;\]\[\}\{\,] {
    echo(true);
    csColumnCnt+=strlen(yytext);
    return yytext[0];
}
[\-\^\+\*\/\=\)\(\&\%\!\?\/\'\"\:\;\|\]\[\}\{\~\,\.\<\>] {
    echo();
    csColumnCnt+=strlen(yytext);
    return yytext[0];
}

. {
    errecho();
    csColumnCnt+=strlen(yytext);
    //return yytext[0];
}

```



## 第三章 语法分析



### 3.1 Yacc

yacc(Yet Another Compiler Compiler)，是一个经典的生成语法分析器的工具。yacc生成的编译器主要是用C语言写成的语法解析器（Parser），需要与词法解析器Lex一起使用，再把两部份产生出来的C程序一并编译。



### 3.2 抽象语法树

在计算机科学中，抽象语法树（Abstract Syntax Tree，AST），或简称语法树（Syntax tree），是源代码语法结构的一种抽象表示。它以树状的形式表现编程语言的语法结构，树上的每个节点都表示源代码中的一种结构。



### 3.3 语法分析的具体实现

我们设计的具体语法如下。

==<font color=red>**本文档只保留了文法设计，没有展示抽象语法树的具体实现。**</font>==

```
cCode0 :
        cCode 
    ;

cCode :
        globalDeclaration 
    |   cCode globalDeclaration 
    ;

/* declaration 用于定义变量或者定义结构体；functionDeclaration 用于定义函数 */
/* 在我们的语言中，定义分为全局和局部两种。全局定义是放在任何 statement block（语句块）之外的。 */

globalDeclaration :
        declaration
    |   functionDeclaration 
    ;


declaration :
        type initializations ';' 
    |   STRUCT IDENTIFIER '{' structMemberDeclarations '}' ';' 
    ;

type :
        typeName {$$ = $1;}          /* int */
    |   CONST typeName {$$ = $2;}     /* const int, 不实现这一条。 */     
    |   STATIC typeName {$$ = $2;}   /* static int, 不实现这一条。 */
    ;

typeName :
        INT             
    |   UNSIGNED INT { /* 不实现这一条 */}  
    |   CHAR 
    |   FLOAT 
    |   DOUBLE 
    |   VOID 
    |   structTypeName 
    ;

/* 定义结构体。注：在定义有名结构体的同时定义该结构体的变量，对应的产生式移到 declaration 里面去了。 */
/* （这是我设计产生式时候的失误） */
structTypeName : 
        STRUCT '{' structMemberDeclarations '}'
    |   STRUCT IDENTIFIER
    ;

/* 定义结构体的成员变量。这个和 declarations 的不同在于，这里不能定义函数，也不能做初始化。 */
structMemberDeclarations :
        structMemberDeclaration
    |   structMemberDeclarations structMemberDeclaration
    ;

structMemberDeclaration :
        type structMembers ';'
    ;

structMembers : /* 注：结构体的成员变量不能做初始化 */
        variable
    |   structMembers ',' variable
    ;

/* 初始化，负责在定义变量的同时赋予初始值。当然也可以不赋予初始值。 */
/* 有时间的话就实现一下初始值，没时间就算了。 */
initializations :
        initialization
    |   initializations ',' initialization
    ;

initialization :
        variable
    |   variable '=' initialValue
    ;

variable :
        pointerSpecifier variableName
    |   variableName
    ;

/* 我们不打算实现指针。 */
pointerSpecifier :
        '*'
    |   pointerSpecifier '*'
    |   '*' CONST
    |   pointerSpecifier '*' CONST
    ;

variableName :
        IDENTIFIER
    |   variableName '[' INT_NUMBER ']'
    |   '(' variable ')'
    |   variableName '(' ')'
    |   variableName '(' paramTypes ')'
    ;

paramTypes :    /* 参数可以没有名字、只有类型。但是我们的参数必须给名字。 */
        paramTypeName 
    |   paramTypes ',' paramTypeName 
    ;

paramTypeName :
        type variable 
    ;

/* 不用管这个，都不实现的。 */
variableWithNoName :        /* !! 如果要阅读这个的话，请和 variable 相关的产生式一起阅读 !!*/
        pointerSpecifier 
    |   variableWithNoNameCore 
    ;

/* 不用管这个，都不实现的。 */
variableWithNoNameCore :    /* !! read this along with 'variableName' !!*/
        variableWithNoNameCore '[' INT_NUMBER ']' 
    |   '(' variableWithNoName ')' 
    |   variableWithNoNameCore '(' ')' 
    |   variableWithNoNameCore '(' paramTypes ')' 
    |   '[' ']' 
    |   '(' ')' 
    |   '(' paramTypes ')' 
    ;

/* 初始值，如果要在定义的时候初始化的话，initialValue 就是跟在 = 后面的部分。有时间的话就实现一下初始值，没时间就算了。 */
initialValue :
        '{' initialValues '}'
    |   assignmentExpression
    ;

/* 初始化列表 */
initialValues :
        initialValue
    |   initialValues ',' initialValue
    ;

/* 函数定义 */
functionDeclaration :   
        type variable  statementBlock
    ;

/* 语句块，即“{...}” */
statementBlock : 
        '{' '}' 
    |   '{' statements '}' 
    ;

/* 局部变量定义。和全局定义的区别在于，局部不能定义函数。 */
localDeclarations :
        declaration
    |   localDeclarations declaration 
    ;

statements :    /* 一串语句 */
        statement
    |   statements statement 
    ;

statement :     /* 一个语句，以封号“;”结尾。（但是语句块可以不以封号结尾） */
        declaration 
    |   expressionStatement 
    |   loopStatement 
    |   statementBlock
    |   branchStatement
    |   jumpStatement
    |   error ';' 
    ;

expressionStatement :
        ';' 
    |   expression ';' 
    |   expression error 
    ;

loopStatement : /* for, while, do-while */
        FOR '(' expressionStatement expressionStatement expression ')' statement 
    |   WHILE '(' expression ')' statement
    // do-while暂不实现
    |   DO statement WHILE '(' expression ')' ';'
    |   WHILE '(' expression error { error_missingRightBrancket(); } ')' statement /* error recovery */
    |   WHILE '(' error { error_wrongExpression; } ')' statement 
    ;

/* 分支跳转语句 */
branchStatement :
        IF '(' expression ')' statement 
    |   IF '(' expression ')' statement ELSE statement 
    |   SWITCH '(' expression ')' caseBlock /* 我们不打算实现 SWITCH-CASE，因为太复杂了 */
    |   error  ELSE statement
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
        RETURN ';'
    |   RETURN expression ';' 
    |   CONTINUE ';'
    |   BREAK ';'
    ; 


/* 表达式，有十六个优先级（大大小小加起来大概有十九个） */

/* PRIORITY 15: "," */

expression : 
        assignmentExpression 
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
    |   logicalOrExpression '?' expression ':' tenaryConditionExpression 
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
    |   equalityComparisonExpression NE relationComparisonExpression 
    ;

/* PRIORITY 6: "<, >, <=, >=" compare relation */

relationComparisonExpression :
        shiftExpression 
    |   relationComparisonExpression '<' shiftExpression
    |   relationComparisonExpression '>' shiftExpression 
    |   relationComparisonExpression LE shiftExpression 
    |   relationComparisonExpression GE shiftExpression 
    ;

/* PRIORITY 5: ">>, <<" shift operator */

shiftExpression :
        arithmeticAddExpression 
    |   shiftExpression SL arithmeticAddExpression 
    |   shiftExpression SR arithmeticAddExpression 
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
/* 类型转换这个我们不实现。只用第一个产生式。 */

castedExpression :
       unaryExpression
    ;

/* PRIORITY 1: "++, --, !, ~" unary operator, and ". ->" */
/* 前++比后++优先的。原因是 ++a[i] 的意思是 ++(a[i]) 而不是 (++a)[i] */

unaryExpression :
        prefixUnaryExpression
    |   postfixUnaryExpression
    ;

prefixUnaryExpression :
        INC postfixUnaryExpression
    |   DEC postfixUnaryExpression
    |   '!' postfixUnaryExpression
    |   '~' postfixUnaryExpression
    |   '-' postfixUnaryExpression
    ;

postfixUnaryExpression :
        atomicExpression
    |   postfixUnaryExpression INC
    |   postfixUnaryExpression DEC
    |   postfixUnaryExpression '[' assignmentExpression ']'
    |   postfixUnaryExpression '(' paramList ')'
    |   postfixUnaryExpression '(' ')'
    |   postfixUnaryExpression '.' IDENTIFIER
    |   postfixUnaryExpression '[' expression error
    ;

paramList :
        assignmentExpression
    |   paramList ',' assignmentExpression
    ;

/* PRIORITY 0: branckets */

atomicExpression :
        IDENTIFIER
    |   DOUBLE_NUMBER
    |   INT_NUMBER
    |   STRING
    |   '(' expression ')'
    ;

```



### 3.4 抽象语法树可视化 





## 第四章 语义分析

### 4.1 LLVM概述



### 4.2 LLVM IR



#### 4.2.1 IR布局



#### 4.2.2 IR上下文环境



#### 4.2.3 IR核心类



### 4.3 IR生成

#### 4.3.1 运行环境设计



#### 4.3.2 类型系统







#### 4.3.3 常量获取



#### 4.3.4 变量创建和存取



#### 4.3.5 标识符/数组引用





#### 4.3.6 二元操作



#### 4.3.7 赋值语句





#### 4.3.8 Program

#### 4.3.9 Routine

#### 4.3.10 常量/变量声明



#### 4.3.11 函数/过程声明

#### 4.3.12 函数/过程调用



#### 4.3.13 系统函数/过程





#### 4.3.14 分支语句

##### 4.3.14.1 if语句

##### 4.3.14.2 case语句



#### 4.3.15 循环语句

## 第四章 优化考虑

###  常量折叠

常量折叠是一种非常常见和重要的优化，在LLVM生成IR的时候支持通过IRBuilder进行常量折叠优化，而不需要通过AST中的任何额外操作来提供支持。在调用IRBuilder时它会自动检查是否存在常量折叠的机会，如果有则直接返回常量而不是创建计算指令。以下是一个常量折叠的例子：

- 优化前

```c
define double @test(double %x) {
entry:
        %addtmp = fadd double 2.000000e+00, 1.000000e+00
        %addtmp1 = fadd double %addtmp, %x
        ret double %addtmp1
}
```

- 优化后

```C
define double @test(double %x) {
entry:
        %addtmp = fadd double 3.000000e+00, %x
        ret double %addtmp
}
```

## 第五章 代码生成

### 5.1 选择目标机器

### 5.2 配置 Module

### 5.3 生成目标代码



## 第六章 测试案例



## 第七章 总结

本次作业生成了目标代码，通过了全部的测试样例，并且实现了符号表、函数调用、结构体和数组等进阶任务，成果显著，成绩优秀。

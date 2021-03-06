%{
#include "./include/ast_node.hpp"
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

%%
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

%%

void echo(bool negligible){
    mkNode(negligible);
    //printf("get: %s\n",yytext);
}
void echoint(){
    yylval.intNodePtr = new IntNode(std::string(yytext));
    yylval.intNodePtr->setPosition(csLineCnt, csColumnCnt);
    yylval.intNodePtr->setType(Node::TYPE_INT);
    yylval.intNodePtr->setKind(Node::KIND_CONSTANT);
    yylval.intNodePtr->setVariableName(std::string(yytext));
}
void echodouble(){
    yylval.doubleNodePtr = new DoubleNode(std::string(yytext));
    yylval.doubleNodePtr->setPosition(csLineCnt, csColumnCnt);
    yylval.doubleNodePtr->setType(Node::TYPE_DOUBLE);
    yylval.doubleNodePtr->setKind(Node::KIND_CONSTANT);
    yylval.doubleNodePtr->setVariableName(std::string(yytext));
}
void echochar(){
    yylval.intNodePtr = new IntNode(std::string(yytext));
    yylval.intNodePtr->setPosition(csLineCnt, csColumnCnt);
    yylval.intNodePtr->setType(Node::TYPE_CHAR);
    yylval.intNodePtr->setKind(Node::KIND_CONSTANT);
    yylval.intNodePtr->setVariableName(std::string(yytext));
}
void errecho(){
    printf("ERROR at line %d, column %d: Unsupported Character, '%s' is not supported in our C-- language, scanner will treat it as an empty character.\n", csLineCnt, csColumnCnt-1, yytext);
}

void echoidentifier(){
    yylval.identifierNodePtr = new IdentifierNode(std::string(yytext), false);
    yylval.identifierNodePtr->setPosition(csLineCnt, csColumnCnt);
}




inline void mkNode(bool negligible){
    yylval.nodePtr = new Node(std::string(yytext), negligible);
    yylval.nodePtr->setPosition(csLineCnt, csColumnCnt);
}

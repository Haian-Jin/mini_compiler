%{
#include"./cCompilerCommon.hpp"
#include "./cParser.hpp"

void echo();
void errecho();
extern YYSTYPE yylval;
static YYSTYPE tempYylval;
%}

%option noyywrap

intNumber ([1-9][0-9]*)|[0-9]
identifier [a-zA-Z_][a-zA-Z0-9_]*
doubleNumber {intNumber}\.{intNumber}
emptyChar [ \t\n]
char \'.\'|\'\\.\'
string \"[^\"]*\"

commitLine \/\/.*\n

%%
{emptyChar} {printf("emptyChar\n");}
{commitLine} {printf("commit: \"%s\"\n",yytext);}

int {echo();return INT;}
float {echo();return FLOAT;}
double {echo();return DOUBLE;}
char {echo();return CHAR;}
for {echo();return FOR;}
do {echo();return DO;}
while {echo();return WHILE;}
continue {echo();return CONTINUE;}
break {echo();return BREAK;}
switch {echo();return SWITCH;}
case {echo();return CASE;}
default {echo();return DEFAULT;}
if {echo();return IF;}
else {echo();return ELSE;}
return {echo();return RETURN;}
struct {echo();return STRUCT;}
unsigned {echo();return UNSIGNED;}
const {echo();return CONST;}
static {echo();return STATIC;}
void {echo();return VOID;}
goto {echo();return GOTO;}



{intNumber} {echo();return NUMBER;}
{doubleNumber} {echo();return NUMBER;}
{char} {echo();return NUMBER;}
\+\= {echo();return ADD_ASSIGN;}
\-\= {echo();return SUB_ASSIGN;}
\*\= {echo();return MUL_ASSIGN;}
\/\= {echo();return DIV_ASSIGN;}
\&\& {echo();return LOGICAL_AND;}
\|\| {echo();return LOGICAL_OR;}
\=\= {echo();return EQ;}
\!\= {echo();return NE;}
\<\= {echo();return LE;}
\>\= {echo();return GE;}
\<\< {echo();return SL;}
\>\> {echo();return SR;}
\+\+ {echo();return INC;}
\-\- {echo();return DEC;}
\-\> {echo();return PTR;}


{identifier} {echo();return IDENTIFIER;}
{string} {echo();return STRING;}
[\-\^\+\*\/\=\)\(\&\%\!\?\/\'\"\:\;\|\]\[\}\{\~\,\.] {
    echo();
    return yytext[0];
}
. {
    errecho();
    return yytext[0];
}

%%

void echo(){
    printf("get: %s\n",yytext);
}
void errecho(){
    printf("undefined: %s\n",yytext);
}

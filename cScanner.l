%{
#include"./cCompilerCommon.h"
%}

intNumber [0-9][0-9]*
identifier [a-zA-Z_][a-zA-Z0-9_]*
doubleNumber {intNumber}.{intNumber}
emptyChar [ \t\n]
char \'.\'
string \"[^\"]*\"

%%
{emptyChar} {;}

int {return INT;}
double {return DOUBLE;}
char {return CHAR;}
for {return FOR;}
do {return DO;}
while {return WHILE;}
continue {return CONTINUE;}
break {return BREAK;}
switch {return SWITCH;}
case {return CASE;}
default {return DEFAULT;}
if {return IF;}
else {return ELSE;}
return {return RETURN;}
struct {return STRUCT;}
unsigned {return UNSIGNED;}
const {return CONST;}
static {return STATIC;}



{intNumber} {return NUMBER;}
{doubleNumber} {return NUMBER;}
\+\= {return ADD_ASSIGN;}
\-\= {return SUB_ASSIGN;}
\*\= {return MUL_ASSIGN;}
\/\= {return DIV_ASSIGN;}
\&\& {return LOGICAL_AND;}
\|\| {return LOGICAL_OR;}
\=\= {return EQ;}
\!\= {return NE;}
\<\< {return SL;}
\>\> {return SR;}
\+\+ {return INC;}
\-\- {return DEC;}
\-\> {return PTR;}

{identifier} {return IDENTIFIER;}
{string} {return STRING;}

%%

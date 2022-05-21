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
void error_missingRightBrancket2();
void error_elseWithNoIf();
void eatToNewLine();
void error_duplicatedVariable(Node*);
void error_variableNotDeclared(std::string);
void error_illegalArraySize(Node*);
void error_expressionTypeError(Node*,Node*,Node*);
void error_expressionTypeError(Node*,Node*);
void error_typeMismatch(Node*);
void error_variableNotDeclaredInStruct(Node*,Node*);
void error_argumentNumberNotMatch(Node*,int);
void error_argumentTypeNotMatch(std::vector<Node::Type>&,Node*,std::vector<std::string>&);
void error_structNotDeclared(std::string);
void error_notArray(Node*);
void error_returnValueTypeMismatch(Attribute* need, Node::Type give);
void error_returnValueTypeMismatch(Attribute* need, Node* give);
void error_functionReturnsArray();
%}
%code requires {
#include"./cCompilerCommon.hpp"
}
%token GOTO ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN LOGICAL_OR LOGICAL_AND EQ NE GE LE SL SR INC DEC IDENTIFIER NUMBER STRING
%token FOR DO WHILE CONTINUE BREAK IF ELSE SWITCH CASE RETURN READ WRITE
%token STRUCT INT DOUBLE CHAR PTR CONST DEFAULT FLOAT STATIC UNSIGNED VOID 

%union{
    Node* nodePtr;
}
%type<nodePtr> GOTO ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN LOGICAL_OR LOGICAL_AND EQ NE GE LE SL SR INC DEC IDENTIFIER NUMBER STRING FOR DO WHILE CONTINUE BREAK IF ELSE SWITCH CASE RETURN STRUCT INT DOUBLE CHAR PTR CONST DEFAULT FLOAT STATIC UNSIGNED VOID 
%type<nodePtr> cCode0 cCode globalDeclaration declaration type READ WRITE
%type<nodePtr> typeName structTypeName structMemberDeclarations structMemberDeclaration structMembers initializations initialization variable pointerSpecifier variableName
%type<nodePtr> paramTypes paramTypeName variableWithNoName variableWithNoNameCore initialValue initialValues functionDeclaration statementBlock localDeclarations statements
%type<nodePtr> statement expressionStatement loopStatement branchStatement caseBlock caseStatements jumpStatement expression assignmentExpression tenaryConditionExpression
%type<nodePtr> logicalOrExpression logicalAndExpression bitwiseOrExpression bitwiseExclusiveOrExpression bitwiseAndExpression equalityComparisonExpression 
%type<nodePtr> shiftExpression arithmeticAddExpression arithmeticMulExpression castedExpression unaryExpression prefixUnaryExpression postfixUnaryExpression 
%type<nodePtr> paramList atomicExpression relationComparisonExpression
%type<nodePtr> '+' '-' '(' ')' '[' ']' '{' '}' '~' '%' '^' '&' '*' '=' ';' '<' '>' ',' '?' '/' ':' '!' '|' '.'
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
            for(int i=0;i<$2->getChildrenNumber();i++){
                std::cout<<"_"<<i<<std::endl;
                Node *child = $2->getChildrenById(i);
                //child->setType($1->getType());
                child->setType($1);
            }
            for(int i=0;i<$2->getChildrenNumber();i++){
                Node *child = $2->getChildrenById(i);
                if(child->isTerminal() && child->getTokenValue().compare({","})==0)continue;
                assert(child!=NULL);
                if(symbolTableStack->insert(new Attribute(child)) == false){// insert fault.
                    error_duplicatedVariable(child);
                }
            }
            $$ = new VariableDeclarationStatementNode($$);
        }
    |   STRUCT IDENTIFIER {
            $2->setType(Node::TYPE_STRUCT);
            $2->setKind(Node::KIND_ATTRIBUTE);
            $2->setStructTypeName($2->getTokenValue());
            $2->setVariableName($2->getTokenValue());
            symbolTableStack->insert(new Attribute($2));
            symbolTableStack->push(new SymbolTable($2->getStructTypeName()));
        } '{' structMemberDeclarations '}' ';' {
            $$ = new Node(nameCounter.getNumberedName("declaration"), 6, $1, $2, $4, $5, $6, $7);
            $$ = new StructDeclarationNode($$); // TODO
            symbolTableStack->pop();
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
            // $$ = new AttributivedNode(nameCounter.getNumberedName("type"), 1, $1);
            // $$->copyFromChild();
            $$ = $1;
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
            $$ = new AttributivedNode(nameCounter.getNumberedName("typeName"), 1, $1);
            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_ATTRIBUTE);
            $$->setPosition(csLineCnt, csColumnCnt);
        }               
    |   UNSIGNED INT { 
            $$ = new AttributivedNode(nameCounter.getNumberedName("typeName"), 2, $1, $2);
            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_ATTRIBUTE);
            $$->setPosition(csLineCnt, csColumnCnt);
        }  
    |   CHAR { 
            $$ = new AttributivedNode(nameCounter.getNumberedName("typeName"), 1, $1);
            $$->setType(Node::TYPE_CHAR);
            $$->setKind(Node::KIND_ATTRIBUTE);
            $$->setPosition(csLineCnt, csColumnCnt);
        }  
    |   FLOAT { 
            $$ = new AttributivedNode(nameCounter.getNumberedName("typeName"), 1, $1);
            $$->setType(Node::TYPE_FLOAT);
            $$->setKind(Node::KIND_ATTRIBUTE);
            $$->setPosition(csLineCnt, csColumnCnt);
        }  
    |   DOUBLE { 
            $$ = new AttributivedNode(nameCounter.getNumberedName("typeName"), 1, $1);
            $$->setType(Node::TYPE_DOUBLE);
            $$->setKind(Node::KIND_ATTRIBUTE);
            $$->setPosition(csLineCnt, csColumnCnt);
        }  
    |   VOID { 
            $$ = new AttributivedNode(nameCounter.getNumberedName("typeName"), 1, $1);
            $$->setType(Node::TYPE_VOID);
            $$->setKind(Node::KIND_ATTRIBUTE);
            $$->setPosition(csLineCnt, csColumnCnt);
        }  
    |   structTypeName { 
            $$ = new AttributivedNode(nameCounter.getNumberedName("typeName"), 1, $1);
            $$->setType(Node::TYPE_STRUCT);
            $$->setKind(Node::KIND_ATTRIBUTE);
            $$->setStructTypeName($1->getStructTypeName());
            $$->setPosition($1);
        }  
    ;

structTypeName : 
    /*    STRUCT IDENTIFIER '{' structMemberDeclarations '}' {
            $$ = new AttributivedNode(nameCounter.getNumberedName("structTypeName"), 5, $1, $2, $3, $4, $5);
            $$->setType(Node::TYPE_STRUCT);
            $$->setKind(Node::KIND_ATTRIBUTE);
            $$->setStructTypeName(nameCounter.getNumberedName($2->getTokenValue()));
            $$->setPosition($1);
        }*/ /* There is a conflict between this rule and the rule "declaration -> STRUCT IDENTIFIER '{' structMemberDeclarations '}' ", so our language will not support defining a struct and a variable of its type at the same time. */
    /*|*/   STRUCT '{' {
            std::string name = nameCounter.getNumberedName("`Unamed_Structure");
            symbolTableStack->insert(new Attribute(name, Node::TYPE_STRUCT, Node::KIND_ATTRIBUTE, std::vector<Node::Type>(), std::vector<std::string>(), 
                                     std::vector<int>(), name, csLineCnt, csColumnCnt-1));
            symbolTableStack->push(new SymbolTable(name));
        } structMemberDeclarations '}' {
            $$ = new AttributivedNode(nameCounter.getNumberedName("structTypeName"), 4, $1, $2, $4, $5);
            $$->setType(Node::TYPE_STRUCT);
            $$->setKind(Node::KIND_ATTRIBUTE);
            $$->setStructTypeName(symbolTableStack->top()->getName());
            $$->setPosition($1);
            symbolTableStack->pop();
        }
    |   STRUCT IDENTIFIER {
            $$ = new AttributivedNode(nameCounter.getNumberedName("structTypeName"), 2, $1, $2);
            $$->setType(Node::TYPE_STRUCT);
            $$->setKind(Node::KIND_ATTRIBUTE);
            $$->setStructTypeName($2->getTokenValue()/*nameCounter.getNumberedName($2->getTokenValue())*/);
            $$->setPosition($1);
            if(symbolTableStack->lookUp($2->getTokenValue())==0){
                error_structNotDeclared($2->getTokenValue());
            }
        }
    ;

structMemberDeclarations :
        structMemberDeclaration {
            $$ = new Node(nameCounter.getNumberedName("structMemberDeclarations"), 1, $1);
            $$ = new StructMemberNode($$);
        }
    |   structMemberDeclarations structMemberDeclaration {
            $$ = $1;
            $$->addChild($2);
        }
    ;

structMemberDeclaration :
        type structMembers ';' {
            $$ = new Node(nameCounter.getNumberedName("structMemberDeclarations"), 3, $1, $2, $3);
            for(int i=0;i<$2->getChildrenNumber();i++){
                $2->getChildrenById(i)->setType($1);
            }
            for(int i=0;i<$2->getChildrenNumber();i++){
                if($2->getChildrenById(i)->isTerminal() && $2->getChildrenById(i)->getTokenValue().compare(",")==0) continue;
                if(symbolTableStack->insert(new Attribute($2->getChildrenById(i))) == false){
                    error_duplicatedVariable($2->getChildrenById(i));
                }
            }
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
            // $$ = new AttributivedNode(nameCounter.getNumberedName("initialization"), 1, $1);
            // $$->copyFromChild();
            std::cout<<csLineCnt<<std::endl;
            $$ = new VariableDeclarationNode($1);
            //std::cout<<"name: "<<$$->getVariableName()<<std::endl;
        }
    |   variable '=' initialValue {   /* int a=10; */
            $$ = new AttributivedNode(nameCounter.getNumberedName("initialization"), 3, $1, $2, $3);
            $$->copyFromChild();
            //std::cout<<"name: "<<$$->getVariableName()<<std::endl;
        }
    ;

variable :
        pointerSpecifier variableName {  /* int *a; */
            $$ = new Node(nameCounter.getNumberedName("variable"), 2, $1, $2);
        }
    |   variableName {
            // $$ = new AttributivedNode(nameCounter.getNumberedName("variable"), 1, $1);
            // $$->copyFromChild();
            $$ = $1;
            //std::cout<<"name: "<<$$->getVariableName()<<std::endl;
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
            $$ = new AttributivedNode(nameCounter.getNumberedName("variableName"), 1, $1);
            $$->setKind(Node::KIND_VARIABLE);
            $$->setVariableName($1->getTokenValue());
            $$->setPosition(csLineCnt, csColumnCnt);
        }
    |   variableName '[' NUMBER ']' {    /* int a[10][10]; only constant int number is allowed */
            $$ = new AttributivedNode(nameCounter.getNumberedName("variableName"), 4, $1, $2, $3, $4);
            if(!(checkType($3,Node::TYPE_INT) && checkKind($3,Node::KIND_CONSTANT))){
                error_illegalArraySize($3);
            }else{
                $$->setKind(Node::KIND_VARIABLE);
                $$->setVariableName($1->getVariableName());
                std::vector<int> sizes = $1->getArraySizes();
                int newSize;
                sscanf($3->getTokenValue().c_str(),"%d",&newSize);
                sizes.push_back(newSize);
                $$->setArraySizes(sizes);
                $$->setPosition($1);
            }
            
        }
    |   '(' variable ')' {              /* used for pointer to an multi-div array, a function, etc. */
            $$ = new Node(nameCounter.getNumberedName("variableName"), 3, $1, $2, $3);
        }
    |   variableName '(' ')' {           /* declaration of a function, but no implementation yet. */
            $$ = new AttributivedNode(nameCounter.getNumberedName("variableName"), 3, $1, $2, $3);
            $$->setKind(Node::KIND_FUNCTION);
            $$->setVariableName($1->getVariableName());
            $$->setPosition($1);
        }
    |   variableName '(' paramTypes ')' {    /* declaration of a function having parameters, not implementint yet*/
            $$ = new AttributivedNode(nameCounter.getNumberedName("variableName"), 4, $1, $2, $3, $4);
            $$->copyFrom($1);
            $$->setKind(Node::KIND_FUNCTION);
            std::vector<Node::Type> argList;
            std::vector<std::string> argListStructName;
            for(int i=0;i<$3->getChildrenNumber();i++){
                auto child = $3->getChildrenById(i);
                if(child->isTerminal())continue;
                argList.push_back(child->getType());
                if(child->getType()==Node::TYPE_STRUCT){
                    argListStructName.push_back(child->getStructTypeName());
                }else{
                    argListStructName.push_back({""});
                }
            }
            $$->setArgList(argList);
            $$->setArgListStructName(argListStructName);
            /* TODO: Think about the argument list */
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
            $$ = new AttributivedNode(nameCounter.getNumberedName("paramTypeName"), 2, $1, $2);
            // $2->setVariableName($2->getVariableName())
            $$->copyFrom($2);
            $$->setType($1);
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
        type variable { 
            $2->setType($1->getType());
            if($2->isArray()){
                error_functionReturnsArray();
            }
            //$2->setKind(Node::KIND_FUNCTION);
            if(symbolTableStack->insert(new Attribute($2))==false){
                error_duplicatedVariable($2);
                $2->setVariableName(nameCounter.getNumberedName($2->getVariableName()));
                while(symbolTableStack->insert(new Attribute($2))==false){
                    $2->setVariableName(nameCounter.getNumberedName($2->getVariableName()));
                }
                //std::cout<<" Your code is not going to be compiled due to this error.\n";
            }
            std::cout<<"function Inserted."<<'\n';
            symbolTableStack->push(new SymbolTable($2->getVariableName()));
            std::cout<<"table pushed."<<'\n';
            if($2->getArgList().size()>0){
                int ii=0;
                for(int i=0;i<$2/*->getChildrenById($2->getChildrenNumber()-1)*/->getChildrenById(2)->getChildrenNumber();i++){
                    std::cout<<"~~"<<i<<'\n';
                    auto argument = $2/*->getChildrenById($2->getChildrenNumber()-1)*/->getChildrenById(2)->getChildrenById(i);
                    if(argument->isTerminal())continue;
                    argument->setKind(Node::KIND_VARIABLE);
                    auto t = new Attribute(argument);
                    t->offset = ii++;
                    if(symbolTableStack->insert(t)==false){
                        error_duplicatedVariable(argument);
                    }
                }
            }
            $2 = new FunctionDeclarationNode($2);
            std::cout<<"function ready."<<'\n';
        } statementBlock {
            //std::cout<<"a function found\n";
            $$ = new Node(nameCounter.getNumberedName("functionDeclaration"), 3, $1, $2, $4);
            symbolTableStack->pop();
            // $$ = new 
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
    |   '{' localDeclarations statements error '}' {
            yyerror("Declaration after statements");
            //printf("Our language doesn't support statements")
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
    |   { symbolTableStack->push(new SymbolTable(nameCounter.getNumberedName("NestedBlock"))); } statementBlock { /* nested blocks is supported. But we are not going to support a block that is not body of loop, branch or function. */
            $$ = new Node(nameCounter.getNumberedName("statement"), 1, $2);
            symbolTableStack->pop();
        }    
    |   branchStatement {
            $$ = new Node(nameCounter.getNumberedName("statement"), 1, $1);
        }
    |   jumpStatement {
            $$ = new Node(nameCounter.getNumberedName("statement"), 1, $1);
        }
    |   READ '(' expression ')' {
            $$ = new ReadNode(nameCounter.getNumberedName("read"), 1, $3);
        }
    |   WRITE '(' expression ')' {
            $$ = new WriteNode(nameCounter.getNumberedName("write"), 1, $3);
        }
    |   error ';' {
        error_wrongStatement();
    }
    /*|   error '}' {
        error_wrongStatement();
    }*/
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
            $$ = new ForNode($$);
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
            $$ = new IfNode($$);
        }
    |   IF '(' expression ')' statement ELSE statement { /* (Hanging-ELSE problem) DON'T move this line to the first rule. YACC handle this conflict the same as we hope. */
            $$ = new Node(nameCounter.getNumberedName("branchStatement"), 7, $1, $2, $3, $4, $5, $6, $7);
            $$ = new IfNode($$);
        }
    |   SWITCH '(' expression ')' caseBlock
    |   error  ELSE statement {
            { error_elseWithNoIf(); }
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
            /* TODO: check if the type of return value matches the function */
            if(symbolTableStack->lookUp(symbolTableStack->top()->getName())->type != Node::TYPE_VOID){
                error_returnValueTypeMismatch(symbolTableStack->lookUp(symbolTableStack->top()->getName()), symbolTableStack->lookUp(symbolTableStack->top()->getName())->type);
            }
            $$ = new RetNode($$);
        }
    |   RETURN expression ';' {
            $$ = new Node(nameCounter.getNumberedName("jumpStatement"), 3, $1, $2, $3);
            if(!typeMatch(symbolTableStack->lookUp(symbolTableStack->top()->getName()), $2)){
                error_returnValueTypeMismatch(symbolTableStack->lookUp(symbolTableStack->top()->getName()), $2);
            }
            $$ = new RetNode($$);
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
            //$$ = new AttributivedNode(nameCounter.getNumberedName("expression"), 1, $1);
            //$$->copyFrom($1);
            if(dynamic_cast<StringNode*>($1)==NULL)
                $$ = new ExpressionNode($1);
            else
                $$=$1;
        }
    |   expression ',' assignmentExpression {
            $$ = $1;
            $$->addChild($2);
            $$->addChild($3);
            $$->copyFrom($$->getChildrenById($$->getChildrenNumber()-1));
        }
    /*|   error ',' {
        error_wrongExpression();
    }*/
    ;

/* PRIORITY 14: "=, +=, -=, ..." assignment */

assignmentExpression :
        tenaryConditionExpression {
            $$ = $1;
        }
    |   unaryExpression '=' assignmentExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFromChild();
            if(!(checkKind($1,Node::KIND_VARIABLE)) || $1->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
            if(!typeMatch($1,$3)){
                error_typeMismatch($1);
            }
            $$ = new ExpressionNode($$);
        }
    |   unaryExpression ADD_ASSIGN assignmentExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFromChild();
            if(!(checkKind($1,Node::KIND_VARIABLE))){
                error_expressionTypeError($1,$2,$3);
            }
            if(!typeMatch($1,$3)){
                error_typeMismatch($1);
            }
        }
    |   unaryExpression SUB_ASSIGN assignmentExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFromChild();
            if(!(checkKind($1,Node::KIND_VARIABLE))){
                error_expressionTypeError($1,$2,$3);
            }
            if(!typeMatch($1,$3)){
                error_typeMismatch($1);
            }
        }
    |   unaryExpression MUL_ASSIGN assignmentExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFromChild();
            if(!(checkKind($1,Node::KIND_VARIABLE))){
                error_expressionTypeError($1,$2,$3);
            }
            if(!typeMatch($1,$3)){
                error_typeMismatch($1);
            }
        }
    |   unaryExpression DIV_ASSIGN assignmentExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFromChild();
            if(!(checkKind($1,Node::KIND_VARIABLE))){
                error_expressionTypeError($1,$2,$3);
            }
            if(!typeMatch($1,$3)){
                error_typeMismatch($1);
            }
        }
    /*|   error ')' {
        error_wrongExpression();
    }*/
    ;

/* PRIORITY 13: "?:" tenary conditional operator */

tenaryConditionExpression :
        logicalOrExpression {
            $$ = $1;
        }
    |   logicalOrExpression '?' expression ':' tenaryConditionExpression {/* Hint: right hand of ':' cannot be expression because no '=' should appear at the right hand of ':'. */
            $$ = new AttributivedNode({"?:"}, 3, $1, $3, $5);
            $$->copyFromChild();
            $$->setType(Node::TYPE_INT);
            if($3->getType()==Node::TYPE_DOUBLE||$5->getType()==Node::TYPE_DOUBLE)$$->setType(Node::TYPE_DOUBLE);
            $$->setKind(Node::KIND_CONSTANT);
            if(!(checkType($1,Node::TYPE_INT))){
                error_expressionTypeError($1,$$);
            }
            if($1->isArray()){
                error_expressionTypeError($1,$$);
            }
        }
    ;

/* PRIORITY 12: "||" logical OR */

logicalOrExpression :
        logicalAndExpression {
            $$ = $1;
        }
    |   logicalOrExpression LOGICAL_OR logicalAndExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFromChild();
            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            if(!(checkType($1,Node::TYPE_INT)&&checkType($3,Node::TYPE_INT)) || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
            $$ = new ExpressionNode($$);
        }
    ;

/* PRIORITY 11: "&&" logical AND */

logicalAndExpression :
        bitwiseOrExpression {
            $$ = $1;
        }
    |   logicalAndExpression LOGICAL_AND bitwiseOrExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFromChild();
            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            if(!(checkType($1,Node::TYPE_INT)&&checkType($3,Node::TYPE_INT)) || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
            $$ = new ExpressionNode($$);
        }
    ;

/* PRIORITY 10: "|" bitwise OR */

bitwiseOrExpression :
        bitwiseExclusiveOrExpression {
            $$ = $1;
        }
    |   bitwiseOrExpression '|' bitwiseExclusiveOrExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFromChild();
            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            if(!(checkType($1,Node::TYPE_INT)&&checkType($3,Node::TYPE_INT)) || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    ;

/* PRIORITY 9: "^" bitwise EXCLUSIVE OR */

bitwiseExclusiveOrExpression :
        bitwiseAndExpression {
            $$ = $1;
        }
    |   bitwiseExclusiveOrExpression '^' bitwiseAndExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFromChild();
            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            if(!(checkType($1,Node::TYPE_INT)&&checkType($3,Node::TYPE_INT)) || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    ;

/* PRIORITY 8: "&" bitwise AND */

bitwiseAndExpression :
        equalityComparisonExpression {
            $$ = $1;
        }
    |   bitwiseAndExpression '&' equalityComparisonExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFromChild();
            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            if(!(checkType($1,Node::TYPE_INT)&&checkType($3,Node::TYPE_INT)) || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    ;

/* PRIORITY 7: "==, !=" compare equality */

equalityComparisonExpression :
        relationComparisonExpression {
            $$ = $1;
        }
    |   equalityComparisonExpression EQ relationComparisonExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFromChild();
            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            /*if(checkType($1,Node::TYPE_STRUCT)||checkType($1,Node::TYPE_VOID)||checkType($1,Node::TYPE_STRING)||checkType($3,Node::TYPE_STRUCT)||checkType($3,Node::TYPE_VOID)||checkType($3,Node::TYPE_STRING)){
                error_expressionTypeError($1,$2,$3);
            }*/
            if(!typeMatch($1,$3) || $1->getType()==Node::TYPE_VOID || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
            $$ = new ExpressionNode($$);
        }
    |   equalityComparisonExpression NE relationComparisonExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFromChild();
            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            /*if(checkType($1,Node::TYPE_STRUCT)||checkType($1,Node::TYPE_VOID)||checkType($1,Node::TYPE_STRING)||checkType($3,Node::TYPE_STRUCT)||checkType($3,Node::TYPE_VOID)||checkType($3,Node::TYPE_STRING)){
                error_expressionTypeError($1,$2,$3);
            }*/
            if(!typeMatch($1,$3) || $1->getType()==Node::TYPE_VOID || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
            $$ = new ExpressionNode($$);
        }
    ;

/* PRIORITY 6: "<, >, <=, >=" compare relation */
/* TYPE_STRING,TYPE_VOID,TYPE_STRUCT */
relationComparisonExpression :
        shiftExpression {
            $$ = $1;
        }
    |   relationComparisonExpression '<' shiftExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFromChild();
            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            if(checkType($1,Node::TYPE_STRUCT)||checkType($1,Node::TYPE_VOID)||checkType($1,Node::TYPE_STRING)||checkType($3,Node::TYPE_STRUCT)||checkType($3,Node::TYPE_VOID)||checkType($3,Node::TYPE_STRING)){
                error_expressionTypeError($1,$2,$3);
            }
            if($1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
            $$ = new ExpressionNode($$);
        }
    |   relationComparisonExpression '>' shiftExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFromChild();
            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            if(checkType($1,Node::TYPE_STRUCT)||checkType($1,Node::TYPE_VOID)||checkType($1,Node::TYPE_STRING)||checkType($3,Node::TYPE_STRUCT)||checkType($3,Node::TYPE_VOID)||checkType($3,Node::TYPE_STRING)){
                error_expressionTypeError($1,$2,$3);
            }
            if($1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
            $$ = new ExpressionNode($$);
        }
    |   relationComparisonExpression LE shiftExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFromChild();
            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            if(checkType($1,Node::TYPE_STRUCT)||checkType($1,Node::TYPE_VOID)||checkType($1,Node::TYPE_STRING)||checkType($3,Node::TYPE_STRUCT)||checkType($3,Node::TYPE_VOID)||checkType($3,Node::TYPE_STRING)){
                error_expressionTypeError($1,$2,$3);
            }
            if($1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
            $$ = new ExpressionNode($$);
        }
    |   relationComparisonExpression GE shiftExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFromChild();
            $$->setType(Node::TYPE_INT);
            $$->setKind(Node::KIND_CONSTANT);
            if(checkType($1,Node::TYPE_STRUCT)||checkType($1,Node::TYPE_VOID)||checkType($1,Node::TYPE_STRING)||checkType($3,Node::TYPE_STRUCT)||checkType($3,Node::TYPE_VOID)||checkType($3,Node::TYPE_STRING)){
                error_expressionTypeError($1,$2,$3);
            }
            if($1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
            $$ = new ExpressionNode($$);
        }
    ;

/* PRIORITY 5: ">>, <<" shift operator */

shiftExpression :
        arithmeticAddExpression {
            $$ = $1;
        }
    |   shiftExpression SL arithmeticAddExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFrom($1);
            if(!(checkType($1,Node::TYPE_INT)&&checkType($3,Node::TYPE_INT)) || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    |   shiftExpression SR arithmeticAddExpression  {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFrom($1);
            if(!(checkType($1,Node::TYPE_INT)&&checkType($3,Node::TYPE_INT)) || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
        }
    ;

/* PRIORITY 4: "+, -" arithmetic add */

arithmeticAddExpression :
        arithmeticMulExpression {
            $$ = $1;
        }
    |   arithmeticAddExpression '+' arithmeticMulExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFrom($3);
            if($1->getType()==Node::TYPE_DOUBLE || $3->getType()==Node::TYPE_DOUBLE){
                $$->setType(Node::TYPE_DOUBLE);
            }
            if($1->getType()==Node::TYPE_STRUCT || $3->getType()==Node::TYPE_STRUCT || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
            $$ = new ExpressionNode($$);
        }
    |   arithmeticAddExpression '-' arithmeticMulExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFrom($3);
            if($1->getType()==Node::TYPE_DOUBLE || $3->getType()==Node::TYPE_DOUBLE){
                $$->setType(Node::TYPE_DOUBLE);
            }
            if($1->getType()==Node::TYPE_STRUCT || $3->getType()==Node::TYPE_STRUCT || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
            $$ = new ExpressionNode($$);
        }
    ;

/* PRIORITY 3: "*, /, %" arithmetic mul */

arithmeticMulExpression :
        unaryExpression {
            $$ = $1;
        }
    |   arithmeticMulExpression '*' castedExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFrom($3);
            if($1->getType()==Node::TYPE_DOUBLE || $3->getType()==Node::TYPE_DOUBLE){
                $$->setType(Node::TYPE_DOUBLE);
            }
            if($1->getType()==Node::TYPE_STRUCT || $3->getType()==Node::TYPE_STRUCT || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
            $$ = new ExpressionNode($$);
        }
    |   arithmeticMulExpression '/' castedExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFrom($3);
            if($1->getType()==Node::TYPE_DOUBLE || $3->getType()==Node::TYPE_DOUBLE){
                $$->setType(Node::TYPE_DOUBLE);
            }
            if($1->getType()==Node::TYPE_STRUCT || $3->getType()==Node::TYPE_STRUCT || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
            $$ = new ExpressionNode($$);
        }
    |   arithmeticMulExpression '%' castedExpression {
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $$->copyFrom($3);
            if($1->getType()==Node::TYPE_DOUBLE || $3->getType()==Node::TYPE_DOUBLE){
                $$->setType(Node::TYPE_DOUBLE);
            }
            if($1->getType()==Node::TYPE_STRUCT || $3->getType()==Node::TYPE_STRUCT || $1->isArray() || $3->isArray()){
                error_expressionTypeError($1,$2,$3);
            }
            $$ = new ExpressionNode($$);
        }
    ;

/* PRIORITY 2: typecasting */

castedExpression :
       unaryExpression {
            $$ = $1;
        }
    |   '(' type ')' castedExpression {
            $$ = new AttributivedNode("castedExpression", 2, $2, $4);
        }
    |   '(' type variableWithNoName ')' castedExpression {
            $$ = new AttributivedNode("castedExpression", 3, $2, $3, $5);
        }
    ;

/* PRIORITY 1: "++, --, !, ~" unary operator, and ". ->" */

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
            $1 = new AttributivedNode(std::string("pre")+$1->getName(), 1, $2);
            $$ = $1;
            $$->copyFromChild();
            if(!checkKind($2, Node::KIND_VARIABLE) || $2->isArray() || $2->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError($2,$1);
            }
        }
    |   DEC postfixUnaryExpression {/* --a, the same as ++a[i] */
            $1 = new AttributivedNode(std::string("pre")+$1->getName(), 1, $2);
            $$ = $1;
            $$->copyFromChild();
            if(!checkKind($2, Node::KIND_VARIABLE) || $2->isArray() || $2->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError($2,$1);
            }
        }
    |   '!' postfixUnaryExpression {/* logical NOT */
            $1 = new AttributivedNode($1->getName(), 1, $2);
            $$ = $1;
            $$->copyFromChild();
            if(!checkType($2, Node::TYPE_INT)){
                error_expressionTypeError($2,$1);
            }
        }
    |   '~' postfixUnaryExpression {/* bitwise NOT */
            $1 = new AttributivedNode($1->getName(), 1, $2);
            $$ = $1;
            $$->copyFromChild();
            if(!checkType($2, Node::TYPE_INT)){
                error_expressionTypeError($2,$1);
            }
        }
    |   '-' postfixUnaryExpression {/* negative */
            $1 = new AttributivedNode($1->getName(), 1, $2);
            $$ = $1;
            if(checkType($2, Node::TYPE_STRUCT)){
                error_expressionTypeError($2,$1);
            }
        }
    ;

postfixUnaryExpression :
        atomicExpression {
            $$ = $1;
        }
    |   postfixUnaryExpression INC {/* a++, espetially a[i]++ is allowed, (a[i])++ is not necessary */
            $2 = new AttributivedNode(std::string("post")+$2->getName(), 1, $1);
            $$ = $2;
            $$->copyFromChild();
            if(!checkKind($1, Node::KIND_VARIABLE) || $1->isArray() || $1->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError($1,$2);
            }
        }
    |   postfixUnaryExpression DEC {/* a-- */
            $2 = new AttributivedNode(std::string("post")+$2->getName(), 1, $1);
            $$ = $2;
            $$->copyFromChild();
            if(!checkKind($1, Node::KIND_VARIABLE) || $1->isArray() || $1->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError($1,$2);
            }
        }
    |   postfixUnaryExpression '[' assignmentExpression ']' {/* array a[10], corresponding to prefix ++ */
            $$ = new AttributivedNode({"[]"}, 2, $1, $3);
            $$->copyFromChild();
            if(!$1->isArray()){
                error_notArray($1);
            }else {
                if(!checkType($3, Node::TYPE_INT)){
                    error_expressionTypeError($3,$$);
                }
                /* minus a dimension */
                auto arraySizes = $$->getArraySizes();
                arraySizes.erase(arraySizes.begin(),arraySizes.begin()+1);
                $$->setArraySizes(arraySizes);
                /*if(!((checkKind($3, Node::KIND_VARIABLE) || checkKind($3, Node::KIND_CONSTANT)) && checkType($3, Node::TYPE_INT) && $1->isArray() )){
                    error_expressionTypeError($1,$$,$3);
                }*/
            }
            $$ = new ExpressionNode($$);
        }
    |   postfixUnaryExpression '(' paramList ')' {/* function, f()[i], f[i](), f[i]()[j] are all allowed */
            $$ = new AttributivedNode({"()"}, 2, $1, $3);
            $$->copyFromChild();
            if(!(checkKind($1, Node::KIND_FUNCTION))){
                error_expressionTypeError($1,$2);
            }else{
                std::vector<Node::Type> argList;
                std::vector<std::string> argListStructName;
                for(int i=0;i<$3->getChildrenNumber();i++){
                    auto child = $3->getChildrenById(i);
                    if(child->isTerminal() && child->getTokenValue().compare(",")==0)continue;
                    argList.push_back(child->getType());
                    if(child->getType()==Node::TYPE_STRUCT){
                        argListStructName.push_back(child->getStructTypeName());
                    }else{
                        argListStructName.push_back({""});
                    }
                }
                if(argList.size()!=$1->getArgList().size()){
                    //std::cout<<"~";
                    error_argumentNumberNotMatch($1,argList.size());
                }else{
                    if(!typeMatch(argList,$1,argListStructName)){
                        error_argumentTypeNotMatch(argList,$1,argListStructName);
                    }
                }
            }
            $$ = new ExpressionNode($$);
        }
    |   postfixUnaryExpression '(' ')'           {/* function with no params. */
            $$ = new AttributivedNode({"()"}, 1, $1);
            $$->copyFromChild();
            if(!(checkKind($1, Node::KIND_FUNCTION))){
                error_expressionTypeError($1,$$);
            }else {
                if($1->getArgList().size()!=0){
                    error_argumentNumberNotMatch($1,0);
                }
            }
            $$ = new ExpressionNode($$);
        }
    |   postfixUnaryExpression '.' IDENTIFIER    {/* struct's member (a.val)*/
            Node *t=$2;
            $2 = new AttributivedNode($2->getName(), 2, $1, $3);
            $$ = $2;
            $2->setPosition(t);
            if(checkKind($1, Node::KIND_ATTRIBUTE) || !(checkType($1, Node::TYPE_STRUCT)) || $1->isArray())
                error_expressionTypeError($1,$2);
            else {
                auto symbolTable = SymbolTable::getSymbolTableByName($1->getStructTypeName());
            
                if(symbolTable->lookUp($3->getTokenValue()) == NULL)
                    error_variableNotDeclaredInStruct($1,$3);
                
                $$->copyFrom(symbolTable->lookUp($3->getTokenValue()));
            }
            $$ = new ExpressionNode($$);
        }
    |   postfixUnaryExpression PTR IDENTIFIER    {/* struct's member, pointer (a->val) */
            $2 = new AttributivedNode($2->getName(), 1, $1);
            $$ = $2;

        }
    |   postfixUnaryExpression '[' expression error  {
            error_missingRightBrancket2();
        }
    ;

paramList :
        assignmentExpression {
            $$ = new Node(nameCounter.getNumberedName("paramList"), 1, $1);
        }
    |   paramList ',' assignmentExpression {/* Don't mess up with "expression"!!! */
            $$ = $1;
            $$->addChild($2);
            $$->addChild($3);
        }
    ;

/* PRIORITY 0: branckets*/

atomicExpression :
        IDENTIFIER {
            $$ = $1;
            if(!symbolTableStack->lookUp($1->getTokenValue())){
                error_variableNotDeclared($1->getTokenValue());
                $$->setKind(Node::KIND_VARIABLE);
                $$->setType(Node::TYPE_INT);
            }else{
                $$->setAttribute(symbolTableStack->lookUp($1->getTokenValue()));
                $$->setPosition(csLineCnt, csColumnCnt);
            }
            $$ = new ExpressionNode($$);
        }
    |   NUMBER {
            $$ = $1;
            $$ = new ExpressionNode($$);
        }
    |   STRING {
            $$ = $1;
            $$ = new StringNode($$);
        }
    |   '(' expression ')' {
            $$ = $2;
        }
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
    std::cout<<"[ERROR] ";
    printf("Missing \';\' at line %d, after column %d\n", csLineCnt, csColumnCnt-(int)strlen(yytext));
    //eatToNewLine();
}
void error_wrongStatement(){
    std::cout<<"[ERROR] ";
    printf("a statement near line %d is illeagal. ", csLineCnt);
    printf("maybe you\'re putting a declaration after a statement.\n");//'
}
void error_wrongExpression(){
    std::cout<<"[ERROR] ";
    printf("an expression near line %d is illeagal.\n", csLineCnt);
}
void error_missingRightBrancket(){
    std::cout<<"[ERROR] ";
    printf("expect \')\' at line %d, after column %d .\n", csLineCnt, csColumnCnt-(int)strlen(yytext));
    //eatToNewLine();
}
void error_missingRightBrancket2(){
    std::cout<<"[ERROR] ";
    printf("expect \']\' at line %d, after column %d .\n", csLineCnt, csColumnCnt-(int)strlen(yytext));
    //eatToNewLine();
}
void error_elseWithNoIf(){
    std::cout<<"[ERROR] ";
    printf("expect \"if\" for the \"else\", at line %d, near column %d .\n", csLineCnt, csColumnCnt-(int)strlen(yytext));
}
void error_duplicatedVariable(Node *c){
    std::cout<<"[ERROR] ";
    std::cout<<"variable \""<<c->getVariableName()<<"\" at line "<<c->getLineNumber()<<" near column "<<c->getColumnNumber()<<""<<" has been declared before.\n";
    std::cout<<" Hint: first declaraed at line "<<symbolTableStack->lookUp(c->getVariableName())->lineNumber<<", near column "<<symbolTableStack->lookUp(c->getVariableName())->columnNumber<<std::endl;
}
void error_variableNotDeclared(std::string name){
    std::cout<<"[ERROR] ";
    std::cout<<"variable \""<<name<<"\" was not declared.\n";
    std::cout<<" Hint: first used at line "<<csLineCnt<<", near column "<<csColumnCnt<<std::endl;
}
void error_structNotDeclared(std::string name){
    std::cout<<"[ERROR] ";
    std::cout<<"struct type name \""<<name<<"\" was not declared.\n";
    std::cout<<" Hint: first used at line "<<csLineCnt<<", near column "<<csColumnCnt<<std::endl;
}
void error_illegalArraySize(Node* c){
    std::cout<<"[ERROR] ";
    std::cout<<"Size of array at line "<<c->getLineNumber()<<" near column "<<c->getColumnNumber()<<" must be a integer and must be a constant.\n";
}
void error_expressionTypeError(Node *exp1, Node *op, Node *exp2){
    std::cout<<"[ERROR] ";
    std::cout<<"Type error at line "<<op->getLineNumber()<<" near column "<<op->getColumnNumber()<<":\n";
    std::cout<<" Type "<<exp1->getTypeString()<<" and type "<<exp2->getTypeString()<<" are not match for the operator \""<<op->getTokenValue()<<"\"\n";
}
void error_expressionTypeError(Node *exp1, Node *op){
    std::cout<<"[ERROR] ";
    std::cout<<"Type error at line "<<op->getLineNumber()<<" near column "<<op->getColumnNumber()<<":\n";
    std::cout<<" Type "<<exp1->getTypeString()<<" is not supported for the operator \""<<op->getTokenValue()<<"\"\n";
}
void error_typeMismatch(Node *c){
    std::cout<<"[ERROR] ";
    std::cout<<"Type mismatch at line "<<c->getLineNumber()<<" near column "<<c->getColumnNumber()<<"\n";
    std::cout<<" Hint: are you putting an array at the left hand of \'=\', or using \'=\' to connect two mismatched type?\n";
}
void error_variableNotDeclaredInStruct(Node *v, Node *m){
    std::cout<<"[ERROR] variable \""<<v->getVariableName()<<"\" dose not has member \""<<m->getTokenValue()<<"\"\n";
    auto attribute = symbolTableStack->lookUp(v->getVariableName());
    if(attribute){
        std::cout<<" Hint: you declared this variable at line "<<attribute->lineNumber<<" near column "<<attribute->columnNumber<<std::endl;
    }
}
void error_argumentNumberNotMatch(Node *f,int an){
    std::cout<<"[ERROR] function's argument number not match at line "<<f->getLineNumber()<<" near column "<<f->getColumnNumber()<<"\n";//'
    std::cout<<" Hint: function \""<<f->getVariableName()<<"\" needs "<<f->getArgList().size()<<" arguments but you gave "<<an<<".\n";
}
void error_notArray(Node *c){
    std::cout<<"[ERROR] \""<<c->getVariableName()<<"\" at line "<<c->getLineNumber()<<" near column "<<c->getColumnNumber()<<" is not an array.\n";
    std::cout<<" Hint: are you using too many \"[]\"\'s to access an array?\n";//'
}
void error_returnValueTypeMismatch(Attribute* need, Node::Type give){
    std::cout<<"[ERROR] return value type mismatch at line "<<csLineCnt<<std::endl;
    std::cout<<" Hint: the function returns "<<type_to_string(need)<<" but you gave nothing\n"; 
}
void error_returnValueTypeMismatch(Attribute* need, Node* give){
    std::cout<<"[ERROR] return value type mismatch at line "<<csLineCnt<<std::endl;
    std::cout<<" Hint: the function returns "<<type_to_string(need)<<" but you gave "<<give->getTypeString()<<std::endl;
}
void error_functionReturnsArray(){
    std::cout<<"[ERROR] at line "<<csLineCnt<<": function cannot return an array\n";
}
void error_argumentTypeNotMatch(std::vector<Node::Type>& userGave,Node *function,std::vector<std::string>& structTypeName){
    std::cout<<"[ERROR] function's argument type not match at line "<<function->getLineNumber()<<" near column "<<function->getColumnNumber()<<"\n";//'
    std::cout<<" Hint: function \""<<function->getVariableName()<<"\" needs parameters of (";
    auto fa = function->getArgList();
    for(int i=0;i<fa.size();i++){
        switch(fa[i]){
            case Node::TYPE_INT:
                std::cout<<"int";
                break;
            case Node::TYPE_DOUBLE:
                std::cout<<"double";
                break;
            case Node::TYPE_STRUCT:
                std::cout<<"struct "<<function->getArgListStructName()[i];
                break;
            default:
                std::cout<<userGave[i]<<' ';
        }
        if(i<fa.size()-1)std::cout<<",";
    }
    std::cout<<") but you gave (";
    for(int i=0;i<userGave.size();i++){
        switch(userGave[i]){
            case Node::TYPE_INT:
                std::cout<<"int";
                break;
            case Node::TYPE_DOUBLE:
                std::cout<<"double";
                break;
            case Node::TYPE_STRUCT:
                std::cout<<"struct "<<structTypeName[i];
                break;
            default:
                std::cout<<userGave[i]<<' ';
        }
        if(i<userGave.size()-1)std::cout<<",";
    }
    std::cout<<")\n";
}
void eatToNewLine(){
    std::cout<<"eating:\n";
    char c;
    while((c=getchar())!=EOF && c!='\n'){
        //std::cout<<c;
    }
    std::cout<<"last eaten: \\"<<(int)c<<std::endl;
    if(c=='\n'){
        csLineCnt++;
        csColumnCnt=0;
    }
}
Node *makeParseTree(){
    yyparse();
    if(!noError){
        std::cout<<"The compiling cannot continue due to errors above.";
        return NULL;
    }
    return treeRoot;
}
/*
int main(){
    yyparse();
    if(!noError){
        std::cout<<"The compiling cannot continue due to errors above.";
        return 0;
    }
    std::cout<<"Parse complete, no error was found.\n";
    //treeRoot->printTree();
}
*/

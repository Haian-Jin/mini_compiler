/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_CPARSER_HPP_INCLUDED
# define YY_YY_CPARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 32 "cParser.y"

#include"./cCompilerCommon.hpp"

#line 52 "cParser.hpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    GOTO = 258,
    ADD_ASSIGN = 259,
    SUB_ASSIGN = 260,
    MUL_ASSIGN = 261,
    DIV_ASSIGN = 262,
    LOGICAL_OR = 263,
    LOGICAL_AND = 264,
    EQ = 265,
    NE = 266,
    GE = 267,
    LE = 268,
    SL = 269,
    SR = 270,
    INC = 271,
    DEC = 272,
    IDENTIFIER = 273,
    NUMBER = 274,
    STRING = 275,
    FOR = 276,
    DO = 277,
    WHILE = 278,
    CONTINUE = 279,
    BREAK = 280,
    IF = 281,
    ELSE = 282,
    SWITCH = 283,
    CASE = 284,
    RETURN = 285,
    STRUCT = 286,
    INT = 287,
    DOUBLE = 288,
    CHAR = 289,
    PTR = 290,
    CONST = 291,
    DEFAULT = 292,
    FLOAT = 293,
    STATIC = 294,
    UNSIGNED = 295,
    VOID = 296
  };
#endif
/* Tokens.  */
#define GOTO 258
#define ADD_ASSIGN 259
#define SUB_ASSIGN 260
#define MUL_ASSIGN 261
#define DIV_ASSIGN 262
#define LOGICAL_OR 263
#define LOGICAL_AND 264
#define EQ 265
#define NE 266
#define GE 267
#define LE 268
#define SL 269
#define SR 270
#define INC 271
#define DEC 272
#define IDENTIFIER 273
#define NUMBER 274
#define STRING 275
#define FOR 276
#define DO 277
#define WHILE 278
#define CONTINUE 279
#define BREAK 280
#define IF 281
#define ELSE 282
#define SWITCH 283
#define CASE 284
#define RETURN 285
#define STRUCT 286
#define INT 287
#define DOUBLE 288
#define CHAR 289
#define PTR 290
#define CONST 291
#define DEFAULT 292
#define FLOAT 293
#define STATIC 294
#define UNSIGNED 295
#define VOID 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 39 "cParser.y"

    Node* nodePtr;

#line 149 "cParser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CPARSER_HPP_INCLUDED  */

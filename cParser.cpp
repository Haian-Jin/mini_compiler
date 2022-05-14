/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "cParser.y"

#include"./cCompilerCommon.hpp"
extern int yylex();
extern char *yytext;
static bool noError = true;
static Node *treeRoot;
static NameCounter nameCounter;
int yyerror(std::string);
static void error_missingSemicolon();
static void error_missingInitializations();
static void error_wrongStatement();
static void error_wrongExpression();
static void error_missingRightBrancket();
static void error_missingRightBrancket2();
static void error_elseWithNoIf();
static void eatToNewLine();
static void error_duplicatedVariable(Node*);
static void error_variableNotDeclared(std::string);
static void error_illegalArraySize(Node*);
static void error_expressionTypeError(Node*,Node*,Node*);
static void error_expressionTypeError(Node*,Node*);
static void error_typeMismatch(Node*);
static void error_variableNotDeclaredInStruct(Node*,Node*);
static void error_argumentNumberNotMatch(Node*,int);
static void error_argumentTypeNotMatch(std::vector<Node::Type>&,Node*,std::vector<std::string>&);
static void error_structNotDeclared(std::string);
static void error_notArray(Node*);
static void error_returnValueTypeMismatch(Attribute* need, Node::Type give);
static void error_returnValueTypeMismatch(Attribute* need, Node* give);
static void error_functionReturnsArray();

#line 102 "cParser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 149 "cParser.cpp"

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
    DOUBLE_NUMBER = 274,
    INT_NUMBER = 275,
    STRING = 276,
    FOR = 277,
    DO = 278,
    WHILE = 279,
    CONTINUE = 280,
    BREAK = 281,
    IF = 282,
    ELSE = 283,
    SWITCH = 284,
    CASE = 285,
    RETURN = 286,
    STRUCT = 287,
    INT = 288,
    DOUBLE = 289,
    CHAR = 290,
    PTR = 291,
    CONST = 292,
    DEFAULT = 293,
    FLOAT = 294,
    STATIC = 295,
    UNSIGNED = 296,
    VOID = 297
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 39 "cParser.y"

    Node* nodePtr;

#line 207 "cParser.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CPARSER_HPP_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  87
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   662

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  164
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  297

#define YYUNDEFTOK  2
#define YYMAXUTOK   297


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    64,     2,     2,     2,    52,    54,     2,
      45,    46,    55,    43,    60,    44,    66,    62,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    63,    57,
      58,    56,    59,    61,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    47,     2,    48,    53,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,    65,    50,    51,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    61,    61,    67,    70,    80,    83,    86,    90,    98,
     113,   113,   125,   131,   135,   138,   144,   150,   156,   162,
     168,   174,   180,   192,   192,   206,   220,   223,   230,   245,
     248,   258,   261,   269,   273,   280,   283,   291,   294,   297,
     300,   306,   312,   327,   330,   336,   358,   361,   369,   372,
     375,   384,   387,   394,   397,   400,   403,   406,   409,   412,
     419,   422,   429,   432,   441,   441,   474,   477,   480,   483,
     486,   493,   496,   503,   506,   513,   516,   519,   519,   525,
     528,   531,   537,   540,   543,   549,   552,   555,   558,   558,
     559,   559,   566,   569,   572,   573,   580,   585,   586,   591,
     598,   606,   609,   612,   623,   627,   639,   642,   653,   664,
     675,   686,   702,   705,   723,   726,   741,   744,   759,   762,
     777,   780,   795,   798,   813,   816,   829,   844,   847,   860,
     873,   886,   904,   907,   915,   928,   931,   942,   958,   961,
     972,   983,  1000,  1015,  1018,  1024,  1032,  1040,  1048,  1056,
    1066,  1069,  1077,  1085,  1100,  1129,  1140,  1162,  1168,  1171,
    1181,  1192,  1195,  1198,  1201
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "GOTO", "ADD_ASSIGN", "SUB_ASSIGN",
  "MUL_ASSIGN", "DIV_ASSIGN", "LOGICAL_OR", "LOGICAL_AND", "EQ", "NE",
  "GE", "LE", "SL", "SR", "INC", "DEC", "IDENTIFIER", "DOUBLE_NUMBER",
  "INT_NUMBER", "STRING", "FOR", "DO", "WHILE", "CONTINUE", "BREAK", "IF",
  "ELSE", "SWITCH", "CASE", "RETURN", "STRUCT", "INT", "DOUBLE", "CHAR",
  "PTR", "CONST", "DEFAULT", "FLOAT", "STATIC", "UNSIGNED", "VOID", "'+'",
  "'-'", "'('", "')'", "'['", "']'", "'{'", "'}'", "'~'", "'%'", "'^'",
  "'&'", "'*'", "'='", "';'", "'<'", "'>'", "','", "'?'", "'/'", "':'",
  "'!'", "'|'", "'.'", "$accept", "cCode0", "cCode", "globalDeclaration",
  "declaration", "$@1", "type", "typeName", "structTypeName", "$@2",
  "structMemberDeclarations", "structMemberDeclaration", "structMembers",
  "initializations", "initialization", "variable", "pointerSpecifier",
  "variableName", "paramTypes", "paramTypeName", "variableWithNoName",
  "variableWithNoNameCore", "initialValue", "initialValues",
  "functionDeclaration", "$@3", "statementBlock", "localDeclarations",
  "statements", "statement", "$@4", "expressionStatement", "loopStatement",
  "$@5", "$@6", "branchStatement", "caseBlock", "caseStatements",
  "jumpStatement", "expression", "assignmentExpression",
  "tenaryConditionExpression", "logicalOrExpression",
  "logicalAndExpression", "bitwiseOrExpression",
  "bitwiseExclusiveOrExpression", "bitwiseAndExpression",
  "equalityComparisonExpression", "relationComparisonExpression",
  "shiftExpression", "arithmeticAddExpression", "arithmeticMulExpression",
  "castedExpression", "unaryExpression", "prefixUnaryExpression",
  "postfixUnaryExpression", "paramList", "atomicExpression", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,    43,    45,    40,    41,    91,    93,   123,
     125,   126,    37,    94,    38,    42,    61,    59,    60,    62,
      44,    63,    47,    58,    33,   124,    46
};
# endif

#define YYPACT_NINF (-227)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-78)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     236,    67,   129,   142,   142,  -227,  -227,  -227,  -227,   -35,
     491,   -26,    45,   122,   140,   167,   101,     0,  -227,  -227,
    -227,   194,  -227,   194,   133,  -227,   142,   533,  -227,   142,
    -227,   142,   222,   174,  -227,  -227,    -7,  -227,  -227,  -227,
    -227,   168,  -227,  -227,  -227,  -227,    29,  -227,  -227,    -2,
     221,   169,   211,   193,    44,    38,   269,   252,   237,    37,
    -227,    -8,  -227,   491,  -227,   209,    -8,    -8,   380,   255,
      87,  -227,  -227,   533,   533,  -227,   116,   266,  -227,    66,
    -227,  -227,  -227,    -8,   -31,    -8,    -8,  -227,  -227,  -227,
      -7,   280,    34,  -227,     7,    95,    88,   287,  -227,  -227,
    -227,   533,   533,   533,   533,   533,   533,   533,   533,   533,
     533,   533,   533,   533,   533,   533,   533,   533,   533,   533,
     533,   533,   533,   533,   533,   533,  -227,  -227,   431,   533,
     305,  -227,  -227,   380,   285,  -227,    39,   -24,    79,  -227,
     276,   620,  -227,  -227,   289,  -227,  -227,  -227,    -7,   482,
     168,   303,    88,   590,   322,  -227,  -227,    -7,   338,   389,
    -227,  -227,   221,  -227,   185,   169,   211,   193,    44,    38,
      38,   269,   269,   269,   269,   252,   252,   237,   237,  -227,
    -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,
      97,    32,   295,  -227,   533,   533,   299,  -227,   491,   491,
     297,   620,    -7,   566,  -227,  -227,  -227,   291,   482,  -227,
    -227,  -227,  -227,  -227,    82,   107,  -227,   300,  -227,  -227,
     440,  -227,  -227,   533,  -227,   533,  -227,  -227,   109,   118,
     491,   304,  -227,   321,   -18,  -227,   578,   234,  -227,  -227,
    -227,  -227,    76,   525,   318,  -227,    95,  -227,   157,  -227,
     620,  -227,    84,  -227,  -227,  -227,   491,   296,  -227,   491,
     491,   533,   311,   302,   319,  -227,    -7,  -227,   482,  -227,
     124,   335,  -227,   605,   348,  -227,  -227,  -227,  -227,  -227,
    -227,   323,   491,  -227,  -227,  -227,  -227,  -227,  -227,  -227,
     126,   336,   491,  -227,  -227,  -227,  -227
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,   160,   161,   162,   163,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    16,    20,
      18,     0,    19,     0,     0,    21,     0,     0,     8,     0,
      82,     0,     0,     0,     3,     5,     0,    13,    22,     6,
       7,     0,    75,    76,    79,    80,     0,   104,   106,   112,
     114,   116,   118,   120,   122,   124,   127,   132,   135,   138,
     143,   144,   150,     0,    81,     0,   145,   146,     0,     0,
       0,   101,   102,     0,     0,    99,     0,    25,    23,     0,
      14,    15,    17,   149,     0,   148,   147,     1,     4,    41,
       0,    37,     0,    31,    33,     0,    36,     0,    78,    84,
      83,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   151,   152,     0,     0,
       0,    95,   103,     0,     0,    90,     0,     0,     0,   100,
       0,     0,    25,   164,     0,    39,    12,     9,     0,     0,
       0,    38,    35,     0,     0,    66,    71,     0,     0,     0,
      73,   105,   115,   138,     0,   117,   119,   121,   123,   125,
     126,   131,   130,   128,   129,   133,   134,   136,   137,   141,
     142,   139,   140,   108,   109,   110,   111,   107,   155,   158,
       0,     0,   104,   156,     0,     0,     0,    88,     0,     0,
       0,     0,     0,     0,    26,    43,    32,    33,     0,    34,
      61,    65,    40,    44,    48,     0,    46,     0,    68,    72,
       0,    67,    74,     0,   154,     0,   157,   153,     0,     0,
       0,     0,    86,    92,     0,    94,     0,     0,    29,    24,
      27,    62,     0,     0,     0,    50,    51,    49,    52,    45,
       0,    42,     0,    69,   113,   159,     0,     0,    91,     0,
       0,     0,     0,     0,     0,    28,     0,    60,     0,    58,
       0,     0,    57,     0,     0,    47,    70,    85,    87,    89,
      93,     0,     0,    96,    11,    30,    63,    59,    54,    55,
       0,     0,     0,    98,    56,    53,    97
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -227,  -227,  -227,   352,   -76,  -227,     1,   121,  -227,  -227,
     190,  -190,  -227,  -227,   245,   -34,  -113,   -90,  -226,   144,
     160,  -227,  -185,  -227,  -227,  -227,   254,  -227,   259,   -10,
    -227,   -52,  -227,  -227,  -227,  -227,  -227,  -227,  -227,   -13,
     -97,  -216,  -227,   317,   324,   316,   320,   315,   189,   130,
      -5,   217,   182,   -40,  -227,   565,  -227,  -227
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    32,    33,    34,    35,   140,   202,    37,    38,   141,
     203,   204,   237,    92,    93,   144,    95,    96,   215,   216,
     247,   248,   209,   242,    39,   150,    98,   158,   159,    40,
      41,    42,    43,   231,   196,    44,   235,   263,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,   179,    59,    60,    61,   190,    62
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      69,    36,    94,    76,   161,   152,   102,   254,   126,   127,
      68,    89,   261,   240,    84,   143,   133,   270,    77,    70,
     262,   156,   199,   241,   183,   184,   185,   186,   187,   101,
      99,   189,   192,   226,    36,   146,   101,   128,    90,   129,
     197,   121,   122,   123,   124,   281,   240,   290,    91,    78,
     110,   111,   210,   131,   108,   109,   -64,   136,   130,   103,
     137,   138,   163,   149,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   180,   180,
     180,   194,   219,   286,   142,   198,   100,   160,   135,   101,
     164,   147,   101,   125,   148,    63,   112,   113,   157,   101,
      89,   246,    71,     3,     4,     5,     6,     7,     8,   175,
     176,   210,    63,    89,   207,    78,   191,     3,     4,     5,
       6,     7,     8,   207,    64,   200,   267,   243,   255,   244,
     246,    26,    27,   153,   276,   154,   268,    91,    29,   101,
      90,    64,    80,   224,    81,    26,    27,    65,   160,   222,
     151,    31,    29,   249,   214,   256,   152,   225,    75,   157,
       5,     6,     7,     8,   257,    31,    82,   250,   238,   101,
     287,   210,   294,   139,    -2,     1,   101,     2,   101,    72,
     245,   228,   229,   163,   250,    73,   250,    27,   232,   233,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,   273,    15,   274,    16,    17,    18,    19,    20,
     222,    21,    74,    22,    23,    24,    25,    97,    26,    27,
     258,   163,    87,   -77,    28,    29,    79,    18,    19,    20,
     104,    30,   285,    22,   105,    24,    25,     1,    31,     2,
     171,   172,   173,   174,   214,   101,   277,   107,   223,   279,
     280,   214,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,   106,    15,   132,    16,    17,    18,
      19,    20,   293,    21,   214,    22,    23,    24,    25,   134,
      26,    27,   296,   114,   115,   -77,    28,    29,     1,   118,
       2,   265,   119,    30,   266,   116,   117,   169,   170,   120,
      31,   181,   182,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   -10,    15,   145,    16,    17,
      18,    19,    20,   193,    21,   201,    22,    23,    24,    25,
     195,    26,    27,   177,   178,   205,   -77,   155,    29,     1,
     212,     2,   217,   227,    30,   230,   234,   149,   251,   260,
     259,    31,   283,   278,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,   272,    15,   291,    16,
      17,    18,    19,    20,   282,    21,   284,    22,    23,    24,
      25,   288,    26,    27,   295,    88,   292,   -77,   218,    29,
       1,   236,     2,   206,   275,    30,     3,     4,     5,     6,
       7,     8,    31,   271,   211,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,   220,    15,   162,
      16,   166,   168,     0,    26,    27,   167,     0,   165,     0,
       0,    29,     0,    26,    27,     0,     0,    30,   -77,   221,
      29,   252,     0,     2,    31,     0,    30,     3,     4,     5,
       6,     7,     8,    31,     0,     0,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,     0,    15,
       0,    16,     0,     0,     0,    26,    27,   188,     0,     0,
       0,     0,    29,     0,    26,    27,     0,     0,     0,   -77,
     253,    29,     1,     0,     2,    31,     0,    30,     3,     4,
       5,     6,     7,     8,    31,     0,     0,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,     0,
      15,     0,    16,     0,     0,     0,    26,    27,     0,     0,
       0,   208,     0,    29,     0,    26,    27,     0,     0,     0,
     -77,     0,    29,    89,     0,     0,    31,     0,    30,     3,
       4,     5,     6,     7,     8,    31,     0,    79,    18,    19,
      20,     0,    21,     0,    22,    23,    24,    25,    66,    67,
     243,   269,   244,     0,     0,     0,     0,    26,    27,     0,
      91,     0,     0,     0,    29,     0,     0,     0,     0,     0,
       0,    83,     0,     0,    85,     0,    86,    31,    79,    18,
      19,    20,     0,    21,     0,    22,    23,    24,    25,     0,
      79,    18,    19,    20,     0,    21,   239,    22,    23,    24,
      25,     0,    79,    18,    19,    20,     0,    21,   264,    22,
      23,    24,    25,     0,     0,     0,   213,    79,    18,    19,
      20,     0,    21,     0,    22,    23,    24,    25,     0,     0,
       0,   289,    79,    18,    19,    20,     0,    21,     0,    22,
      23,    24,    25
};

static const yytype_int16 yycheck[] =
{
      10,     0,    36,    16,   101,    95,     8,   223,    16,    17,
      45,    18,    30,   203,    27,    46,    68,   243,    18,    45,
      38,    97,    46,   208,   121,   122,   123,   124,   125,    60,
       1,   128,   129,     1,    33,     1,    60,    45,    45,    47,
       1,     4,     5,     6,     7,   261,   236,   273,    55,    49,
      12,    13,   149,    63,    10,    11,    49,    70,    66,    61,
      73,    74,   102,    56,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   133,   158,   268,    18,    46,    57,    97,     1,    60,
     103,    57,    60,    56,    60,    28,    58,    59,    97,    60,
      18,   214,    57,    16,    17,    18,    19,    20,    21,   114,
     115,   208,    28,    18,   148,    49,   129,    16,    17,    18,
      19,    20,    21,   157,    57,    46,    50,    45,   225,    47,
     243,    44,    45,    45,    50,    47,    60,    55,    51,    60,
      45,    57,    21,    46,    23,    44,    45,    18,   158,   159,
      55,    64,    51,    46,   153,    46,   246,    60,    57,   158,
      18,    19,    20,    21,    46,    64,    33,    60,   202,    60,
      46,   268,    46,    57,     0,     1,    60,     3,    60,    57,
     214,   194,   195,   223,    60,    45,    60,    45,   198,   199,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    45,    29,    47,    31,    32,    33,    34,    35,
     220,    37,    45,    39,    40,    41,    42,    49,    44,    45,
     230,   261,     0,    49,    50,    51,    32,    33,    34,    35,
       9,    57,   266,    39,    65,    41,    42,     1,    64,     3,
     110,   111,   112,   113,   243,    60,   256,    54,    63,   259,
     260,   250,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    53,    29,    57,    31,    32,    33,
      34,    35,   282,    37,   273,    39,    40,    41,    42,    24,
      44,    45,   292,    14,    15,    49,    50,    51,     1,    52,
       3,    57,    55,    57,    60,    43,    44,   108,   109,    62,
      64,   119,   120,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    49,    29,    37,    31,    32,
      33,    34,    35,    18,    37,    49,    39,    40,    41,    42,
      45,    44,    45,   116,   117,    46,    49,    50,    51,     1,
      37,     3,    20,    48,    57,    46,    49,    56,    48,    28,
      46,    64,    50,    57,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    48,    29,    20,    31,
      32,    33,    34,    35,    63,    37,    57,    39,    40,    41,
      42,    46,    44,    45,    48,    33,    63,    49,    50,    51,
       1,   201,     3,   148,   250,    57,    16,    17,    18,    19,
      20,    21,    64,   243,   150,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,   158,    29,   102,
      31,   105,   107,    -1,    44,    45,   106,    -1,   104,    -1,
      -1,    51,    -1,    44,    45,    -1,    -1,    57,    49,    50,
      51,     1,    -1,     3,    64,    -1,    57,    16,    17,    18,
      19,    20,    21,    64,    -1,    -1,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    -1,    29,
      -1,    31,    -1,    -1,    -1,    44,    45,    46,    -1,    -1,
      -1,    -1,    51,    -1,    44,    45,    -1,    -1,    -1,    49,
      50,    51,     1,    -1,     3,    64,    -1,    57,    16,    17,
      18,    19,    20,    21,    64,    -1,    -1,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    -1,
      29,    -1,    31,    -1,    -1,    -1,    44,    45,    -1,    -1,
      -1,    49,    -1,    51,    -1,    44,    45,    -1,    -1,    -1,
      49,    -1,    51,    18,    -1,    -1,    64,    -1,    57,    16,
      17,    18,    19,    20,    21,    64,    -1,    32,    33,    34,
      35,    -1,    37,    -1,    39,    40,    41,    42,     3,     4,
      45,    46,    47,    -1,    -1,    -1,    -1,    44,    45,    -1,
      55,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    -1,    -1,    29,    -1,    31,    64,    32,    33,
      34,    35,    -1,    37,    -1,    39,    40,    41,    42,    -1,
      32,    33,    34,    35,    -1,    37,    50,    39,    40,    41,
      42,    -1,    32,    33,    34,    35,    -1,    37,    50,    39,
      40,    41,    42,    -1,    -1,    -1,    46,    32,    33,    34,
      35,    -1,    37,    -1,    39,    40,    41,    42,    -1,    -1,
      -1,    46,    32,    33,    34,    35,    -1,    37,    -1,    39,
      40,    41,    42
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    29,    31,    32,    33,    34,
      35,    37,    39,    40,    41,    42,    44,    45,    50,    51,
      57,    64,    68,    69,    70,    71,    73,    74,    75,    91,
      96,    97,    98,    99,   102,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   120,
     121,   122,   124,    28,    57,    18,   122,   122,    45,    96,
      45,    57,    57,    45,    45,    57,   106,    18,    49,    32,
      74,    74,    33,   122,   106,   122,   122,     0,    70,    18,
      45,    55,    80,    81,    82,    83,    84,    49,    93,     1,
      57,    60,     8,    61,     9,    65,    53,    54,    10,    11,
      12,    13,    58,    59,    14,    15,    43,    44,    52,    55,
      62,     4,     5,     6,     7,    56,    16,    17,    45,    47,
      66,    96,    57,    98,    24,     1,   106,   106,   106,    57,
      72,    76,    18,    46,    82,    37,     1,    57,    60,    56,
      92,    55,    84,    45,    47,    50,    71,    73,    94,    95,
      96,   107,   110,   120,   106,   111,   112,   113,   114,   115,
     115,   116,   116,   116,   116,   117,   117,   118,   118,   119,
     120,   119,   119,   107,   107,   107,   107,   107,    46,   107,
     123,   106,   107,    18,    98,    45,   101,     1,    46,    46,
      46,    49,    73,    77,    78,    46,    81,    82,    49,    89,
     107,    93,    37,    46,    73,    85,    86,    20,    50,    71,
      95,    50,    96,    63,    46,    60,     1,    48,   106,   106,
      46,   100,    96,    96,    49,   103,    77,    79,    82,    50,
      78,    89,    90,    45,    47,    82,    83,    87,    88,    46,
      60,    48,     1,    50,   108,   107,    46,    46,    96,    46,
      28,    30,    38,   104,    50,    57,    60,    50,    60,    46,
      85,    87,    48,    45,    47,    86,    50,    96,    57,    96,
      96,   108,    63,    50,    57,    82,    89,    46,    46,    46,
      85,    20,    63,    96,    46,    48,    96
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    67,    68,    69,    69,    70,    70,    70,    70,    71,
      72,    71,    71,    73,    73,    73,    74,    74,    74,    74,
      74,    74,    74,    76,    75,    75,    77,    77,    78,    79,
      79,    80,    80,    81,    81,    82,    82,    83,    83,    83,
      83,    84,    84,    84,    84,    84,    85,    85,    86,    86,
      86,    87,    87,    88,    88,    88,    88,    88,    88,    88,
      89,    89,    90,    90,    92,    91,    93,    93,    93,    93,
      93,    94,    94,    95,    95,    96,    96,    97,    96,    96,
      96,    96,    98,    98,    98,    99,    99,    99,   100,    99,
     101,    99,   102,   102,   102,   102,   103,   104,   104,   105,
     105,   105,   105,   105,   106,   106,   107,   107,   107,   107,
     107,   107,   108,   108,   109,   109,   110,   110,   111,   111,
     112,   112,   113,   113,   114,   114,   114,   115,   115,   115,
     115,   115,   116,   116,   116,   117,   117,   117,   118,   118,
     118,   118,   119,   120,   120,   121,   121,   121,   121,   121,
     122,   122,   122,   122,   122,   122,   122,   122,   123,   123,
     124,   124,   124,   124,   124
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     3,
       0,     7,     3,     1,     2,     2,     1,     2,     1,     1,
       1,     1,     1,     0,     5,     2,     1,     2,     3,     1,
       3,     1,     3,     1,     3,     2,     1,     1,     2,     2,
       3,     1,     4,     3,     3,     4,     1,     3,     1,     2,
       2,     1,     1,     4,     3,     3,     4,     2,     2,     3,
       3,     1,     1,     3,     0,     4,     2,     3,     3,     4,
       5,     1,     2,     1,     2,     1,     1,     0,     2,     1,
       1,     2,     1,     2,     2,     7,     5,     7,     0,     7,
       0,     6,     5,     7,     5,     3,     3,     4,     3,     2,
       3,     2,     2,     3,     1,     3,     1,     3,     3,     3,
       3,     3,     1,     5,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     3,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     1,     1,     1,     2,     2,     2,     2,     2,
       1,     2,     2,     4,     4,     3,     3,     4,     1,     3,
       1,     1,     1,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 61 "cParser.y"
              {
            treeRoot = (yyvsp[0].nodePtr);
        }
#line 1681 "cParser.cpp"
    break;

  case 3:
#line 67 "cParser.y"
                          {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("cCode"), 1, (yyvsp[0].nodePtr));
        }
#line 1689 "cParser.cpp"
    break;

  case 4:
#line 70 "cParser.y"
                                {
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
    }
#line 1698 "cParser.cpp"
    break;

  case 5:
#line 80 "cParser.y"
                    { /* 全局的变量定义，兼定义结构体。 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("globalDeclaration"), 1, (yyvsp[0].nodePtr));
        }
#line 1706 "cParser.cpp"
    break;

  case 6:
#line 83 "cParser.y"
                            { /* 语法上，所有的函数都必须要定义在全局。 */ 
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("globalDeclaration"), 1, (yyvsp[0].nodePtr));
        }
#line 1714 "cParser.cpp"
    break;

  case 7:
#line 86 "cParser.y"
                  { /* 不允许在全局范围内出现不是定义的语句。 */
            yyerror("syntax error");
            std::cout<<"C-- only supports statements within a function.\n";
        }
#line 1723 "cParser.cpp"
    break;

  case 8:
#line 90 "cParser.y"
            {
            yyerror("syntax error");
            std::cout<<"a '}' without its '{'.\n";
        }
#line 1732 "cParser.cpp"
    break;

  case 9:
#line 98 "cParser.y"
                                 { /* 定义变量 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("declaration"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            for(int i = 0; i < (yyvsp[-1].nodePtr)->getChildrenNumber(); i++){
                Node *child = (yyvsp[-1].nodePtr)->getChildrenById(i);
                //child->setType($1->getType());
                child->setType((yyvsp[-2].nodePtr));
            }
            for(int i = 0;i < (yyvsp[-1].nodePtr)->getChildrenNumber(); i++){
                Node *child = (yyvsp[-1].nodePtr)->getChildrenById(i);
                if(child->isTerminal() && child->getTokenValue().compare({","})==0)continue;
                if(symbolTableStack->insert(new Attribute(child)) == false){// insert fault.
                    error_duplicatedVariable(child);
                }
            }
        }
#line 1752 "cParser.cpp"
    break;

  case 10:
#line 113 "cParser.y"
                          { /* 定义结构体 */
            /* 取得结构体名之后，即使为该结构体构建符号表 */
            (yyvsp[0].nodePtr)->setType(Node::TYPE_STRUCT);
            (yyvsp[0].nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyvsp[0].nodePtr)->setStructTypeName((yyvsp[0].nodePtr)->getTokenValue());
            (yyvsp[0].nodePtr)->setVariableName((yyvsp[0].nodePtr)->getTokenValue());
            symbolTableStack->insert(new Attribute((yyvsp[0].nodePtr)));
            symbolTableStack->push(new SymbolTable((yyvsp[0].nodePtr)->getStructTypeName()));
        }
#line 1766 "cParser.cpp"
    break;

  case 11:
#line 121 "cParser.y"
                                               {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("declaration"), 6, (yyvsp[-6].nodePtr), (yyvsp[-5].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            symbolTableStack->pop();
        }
#line 1775 "cParser.cpp"
    break;

  case 12:
#line 125 "cParser.y"
                                    {
            error_missingSemicolon();
        }
#line 1783 "cParser.cpp"
    break;

  case 13:
#line 131 "cParser.y"
                 {           /* int */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("type"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->copyFromChild();
        }
#line 1792 "cParser.cpp"
    break;

  case 14:
#line 135 "cParser.y"
                       {     /* const int，不实现这一条。 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("type"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 1800 "cParser.cpp"
    break;

  case 15:
#line 138 "cParser.y"
                        {    /* static int，不实现这一条。 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("type"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 1808 "cParser.cpp"
    break;

  case 16:
#line 144 "cParser.y"
            { 
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("typeName"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1819 "cParser.cpp"
    break;

  case 17:
#line 150 "cParser.y"
                     { /* 不实现这一条 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("typeName"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1830 "cParser.cpp"
    break;

  case 18:
#line 156 "cParser.y"
             { 
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("typeName"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_CHAR);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1841 "cParser.cpp"
    break;

  case 19:
#line 162 "cParser.y"
              { /* 不实现这一条 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("typeName"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_FLOAT);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1852 "cParser.cpp"
    break;

  case 20:
#line 168 "cParser.y"
               { 
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("typeName"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_DOUBLE);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1863 "cParser.cpp"
    break;

  case 21:
#line 174 "cParser.y"
             { 
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("typeName"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_VOID);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1874 "cParser.cpp"
    break;

  case 22:
#line 180 "cParser.y"
                       { 
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("typeName"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_STRUCT);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setStructTypeName((yyvsp[0].nodePtr)->getStructTypeName());
            (yyval.nodePtr)->setPosition((yyvsp[0].nodePtr));
        }
#line 1886 "cParser.cpp"
    break;

  case 23:
#line 192 "cParser.y"
                   {
            /* 为该匿名结构体维护符号表 */
            std::string name = nameCounter.getNumberedName("`Unamed_Structure");
            symbolTableStack->insert(new Attribute(name, Node::TYPE_STRUCT, Node::KIND_ATTRIBUTE, std::vector<Node::Type>(), std::vector<std::string>(), 
                                     std::vector<int>(), name, csLineCnt, csColumnCnt-1));
            symbolTableStack->push(new SymbolTable(name));
        }
#line 1898 "cParser.cpp"
    break;

  case 24:
#line 198 "cParser.y"
                                       {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("structTypeName"), 4, (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_STRUCT);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setStructTypeName(symbolTableStack->top()->getName());
            (yyval.nodePtr)->setPosition((yyvsp[-4].nodePtr));
            symbolTableStack->pop();
        }
#line 1911 "cParser.cpp"
    break;

  case 25:
#line 206 "cParser.y"
                          { /* 一个之前已经定义过的结构体名字。 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("structTypeName"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_STRUCT);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setStructTypeName((yyvsp[0].nodePtr)->getTokenValue()/*nameCounter.getNumberedName($2->getTokenValue())*/);
            (yyval.nodePtr)->setPosition((yyvsp[-1].nodePtr));
            if(symbolTableStack->lookUp((yyvsp[0].nodePtr)->getTokenValue())==0){
                error_structNotDeclared((yyvsp[0].nodePtr)->getTokenValue());
            }
        }
#line 1926 "cParser.cpp"
    break;

  case 26:
#line 220 "cParser.y"
                                {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("structMemberDeclarations"), 1, (yyvsp[0].nodePtr));
        }
#line 1934 "cParser.cpp"
    break;

  case 27:
#line 223 "cParser.y"
                                                         {
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 1943 "cParser.cpp"
    break;

  case 28:
#line 230 "cParser.y"
                               {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("structMemberDeclarations"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            for(int i=0;i<(yyvsp[-1].nodePtr)->getChildrenNumber();i++){
                (yyvsp[-1].nodePtr)->getChildrenById(i)->setType((yyvsp[-2].nodePtr));
            }
            for(int i=0;i<(yyvsp[-1].nodePtr)->getChildrenNumber();i++){
                if((yyvsp[-1].nodePtr)->getChildrenById(i)->isTerminal() && (yyvsp[-1].nodePtr)->getChildrenById(i)->getTokenValue().compare(",")==0) continue;
                if(symbolTableStack->insert(new Attribute((yyvsp[-1].nodePtr)->getChildrenById(i))) == false){
                    error_duplicatedVariable((yyvsp[-1].nodePtr)->getChildrenById(i));
                }
            }
        }
#line 1960 "cParser.cpp"
    break;

  case 29:
#line 245 "cParser.y"
                 {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("structMembers"), 1, (yyvsp[0].nodePtr));
        }
#line 1968 "cParser.cpp"
    break;

  case 30:
#line 248 "cParser.y"
                                   {
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[-1].nodePtr));
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 1978 "cParser.cpp"
    break;

  case 31:
#line 258 "cParser.y"
                       {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("initializations"), 1, (yyvsp[0].nodePtr));
        }
#line 1986 "cParser.cpp"
    break;

  case 32:
#line 261 "cParser.y"
                                           {
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[-1].nodePtr));
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 1996 "cParser.cpp"
    break;

  case 33:
#line 269 "cParser.y"
                 {                       /* int a; 没有初始值 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("initialization"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->copyFromChild();
        }
#line 2005 "cParser.cpp"
    break;

  case 34:
#line 273 "cParser.y"
                                  {   /* int a=10; 有初始值 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("initialization"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr)->copyFromChild();
        }
#line 2014 "cParser.cpp"
    break;

  case 35:
#line 280 "cParser.y"
                                      {  /* int *a; 指针变量，这里不打算实现。 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variable"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2022 "cParser.cpp"
    break;

  case 36:
#line 283 "cParser.y"
                     { /* 不是指针的变量 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variable"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->copyFromChild();
        }
#line 2031 "cParser.cpp"
    break;

  case 37:
#line 291 "cParser.y"
            { /* a simple pointer */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("pointerSpecifier"), 1, (yyvsp[0].nodePtr));
        }
#line 2039 "cParser.cpp"
    break;

  case 38:
#line 294 "cParser.y"
                             { /* a pointer to another pointer variable */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("pointerSpecifier"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2047 "cParser.cpp"
    break;

  case 39:
#line 297 "cParser.y"
                  { /* a pointer to a const variable */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("pointerSpecifier"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2055 "cParser.cpp"
    break;

  case 40:
#line 300 "cParser.y"
                                   { /* a pointer to another pointer which is a pointer to a const value */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("pointerSpecifier"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2063 "cParser.cpp"
    break;

  case 41:
#line 306 "cParser.y"
                   { /* 一个普通的变量 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableName"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setKind(Node::KIND_VARIABLE);
            (yyval.nodePtr)->setVariableName((yyvsp[0].nodePtr)->getTokenValue());
            (yyval.nodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 2074 "cParser.cpp"
    break;

  case 42:
#line 312 "cParser.y"
                                        {    /* 数组，可以是多维度的。其中 NUMBER 必须是整数。 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableName"), 4, (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            if(!(checkType((yyvsp[-1].nodePtr),Node::TYPE_INT) && checkKind((yyvsp[-1].nodePtr),Node::KIND_CONSTANT))){
                error_illegalArraySize((yyvsp[-1].nodePtr));
            }else{
                (yyval.nodePtr)->setKind(Node::KIND_VARIABLE);
                (yyval.nodePtr)->setVariableName((yyvsp[-3].nodePtr)->getVariableName());
                std::vector<int> sizes = (yyvsp[-3].nodePtr)->getArraySizes();
                int newSize;
                sscanf((yyvsp[-1].nodePtr)->getTokenValue().c_str(),"%d",&newSize);
                sizes.push_back(newSize);
                (yyval.nodePtr)->setArraySizes(sizes);
                (yyval.nodePtr)->setPosition((yyvsp[-3].nodePtr));
            }
        }
#line 2094 "cParser.cpp"
    break;

  case 43:
#line 327 "cParser.y"
                         {              /* 这一条弃之不用，太复杂了 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableName"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2102 "cParser.cpp"
    break;

  case 44:
#line 330 "cParser.y"
                             {           /* 函数定义 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableName"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setKind(Node::KIND_FUNCTION);
            (yyval.nodePtr)->setVariableName((yyvsp[-2].nodePtr)->getVariableName());
            (yyval.nodePtr)->setPosition((yyvsp[-2].nodePtr));
        }
#line 2113 "cParser.cpp"
    break;

  case 45:
#line 336 "cParser.y"
                                        {    /* 函数定义 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableName"), 4, (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr)->copyFrom((yyvsp[-3].nodePtr));
            (yyval.nodePtr)->setKind(Node::KIND_FUNCTION);
            std::vector<Node::Type> argList;
            std::vector<std::string> argListStructName;
            for(int i=0;i<(yyvsp[-1].nodePtr)->getChildrenNumber();i++){
                auto child = (yyvsp[-1].nodePtr)->getChildrenById(i);
                if(child->isTerminal())continue;
                argList.push_back(child->getType());
                if(child->getType()==Node::TYPE_STRUCT){
                    argListStructName.push_back(child->getStructTypeName());
                }else{
                    argListStructName.push_back({""});
                }
            }
            (yyval.nodePtr)->setArgList(argList);
            (yyval.nodePtr)->setArgListStructName(argListStructName);
        }
#line 2137 "cParser.cpp"
    break;

  case 46:
#line 358 "cParser.y"
                      {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("paramTypes"), 1, (yyvsp[0].nodePtr));
        }
#line 2145 "cParser.cpp"
    break;

  case 47:
#line 361 "cParser.y"
                                     {
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[-1].nodePtr));
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 2155 "cParser.cpp"
    break;

  case 48:
#line 369 "cParser.y"
             {   /* int (*f)(double,char); 不实现这一条，太复杂 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("paramTypeName"), 1, (yyvsp[0].nodePtr));
        }
#line 2163 "cParser.cpp"
    break;

  case 49:
#line 372 "cParser.y"
                                { /* 无名字的指针变量。不实现这一条，天复杂 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("paramTypeName"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2171 "cParser.cpp"
    break;

  case 50:
#line 375 "cParser.y"
                      {      /* 这一条是要正常实现的，定义函数用的 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("paramTypeName"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr)->copyFrom((yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType((yyvsp[-1].nodePtr));
        }
#line 2181 "cParser.cpp"
    break;

  case 51:
#line 384 "cParser.y"
                         {       /* 不实现指针 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoName"), 1, (yyvsp[0].nodePtr));
        }
#line 2189 "cParser.cpp"
    break;

  case 52:
#line 387 "cParser.y"
                               { 
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoName"), 1, (yyvsp[0].nodePtr));
        }
#line 2197 "cParser.cpp"
    break;

  case 53:
#line 394 "cParser.y"
                                                  {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 4, (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2205 "cParser.cpp"
    break;

  case 54:
#line 397 "cParser.y"
                                   {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2213 "cParser.cpp"
    break;

  case 55:
#line 400 "cParser.y"
                                       {  /* a function taking another function as param... */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2221 "cParser.cpp"
    break;

  case 56:
#line 403 "cParser.y"
                                                  { /* a function taking another function as param... */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 4, (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2229 "cParser.cpp"
    break;

  case 57:
#line 406 "cParser.y"
                {            /* because it has no name, it must stop some way. Below is some terminators */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2237 "cParser.cpp"
    break;

  case 58:
#line 409 "cParser.y"
                {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2245 "cParser.cpp"
    break;

  case 59:
#line 412 "cParser.y"
                           { /* a function taking another function as param... */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2253 "cParser.cpp"
    break;

  case 60:
#line 419 "cParser.y"
                              {          /* int a[10]={1}; 初始化列表 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("initialValue"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2261 "cParser.cpp"
    break;

  case 61:
#line 422 "cParser.y"
                             {          /* int a=5+6; int b=a=3; 普通的初始值 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("initialValue"), 1, (yyvsp[0].nodePtr));
    }
#line 2269 "cParser.cpp"
    break;

  case 62:
#line 429 "cParser.y"
                     {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("initialValues"), 1, (yyvsp[0].nodePtr));
        }
#line 2277 "cParser.cpp"
    break;

  case 63:
#line 432 "cParser.y"
                                       { /* int a[10]={1,2,3} */
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[-1].nodePtr));
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 2287 "cParser.cpp"
    break;

  case 64:
#line 441 "cParser.y"
                      { /* 在取得函数名字之后，及时建立该函数的符号表 */
            (yyvsp[0].nodePtr)->setType((yyvsp[-1].nodePtr)->getType());
            if((yyvsp[0].nodePtr)->isArray()){
                error_functionReturnsArray();
            }
            if(symbolTableStack->insert(new Attribute((yyvsp[0].nodePtr)))==false){
                error_duplicatedVariable((yyvsp[0].nodePtr));
                (yyvsp[0].nodePtr)->setVariableName(nameCounter.getNumberedName((yyvsp[0].nodePtr)->getVariableName()));
                while(symbolTableStack->insert(new Attribute((yyvsp[0].nodePtr)))==false){
                    (yyvsp[0].nodePtr)->setVariableName(nameCounter.getNumberedName((yyvsp[0].nodePtr)->getVariableName()));
                }
            }
            symbolTableStack->push(new SymbolTable((yyvsp[0].nodePtr)->getVariableName()));
            if((yyvsp[0].nodePtr)->getArgList().size()>0){
                for(int i=0;i<(yyvsp[0].nodePtr)->getChildrenById((yyvsp[0].nodePtr)->getChildrenNumber()-1)->getChildrenById(2)->getChildrenNumber();i++){
                    auto argument = (yyvsp[0].nodePtr)->getChildrenById((yyvsp[0].nodePtr)->getChildrenNumber()-1)->getChildrenById(2)->getChildrenById(i);
                    if(argument->isTerminal())continue;
                    /* 所有的参数都被当作局部变量来对待了。 */
                    argument->setKind(Node::KIND_VARIABLE);
                    if(symbolTableStack->insert(new Attribute(argument))==false){
                        error_duplicatedVariable(argument);
                    }
                }
            }
        }
#line 2317 "cParser.cpp"
    break;

  case 65:
#line 465 "cParser.y"
                         {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("functionDeclaration"), 3, (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            symbolTableStack->pop();
            /* parse 完一个函数之后，把这个函数的符号表出栈，维护变量的生命周期。 */
        }
#line 2327 "cParser.cpp"
    break;

  case 66:
#line 474 "cParser.y"
                { /* 可以 {} 这样而不必 {;} 这样 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("statementBlock"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2335 "cParser.cpp"
    break;

  case 67:
#line 477 "cParser.y"
                           {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("statementBlock"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2343 "cParser.cpp"
    break;

  case 68:
#line 480 "cParser.y"
                                  {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("statementBlock"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2351 "cParser.cpp"
    break;

  case 69:
#line 483 "cParser.y"
                                             { /* 如果要定义局部变量，必须要把所有的定义语句语句块的最前面。 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("statementBlock"), 4, (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2359 "cParser.cpp"
    break;

  case 70:
#line 486 "cParser.y"
                                                   {
            yyerror("Declaration after statements");
        }
#line 2367 "cParser.cpp"
    break;

  case 71:
#line 493 "cParser.y"
                    {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("localDeclarations"), 1, (yyvsp[0].nodePtr));
        }
#line 2375 "cParser.cpp"
    break;

  case 72:
#line 496 "cParser.y"
                                      {
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 2384 "cParser.cpp"
    break;

  case 73:
#line 503 "cParser.y"
                  {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("statements"), 1, (yyvsp[0].nodePtr));
        }
#line 2392 "cParser.cpp"
    break;

  case 74:
#line 506 "cParser.y"
                             {
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 2401 "cParser.cpp"
    break;

  case 75:
#line 513 "cParser.y"
                            { /* 表达式，也是最常见的语句 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("statement"), 1, (yyvsp[0].nodePtr));
        }
#line 2409 "cParser.cpp"
    break;

  case 76:
#line 516 "cParser.y"
                      { /* 循环 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("statement"), 1, (yyvsp[0].nodePtr));
        }
#line 2417 "cParser.cpp"
    break;

  case 77:
#line 519 "cParser.y"
        { symbolTableStack->push(new SymbolTable(nameCounter.getNumberedName("NestedBlock"))); }
#line 2423 "cParser.cpp"
    break;

  case 78:
#line 519 "cParser.y"
                                                                                                                { /* 语句块。 */
            /* 注：非函数体的语句块是管变量的生命周期的，所以这里要维护符号表。 */
            /* 不能把这个维护放在 statementBlock:'{'...'}' 这个产生式里面，因为这样的话函数体语句块会维护两次符号表。 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("statement"), 1, (yyvsp[0].nodePtr));
            symbolTableStack->pop();
        }
#line 2434 "cParser.cpp"
    break;

  case 79:
#line 525 "cParser.y"
                        {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("statement"), 1, (yyvsp[0].nodePtr));
        }
#line 2442 "cParser.cpp"
    break;

  case 80:
#line 528 "cParser.y"
                      {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("statement"), 1, (yyvsp[0].nodePtr));
        }
#line 2450 "cParser.cpp"
    break;

  case 81:
#line 531 "cParser.y"
                  {
        error_wrongStatement();
    }
#line 2458 "cParser.cpp"
    break;

  case 82:
#line 537 "cParser.y"
            { /* 注：空语句是一个 expressionStatement */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("expressionStatement"), 1, (yyvsp[0].nodePtr));
        }
#line 2466 "cParser.cpp"
    break;

  case 83:
#line 540 "cParser.y"
                       {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("expressionStatement"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2474 "cParser.cpp"
    break;

  case 84:
#line 543 "cParser.y"
                         {
            error_missingSemicolon();
        }
#line 2482 "cParser.cpp"
    break;

  case 85:
#line 549 "cParser.y"
                                                                                 { /* 不允许 for(int i;i<10;i++) 这样 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("loopStatement"), 7, (yyvsp[-6].nodePtr), (yyvsp[-5].nodePtr), (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2490 "cParser.cpp"
    break;

  case 86:
#line 552 "cParser.y"
                                           {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("loopStatement"), 5, (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2498 "cParser.cpp"
    break;

  case 87:
#line 555 "cParser.y"
                                                  {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("loopStatement"), 7, (yyvsp[-6].nodePtr), (yyvsp[-5].nodePtr), (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2506 "cParser.cpp"
    break;

  case 88:
#line 558 "cParser.y"
                                   { error_missingRightBrancket(); }
#line 2512 "cParser.cpp"
    break;

  case 90:
#line 559 "cParser.y"
                        { error_wrongExpression; }
#line 2518 "cParser.cpp"
    break;

  case 91:
#line 559 "cParser.y"
                                                                 { 

        }
#line 2526 "cParser.cpp"
    break;

  case 92:
#line 566 "cParser.y"
                                        {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("branchStatement"), 5, (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2534 "cParser.cpp"
    break;

  case 93:
#line 569 "cParser.y"
                                                       { /* （else悬挂问题）这一条和上一条不能颠倒。 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("branchStatement"), 7, (yyvsp[-6].nodePtr), (yyvsp[-5].nodePtr), (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2542 "cParser.cpp"
    break;

  case 95:
#line 573 "cParser.y"
                              {
            { error_elseWithNoIf(); }
        }
#line 2550 "cParser.cpp"
    break;

  case 99:
#line 591 "cParser.y"
                   { /* 函数返回，这里要检查返回类型 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("jumpStatement"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            /* TODO: check if the type of return value matches the function */
            if(symbolTableStack->lookUp(symbolTableStack->top()->getName())->type != Node::TYPE_VOID){
                error_returnValueTypeMismatch(symbolTableStack->lookUp(symbolTableStack->top()->getName()), symbolTableStack->lookUp(symbolTableStack->top()->getName())->type);
            }
        }
#line 2562 "cParser.cpp"
    break;

  case 100:
#line 598 "cParser.y"
                              { /* 函数返回，这里要检查返回类型 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("jumpStatement"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            /* 因为这个语句出现时，符号表栈顶附近必定是一个函数的符号表。这个时候只需要先查到该函数的符号表的名字，然后再在全局符号表中看这个名字的类型即可。 */
            /* 因为符号表名和函数名永远是一样的。（在我们的设计中） */
            if(!typeMatch(symbolTableStack->lookUp(symbolTableStack->top()->getName()), (yyvsp[-1].nodePtr))){
                error_returnValueTypeMismatch(symbolTableStack->lookUp(symbolTableStack->top()->getName()), (yyvsp[-1].nodePtr));
            }
        }
#line 2575 "cParser.cpp"
    break;

  case 101:
#line 606 "cParser.y"
                     { /* 循环控制 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("jumpStatement"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2583 "cParser.cpp"
    break;

  case 102:
#line 609 "cParser.y"
                  { /* 循环控制 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("jumpStatement"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2591 "cParser.cpp"
    break;

  case 103:
#line 612 "cParser.y"
                            { /* 太复杂了，不实现 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("jumpStatement"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2599 "cParser.cpp"
    break;

  case 104:
#line 623 "cParser.y"
                             {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("expression"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->copyFrom((yyvsp[0].nodePtr));
        }
#line 2608 "cParser.cpp"
    break;

  case 105:
#line 627 "cParser.y"
                                            {
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[-1].nodePtr));
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
            /* 一串逗号分隔的表达式的值，是最后一个表达式的值。 */
            (yyval.nodePtr)->copyFrom((yyval.nodePtr)->getChildrenById((yyval.nodePtr)->getChildrenNumber()-1));
        }
#line 2620 "cParser.cpp"
    break;

  case 106:
#line 639 "cParser.y"
                                  {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2628 "cParser.cpp"
    break;

  case 107:
#line 642 "cParser.y"
                                                 {
            (yyvsp[-1].nodePtr) = new AssignmentNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!(checkKind((yyvsp[-2].nodePtr), Node::KIND_VARIABLE)) || (yyvsp[-2].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
            if(!typeMatch((yyvsp[-2].nodePtr), (yyvsp[0].nodePtr))){
                error_typeMismatch((yyvsp[-2].nodePtr));
            }
        }
#line 2644 "cParser.cpp"
    break;

  case 108:
#line 653 "cParser.y"
                                                        {
            (yyvsp[-1].nodePtr) = new AssignmentNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!(checkKind((yyvsp[-2].nodePtr), Node::KIND_VARIABLE))){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
            if(!typeMatch((yyvsp[-2].nodePtr), (yyvsp[0].nodePtr))){
                error_typeMismatch((yyvsp[-2].nodePtr));
            }
        }
#line 2660 "cParser.cpp"
    break;

  case 109:
#line 664 "cParser.y"
                                                        {
            (yyvsp[-1].nodePtr) = new AssignmentNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!(checkKind((yyvsp[-2].nodePtr),Node::KIND_VARIABLE))){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
            if(!typeMatch((yyvsp[-2].nodePtr),(yyvsp[0].nodePtr))){
                error_typeMismatch((yyvsp[-2].nodePtr));
            }
        }
#line 2676 "cParser.cpp"
    break;

  case 110:
#line 675 "cParser.y"
                                                        {
            (yyvsp[-1].nodePtr) = new AssignmentNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!(checkKind((yyvsp[-2].nodePtr),Node::KIND_VARIABLE))){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
            if(!typeMatch((yyvsp[-2].nodePtr),(yyvsp[0].nodePtr))){
                error_typeMismatch((yyvsp[-2].nodePtr));
            }
        }
#line 2692 "cParser.cpp"
    break;

  case 111:
#line 686 "cParser.y"
                                                        {
            (yyvsp[-1].nodePtr) = new AssignmentNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!(checkKind((yyvsp[-2].nodePtr),Node::KIND_VARIABLE))){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
            if(!typeMatch((yyvsp[-2].nodePtr),(yyvsp[0].nodePtr))){
                error_typeMismatch((yyvsp[-2].nodePtr));
            }
        }
#line 2708 "cParser.cpp"
    break;

  case 112:
#line 702 "cParser.y"
                            {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2716 "cParser.cpp"
    break;

  case 113:
#line 705 "cParser.y"
                                                                         {/* Hint: right hand of ':' cannot be expression because no '=' should appear at the right hand of ':'. */
            (yyval.nodePtr) = new TenaryOperatorNode({"?:"}, 3, (yyvsp[-4].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr)->copyFromChild();
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_DOUBLE||(yyvsp[0].nodePtr)->getType()==Node::TYPE_DOUBLE)(yyval.nodePtr)->setType(Node::TYPE_DOUBLE);
            (yyval.nodePtr)->setKind(Node::KIND_CONSTANT);
            if(!(checkType((yyvsp[-4].nodePtr),Node::TYPE_INT))){
                error_expressionTypeError((yyvsp[-4].nodePtr),(yyval.nodePtr));
            }
            if((yyvsp[-4].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-4].nodePtr),(yyval.nodePtr));
            }
        }
#line 2734 "cParser.cpp"
    break;

  case 114:
#line 723 "cParser.y"
                             {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2742 "cParser.cpp"
    break;

  case 115:
#line 726 "cParser.y"
                                                            {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_CONSTANT);
            if(!(checkType((yyvsp[-2].nodePtr),Node::TYPE_INT)&&checkType((yyvsp[0].nodePtr),Node::TYPE_INT)) || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2757 "cParser.cpp"
    break;

  case 116:
#line 741 "cParser.y"
                            {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2765 "cParser.cpp"
    break;

  case 117:
#line 744 "cParser.y"
                                                             {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_CONSTANT);
            if(!(checkType((yyvsp[-2].nodePtr),Node::TYPE_INT)&&checkType((yyvsp[0].nodePtr),Node::TYPE_INT)) || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2780 "cParser.cpp"
    break;

  case 118:
#line 759 "cParser.y"
                                     {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2788 "cParser.cpp"
    break;

  case 119:
#line 762 "cParser.y"
                                                             {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_CONSTANT);
            if(!(checkType((yyvsp[-2].nodePtr),Node::TYPE_INT)&&checkType((yyvsp[0].nodePtr),Node::TYPE_INT)) || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2803 "cParser.cpp"
    break;

  case 120:
#line 777 "cParser.y"
                             {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2811 "cParser.cpp"
    break;

  case 121:
#line 780 "cParser.y"
                                                              {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_CONSTANT);
            if(!(checkType((yyvsp[-2].nodePtr),Node::TYPE_INT)&&checkType((yyvsp[0].nodePtr),Node::TYPE_INT)) || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2826 "cParser.cpp"
    break;

  case 122:
#line 795 "cParser.y"
                                     {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2834 "cParser.cpp"
    break;

  case 123:
#line 798 "cParser.y"
                                                              {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_CONSTANT);
            if(!(checkType((yyvsp[-2].nodePtr),Node::TYPE_INT)&&checkType((yyvsp[0].nodePtr),Node::TYPE_INT)) || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2849 "cParser.cpp"
    break;

  case 124:
#line 813 "cParser.y"
                                     {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2857 "cParser.cpp"
    break;

  case 125:
#line 816 "cParser.y"
                                                                     {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_CONSTANT);
            /*if(checkType($1,Node::TYPE_STRUCT)||checkType($1,Node::TYPE_VOID)||checkType($1,Node::TYPE_STRING)||checkType($3,Node::TYPE_STRUCT)||checkType($3,Node::TYPE_VOID)||checkType($3,Node::TYPE_STRING)){
                error_expressionTypeError($1,$2,$3);
            }*/
            if(!typeMatch((yyvsp[-2].nodePtr),(yyvsp[0].nodePtr)) || (yyvsp[-2].nodePtr)->getType()==Node::TYPE_VOID || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2875 "cParser.cpp"
    break;

  case 126:
#line 829 "cParser.y"
                                                                     {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_CONSTANT);
            if(!typeMatch((yyvsp[-2].nodePtr),(yyvsp[0].nodePtr)) || (yyvsp[-2].nodePtr)->getType()==Node::TYPE_VOID || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2890 "cParser.cpp"
    break;

  case 127:
#line 844 "cParser.y"
                        {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2898 "cParser.cpp"
    break;

  case 128:
#line 847 "cParser.y"
                                                         {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_CONSTANT);
            if(checkType((yyvsp[-2].nodePtr),Node::TYPE_STRUCT)||checkType((yyvsp[-2].nodePtr),Node::TYPE_VOID)||checkType((yyvsp[-2].nodePtr),Node::TYPE_STRING)||checkType((yyvsp[0].nodePtr),Node::TYPE_STRUCT)||checkType((yyvsp[0].nodePtr),Node::TYPE_VOID)||checkType((yyvsp[0].nodePtr),Node::TYPE_STRING)){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
            if((yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2916 "cParser.cpp"
    break;

  case 129:
#line 860 "cParser.y"
                                                         {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_CONSTANT);
            if(checkType((yyvsp[-2].nodePtr),Node::TYPE_STRUCT)||checkType((yyvsp[-2].nodePtr),Node::TYPE_VOID)||checkType((yyvsp[-2].nodePtr),Node::TYPE_STRING)||checkType((yyvsp[0].nodePtr),Node::TYPE_STRUCT)||checkType((yyvsp[0].nodePtr),Node::TYPE_VOID)||checkType((yyvsp[0].nodePtr),Node::TYPE_STRING)){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
            if((yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2934 "cParser.cpp"
    break;

  case 130:
#line 873 "cParser.y"
                                                        {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_CONSTANT);
            if(checkType((yyvsp[-2].nodePtr),Node::TYPE_STRUCT)||checkType((yyvsp[-2].nodePtr),Node::TYPE_VOID)||checkType((yyvsp[-2].nodePtr),Node::TYPE_STRING)||checkType((yyvsp[0].nodePtr),Node::TYPE_STRUCT)||checkType((yyvsp[0].nodePtr),Node::TYPE_VOID)||checkType((yyvsp[0].nodePtr),Node::TYPE_STRING)){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
            if((yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2952 "cParser.cpp"
    break;

  case 131:
#line 886 "cParser.y"
                                                        {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_CONSTANT);
            if(checkType((yyvsp[-2].nodePtr),Node::TYPE_STRUCT)||checkType((yyvsp[-2].nodePtr),Node::TYPE_VOID)||checkType((yyvsp[-2].nodePtr),Node::TYPE_STRING)||checkType((yyvsp[0].nodePtr),Node::TYPE_STRUCT)||checkType((yyvsp[0].nodePtr),Node::TYPE_VOID)||checkType((yyvsp[0].nodePtr),Node::TYPE_STRING)){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
            if((yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2970 "cParser.cpp"
    break;

  case 132:
#line 904 "cParser.y"
                                {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2978 "cParser.cpp"
    break;

  case 133:
#line 907 "cParser.y"
                                                   {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFrom((yyvsp[-2].nodePtr));
            if(!(checkType((yyvsp[-2].nodePtr),Node::TYPE_INT)&&checkType((yyvsp[0].nodePtr),Node::TYPE_INT)) || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2991 "cParser.cpp"
    break;

  case 134:
#line 915 "cParser.y"
                                                    {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFrom((yyvsp[-2].nodePtr));
            if(!(checkType((yyvsp[-2].nodePtr),Node::TYPE_INT)&&checkType((yyvsp[0].nodePtr),Node::TYPE_INT)) || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 3004 "cParser.cpp"
    break;

  case 135:
#line 928 "cParser.y"
                                {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3012 "cParser.cpp"
    break;

  case 136:
#line 931 "cParser.y"
                                                            {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFrom((yyvsp[0].nodePtr));
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_DOUBLE || (yyvsp[0].nodePtr)->getType()==Node::TYPE_DOUBLE){
                (yyval.nodePtr)->setType(Node::TYPE_DOUBLE);
            }
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_STRUCT || (yyvsp[0].nodePtr)->getType()==Node::TYPE_STRUCT || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 3028 "cParser.cpp"
    break;

  case 137:
#line 942 "cParser.y"
                                                            {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFrom((yyvsp[0].nodePtr));
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_DOUBLE || (yyvsp[0].nodePtr)->getType()==Node::TYPE_DOUBLE){
                (yyval.nodePtr)->setType(Node::TYPE_DOUBLE);
            }
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_STRUCT || (yyvsp[0].nodePtr)->getType()==Node::TYPE_STRUCT || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 3044 "cParser.cpp"
    break;

  case 138:
#line 958 "cParser.y"
                        {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3052 "cParser.cpp"
    break;

  case 139:
#line 961 "cParser.y"
                                                     {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFrom((yyvsp[0].nodePtr));
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_DOUBLE || (yyvsp[0].nodePtr)->getType()==Node::TYPE_DOUBLE){
                (yyval.nodePtr)->setType(Node::TYPE_DOUBLE);
            }
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_STRUCT || (yyvsp[0].nodePtr)->getType()==Node::TYPE_STRUCT || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 3068 "cParser.cpp"
    break;

  case 140:
#line 972 "cParser.y"
                                                     {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFrom((yyvsp[0].nodePtr));
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_DOUBLE || (yyvsp[0].nodePtr)->getType()==Node::TYPE_DOUBLE){
                (yyval.nodePtr)->setType(Node::TYPE_DOUBLE);
            }
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_STRUCT || (yyvsp[0].nodePtr)->getType()==Node::TYPE_STRUCT || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 3084 "cParser.cpp"
    break;

  case 141:
#line 983 "cParser.y"
                                                     {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFrom((yyvsp[0].nodePtr));
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_DOUBLE || (yyvsp[0].nodePtr)->getType()==Node::TYPE_DOUBLE){
                (yyval.nodePtr)->setType(Node::TYPE_DOUBLE);
            }
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_STRUCT || (yyvsp[0].nodePtr)->getType()==Node::TYPE_STRUCT || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 3100 "cParser.cpp"
    break;

  case 142:
#line 1000 "cParser.y"
                       {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3108 "cParser.cpp"
    break;

  case 143:
#line 1015 "cParser.y"
                              {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3116 "cParser.cpp"
    break;

  case 144:
#line 1018 "cParser.y"
                               {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3124 "cParser.cpp"
    break;

  case 145:
#line 1024 "cParser.y"
                                   {/* ++a, especially ++a[i] is ++(a[i]) but not (++a)[i] */
            (yyvsp[-1].nodePtr) = new UnaryOperatorNode(std::string("pre")+(yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkKind((yyvsp[0].nodePtr), Node::KIND_VARIABLE) || (yyvsp[0].nodePtr)->isArray() || (yyvsp[0].nodePtr)->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError((yyvsp[0].nodePtr),(yyvsp[-1].nodePtr));
            }
        }
#line 3137 "cParser.cpp"
    break;

  case 146:
#line 1032 "cParser.y"
                                   {/* --a, the same as ++a[i] */
            (yyvsp[-1].nodePtr) = new UnaryOperatorNode(std::string("pre")+(yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkKind((yyvsp[0].nodePtr), Node::KIND_VARIABLE) || (yyvsp[0].nodePtr)->isArray() || (yyvsp[0].nodePtr)->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError((yyvsp[0].nodePtr),(yyvsp[-1].nodePtr));
            }
        }
#line 3150 "cParser.cpp"
    break;

  case 147:
#line 1040 "cParser.y"
                                   {/* logical NOT */
            (yyvsp[-1].nodePtr) = new UnaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkType((yyvsp[0].nodePtr), Node::TYPE_INT)){
                error_expressionTypeError((yyvsp[0].nodePtr),(yyvsp[-1].nodePtr));
            }
        }
#line 3163 "cParser.cpp"
    break;

  case 148:
#line 1048 "cParser.y"
                                   {/* bitwise NOT */
            (yyvsp[-1].nodePtr) = new UnaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkType((yyvsp[0].nodePtr), Node::TYPE_INT)){
                error_expressionTypeError((yyvsp[0].nodePtr),(yyvsp[-1].nodePtr));
            }
        }
#line 3176 "cParser.cpp"
    break;

  case 149:
#line 1056 "cParser.y"
                                   {/* negative */
            (yyvsp[-1].nodePtr) = new UnaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            if(checkType((yyvsp[0].nodePtr), Node::TYPE_STRUCT)){
                error_expressionTypeError((yyvsp[0].nodePtr),(yyvsp[-1].nodePtr));
            }
        }
#line 3188 "cParser.cpp"
    break;

  case 150:
#line 1066 "cParser.y"
                         {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3196 "cParser.cpp"
    break;

  case 151:
#line 1069 "cParser.y"
                                   {/* a++, espetially a[i]++ is allowed, (a[i])++ is not necessary */
            (yyvsp[0].nodePtr) = new UnaryOperatorNode(std::string("post")+(yyvsp[0].nodePtr)->getName(), 1, (yyvsp[-1].nodePtr));
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkKind((yyvsp[-1].nodePtr), Node::KIND_VARIABLE) || (yyvsp[-1].nodePtr)->isArray() || (yyvsp[-1].nodePtr)->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError((yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 3209 "cParser.cpp"
    break;

  case 152:
#line 1077 "cParser.y"
                                   {/* a-- */
            (yyvsp[0].nodePtr) = new UnaryOperatorNode(std::string("post")+(yyvsp[0].nodePtr)->getName(), 1, (yyvsp[-1].nodePtr));
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkKind((yyvsp[-1].nodePtr), Node::KIND_VARIABLE) || (yyvsp[-1].nodePtr)->isArray() || (yyvsp[-1].nodePtr)->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError((yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 3222 "cParser.cpp"
    break;

  case 153:
#line 1085 "cParser.y"
                                                            {/* array a[10], corresponding to prefix ++ */
            (yyval.nodePtr) = new BinaryOperatorNode({"[]"}, 2, (yyvsp[-3].nodePtr), (yyvsp[-1].nodePtr));
            (yyval.nodePtr)->copyFromChild();
            if(!(yyvsp[-3].nodePtr)->isArray()){
                error_notArray((yyvsp[-3].nodePtr));
            }else {
                if(!checkType((yyvsp[-1].nodePtr), Node::TYPE_INT)){
                    error_expressionTypeError((yyvsp[-1].nodePtr),(yyval.nodePtr));
                }
                /* 减少一个维度 */
                auto arraySizes = (yyval.nodePtr)->getArraySizes();
                arraySizes.erase(arraySizes.begin(),arraySizes.begin()+1);
                (yyval.nodePtr)->setArraySizes(arraySizes);
            }
        }
#line 3242 "cParser.cpp"
    break;

  case 154:
#line 1100 "cParser.y"
                                                 {/* function, f()[i], f[i](), f[i]()[j] are all allowed，但我们不=实现它。 */
            (yyval.nodePtr) = new FunctionCallNode({"()"}, 2, (yyvsp[-3].nodePtr), (yyvsp[-1].nodePtr));
            (yyval.nodePtr)->copyFromChild();
            if(!(checkKind((yyvsp[-3].nodePtr), Node::KIND_FUNCTION))){
                error_expressionTypeError((yyvsp[-3].nodePtr),(yyvsp[-2].nodePtr));
            }else{
                std::vector<Node::Type> argList;
                std::vector<std::string> argListStructName;
                for(int i=0; i<(yyvsp[-1].nodePtr)->getChildrenNumber(); i++){
                    auto child = (yyvsp[-1].nodePtr)->getChildrenById(i);
                    if(child->isTerminal() && child->getTokenValue().compare(",")==0)continue;
                    argList.push_back(child->getType());
                    if(child->getType()==Node::TYPE_STRUCT){
                        argListStructName.push_back(child->getStructTypeName());
                    }else{
                        argListStructName.push_back({""});
                    }
                    (dynamic_cast<FunctionCallNode*>((yyval.nodePtr)))->addArgument(child);
                }
                if(argList.size()!=(yyvsp[-3].nodePtr)->getArgList().size()){
                    //std::cout<<"~";
                    error_argumentNumberNotMatch((yyvsp[-3].nodePtr),argList.size());
                }else{
                    if(!typeMatch(argList,(yyvsp[-3].nodePtr),argListStructName)){
                        error_argumentTypeNotMatch(argList,(yyvsp[-3].nodePtr),argListStructName);
                    }
                }
            }
        }
#line 3276 "cParser.cpp"
    break;

  case 155:
#line 1129 "cParser.y"
                                                 {/* function with no params. */
            (yyval.nodePtr) = new FunctionCallNode({"()"}, 1, (yyvsp[-2].nodePtr));
            (yyval.nodePtr)->copyFromChild();
            if(!(checkKind((yyvsp[-2].nodePtr), Node::KIND_FUNCTION))){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyval.nodePtr));
            }else {
                if((yyvsp[-2].nodePtr)->getArgList().size()!=0){
                    error_argumentNumberNotMatch((yyvsp[-2].nodePtr),0);
                }
            }
        }
#line 3292 "cParser.cpp"
    break;

  case 156:
#line 1140 "cParser.y"
                                                 {/* struct's member (a.val) */
            Node *t = (yyvsp[-1].nodePtr);
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyvsp[-1].nodePtr)->setPosition(t);
            if(checkKind((yyvsp[-2].nodePtr), Node::KIND_ATTRIBUTE) || !(checkType((yyvsp[-2].nodePtr), Node::TYPE_STRUCT)) || (yyvsp[-2].nodePtr)->isArray())
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr));
            else {
                auto symbolTable = SymbolTable::getSymbolTableByName((yyvsp[-2].nodePtr)->getStructTypeName());
            
                if(symbolTable->lookUp((yyvsp[0].nodePtr)->getTokenValue()) == NULL)
                    error_variableNotDeclaredInStruct((yyvsp[-2].nodePtr),(yyvsp[0].nodePtr));
                
                (yyval.nodePtr)->copyFrom(symbolTable->lookUp((yyvsp[0].nodePtr)->getTokenValue()));
            }
        }
#line 3313 "cParser.cpp"
    break;

  case 157:
#line 1162 "cParser.y"
                                                     {
            error_missingRightBrancket2();
        }
#line 3321 "cParser.cpp"
    break;

  case 158:
#line 1168 "cParser.y"
                             {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("paramList"), 1, (yyvsp[0].nodePtr));
        }
#line 3329 "cParser.cpp"
    break;

  case 159:
#line 1171 "cParser.y"
                                           {/* 这里面不能填 expression，因为 expression 也是用逗号隔开的一串表达式 */
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[-1].nodePtr));
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 3339 "cParser.cpp"
    break;

  case 160:
#line 1181 "cParser.y"
                   {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
            if(!symbolTableStack->lookUp((yyvsp[0].nodePtr)->getTokenValue())){
                error_variableNotDeclared((yyvsp[0].nodePtr)->getTokenValue());
                (yyval.nodePtr)->setKind(Node::KIND_VARIABLE);
                (yyval.nodePtr)->setType(Node::TYPE_INT);
            }else{
                (yyval.nodePtr)->setAttribute(symbolTableStack->lookUp((yyvsp[0].nodePtr)->getTokenValue()));
                (yyval.nodePtr)->setPosition(csLineCnt, csColumnCnt);
            }
        }
#line 3355 "cParser.cpp"
    break;

  case 161:
#line 1192 "cParser.y"
                      {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3363 "cParser.cpp"
    break;

  case 162:
#line 1195 "cParser.y"
                   {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3371 "cParser.cpp"
    break;

  case 163:
#line 1198 "cParser.y"
               { /* 这个就不实现了吧 */
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3379 "cParser.cpp"
    break;

  case 164:
#line 1201 "cParser.y"
                           {
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
        }
#line 3387 "cParser.cpp"
    break;


#line 3391 "cParser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1207 "cParser.y"

int yyerror(std::string s){
    noError = false;
    printf("syntax error at line %d, column %d.\n", csLineCnt, csColumnCnt);
}
static void error_missingSemicolon(){
    std::cout<<"[ERROR] ";
    printf("Missing \';\' at line %d, after column %d\n", csLineCnt, csColumnCnt-(int)strlen(yytext));
}
static void error_wrongStatement(){
    std::cout<<"[ERROR] ";
    printf("a statement near line %d is illeagal. ", csLineCnt);
    printf("maybe you\'re putting a declaration after a statement.\n");//'
}
static void error_wrongExpression(){
    std::cout<<"[ERROR] ";
    printf("an expression near line %d is illeagal.\n", csLineCnt);
}
static void error_missingRightBrancket(){
    std::cout<<"[ERROR] ";
    printf("expect \')\' at line %d, after column %d .\n", csLineCnt, csColumnCnt-(int)strlen(yytext));
}
static void error_missingRightBrancket2(){
    std::cout<<"[ERROR] ";
    printf("expect \']\' at line %d, after column %d .\n", csLineCnt, csColumnCnt-(int)strlen(yytext));
}
static void error_elseWithNoIf(){
    std::cout<<"[ERROR] ";
    printf("expect \"if\" for the \"else\", at line %d, near column %d .\n", csLineCnt, csColumnCnt-(int)strlen(yytext));
}
static void error_duplicatedVariable(Node *c){
    std::cout<<"[ERROR] ";
    std::cout<<"variable \""<<c->getVariableName()<<"\" at line "<<c->getLineNumber()<<" near column "<<c->getColumnNumber()<<""<<" has been declared before.\n";
    std::cout<<" Hint: first declaraed at line "<<symbolTableStack->lookUp(c->getVariableName())->lineNumber<<", near column "<<symbolTableStack->lookUp(c->getVariableName())->columnNumber<<std::endl;
}
static void error_variableNotDeclared(std::string name){
    std::cout<<"[ERROR] ";
    std::cout<<"variable \""<<name<<"\" was not declared.\n";
    std::cout<<" Hint: first used at line "<<csLineCnt<<", near column "<<csColumnCnt<<std::endl;
}
static void error_structNotDeclared(std::string name){
    std::cout<<"[ERROR] ";
    std::cout<<"struct type name \""<<name<<"\" was not declared.\n";
    std::cout<<" Hint: first used at line "<<csLineCnt<<", near column "<<csColumnCnt<<std::endl;
}
static void error_illegalArraySize(Node* c){
    std::cout<<"[ERROR] ";
    std::cout<<"Size of array at line "<<c->getLineNumber()<<" near column "<<c->getColumnNumber()<<" must be a integer and must be a constant.\n";
}
static void error_expressionTypeError(Node *exp1, Node *op, Node *exp2){
    std::cout<<"[ERROR] ";
    std::cout<<"Type error at line "<<op->getLineNumber()<<" near column "<<op->getColumnNumber()<<":\n";
    std::cout<<" Type "<<exp1->getTypeString()<<" and type "<<exp2->getTypeString()<<" are not match for the operator \""<<op->getTokenValue()<<"\"\n";
}
static void error_expressionTypeError(Node *exp1, Node *op){
    std::cout<<"[ERROR] ";
    std::cout<<"Type error at line "<<op->getLineNumber()<<" near column "<<op->getColumnNumber()<<":\n";
    std::cout<<" Type "<<exp1->getTypeString()<<" is not supported for the operator \""<<op->getTokenValue()<<"\"\n";
}
static void error_typeMismatch(Node *c){
    std::cout<<"[ERROR] ";
    std::cout<<"Type mismatch at line "<<c->getLineNumber()<<" near column "<<c->getColumnNumber()<<"\n";
    std::cout<<" Hint: are you putting an array at the left hand of \'=\', or using \'=\' to connect two mismatched type?\n";
}
static void error_variableNotDeclaredInStruct(Node *v, Node *m){
    std::cout<<"[ERROR] variable \""<<v->getVariableName()<<"\" dose not has member \""<<m->getTokenValue()<<"\"\n";
    auto attribute = symbolTableStack->lookUp(v->getVariableName());
    if(attribute){
        std::cout<<" Hint: you declared this variable at line "<<attribute->lineNumber<<" near column "<<attribute->columnNumber<<std::endl;
    }
}
static void error_argumentNumberNotMatch(Node *f,int an){
    std::cout<<"[ERROR] function's argument number not match at line "<<f->getLineNumber()<<" near column "<<f->getColumnNumber()<<"\n";//'
    std::cout<<" Hint: function \""<<f->getVariableName()<<"\" needs "<<f->getArgList().size()<<" arguments but you gave "<<an<<".\n";
}
static void error_notArray(Node *c){
    std::cout<<"[ERROR] \""<<c->getVariableName()<<"\" at line "<<c->getLineNumber()<<" near column "<<c->getColumnNumber()<<" is not an array.\n";
    std::cout<<" Hint: are you using too many \"[]\"\'s to access an array?\n";//'
}
static void error_returnValueTypeMismatch(Attribute* need, Node::Type give){
    std::cout<<"[ERROR] return value type mismatch at line "<<csLineCnt<<std::endl;
    std::cout<<" Hint: the function returns "<<type_to_string(need)<<" but you gave nothing\n"; 
}
static void error_returnValueTypeMismatch(Attribute* need, Node* give){
    std::cout<<"[ERROR] return value type mismatch at line "<<csLineCnt<<std::endl;
    std::cout<<" Hint: the function returns "<<type_to_string(need)<<" but you gave "<<give->getTypeString()<<std::endl;
}
static void error_functionReturnsArray(){
    std::cout<<"[ERROR] at line "<<csLineCnt<<": function cannot return an array\n";
}
static void error_argumentTypeNotMatch(std::vector<Node::Type>& userGave,Node *function,std::vector<std::string>& structTypeName){
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
static void eatToNewLine(){ /* 该函数已弃置不用 */
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

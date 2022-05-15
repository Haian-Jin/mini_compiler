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
#line 36 "cParser.y"

    shared_ptr<Node> nodePtr;
    IdentifierNodeList* identifierNodeListPtr;
    IdentifierNode* identifierNodePtr;
    VarDeclarationList* varDeclarationListPtr;
    StatementNodesBlock* statementNodesBlockPtr;
    GlobalDeclaraionNode* globalDeclaraionNodePtr;

#line 212 "cParser.cpp"

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
#define YYFINAL  89
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   616

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  159
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  289

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
       0,    79,    79,    85,    88,    98,   101,   104,   108,   116,
     121,   121,   133,   139,   140,   141,   145,   149,   150,   154,
     158,   162,   166,   178,   178,   192,   206,   209,   216,   231,
     234,   244,   248,   255,   258,   265,   268,   275,   278,   281,
     284,   290,   293,   308,   311,   317,   323,   327,   334,   337,
     340,   348,   351,   358,   361,   364,   367,   370,   373,   376,
     383,   386,   393,   396,   405,   412,   416,   446,   449,   456,
     459,   462,   465,   465,   471,   474,   477,   483,   486,   489,
     495,   498,   501,   504,   504,   505,   505,   512,   515,   518,
     519,   526,   531,   532,   537,   544,   552,   555,   558,   569,
     573,   585,   588,   599,   610,   621,   632,   648,   651,   669,
     672,   687,   690,   705,   708,   723,   726,   741,   744,   759,
     762,   775,   790,   793,   806,   819,   832,   850,   853,   861,
     874,   877,   888,   904,   907,   918,   929,   946,   961,   964,
     970,   978,   986,   994,  1002,  1012,  1015,  1023,  1031,  1046,
    1075,  1086,  1108,  1114,  1117,  1127,  1138,  1141,  1144,  1147
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
  "functionDeclaration", "statementBlock", "statements", "statement",
  "$@3", "expressionStatement", "loopStatement", "$@4", "$@5",
  "branchStatement", "caseBlock", "caseStatements", "jumpStatement",
  "expression", "assignmentExpression", "tenaryConditionExpression",
  "logicalOrExpression", "logicalAndExpression", "bitwiseOrExpression",
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

#define YYPACT_NINF (-192)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-73)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     310,   108,    -5,   192,   192,  -192,  -192,  -192,  -192,   -21,
     463,   -15,    33,    46,    50,    54,    96,    90,  -192,  -192,
    -192,   574,  -192,   574,   104,  -192,   192,   513,  -192,   192,
    -192,   192,   142,   259,  -192,  -192,    89,  -192,  -192,  -192,
    -192,   103,  -192,  -192,  -192,  -192,     7,  -192,  -192,    10,
     153,   167,   115,   125,   146,    62,   194,   173,   250,    16,
    -192,    40,  -192,   463,  -192,   184,    40,    40,   110,  -192,
      89,   228,    60,  -192,  -192,   513,   513,  -192,   -45,   205,
    -192,   117,  -192,  -192,  -192,    40,   -29,    40,    40,  -192,
    -192,  -192,    89,   224,     8,  -192,    44,   114,   130,   361,
    -192,  -192,  -192,   513,   513,   513,   513,   513,   513,   513,
     513,   513,   513,   513,   513,   513,   513,   513,   513,   513,
     513,   513,   513,   513,   513,   513,   513,   513,  -192,  -192,
     174,   513,   245,  -192,  -192,   110,   209,   222,  -192,     9,
      37,    38,  -192,   238,   563,  -192,  -192,   227,  -192,  -192,
    -192,    89,   505,  -192,   252,   130,   533,   275,  -192,   412,
    -192,  -192,   153,  -192,   254,   167,   115,   125,   146,    62,
      62,   194,   194,   194,   194,   173,   173,   250,   250,  -192,
    -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,
      42,     6,   249,  -192,   513,   513,   278,  -192,   463,   463,
     276,   563,    89,   216,  -192,  -192,  -192,   505,  -192,  -192,
    -192,  -192,    78,   126,  -192,   290,  -192,  -192,   513,  -192,
     513,  -192,  -192,   137,   139,   463,   294,  -192,   318,   -19,
    -192,   503,   258,  -192,  -192,  -192,  -192,    41,   189,   300,
    -192,   114,  -192,   151,  -192,   563,  -192,  -192,  -192,   463,
     296,  -192,   463,   463,   513,   293,   307,   301,  -192,    89,
    -192,   505,  -192,   141,   317,  -192,   548,   345,  -192,  -192,
    -192,  -192,  -192,   303,   463,  -192,  -192,  -192,  -192,  -192,
    -192,  -192,   154,   320,   463,  -192,  -192,  -192,  -192
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,   155,   156,   157,   158,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    16,    20,
      18,     0,    19,     0,     0,    21,     0,     0,     8,     0,
      77,     0,     0,     0,     3,     5,     0,    13,    22,     6,
       7,     0,    70,    71,    74,    75,     0,    99,   101,   107,
     109,   111,   113,   115,   117,   119,   122,   127,   130,   133,
     138,   139,   145,     0,    76,     0,   140,   141,     0,    69,
       0,     0,     0,    96,    97,     0,     0,    94,     0,    25,
      23,     0,    14,    15,    17,   144,     0,   143,   142,     1,
       4,    41,     0,    37,     0,    31,    33,     0,    36,     0,
      73,    79,    78,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   146,   147,
       0,     0,     0,    90,    98,     0,    33,     0,    85,     0,
       0,     0,    95,     0,     0,    25,   159,     0,    39,    12,
       9,     0,     0,    64,    38,    35,     0,     0,    65,     0,
      67,   100,   110,   133,     0,   112,   114,   116,   118,   120,
     121,   126,   125,   123,   124,   128,   129,   131,   132,   136,
     137,   134,   135,   103,   104,   105,   106,   102,   150,   153,
       0,     0,    99,   151,     0,     0,     0,    83,     0,     0,
       0,     0,     0,     0,    26,    43,    32,     0,    34,    61,
      40,    44,    48,     0,    46,     0,    66,    68,     0,   149,
       0,   152,   148,     0,     0,     0,     0,    81,    87,     0,
      89,     0,     0,    29,    24,    27,    62,     0,     0,     0,
      50,    51,    49,    52,    45,     0,    42,   108,   154,     0,
       0,    86,     0,     0,     0,     0,     0,     0,    28,     0,
      60,     0,    58,     0,     0,    57,     0,     0,    47,    80,
      82,    84,    88,     0,     0,    91,    11,    30,    63,    59,
      54,    55,     0,     0,     0,    93,    56,    53,    92
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -192,  -192,  -192,   336,    86,  -192,     2,   181,  -192,  -192,
     169,  -121,  -192,  -192,   220,   -32,   -74,   -96,   -95,   127,
     138,  -192,  -191,  -192,  -192,   277,  -192,   -10,  -192,   -62,
    -192,  -192,  -192,  -192,  -192,  -192,  -192,   -13,   -98,  -160,
    -192,   271,   283,   284,   289,   295,   135,   157,   190,   201,
     200,   -70,  -192,   147,  -192,  -192
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    32,    33,    34,    69,   143,    70,    37,    38,   144,
     203,   204,   232,    94,    95,   136,    97,    98,   213,   214,
     242,   243,   208,   237,    39,   100,   159,    40,    41,    42,
      43,   226,   196,    44,   230,   256,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
     179,    59,    60,    61,   190,    62
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      71,   155,    36,    78,    96,   161,   135,   221,   101,   149,
     197,   254,   142,    65,    86,   103,   236,   146,   104,   255,
     123,   124,   125,   126,    68,   183,   184,   185,   186,   187,
      72,   103,   189,   192,   163,    36,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   163,   163,
     180,   180,   180,   133,   209,   198,   128,   129,   247,   139,
     147,   138,   140,   141,   102,   150,   103,   103,   151,   103,
     278,   105,   127,   194,   112,   113,     3,     4,     5,     6,
       7,     8,   235,   199,   200,   130,    35,   131,   219,   160,
      73,   260,   164,    99,   273,    75,    91,   103,   103,    76,
     152,   261,   220,    74,    26,    27,   132,    91,    79,   209,
     235,    29,     3,     4,     5,     6,     7,     8,   191,    35,
     114,   115,   248,   238,    31,   239,     3,     4,     5,     6,
       7,     8,    91,    93,    92,   145,    63,    84,   241,    80,
      26,    27,    89,   263,    93,   155,   202,    29,   163,   217,
      66,    67,    99,    77,    26,    27,   110,   111,   212,    92,
      31,    29,   106,   209,   241,    64,    80,    30,   108,   154,
     233,   282,   244,    85,    31,   156,    87,   157,    88,   109,
     240,   223,   224,   249,   163,   250,   245,   279,   227,   228,
       3,     4,     5,     6,     7,     8,   266,   103,   267,   103,
     286,   245,    82,   202,    83,   202,   147,    91,   116,   117,
       5,     6,     7,     8,   245,   251,   118,   119,    26,    27,
     188,    81,    18,    19,    20,    29,    21,   277,    22,    23,
      24,    25,   107,   202,   238,   262,   239,    27,    31,   269,
     212,   134,   271,   272,    93,   169,   170,   212,    81,    18,
      19,    20,   137,    21,   -10,    22,    23,    24,    25,    -2,
       1,   148,     2,   193,   285,   152,   234,   195,   212,   171,
     172,   173,   174,   205,   288,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,   201,    15,   210,
      16,    17,    18,    19,    20,   215,    21,   222,    22,    23,
      24,    25,   120,    26,    27,   121,   175,   176,   -72,    28,
      29,     1,   122,     2,   103,   258,    30,   218,   259,   177,
     178,   181,   182,    31,   225,   229,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,   246,    15,
     252,    16,    17,    18,    19,    20,   253,    21,   265,    22,
      23,    24,    25,   270,    26,    27,   274,   275,   276,   -72,
      28,    29,     1,   280,     2,   283,   284,    30,   287,    90,
     231,   206,   268,   153,    31,   162,   264,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,   165,
      15,   166,    16,    17,    18,    19,    20,   167,    21,     0,
      22,    23,    24,    25,   168,    26,    27,     0,     0,     0,
     -72,   158,    29,     1,     0,     2,     0,     0,    30,     0,
       0,     0,     0,     0,     0,    31,     0,     0,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
       0,    15,     0,    16,    17,    18,    19,    20,     0,    21,
       0,    22,    23,    24,    25,     0,    26,    27,     0,     0,
       0,   -72,   216,    29,     1,     0,     2,     0,     0,    30,
       0,     0,     0,     0,     0,     0,    31,     0,     0,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,     0,    15,     0,    16,    17,    18,    19,    20,     0,
      21,     0,    22,    23,    24,    25,     0,    26,    27,     0,
       0,     0,   -72,     0,    29,     0,     0,     0,     0,     0,
      30,     3,     4,     5,     6,     7,     8,    31,     0,     3,
       4,     5,     6,     7,     8,    81,    18,    19,    20,     0,
      21,     0,    22,    23,    24,    25,     0,     0,     0,    26,
      27,     0,     0,   257,   207,     0,    29,    26,    27,     0,
       0,     0,     0,     0,    29,    81,    18,    19,    20,    31,
      21,     0,    22,    23,    24,    25,     0,    31,     0,   211,
      81,    18,    19,    20,     0,    21,     0,    22,    23,    24,
      25,     0,     0,     0,   281,    81,    18,    19,    20,     0,
      21,     0,    22,    23,    24,    25,    81,    18,    19,    20,
       0,     0,     0,    22,     0,    24,    25
};

static const yytype_int16 yycheck[] =
{
      10,    97,     0,    16,    36,   103,    68,     1,     1,     1,
       1,    30,    57,    18,    27,    60,   207,    46,     8,    38,
       4,     5,     6,     7,    45,   123,   124,   125,   126,   127,
      45,    60,   130,   131,   104,    33,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,    63,   152,    46,    16,    17,   218,    72,
      92,     1,    75,    76,    57,    57,    60,    60,    60,    60,
     261,    61,    56,   135,    12,    13,    16,    17,    18,    19,
      20,    21,   203,    46,    46,    45,     0,    47,    46,    99,
      57,    50,   105,    49,   254,    45,    18,    60,    60,    45,
      56,    60,    60,    57,    44,    45,    66,    18,    18,   207,
     231,    51,    16,    17,    18,    19,    20,    21,   131,    33,
      58,    59,   220,    45,    64,    47,    16,    17,    18,    19,
      20,    21,    18,    55,    45,    18,    28,    33,   212,    49,
      44,    45,     0,   238,    55,   241,   144,    51,   218,   159,
       3,     4,    49,    57,    44,    45,    10,    11,   156,    45,
      64,    51,     9,   261,   238,    57,    49,    57,    53,    55,
     202,   266,    46,    26,    64,    45,    29,    47,    31,    54,
     212,   194,   195,    46,   254,    46,    60,    46,   198,   199,
      16,    17,    18,    19,    20,    21,    45,    60,    47,    60,
      46,    60,    21,   201,    23,   203,   238,    18,    14,    15,
      18,    19,    20,    21,    60,   225,    43,    44,    44,    45,
      46,    32,    33,    34,    35,    51,    37,   259,    39,    40,
      41,    42,    65,   231,    45,    46,    47,    45,    64,   249,
     238,    57,   252,   253,    55,   110,   111,   245,    32,    33,
      34,    35,    24,    37,    49,    39,    40,    41,    42,     0,
       1,    37,     3,    18,   274,    56,    50,    45,   266,   112,
     113,   114,   115,    46,   284,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    49,    29,    37,
      31,    32,    33,    34,    35,    20,    37,    48,    39,    40,
      41,    42,    52,    44,    45,    55,   116,   117,    49,    50,
      51,     1,    62,     3,    60,    57,    57,    63,    60,   118,
     119,   121,   122,    64,    46,    49,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    48,    29,
      46,    31,    32,    33,    34,    35,    28,    37,    48,    39,
      40,    41,    42,    57,    44,    45,    63,    50,    57,    49,
      50,    51,     1,    46,     3,    20,    63,    57,    48,    33,
     201,   151,   245,    96,    64,   104,   238,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,   106,
      29,   107,    31,    32,    33,    34,    35,   108,    37,    -1,
      39,    40,    41,    42,   109,    44,    45,    -1,    -1,    -1,
      49,    50,    51,     1,    -1,     3,    -1,    -1,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      -1,    29,    -1,    31,    32,    33,    34,    35,    -1,    37,
      -1,    39,    40,    41,    42,    -1,    44,    45,    -1,    -1,
      -1,    49,    50,    51,     1,    -1,     3,    -1,    -1,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,    29,    -1,    31,    32,    33,    34,    35,    -1,
      37,    -1,    39,    40,    41,    42,    -1,    44,    45,    -1,
      -1,    -1,    49,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      57,    16,    17,    18,    19,    20,    21,    64,    -1,    16,
      17,    18,    19,    20,    21,    32,    33,    34,    35,    -1,
      37,    -1,    39,    40,    41,    42,    -1,    -1,    -1,    44,
      45,    -1,    -1,    50,    49,    -1,    51,    44,    45,    -1,
      -1,    -1,    -1,    -1,    51,    32,    33,    34,    35,    64,
      37,    -1,    39,    40,    41,    42,    -1,    64,    -1,    46,
      32,    33,    34,    35,    -1,    37,    -1,    39,    40,    41,
      42,    -1,    -1,    -1,    46,    32,    33,    34,    35,    -1,
      37,    -1,    39,    40,    41,    42,    32,    33,    34,    35,
      -1,    -1,    -1,    39,    -1,    41,    42
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    29,    31,    32,    33,    34,
      35,    37,    39,    40,    41,    42,    44,    45,    50,    51,
      57,    64,    68,    69,    70,    71,    73,    74,    75,    91,
      94,    95,    96,    97,   100,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   118,
     119,   120,   122,    28,    57,    18,   120,   120,    45,    71,
      73,    94,    45,    57,    57,    45,    45,    57,   104,    18,
      49,    32,    74,    74,    33,   120,   104,   120,   120,     0,
      70,    18,    45,    55,    80,    81,    82,    83,    84,    49,
      92,     1,    57,    60,     8,    61,     9,    65,    53,    54,
      10,    11,    12,    13,    58,    59,    14,    15,    43,    44,
      52,    55,    62,     4,     5,     6,     7,    56,    16,    17,
      45,    47,    66,    94,    57,    96,    82,    24,     1,   104,
     104,   104,    57,    72,    76,    18,    46,    82,    37,     1,
      57,    60,    56,    92,    55,    84,    45,    47,    50,    93,
      94,   105,   108,   118,   104,   109,   110,   111,   112,   113,
     113,   114,   114,   114,   114,   115,   115,   116,   116,   117,
     118,   117,   117,   105,   105,   105,   105,   105,    46,   105,
     121,   104,   105,    18,    96,    45,    99,     1,    46,    46,
      46,    49,    73,    77,    78,    46,    81,    49,    89,   105,
      37,    46,    73,    85,    86,    20,    50,    94,    63,    46,
      60,     1,    48,   104,   104,    46,    98,    94,    94,    49,
     101,    77,    79,    82,    50,    78,    89,    90,    45,    47,
      82,    83,    87,    88,    46,    60,    48,   106,   105,    46,
      46,    94,    46,    28,    30,    38,   102,    50,    57,    60,
      50,    60,    46,    85,    87,    48,    45,    47,    86,    94,
      57,    94,    94,   106,    63,    50,    57,    82,    89,    46,
      46,    46,    85,    20,    63,    94,    46,    48,    94
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
      89,    89,    90,    90,    91,    92,    92,    93,    93,    94,
      94,    94,    95,    94,    94,    94,    94,    96,    96,    96,
      97,    97,    97,    98,    97,    99,    97,   100,   100,   100,
     100,   101,   102,   102,   103,   103,   103,   103,   103,   104,
     104,   105,   105,   105,   105,   105,   105,   106,   106,   107,
     107,   108,   108,   109,   109,   110,   110,   111,   111,   112,
     112,   112,   113,   113,   113,   113,   113,   114,   114,   114,
     115,   115,   115,   116,   116,   116,   116,   117,   118,   118,
     119,   119,   119,   119,   119,   120,   120,   120,   120,   120,
     120,   120,   120,   121,   121,   122,   122,   122,   122,   122
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
       3,     1,     1,     3,     3,     2,     3,     1,     2,     1,
       1,     1,     0,     2,     1,     1,     2,     1,     2,     2,
       7,     5,     7,     0,     7,     0,     6,     5,     7,     5,
       3,     3,     4,     3,     2,     3,     2,     2,     3,     1,
       3,     1,     3,     3,     3,     3,     3,     1,     5,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     1,     1,     1,
       2,     2,     2,     2,     2,     1,     2,     2,     4,     4,
       3,     3,     4,     1,     3,     1,     1,     1,     1,     3
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
#line 79 "cParser.y"
              {
            treeRoot = (yyvsp[0].globalDeclaraionNodePtr);
        }
#line 1669 "cParser.cpp"
    break;

  case 3:
#line 85 "cParser.y"
                          {
            (yyval.globalDeclaraionNodePtr) = (yyvsp[0].statementNodesBlockPtr);
        }
#line 1677 "cParser.cpp"
    break;

  case 4:
#line 88 "cParser.y"
                                {
            (yyval.globalDeclaraionNodePtr) = (yyvsp[-1].globalDeclaraionNodePtr);
            (yyval.globalDeclaraionNodePtr)->mergeStatements(shared_ptr<GlobalDeclaraionNode>((yyvsp[0].statementNodesBlockPtr)));
    }
#line 1686 "cParser.cpp"
    break;

  case 5:
#line 98 "cParser.y"
                    { /* 全局的变量定义，兼定义结构体。 */
            (yyval.statementNodesBlockPtr) = new GlobalDeclaraionNode(shared_ptr<StatementNodesBlock>((yyvsp[0].statementNodesBlockPtr)));
        }
#line 1694 "cParser.cpp"
    break;

  case 6:
#line 101 "cParser.y"
                            { /* 语法上，所有的函数都必须要定义在全局。 */ 
            (yyval.statementNodesBlockPtr) = new GlobalDeclaraionNode(shared_ptr<StatementNodesBlock>((yyvsp[0].nodePtr)));
        }
#line 1702 "cParser.cpp"
    break;

  case 7:
#line 104 "cParser.y"
                  { /* 不允许在全局范围内出现不是定义的语句。 */
            yyerror("syntax error");
            std::cout<<"C-- only supports statements within a function.\n";
        }
#line 1711 "cParser.cpp"
    break;

  case 8:
#line 108 "cParser.y"
            {
            yyerror("syntax error");
            std::cout<<"a '}' without its '{'.\n";
        }
#line 1720 "cParser.cpp"
    break;

  case 9:
#line 116 "cParser.y"
                                 { /* 定义变量 */
            (yyval.statementNodesBlockPtr) = new StatementNodesBlock();
            (yyval.statementNodesBlockPtr)->createMultiVarDeclaration(shared_ptr<IdentifierNode>((yyvsp[-2].identifierNodePtr)), shared_ptr<IdentifierNodeList>((yyvsp[-1].identifierNodeListPtr)));

        }
#line 1730 "cParser.cpp"
    break;

  case 10:
#line 121 "cParser.y"
                          { /* 定义结构体 */ /* TODO */
            /* 取得结构体名之后，即使为该结构体构建符号表 */
            (yyvsp[0].identifierNodePtr)->setType(Node::TYPE_STRUCT);
            (yyvsp[0].identifierNodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyvsp[0].identifierNodePtr)->setStructTypeName((yyvsp[0].identifierNodePtr)->getTokenValue());
            (yyvsp[0].identifierNodePtr)->setVariableName((yyvsp[0].identifierNodePtr)->getTokenValue());
            symbolTableStack->insert(new Attribute((yyvsp[0].identifierNodePtr)));
            symbolTableStack->push(new SymbolTable((yyvsp[0].identifierNodePtr)->getStructTypeName()));
        }
#line 1744 "cParser.cpp"
    break;

  case 11:
#line 129 "cParser.y"
                                               { /* TODO */
            (yyval.statementNodesBlockPtr) = new Node(nameCounter.getNumberedName("declaration"), 6, (yyvsp[-6].nodePtr), (yyvsp[-5].identifierNodePtr), (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            symbolTableStack->pop();
        }
#line 1753 "cParser.cpp"
    break;

  case 12:
#line 133 "cParser.y"
                                    {
            error_missingSemicolon();
        }
#line 1761 "cParser.cpp"
    break;

  case 13:
#line 139 "cParser.y"
                 {(yyval.identifierNodePtr) = (yyvsp[0].identifierNodePtr);}
#line 1767 "cParser.cpp"
    break;

  case 14:
#line 140 "cParser.y"
                       {(yyval.identifierNodePtr) = (yyvsp[-1].nodePtr);}
#line 1773 "cParser.cpp"
    break;

  case 15:
#line 141 "cParser.y"
                        {(yyval.identifierNodePtr) = (yyvsp[-1].nodePtr);}
#line 1779 "cParser.cpp"
    break;

  case 16:
#line 145 "cParser.y"
            { 
            (yyval.identifierNodePtr) = new IdentifierNode(std::string((yyvsp[0].nodePtr), isType==true));
            (yyval.identifierNodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1788 "cParser.cpp"
    break;

  case 17:
#line 149 "cParser.y"
                     { /* 不实现这一条 */}
#line 1794 "cParser.cpp"
    break;

  case 18:
#line 150 "cParser.y"
             { 
            (yyval.identifierNodePtr) = new IdentifierNode(std::string((yyvsp[0].nodePtr), isType==true));
            (yyval.identifierNodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1803 "cParser.cpp"
    break;

  case 19:
#line 154 "cParser.y"
              { /* 不实现这一条, 只支持double */
            (yyval.identifierNodePtr) = new IdentifierNode(std::string((yyvsp[0].nodePtr), isType==true));
            (yyval.identifierNodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1812 "cParser.cpp"
    break;

  case 20:
#line 158 "cParser.y"
               { 
            (yyval.identifierNodePtr) = new IdentifierNode(std::string((yyvsp[0].nodePtr), isType==true));
            (yyval.identifierNodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1821 "cParser.cpp"
    break;

  case 21:
#line 162 "cParser.y"
             { 
            (yyval.identifierNodePtr) = new IdentifierNode(std::string((yyvsp[0].nodePtr), isType==true));
            (yyval.identifierNodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1830 "cParser.cpp"
    break;

  case 22:
#line 166 "cParser.y"
                       { /* TODO */
            (yyval.identifierNodePtr) = new IdentifierNode(std::string((yyvsp[0].nodePtr), isType==true));
            (yyval.identifierNodePtr)->setType(Node::TYPE_STRUCT);
            (yyval.identifierNodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.identifierNodePtr)->setStructTypeName((yyvsp[0].nodePtr)->getStructTypeName());
            (yyval.identifierNodePtr)->setPosition((yyvsp[0].nodePtr));
        }
#line 1842 "cParser.cpp"
    break;

  case 23:
#line 178 "cParser.y"
                   {
            /* 为该匿名结构体维护符号表 */
            std::string name = nameCounter.getNumberedName("`Unamed_Structure");
            symbolTableStack->insert(new Attribute(name, Node::TYPE_STRUCT, Node::KIND_ATTRIBUTE, std::vector<Node::Type>(), std::vector<std::string>(), 
                                     std::vector<int>(), name, csLineCnt, csColumnCnt-1));
            symbolTableStack->push(new SymbolTable(name));
        }
#line 1854 "cParser.cpp"
    break;

  case 24:
#line 184 "cParser.y"
                                       {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("structTypeName"), 4, (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_STRUCT);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setStructTypeName(symbolTableStack->top()->getName());
            (yyval.nodePtr)->setPosition((yyvsp[-4].nodePtr));
            symbolTableStack->pop();
        }
#line 1867 "cParser.cpp"
    break;

  case 25:
#line 192 "cParser.y"
                          { /* 一个之前已经定义过的结构体名字。 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("structTypeName"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].identifierNodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_STRUCT);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setStructTypeName((yyvsp[0].identifierNodePtr)->getTokenValue()/*nameCounter.getNumberedName($2->getTokenValue())*/);
            (yyval.nodePtr)->setPosition((yyvsp[-1].nodePtr));
            if(symbolTableStack->lookUp((yyvsp[0].identifierNodePtr)->getTokenValue())==0){
                error_structNotDeclared((yyvsp[0].identifierNodePtr)->getTokenValue());
            }
        }
#line 1882 "cParser.cpp"
    break;

  case 26:
#line 206 "cParser.y"
                                {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("structMemberDeclarations"), 1, (yyvsp[0].nodePtr));
        }
#line 1890 "cParser.cpp"
    break;

  case 27:
#line 209 "cParser.y"
                                                         {
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 1899 "cParser.cpp"
    break;

  case 28:
#line 216 "cParser.y"
                               {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("structMemberDeclarations"), 3, (yyvsp[-2].identifierNodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            for(int i=0;i<(yyvsp[-1].nodePtr)->getChildrenNumber();i++){
                (yyvsp[-1].nodePtr)->getChildrenById(i)->setType((yyvsp[-2].identifierNodePtr));
            }
            for(int i=0;i<(yyvsp[-1].nodePtr)->getChildrenNumber();i++){
                if((yyvsp[-1].nodePtr)->getChildrenById(i)->isTerminal() && (yyvsp[-1].nodePtr)->getChildrenById(i)->getTokenValue().compare(",")==0) continue;
                if(symbolTableStack->insert(new Attribute((yyvsp[-1].nodePtr)->getChildrenById(i))) == false){
                    error_duplicatedVariable((yyvsp[-1].nodePtr)->getChildrenById(i));
                }
            }
        }
#line 1916 "cParser.cpp"
    break;

  case 29:
#line 231 "cParser.y"
                 {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("structMembers"), 1, (yyvsp[0].nodePtr));
        }
#line 1924 "cParser.cpp"
    break;

  case 30:
#line 234 "cParser.y"
                                   {
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[-1].nodePtr));
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 1934 "cParser.cpp"
    break;

  case 31:
#line 244 "cParser.y"
                       {
            (yyval.identifierNodeListPtr) = new IndentifierNodeList();
            (yyval.identifierNodeListPtr)->mIdentifierNodeList.push_back((yyvsp[0].identifierNodePtr));
        }
#line 1943 "cParser.cpp"
    break;

  case 32:
#line 248 "cParser.y"
                                           {
            (yyval.identifierNodeListPtr) = (yyvsp[-2].identifierNodeListPtr);
            (yyval.identifierNodeListPtr)->mIdentifierNodeList.push_back((yyvsp[0].identifierNodePtr));
        }
#line 1952 "cParser.cpp"
    break;

  case 33:
#line 255 "cParser.y"
                 {                       /* int a; 没有初始值 */
            (yyval.identifierNodePtr) = (yyvsp[0].nodePtr);
        }
#line 1960 "cParser.cpp"
    break;

  case 34:
#line 258 "cParser.y"
                                  {   /* int a=10; 有初始值, 暂不实现 */
            (yyval.identifierNodePtr) = new Node(nameCounter.getNumberedName("initialization"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            (yyval.identifierNodePtr)->copyFromChild();
        }
#line 1969 "cParser.cpp"
    break;

  case 35:
#line 265 "cParser.y"
                                      {  /* int *a; 指针变量，这里不打算实现。 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variable"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 1977 "cParser.cpp"
    break;

  case 36:
#line 268 "cParser.y"
                     { /* 不是指针的变量 */
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 1985 "cParser.cpp"
    break;

  case 37:
#line 275 "cParser.y"
            { /* a simple pointer */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("pointerSpecifier"), 1, (yyvsp[0].nodePtr));
        }
#line 1993 "cParser.cpp"
    break;

  case 38:
#line 278 "cParser.y"
                             { /* a pointer to another pointer variable */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("pointerSpecifier"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2001 "cParser.cpp"
    break;

  case 39:
#line 281 "cParser.y"
                  { /* a pointer to a const variable */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("pointerSpecifier"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2009 "cParser.cpp"
    break;

  case 40:
#line 284 "cParser.y"
                                   { /* a pointer to another pointer which is a pointer to a const value */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("pointerSpecifier"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2017 "cParser.cpp"
    break;

  case 41:
#line 290 "cParser.y"
                   { /* 一个普通的变量 */
            (yyval.nodePtr) = (yyvsp[0].identifierNodePtr);
        }
#line 2025 "cParser.cpp"
    break;

  case 42:
#line 293 "cParser.y"
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
#line 2045 "cParser.cpp"
    break;

  case 43:
#line 308 "cParser.y"
                         {              /* 这一条弃之不用，太复杂了 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableName"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2053 "cParser.cpp"
    break;

  case 44:
#line 311 "cParser.y"
                             {           /* 函数定义 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableName"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setKind(Node::KIND_FUNCTION);
            (yyval.nodePtr)->setVariableName((yyvsp[-2].nodePtr)->getVariableName());
            (yyval.nodePtr)->setPosition((yyvsp[-2].nodePtr));
        }
#line 2064 "cParser.cpp"
    break;

  case 45:
#line 317 "cParser.y"
                                        {    /* 函数定义 */
            (yyval.nodePtr) = new FuncNameAndArgsNode(shared_ptr<IdentifierNode>(variableName), shared_ptr<VarDeclarationList(paramTypes)>(paramTypes));
        }
#line 2072 "cParser.cpp"
    break;

  case 46:
#line 323 "cParser.y"
                      {
            (yyval.varDeclarationListPtr) = new VarDeclarationList();
            (yyval.varDeclarationListPtr)->mVarDeclarationLis.push_back(shared_ptr<VariableDeclarationNode>((yyvsp[0].nodePtr)))
        }
#line 2081 "cParser.cpp"
    break;

  case 47:
#line 327 "cParser.y"
                                     {
            (yyval.varDeclarationListPtr) = (yyvsp[-2].varDeclarationListPtr);
            (yyval.varDeclarationListPtr)->mVarDeclarationLis.push_back(shared_ptr<VariableDeclarationNode>((yyvsp[0].nodePtr)))
        }
#line 2090 "cParser.cpp"
    break;

  case 48:
#line 334 "cParser.y"
             {   /* int (*f)(double,char); 不实现这一条，太复杂 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("paramTypeName"), 1, (yyvsp[0].identifierNodePtr));
        }
#line 2098 "cParser.cpp"
    break;

  case 49:
#line 337 "cParser.y"
                                { /* 无名字的指针变量。不实现这一条，天复杂 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("paramTypeName"), 2, (yyvsp[-1].identifierNodePtr), (yyvsp[0].nodePtr));
        }
#line 2106 "cParser.cpp"
    break;

  case 50:
#line 340 "cParser.y"
                      {      /* 这一条是要正常实现的，定义函数用的 */
            (yyval.nodePtr) = new VariableDeclarationNode(shared_ptr<IdentifierNode>((yyvsp[-1].identifierNodePtr)), shared_ptr<IdentifierNode>((yyvsp[0].nodePtr)));

        }
#line 2115 "cParser.cpp"
    break;

  case 51:
#line 348 "cParser.y"
                         {       /* 不实现指针 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoName"), 1, (yyvsp[0].nodePtr));
        }
#line 2123 "cParser.cpp"
    break;

  case 52:
#line 351 "cParser.y"
                               { 
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoName"), 1, (yyvsp[0].nodePtr));
        }
#line 2131 "cParser.cpp"
    break;

  case 53:
#line 358 "cParser.y"
                                                  {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 4, (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2139 "cParser.cpp"
    break;

  case 54:
#line 361 "cParser.y"
                                   {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2147 "cParser.cpp"
    break;

  case 55:
#line 364 "cParser.y"
                                       {  /* a function taking another function as param... */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2155 "cParser.cpp"
    break;

  case 56:
#line 367 "cParser.y"
                                                  { /* a function taking another function as param... */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 4, (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].varDeclarationListPtr), (yyvsp[0].nodePtr));
        }
#line 2163 "cParser.cpp"
    break;

  case 57:
#line 370 "cParser.y"
                {            /* because it has no name, it must stop some way. Below is some terminators */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2171 "cParser.cpp"
    break;

  case 58:
#line 373 "cParser.y"
                {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2179 "cParser.cpp"
    break;

  case 59:
#line 376 "cParser.y"
                           { /* a function taking another function as param... */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].varDeclarationListPtr), (yyvsp[0].nodePtr));
        }
#line 2187 "cParser.cpp"
    break;

  case 60:
#line 383 "cParser.y"
                              {          /* int a[10]={1}; 初始化列表 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("initialValue"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2195 "cParser.cpp"
    break;

  case 61:
#line 386 "cParser.y"
                             {          /* int a=5+6; int b=a=3; 普通的初始值 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("initialValue"), 1, (yyvsp[0].nodePtr));
    }
#line 2203 "cParser.cpp"
    break;

  case 62:
#line 393 "cParser.y"
                     {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("initialValues"), 1, (yyvsp[0].nodePtr));
        }
#line 2211 "cParser.cpp"
    break;

  case 63:
#line 396 "cParser.y"
                                       { /* int a[10]={1,2,3} */
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[-1].nodePtr));
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 2221 "cParser.cpp"
    break;

  case 64:
#line 405 "cParser.y"
                                      {
            (yyval.nodePtr) = new FunctionDeclarationNode(shared_ptr<IdentifierNode>((yyvsp[-2].identifierNodePtr)), shared_ptr<FuncNameAndArgsNode>((yyvsp[-1].nodePtr)), shared_ptr<StatementBlockNode>((yyvsp[0].statementNodesBlockPtr)));
        }
#line 2229 "cParser.cpp"
    break;

  case 65:
#line 412 "cParser.y"
                { /* 可以 {} 这样而不必 {;} 这样 */
            (yyval.statementNodesBlockPtr) = StatementNodesBlock();
            (yyval.statementNodesBlockPtr)->mStatementList.push_back(new NullStatementNode());
        }
#line 2238 "cParser.cpp"
    break;

  case 66:
#line 416 "cParser.y"
                           {
            (yyval.statementNodesBlockPtr) = (yyvsp[-1].statementNodesBlockPtr);
        }
#line 2246 "cParser.cpp"
    break;

  case 67:
#line 446 "cParser.y"
                  {
            (yyval.statementNodesBlockPtr) = (yyvsp[0].statementNodesBlockPtr);
        }
#line 2254 "cParser.cpp"
    break;

  case 68:
#line 449 "cParser.y"
                             {
            (yyval.statementNodesBlockPtr) = (yyvsp[-1].statementNodesBlockPtr);
            (yyval.statementNodesBlockPtr)->mergeStatements(shared_ptr<StatementNodesBlock>((yyvsp[0].statementNodesBlockPtr)));
        }
#line 2263 "cParser.cpp"
    break;

  case 69:
#line 456 "cParser.y"
                    {
            (yyval.statementNodesBlockPtr) = (yyvsp[0].statementNodesBlockPtr);
        }
#line 2271 "cParser.cpp"
    break;

  case 70:
#line 459 "cParser.y"
                            { /* 表达式，也是最常见的语句 */
            (yyval.statementNodesBlockPtr) = new Node(nameCounter.getNumberedName("statement"), 1, (yyvsp[0].nodePtr));
        }
#line 2279 "cParser.cpp"
    break;

  case 71:
#line 462 "cParser.y"
                      { /* 循环 */
            (yyval.statementNodesBlockPtr) = new Node(nameCounter.getNumberedName("statement"), 1, (yyvsp[0].nodePtr));
        }
#line 2287 "cParser.cpp"
    break;

  case 72:
#line 465 "cParser.y"
        { symbolTableStack->push(new SymbolTable(nameCounter.getNumberedName("NestedBlock"))); }
#line 2293 "cParser.cpp"
    break;

  case 73:
#line 465 "cParser.y"
                                                                                                                { /* 语句块。 */
            /* 注：非函数体的语句块是管变量的生命周期的，所以这里要维护符号表。 */
            /* 不能把这个维护放在 statementBlock:'{'...'}' 这个产生式里面，因为这样的话函数体语句块会维护两次符号表。 */
            (yyval.statementNodesBlockPtr) = new Node(nameCounter.getNumberedName("statement"), 1, (yyvsp[0].statementNodesBlockPtr));
            symbolTableStack->pop();
        }
#line 2304 "cParser.cpp"
    break;

  case 74:
#line 471 "cParser.y"
                        {
            (yyval.statementNodesBlockPtr) = new Node(nameCounter.getNumberedName("statement"), 1, (yyvsp[0].nodePtr));
        }
#line 2312 "cParser.cpp"
    break;

  case 75:
#line 474 "cParser.y"
                      {
            (yyval.statementNodesBlockPtr) = new Node(nameCounter.getNumberedName("statement"), 1, (yyvsp[0].nodePtr));
        }
#line 2320 "cParser.cpp"
    break;

  case 76:
#line 477 "cParser.y"
                  {
        error_wrongStatement();
    }
#line 2328 "cParser.cpp"
    break;

  case 77:
#line 483 "cParser.y"
            { /* 注：空语句是一个 expressionStatement */
            (yyval.nodePtr) = new NullStatementNode();
        }
#line 2336 "cParser.cpp"
    break;

  case 78:
#line 486 "cParser.y"
                       {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("expressionStatement"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2344 "cParser.cpp"
    break;

  case 79:
#line 489 "cParser.y"
                         {
            error_missingSemicolon();
        }
#line 2352 "cParser.cpp"
    break;

  case 80:
#line 495 "cParser.y"
                                                                                 { /* 不允许 for(int i;i<10;i++) 这样 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("loopStatement"), 7, (yyvsp[-6].nodePtr), (yyvsp[-5].nodePtr), (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].statementNodesBlockPtr));
        }
#line 2360 "cParser.cpp"
    break;

  case 81:
#line 498 "cParser.y"
                                           {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("loopStatement"), 5, (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].statementNodesBlockPtr));
        }
#line 2368 "cParser.cpp"
    break;

  case 82:
#line 501 "cParser.y"
                                                  {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("loopStatement"), 7, (yyvsp[-6].nodePtr), (yyvsp[-5].statementNodesBlockPtr), (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2376 "cParser.cpp"
    break;

  case 83:
#line 504 "cParser.y"
                                   { error_missingRightBrancket(); }
#line 2382 "cParser.cpp"
    break;

  case 85:
#line 505 "cParser.y"
                        { error_wrongExpression; }
#line 2388 "cParser.cpp"
    break;

  case 86:
#line 505 "cParser.y"
                                                                 { 

        }
#line 2396 "cParser.cpp"
    break;

  case 87:
#line 512 "cParser.y"
                                        {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("branchStatement"), 5, (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].statementNodesBlockPtr));
        }
#line 2404 "cParser.cpp"
    break;

  case 88:
#line 515 "cParser.y"
                                                       { /* （else悬挂问题）这一条和上一条不能颠倒。 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("branchStatement"), 7, (yyvsp[-6].nodePtr), (yyvsp[-5].nodePtr), (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-2].statementNodesBlockPtr), (yyvsp[-1].nodePtr), (yyvsp[0].statementNodesBlockPtr));
        }
#line 2412 "cParser.cpp"
    break;

  case 90:
#line 519 "cParser.y"
                              {
            { error_elseWithNoIf(); }
        }
#line 2420 "cParser.cpp"
    break;

  case 94:
#line 537 "cParser.y"
                   { /* 函数返回，这里要检查返回类型 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("jumpStatement"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            /* TODO: check if the type of return value matches the function */
            if(symbolTableStack->lookUp(symbolTableStack->top()->getName())->type != Node::TYPE_VOID){
                error_returnValueTypeMismatch(symbolTableStack->lookUp(symbolTableStack->top()->getName()), symbolTableStack->lookUp(symbolTableStack->top()->getName())->type);
            }
        }
#line 2432 "cParser.cpp"
    break;

  case 95:
#line 544 "cParser.y"
                              { /* 函数返回，这里要检查返回类型 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("jumpStatement"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            /* 因为这个语句出现时，符号表栈顶附近必定是一个函数的符号表。这个时候只需要先查到该函数的符号表的名字，然后再在全局符号表中看这个名字的类型即可。 */
            /* 因为符号表名和函数名永远是一样的。（在我们的设计中） */
            if(!typeMatch(symbolTableStack->lookUp(symbolTableStack->top()->getName()), (yyvsp[-1].nodePtr))){
                error_returnValueTypeMismatch(symbolTableStack->lookUp(symbolTableStack->top()->getName()), (yyvsp[-1].nodePtr));
            }
        }
#line 2445 "cParser.cpp"
    break;

  case 96:
#line 552 "cParser.y"
                     { /* 循环控制 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("jumpStatement"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2453 "cParser.cpp"
    break;

  case 97:
#line 555 "cParser.y"
                  { /* 循环控制 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("jumpStatement"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2461 "cParser.cpp"
    break;

  case 98:
#line 558 "cParser.y"
                            { /* 太复杂了，不实现 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("jumpStatement"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].identifierNodePtr), (yyvsp[0].nodePtr));
        }
#line 2469 "cParser.cpp"
    break;

  case 99:
#line 569 "cParser.y"
                             {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("expression"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->copyFrom((yyvsp[0].nodePtr));
        }
#line 2478 "cParser.cpp"
    break;

  case 100:
#line 573 "cParser.y"
                                            {
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[-1].nodePtr));
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
            /* 一串逗号分隔的表达式的值，是最后一个表达式的值。 */
            (yyval.nodePtr)->copyFrom((yyval.nodePtr)->getChildrenById((yyval.nodePtr)->getChildrenNumber()-1));
        }
#line 2490 "cParser.cpp"
    break;

  case 101:
#line 585 "cParser.y"
                                  {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2498 "cParser.cpp"
    break;

  case 102:
#line 588 "cParser.y"
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
#line 2514 "cParser.cpp"
    break;

  case 103:
#line 599 "cParser.y"
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
#line 2530 "cParser.cpp"
    break;

  case 104:
#line 610 "cParser.y"
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
#line 2546 "cParser.cpp"
    break;

  case 105:
#line 621 "cParser.y"
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
#line 2562 "cParser.cpp"
    break;

  case 106:
#line 632 "cParser.y"
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
#line 2578 "cParser.cpp"
    break;

  case 107:
#line 648 "cParser.y"
                            {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2586 "cParser.cpp"
    break;

  case 108:
#line 651 "cParser.y"
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
#line 2604 "cParser.cpp"
    break;

  case 109:
#line 669 "cParser.y"
                             {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2612 "cParser.cpp"
    break;

  case 110:
#line 672 "cParser.y"
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
#line 2627 "cParser.cpp"
    break;

  case 111:
#line 687 "cParser.y"
                            {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2635 "cParser.cpp"
    break;

  case 112:
#line 690 "cParser.y"
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
#line 2650 "cParser.cpp"
    break;

  case 113:
#line 705 "cParser.y"
                                     {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2658 "cParser.cpp"
    break;

  case 114:
#line 708 "cParser.y"
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
#line 2673 "cParser.cpp"
    break;

  case 115:
#line 723 "cParser.y"
                             {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2681 "cParser.cpp"
    break;

  case 116:
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
#line 2696 "cParser.cpp"
    break;

  case 117:
#line 741 "cParser.y"
                                     {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2704 "cParser.cpp"
    break;

  case 118:
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
#line 2719 "cParser.cpp"
    break;

  case 119:
#line 759 "cParser.y"
                                     {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2727 "cParser.cpp"
    break;

  case 120:
#line 762 "cParser.y"
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
#line 2745 "cParser.cpp"
    break;

  case 121:
#line 775 "cParser.y"
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
#line 2760 "cParser.cpp"
    break;

  case 122:
#line 790 "cParser.y"
                        {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2768 "cParser.cpp"
    break;

  case 123:
#line 793 "cParser.y"
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
#line 2786 "cParser.cpp"
    break;

  case 124:
#line 806 "cParser.y"
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
#line 2804 "cParser.cpp"
    break;

  case 125:
#line 819 "cParser.y"
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
#line 2822 "cParser.cpp"
    break;

  case 126:
#line 832 "cParser.y"
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
#line 2840 "cParser.cpp"
    break;

  case 127:
#line 850 "cParser.y"
                                {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2848 "cParser.cpp"
    break;

  case 128:
#line 853 "cParser.y"
                                                   {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFrom((yyvsp[-2].nodePtr));
            if(!(checkType((yyvsp[-2].nodePtr),Node::TYPE_INT)&&checkType((yyvsp[0].nodePtr),Node::TYPE_INT)) || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2861 "cParser.cpp"
    break;

  case 129:
#line 861 "cParser.y"
                                                    {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFrom((yyvsp[-2].nodePtr));
            if(!(checkType((yyvsp[-2].nodePtr),Node::TYPE_INT)&&checkType((yyvsp[0].nodePtr),Node::TYPE_INT)) || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2874 "cParser.cpp"
    break;

  case 130:
#line 874 "cParser.y"
                                {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2882 "cParser.cpp"
    break;

  case 131:
#line 877 "cParser.y"
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
#line 2898 "cParser.cpp"
    break;

  case 132:
#line 888 "cParser.y"
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
#line 2914 "cParser.cpp"
    break;

  case 133:
#line 904 "cParser.y"
                        {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2922 "cParser.cpp"
    break;

  case 134:
#line 907 "cParser.y"
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
#line 2938 "cParser.cpp"
    break;

  case 135:
#line 918 "cParser.y"
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
#line 2954 "cParser.cpp"
    break;

  case 136:
#line 929 "cParser.y"
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
#line 2970 "cParser.cpp"
    break;

  case 137:
#line 946 "cParser.y"
                       {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2978 "cParser.cpp"
    break;

  case 138:
#line 961 "cParser.y"
                              {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2986 "cParser.cpp"
    break;

  case 139:
#line 964 "cParser.y"
                               {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2994 "cParser.cpp"
    break;

  case 140:
#line 970 "cParser.y"
                                   {/* ++a, especially ++a[i] is ++(a[i]) but not (++a)[i] */
            (yyvsp[-1].nodePtr) = new UnaryOperatorNode(std::string("pre")+(yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkKind((yyvsp[0].nodePtr), Node::KIND_VARIABLE) || (yyvsp[0].nodePtr)->isArray() || (yyvsp[0].nodePtr)->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError((yyvsp[0].nodePtr),(yyvsp[-1].nodePtr));
            }
        }
#line 3007 "cParser.cpp"
    break;

  case 141:
#line 978 "cParser.y"
                                   {/* --a, the same as ++a[i] */
            (yyvsp[-1].nodePtr) = new UnaryOperatorNode(std::string("pre")+(yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkKind((yyvsp[0].nodePtr), Node::KIND_VARIABLE) || (yyvsp[0].nodePtr)->isArray() || (yyvsp[0].nodePtr)->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError((yyvsp[0].nodePtr),(yyvsp[-1].nodePtr));
            }
        }
#line 3020 "cParser.cpp"
    break;

  case 142:
#line 986 "cParser.y"
                                   {/* logical NOT */
            (yyvsp[-1].nodePtr) = new UnaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkType((yyvsp[0].nodePtr), Node::TYPE_INT)){
                error_expressionTypeError((yyvsp[0].nodePtr),(yyvsp[-1].nodePtr));
            }
        }
#line 3033 "cParser.cpp"
    break;

  case 143:
#line 994 "cParser.y"
                                   {/* bitwise NOT */
            (yyvsp[-1].nodePtr) = new UnaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkType((yyvsp[0].nodePtr), Node::TYPE_INT)){
                error_expressionTypeError((yyvsp[0].nodePtr),(yyvsp[-1].nodePtr));
            }
        }
#line 3046 "cParser.cpp"
    break;

  case 144:
#line 1002 "cParser.y"
                                   {/* negative */
            (yyvsp[-1].nodePtr) = new UnaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            if(checkType((yyvsp[0].nodePtr), Node::TYPE_STRUCT)){
                error_expressionTypeError((yyvsp[0].nodePtr),(yyvsp[-1].nodePtr));
            }
        }
#line 3058 "cParser.cpp"
    break;

  case 145:
#line 1012 "cParser.y"
                         {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3066 "cParser.cpp"
    break;

  case 146:
#line 1015 "cParser.y"
                                   {/* a++, espetially a[i]++ is allowed, (a[i])++ is not necessary */
            (yyvsp[0].nodePtr) = new UnaryOperatorNode(std::string("post")+(yyvsp[0].nodePtr)->getName(), 1, (yyvsp[-1].nodePtr));
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkKind((yyvsp[-1].nodePtr), Node::KIND_VARIABLE) || (yyvsp[-1].nodePtr)->isArray() || (yyvsp[-1].nodePtr)->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError((yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 3079 "cParser.cpp"
    break;

  case 147:
#line 1023 "cParser.y"
                                   {/* a-- */
            (yyvsp[0].nodePtr) = new UnaryOperatorNode(std::string("post")+(yyvsp[0].nodePtr)->getName(), 1, (yyvsp[-1].nodePtr));
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkKind((yyvsp[-1].nodePtr), Node::KIND_VARIABLE) || (yyvsp[-1].nodePtr)->isArray() || (yyvsp[-1].nodePtr)->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError((yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 3092 "cParser.cpp"
    break;

  case 148:
#line 1031 "cParser.y"
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
#line 3112 "cParser.cpp"
    break;

  case 149:
#line 1046 "cParser.y"
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
#line 3146 "cParser.cpp"
    break;

  case 150:
#line 1075 "cParser.y"
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
#line 3162 "cParser.cpp"
    break;

  case 151:
#line 1086 "cParser.y"
                                                 {/* struct's member (a.val) */
            Node *t = (yyvsp[-1].nodePtr);
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].identifierNodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyvsp[-1].nodePtr)->setPosition(t);
            if(checkKind((yyvsp[-2].nodePtr), Node::KIND_ATTRIBUTE) || !(checkType((yyvsp[-2].nodePtr), Node::TYPE_STRUCT)) || (yyvsp[-2].nodePtr)->isArray())
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr));
            else {
                auto symbolTable = SymbolTable::getSymbolTableByName((yyvsp[-2].nodePtr)->getStructTypeName());
            
                if(symbolTable->lookUp((yyvsp[0].identifierNodePtr)->getTokenValue()) == NULL)
                    error_variableNotDeclaredInStruct((yyvsp[-2].nodePtr),(yyvsp[0].identifierNodePtr));
                
                (yyval.nodePtr)->copyFrom(symbolTable->lookUp((yyvsp[0].identifierNodePtr)->getTokenValue()));
            }
        }
#line 3183 "cParser.cpp"
    break;

  case 152:
#line 1108 "cParser.y"
                                                     {
            error_missingRightBrancket2();
        }
#line 3191 "cParser.cpp"
    break;

  case 153:
#line 1114 "cParser.y"
                             {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("paramList"), 1, (yyvsp[0].nodePtr));
        }
#line 3199 "cParser.cpp"
    break;

  case 154:
#line 1117 "cParser.y"
                                           {/* 这里面不能填 expression，因为 expression 也是用逗号隔开的一串表达式 */
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[-1].nodePtr));
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 3209 "cParser.cpp"
    break;

  case 155:
#line 1127 "cParser.y"
                   {
            (yyval.nodePtr) = (yyvsp[0].identifierNodePtr);
            if(!symbolTableStack->lookUp((yyvsp[0].identifierNodePtr)->getTokenValue())){
                error_variableNotDeclared((yyvsp[0].identifierNodePtr)->getTokenValue());
                (yyval.nodePtr)->setKind(Node::KIND_VARIABLE);
                (yyval.nodePtr)->setType(Node::TYPE_INT);
            }else{
                (yyval.nodePtr)->setAttribute(symbolTableStack->lookUp((yyvsp[0].identifierNodePtr)->getTokenValue()));
                (yyval.nodePtr)->setPosition(csLineCnt, csColumnCnt);
            }
        }
#line 3225 "cParser.cpp"
    break;

  case 156:
#line 1138 "cParser.y"
                      {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3233 "cParser.cpp"
    break;

  case 157:
#line 1141 "cParser.y"
                   {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3241 "cParser.cpp"
    break;

  case 158:
#line 1144 "cParser.y"
               { /* 这个就不实现了吧 */
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3249 "cParser.cpp"
    break;

  case 159:
#line 1147 "cParser.y"
                           {
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
        }
#line 3257 "cParser.cpp"
    break;


#line 3261 "cParser.cpp"

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
#line 1153 "cParser.y"

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

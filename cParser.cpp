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
static void error_duplicatedVariable(Node *);
static void error_variableNotDeclared(std::string);
static void error_illegalArraySize(Node *);
static void error_expressionTypeError(Node *,Node *,Node *);
static void error_expressionTypeError(Node *,Node *);
static void error_typeMismatch(Node *);
static void error_variableNotDeclaredInStruct(Node *,Node *);
static void error_argumentNumberNotMatch(Node *,int);
static void error_argumentTypeNotMatch(std::vector<Node::Type>&,Node *,std::vector<std::string>&);
static void error_structNotDeclared(std::string);
static void error_notArray(Node *);
static void error_returnValueTypeMismatch(Attribute* need, Node::Type give);
static void error_returnValueTypeMismatch(Attribute* need, Node * give);
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

    Node * nodePtr;
    DoubleNode * doubleNodePtr;
    IntNode * intNodePtr;
    IdentifierNodeList* identifierNodeListPtr;
    IdentifierNode* identifierNodePtr;
    VarDeclarationList* varDeclarationListPtr;
    StatementNodesBlock* statementNodesBlockPtr;
    GlobalDeclaraionNode * globalDeclaraionNodePtr;

#line 214 "cParser.cpp"

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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  23
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   281

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  125
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  205

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
       0,    81,    81,    87,    90,   100,   104,   120,   144,   145,
     146,   150,   154,   155,   159,   163,   167,   171,   183,   183,
     197,   211,   214,   221,   236,   239,   249,   253,   260,   263,
     270,   273,   280,   283,   286,   289,   295,   298,   313,   316,
     319,   325,   329,   336,   339,   342,   350,   353,   360,   363,
     366,   369,   372,   375,   378,   385,   388,   395,   398,   407,
     414,   418,   448,   451,   458,   572,   576,   588,   591,   602,
     613,   624,   635,   651,   654,   672,   675,   690,   693,   708,
     711,   726,   729,   744,   747,   762,   765,   778,   793,   796,
     809,   822,   835,   853,   856,   864,   877,   880,   891,   907,
     910,   921,   932,   949,   964,   967,   973,   981,   989,   997,
    1005,  1015,  1018,  1026,  1034,  1049,  1078,  1089,  1111,  1117,
    1120,  1130,  1141,  1144,  1147,  1150
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
  "declaration", "type", "typeName", "structTypeName", "$@1",
  "structMemberDeclarations", "structMemberDeclaration", "structMembers",
  "initializations", "initialization", "variable", "pointerSpecifier",
  "variableName", "paramTypes", "paramTypeName", "variableWithNoName",
  "variableWithNoNameCore", "initialValue", "initialValues",
  "functionDeclaration", "statementBlock", "statements", "statement",
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

#define YYPACT_NINF (-131)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     215,   -12,  -131,  -131,  -131,   226,  -131,   226,   -11,  -131,
      26,   215,  -131,  -131,    -3,  -131,  -131,  -131,  -131,  -131,
    -131,  -131,  -131,  -131,  -131,  -131,    -3,    10,   -22,  -131,
      17,     3,    89,   215,    -6,  -131,  -131,    -3,   164,    79,
    -131,    27,    89,   127,    54,    -3,   176,  -131,  -131,  -131,
      25,  -131,  -131,    -3,   188,  -131,    84,    84,  -131,  -131,
    -131,  -131,    84,   130,    79,    84,    84,  -131,  -131,  -131,
      -5,    82,    36,    63,    67,   116,    20,   142,   201,   -35,
       7,  -131,    14,  -131,  -131,  -131,    -2,     5,  -131,   104,
      65,  -131,  -131,  -131,  -131,  -131,    14,    14,    14,    60,
    -131,  -131,   -21,    14,    14,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,  -131,
    -131,    94,   130,   124,   145,   117,  -131,     3,  -131,   108,
    -131,   215,  -131,  -131,    -3,  -131,   130,  -131,    79,    82,
    -131,    81,    36,    63,    67,   116,    20,    20,   142,   142,
     142,   142,   201,   201,   -35,   -35,  -131,  -131,  -131,  -131,
    -131,  -131,  -131,  -131,  -131,  -131,  -131,    71,     0,   123,
    -131,  -131,    72,   137,  -131,   200,   156,  -131,  -131,  -131,
    -131,   130,  -131,   130,  -131,  -131,  -131,  -131,  -131,    73,
     147,  -131,  -131,  -131,  -131
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    11,    15,    13,     0,    14,     0,     0,    16,
       0,     2,     3,     5,     0,     8,    17,     6,    20,    18,
       9,    10,    12,     1,     4,    36,     0,    32,     0,    26,
      28,     0,    31,     0,     0,    34,     7,     0,     0,     0,
      59,    33,    30,     0,     0,     0,     0,    21,    38,    27,
      28,    60,    64,     0,     0,    62,     0,     0,   121,   122,
     123,   124,     0,     0,     0,     0,     0,    29,    56,    67,
      73,    75,    77,    79,    81,    83,    85,    88,    93,    96,
      99,   104,   105,   111,    35,    39,    43,     0,    41,     0,
       0,    24,    19,    22,    61,    63,   106,   107,   110,     0,
      65,    57,     0,   109,   108,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     113,     0,     0,     0,     0,     0,    45,    46,    44,    47,
      40,     0,    37,    23,     0,   125,     0,    55,     0,    76,
      99,     0,    78,    80,    82,    84,    86,    87,    92,    91,
      89,    90,    94,    95,    97,    98,   102,   103,   100,   101,
      69,    70,    71,    72,    68,   116,   119,     0,     0,    65,
     117,    53,     0,     0,    52,     0,     0,    42,    25,    66,
      58,     0,   115,     0,   118,   114,    54,    49,    50,     0,
       0,    74,   120,    51,    48
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -131,  -131,  -131,   182,   -20,     8,   165,  -131,  -131,  -131,
     166,  -131,  -131,   170,    -9,   -77,   -29,  -130,    61,    85,
    -131,   -54,  -131,  -131,  -131,  -131,   177,   -83,   -56,    33,
    -131,   131,   136,   143,   144,   152,    77,   161,   153,   159,
     158,   -39,  -131,   207,  -131,  -131
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    10,    11,    12,    13,    86,    15,    16,    33,    46,
      47,    90,    28,    29,    34,    31,    32,    87,    88,   138,
     139,    67,   102,    17,    40,    54,    55,    99,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
     166,   150,    81,    82,   177,    83
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      80,   194,    42,   105,   182,    30,    18,   100,    14,   137,
     101,   124,   125,   126,   127,    25,    25,   121,    52,    14,
     122,    25,    22,   151,    80,    80,    23,   123,    50,   147,
     129,   130,   113,   114,    52,    36,    91,    19,    37,   148,
      48,    45,    26,   134,    50,   135,    53,    35,    26,   178,
     100,   140,    27,    27,    45,   199,   106,   137,    41,   131,
     146,   132,    53,   128,    84,   141,    38,    80,   170,   171,
     172,   173,   174,    39,    89,   176,   179,   136,   115,   116,
     133,    39,   167,   167,   167,    80,    80,    80,    80,    80,
     189,   107,    80,    80,   190,    56,    57,    58,    59,    60,
      61,   108,    58,    59,    60,    61,   145,    80,    42,    80,
      56,    57,    58,    59,    60,    61,   109,   192,   196,   203,
     146,   110,   143,    62,    63,   144,   111,   112,    64,    63,
      65,   193,   141,   141,    43,   188,    44,   202,    62,    63,
     175,   146,   180,    66,   191,    65,    56,    57,    58,    59,
      60,    61,   142,   185,    80,   186,   117,   118,    66,     1,
       2,     3,     4,    25,     5,   184,     6,     7,     8,     9,
      20,   195,    21,    85,    62,    63,   200,     1,     2,     3,
       4,    65,     5,   197,     6,     7,     8,     9,   156,   157,
     134,   181,   135,    24,    66,   204,     1,     2,     3,     4,
      27,     5,   187,     6,     7,     8,     9,    49,     1,     2,
       3,     4,    93,     5,    51,     6,     7,     8,     9,   183,
       1,     2,     3,     4,   201,     5,    92,     6,     7,     8,
       9,    95,     1,     2,     3,     4,   149,     5,    94,     6,
       7,     8,     9,   152,   119,   120,   198,     1,     2,     3,
       4,   153,     5,   154,     6,     7,     8,     9,     1,     2,
       3,     4,   155,    96,    97,     6,     0,     8,     9,    98,
     162,   163,   103,   104,   158,   159,   160,   161,   164,   165,
     168,   169
};

static const yytype_int16 yycheck[] =
{
      39,     1,    31,     8,   134,    14,    18,    63,     0,    86,
      64,     4,     5,     6,     7,    18,    18,    52,    38,    11,
      55,    18,    33,   106,    63,    64,     0,    62,    37,    50,
      16,    17,    12,    13,    54,    57,    45,    49,    60,    60,
      46,    33,    45,    45,    53,    47,    38,    37,    45,   132,
     106,    46,    55,    55,    46,   185,    61,   134,    55,    45,
      60,    47,    54,    56,    37,    60,    49,   106,   124,   125,
     126,   127,   128,    56,    20,   131,   132,    86,    58,    59,
      66,    56,   121,   122,   123,   124,   125,   126,   127,   128,
     146,     9,   131,   132,   148,    16,    17,    18,    19,    20,
      21,    65,    18,    19,    20,    21,    46,   146,   137,   148,
      16,    17,    18,    19,    20,    21,    53,    46,    46,    46,
      60,    54,    57,    44,    45,    60,    10,    11,    49,    45,
      51,    60,    60,    60,    45,   144,    47,   193,    44,    45,
      46,    60,    18,    64,    63,    51,    16,    17,    18,    19,
      20,    21,    48,    45,   193,    47,    14,    15,    64,    32,
      33,    34,    35,    18,    37,    48,    39,    40,    41,    42,
       5,    48,     7,    46,    44,    45,    20,    32,    33,    34,
      35,    51,    37,    46,    39,    40,    41,    42,   111,   112,
      45,    46,    47,    11,    64,    48,    32,    33,    34,    35,
      55,    37,   141,    39,    40,    41,    42,    37,    32,    33,
      34,    35,    46,    37,    50,    39,    40,    41,    42,   134,
      32,    33,    34,    35,   191,    37,    50,    39,    40,    41,
      42,    54,    32,    33,    34,    35,   105,    37,    50,    39,
      40,    41,    42,   107,    43,    44,    46,    32,    33,    34,
      35,   108,    37,   109,    39,    40,    41,    42,    32,    33,
      34,    35,   110,    56,    57,    39,    -1,    41,    42,    62,
     117,   118,    65,    66,   113,   114,   115,   116,   119,   120,
     122,   123
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    32,    33,    34,    35,    37,    39,    40,    41,    42,
      68,    69,    70,    71,    72,    73,    74,    90,    18,    49,
      73,    73,    33,     0,    70,    18,    45,    55,    79,    80,
      81,    82,    83,    75,    81,    37,    57,    60,    49,    56,
      91,    55,    83,    45,    47,    72,    76,    77,    46,    80,
      81,    50,    71,    72,    92,    93,    16,    17,    18,    19,
      20,    21,    44,    45,    49,    51,    64,    88,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     108,   109,   110,   112,    37,    46,    72,    84,    85,    20,
      78,    81,    50,    77,    50,    93,   110,   110,   110,    94,
      95,    88,    89,   110,   110,     8,    61,     9,    65,    53,
      54,    10,    11,    12,    13,    58,    59,    14,    15,    43,
      44,    52,    55,    62,     4,     5,     6,     7,    56,    16,
      17,    45,    47,    66,    45,    47,    81,    82,    86,    87,
      46,    60,    48,    57,    60,    46,    60,    50,    60,    98,
     108,    94,    99,   100,   101,   102,   103,   103,   104,   104,
     104,   104,   105,   105,   106,   106,   107,   108,   107,   107,
      95,    95,    95,    95,    95,    46,    95,   111,    94,    95,
      18,    46,    84,    86,    48,    45,    47,    85,    81,    95,
      88,    63,    46,    60,     1,    48,    46,    46,    46,    84,
      20,    96,    95,    46,    48
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    67,    68,    69,    69,    70,    70,    71,    72,    72,
      72,    73,    73,    73,    73,    73,    73,    73,    75,    74,
      74,    76,    76,    77,    78,    78,    79,    79,    80,    80,
      81,    81,    82,    82,    82,    82,    83,    83,    83,    83,
      83,    84,    84,    85,    85,    85,    86,    86,    87,    87,
      87,    87,    87,    87,    87,    88,    88,    89,    89,    90,
      91,    91,    92,    92,    93,    94,    94,    95,    95,    95,
      95,    95,    95,    96,    96,    97,    97,    98,    98,    99,
      99,   100,   100,   101,   101,   102,   102,   102,   103,   103,
     103,   103,   103,   104,   104,   104,   105,   105,   105,   106,
     106,   106,   106,   107,   108,   108,   109,   109,   109,   109,
     109,   110,   110,   110,   110,   110,   110,   110,   110,   111,
     111,   112,   112,   112,   112,   112
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     3,     1,     2,
       2,     1,     2,     1,     1,     1,     1,     1,     0,     5,
       2,     1,     2,     3,     1,     3,     1,     3,     1,     3,
       2,     1,     1,     2,     2,     3,     1,     4,     3,     3,
       4,     1,     3,     1,     2,     2,     1,     1,     4,     3,
       3,     4,     2,     2,     3,     3,     1,     1,     3,     3,
       2,     3,     1,     2,     1,     1,     3,     1,     3,     3,
       3,     3,     3,     1,     5,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     1,
       3,     3,     3,     1,     1,     1,     2,     2,     2,     2,
       2,     1,     2,     2,     4,     4,     3,     3,     4,     1,
       3,     1,     1,     1,     1,     3
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
#line 81 "cParser.y"
              {
            treeRoot = (yyvsp[0].globalDeclaraionNodePtr);
        }
#line 1568 "cParser.cpp"
    break;

  case 3:
#line 87 "cParser.y"
                          {
            (yyval.globalDeclaraionNodePtr) = new GlobalDeclaraionNode(dynamic_cast<StatementNodesBlock*>((yyvsp[0].statementNodesBlockPtr)));
        }
#line 1576 "cParser.cpp"
    break;

  case 4:
#line 90 "cParser.y"
                                {
            (yyval.globalDeclaraionNodePtr) = (yyvsp[-1].globalDeclaraionNodePtr);
            (yyval.globalDeclaraionNodePtr)->mergeGlobalStatements(dynamic_cast<GlobalDeclaraionNode*>((yyvsp[0].statementNodesBlockPtr)));
    }
#line 1585 "cParser.cpp"
    break;

  case 5:
#line 100 "cParser.y"
                    { /* 全局的变量定义，兼定义结构体。 */
            printf("global declaration\n");
            (yyval.statementNodesBlockPtr) = (yyvsp[0].statementNodesBlockPtr);
        }
#line 1594 "cParser.cpp"
    break;

  case 6:
#line 104 "cParser.y"
                            { /* 语法上，所有的函数都必须要定义在全局。 */
            (yyval.statementNodesBlockPtr) = new StatementNodesBlock(); 
            (yyval.statementNodesBlockPtr)->mStatementList.push_back(dynamic_cast<StatementNode*>((yyvsp[0].nodePtr)));
        }
#line 1603 "cParser.cpp"
    break;

  case 7:
#line 120 "cParser.y"
                                 { /* 定义变量 */
            (yyval.statementNodesBlockPtr) = new StatementNodesBlock();
            (yyval.statementNodesBlockPtr)->createMultiVarDeclaration(dynamic_cast<IdentifierNode *>((yyvsp[-2].identifierNodePtr)), dynamic_cast<IdentifierNodeList *>((yyvsp[-1].identifierNodeListPtr)));

        }
#line 1613 "cParser.cpp"
    break;

  case 8:
#line 144 "cParser.y"
                 {(yyval.identifierNodePtr) = (yyvsp[0].identifierNodePtr);}
#line 1619 "cParser.cpp"
    break;

  case 9:
#line 145 "cParser.y"
                       {(yyval.identifierNodePtr) = (yyvsp[0].identifierNodePtr);}
#line 1625 "cParser.cpp"
    break;

  case 10:
#line 146 "cParser.y"
                        {(yyval.identifierNodePtr) = (yyvsp[0].identifierNodePtr);}
#line 1631 "cParser.cpp"
    break;

  case 11:
#line 150 "cParser.y"
            { 
            (yyval.identifierNodePtr) = new IdentifierNode((yyvsp[0].nodePtr)->getTokenValue(), true);
            (yyval.identifierNodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1640 "cParser.cpp"
    break;

  case 12:
#line 154 "cParser.y"
                     { /* 不实现这一条 */}
#line 1646 "cParser.cpp"
    break;

  case 13:
#line 155 "cParser.y"
             { 
            (yyval.identifierNodePtr) = new IdentifierNode((yyvsp[0].nodePtr)->getTokenValue(), true);
            (yyval.identifierNodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1655 "cParser.cpp"
    break;

  case 14:
#line 159 "cParser.y"
              { /* 不实现这一条, 只支持double */
            (yyval.identifierNodePtr) = new IdentifierNode((yyvsp[0].nodePtr)->getTokenValue(), true);
            (yyval.identifierNodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1664 "cParser.cpp"
    break;

  case 15:
#line 163 "cParser.y"
               { 
            (yyval.identifierNodePtr) = new IdentifierNode((yyvsp[0].nodePtr)->getTokenValue(), true);
            (yyval.identifierNodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1673 "cParser.cpp"
    break;

  case 16:
#line 167 "cParser.y"
             { 
            (yyval.identifierNodePtr) = new IdentifierNode((yyvsp[0].nodePtr)->getTokenValue(), true);
            (yyval.identifierNodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1682 "cParser.cpp"
    break;

  case 17:
#line 171 "cParser.y"
                       { /* TODO */
            (yyval.identifierNodePtr) = new IdentifierNode((yyvsp[0].nodePtr)->getTokenValue(), true);
            (yyval.identifierNodePtr)->setType(Node::TYPE_STRUCT);
            (yyval.identifierNodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.identifierNodePtr)->setStructTypeName((yyvsp[0].nodePtr)->getStructTypeName());
            (yyval.identifierNodePtr)->setPosition((yyvsp[0].nodePtr));
        }
#line 1694 "cParser.cpp"
    break;

  case 18:
#line 183 "cParser.y"
                   {
            /* 为该匿名结构体维护符号表 */
            std::string name = nameCounter.getNumberedName("`Unamed_Structure");
            symbolTableStack->insert(new Attribute(name, Node::TYPE_STRUCT, Node::KIND_ATTRIBUTE, std::vector<Node::Type>(), std::vector<std::string>(), 
                                     std::vector<int>(), name, csLineCnt, csColumnCnt-1));
            symbolTableStack->push(new SymbolTable(name));
        }
#line 1706 "cParser.cpp"
    break;

  case 19:
#line 189 "cParser.y"
                                       {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("structTypeName"), 4, (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_STRUCT);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setStructTypeName(symbolTableStack->top()->getName());
            (yyval.nodePtr)->setPosition((yyvsp[-4].nodePtr));
            symbolTableStack->pop();
        }
#line 1719 "cParser.cpp"
    break;

  case 20:
#line 197 "cParser.y"
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
#line 1734 "cParser.cpp"
    break;

  case 21:
#line 211 "cParser.y"
                                {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("structMemberDeclarations"), 1, (yyvsp[0].nodePtr));
        }
#line 1742 "cParser.cpp"
    break;

  case 22:
#line 214 "cParser.y"
                                                         {
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 1751 "cParser.cpp"
    break;

  case 23:
#line 221 "cParser.y"
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
#line 1768 "cParser.cpp"
    break;

  case 24:
#line 236 "cParser.y"
                 {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("structMembers"), 1, (yyvsp[0].nodePtr));
        }
#line 1776 "cParser.cpp"
    break;

  case 25:
#line 239 "cParser.y"
                                   {
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[-1].nodePtr));
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 1786 "cParser.cpp"
    break;

  case 26:
#line 249 "cParser.y"
                       {
            (yyval.identifierNodeListPtr) = new IdentifierNodeList();
            (yyval.identifierNodeListPtr)->addIdentifierNode((yyvsp[0].identifierNodePtr));
        }
#line 1795 "cParser.cpp"
    break;

  case 27:
#line 253 "cParser.y"
                                           {
            (yyval.identifierNodeListPtr) = (yyvsp[-2].identifierNodeListPtr);
            (yyval.identifierNodeListPtr)->addIdentifierNode((yyvsp[0].identifierNodePtr));
        }
#line 1804 "cParser.cpp"
    break;

  case 28:
#line 260 "cParser.y"
                 {                       /* int a; 没有初始值 */
            (yyval.identifierNodePtr) = dynamic_cast<IdentifierNode*>((yyvsp[0].nodePtr));
        }
#line 1812 "cParser.cpp"
    break;

  case 29:
#line 263 "cParser.y"
                                  {   /* int a=10; 有初始值, 暂不实现 */
            /* $$ = new Node(nameCounter.getNumberedName("initialization"), 3, $1, $2, $3);
            $$->copyFromChild(); */
        }
#line 1821 "cParser.cpp"
    break;

  case 30:
#line 270 "cParser.y"
                                      {  /* int *a; 指针变量，这里不打算实现。 */
           // $$ = new Node(nameCounter.getNumberedName("variable"), 2, $1, $2);
        }
#line 1829 "cParser.cpp"
    break;

  case 31:
#line 273 "cParser.y"
                     { /* 不是指针的变量 */
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 1837 "cParser.cpp"
    break;

  case 32:
#line 280 "cParser.y"
            { /* a simple pointer */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("pointerSpecifier"), 1, (yyvsp[0].nodePtr));
        }
#line 1845 "cParser.cpp"
    break;

  case 33:
#line 283 "cParser.y"
                             { /* a pointer to another pointer variable */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("pointerSpecifier"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 1853 "cParser.cpp"
    break;

  case 34:
#line 286 "cParser.y"
                  { /* a pointer to a const variable */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("pointerSpecifier"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 1861 "cParser.cpp"
    break;

  case 35:
#line 289 "cParser.y"
                                   { /* a pointer to another pointer which is a pointer to a const value */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("pointerSpecifier"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 1869 "cParser.cpp"
    break;

  case 36:
#line 295 "cParser.y"
                   { /* 一个普通的变量 */
            (yyval.nodePtr) = (yyvsp[0].identifierNodePtr);
        }
#line 1877 "cParser.cpp"
    break;

  case 37:
#line 298 "cParser.y"
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
#line 1897 "cParser.cpp"
    break;

  case 38:
#line 313 "cParser.y"
                         {              /* 这一条弃之不用，太复杂了 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableName"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 1905 "cParser.cpp"
    break;

  case 39:
#line 316 "cParser.y"
                             {           /* 函数定义 */
           (yyval.nodePtr) = new FuncNameAndArgsNode(dynamic_cast<IdentifierNode *>((yyvsp[-2].nodePtr)), nullptr);
        }
#line 1913 "cParser.cpp"
    break;

  case 40:
#line 319 "cParser.y"
                                        {    /* 函数定义 */
            (yyval.nodePtr) = new FuncNameAndArgsNode(dynamic_cast<IdentifierNode *>((yyvsp[-3].nodePtr)), dynamic_cast<VarDeclarationList *>((yyvsp[-1].varDeclarationListPtr)));
        }
#line 1921 "cParser.cpp"
    break;

  case 41:
#line 325 "cParser.y"
                      {
            (yyval.varDeclarationListPtr) = new VarDeclarationList();
            (yyval.varDeclarationListPtr)->mVarDeclarationList.push_back(dynamic_cast<VariableDeclarationNode *>((yyvsp[0].nodePtr)));
        }
#line 1930 "cParser.cpp"
    break;

  case 42:
#line 329 "cParser.y"
                                     {
            (yyval.varDeclarationListPtr) = (yyvsp[-2].varDeclarationListPtr);
            (yyval.varDeclarationListPtr)->mVarDeclarationList.push_back(dynamic_cast<VariableDeclarationNode *>((yyvsp[0].nodePtr)));
        }
#line 1939 "cParser.cpp"
    break;

  case 43:
#line 336 "cParser.y"
             {   /* int (*f)(double,char); 不实现这一条，太复杂 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("paramTypeName"), 1, (yyvsp[0].identifierNodePtr));
        }
#line 1947 "cParser.cpp"
    break;

  case 44:
#line 339 "cParser.y"
                                { /* 无名字的指针变量。不实现这一条，天复杂 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("paramTypeName"), 2, (yyvsp[-1].identifierNodePtr), (yyvsp[0].nodePtr));
        }
#line 1955 "cParser.cpp"
    break;

  case 45:
#line 342 "cParser.y"
                      {      /* 这一条是要正常实现的，定义函数用的 */
            (yyval.nodePtr) = new VariableDeclarationNode(dynamic_cast<IdentifierNode *>((yyvsp[-1].identifierNodePtr)), dynamic_cast<IdentifierNode *>((yyvsp[0].nodePtr)));

        }
#line 1964 "cParser.cpp"
    break;

  case 46:
#line 350 "cParser.y"
                         {       /* 不实现指针 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoName"), 1, (yyvsp[0].nodePtr));
        }
#line 1972 "cParser.cpp"
    break;

  case 47:
#line 353 "cParser.y"
                               { 
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoName"), 1, (yyvsp[0].nodePtr));
        }
#line 1980 "cParser.cpp"
    break;

  case 48:
#line 360 "cParser.y"
                                                  {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 4, (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 1988 "cParser.cpp"
    break;

  case 49:
#line 363 "cParser.y"
                                   {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 1996 "cParser.cpp"
    break;

  case 50:
#line 366 "cParser.y"
                                       {  /* a function taking another function as param... */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2004 "cParser.cpp"
    break;

  case 51:
#line 369 "cParser.y"
                                                  { /* a function taking another function as param... */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 4, (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].varDeclarationListPtr), (yyvsp[0].nodePtr));
        }
#line 2012 "cParser.cpp"
    break;

  case 52:
#line 372 "cParser.y"
                {            /* because it has no name, it must stop some way. Below is some terminators */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2020 "cParser.cpp"
    break;

  case 53:
#line 375 "cParser.y"
                {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2028 "cParser.cpp"
    break;

  case 54:
#line 378 "cParser.y"
                           { /* a function taking another function as param... */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].varDeclarationListPtr), (yyvsp[0].nodePtr));
        }
#line 2036 "cParser.cpp"
    break;

  case 55:
#line 385 "cParser.y"
                              {          /* int a[10]={1}; 初始化列表 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("initialValue"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2044 "cParser.cpp"
    break;

  case 56:
#line 388 "cParser.y"
                             {          /* int a=5+6; int b=a=3; 普通的初始值 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("initialValue"), 1, (yyvsp[0].nodePtr));
    }
#line 2052 "cParser.cpp"
    break;

  case 57:
#line 395 "cParser.y"
                     {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("initialValues"), 1, (yyvsp[0].nodePtr));
        }
#line 2060 "cParser.cpp"
    break;

  case 58:
#line 398 "cParser.y"
                                       { /* int a[10]={1,2,3} */
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[-1].nodePtr));
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 2070 "cParser.cpp"
    break;

  case 59:
#line 407 "cParser.y"
                                      {
            (yyval.nodePtr) = new FunctionDeclarationNode(dynamic_cast<IdentifierNode *>((yyvsp[-2].identifierNodePtr)), dynamic_cast<FuncNameAndArgsNode *>((yyvsp[-1].nodePtr)), dynamic_cast<StatementNodesBlock*>((yyvsp[0].statementNodesBlockPtr)));
        }
#line 2078 "cParser.cpp"
    break;

  case 60:
#line 414 "cParser.y"
                { /* 可以 {} 这样而不必 {;} 这样 */
            (yyval.statementNodesBlockPtr) = new StatementNodesBlock();
            (yyval.statementNodesBlockPtr)->mStatementList.push_back(new NullStatementNode());
        }
#line 2087 "cParser.cpp"
    break;

  case 61:
#line 418 "cParser.y"
                           {
            (yyval.statementNodesBlockPtr) = (yyvsp[-1].statementNodesBlockPtr);
        }
#line 2095 "cParser.cpp"
    break;

  case 62:
#line 448 "cParser.y"
                  {
            (yyval.statementNodesBlockPtr) = (yyvsp[0].statementNodesBlockPtr);
        }
#line 2103 "cParser.cpp"
    break;

  case 63:
#line 451 "cParser.y"
                             {
            (yyval.statementNodesBlockPtr) = (yyvsp[-1].statementNodesBlockPtr);
            (yyval.statementNodesBlockPtr)->mergeStatements(dynamic_cast<StatementNodesBlock *>((yyvsp[0].statementNodesBlockPtr)));
        }
#line 2112 "cParser.cpp"
    break;

  case 64:
#line 458 "cParser.y"
                    {
            (yyval.statementNodesBlockPtr) = (yyvsp[0].statementNodesBlockPtr);
        }
#line 2120 "cParser.cpp"
    break;

  case 65:
#line 572 "cParser.y"
                             {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("expression"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->copyFrom((yyvsp[0].nodePtr));
        }
#line 2129 "cParser.cpp"
    break;

  case 66:
#line 576 "cParser.y"
                                            {
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[-1].nodePtr));
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
            /* 一串逗号分隔的表达式的值，是最后一个表达式的值。 */
            (yyval.nodePtr)->copyFrom((yyval.nodePtr)->getChildrenById((yyval.nodePtr)->getChildrenNumber()-1));
        }
#line 2141 "cParser.cpp"
    break;

  case 67:
#line 588 "cParser.y"
                                  {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2149 "cParser.cpp"
    break;

  case 68:
#line 591 "cParser.y"
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
#line 2165 "cParser.cpp"
    break;

  case 69:
#line 602 "cParser.y"
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
#line 2181 "cParser.cpp"
    break;

  case 70:
#line 613 "cParser.y"
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
#line 2197 "cParser.cpp"
    break;

  case 71:
#line 624 "cParser.y"
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
#line 2213 "cParser.cpp"
    break;

  case 72:
#line 635 "cParser.y"
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
#line 2229 "cParser.cpp"
    break;

  case 73:
#line 651 "cParser.y"
                            {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2237 "cParser.cpp"
    break;

  case 74:
#line 654 "cParser.y"
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
#line 2255 "cParser.cpp"
    break;

  case 75:
#line 672 "cParser.y"
                             {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2263 "cParser.cpp"
    break;

  case 76:
#line 675 "cParser.y"
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
#line 2278 "cParser.cpp"
    break;

  case 77:
#line 690 "cParser.y"
                            {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2286 "cParser.cpp"
    break;

  case 78:
#line 693 "cParser.y"
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
#line 2301 "cParser.cpp"
    break;

  case 79:
#line 708 "cParser.y"
                                     {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2309 "cParser.cpp"
    break;

  case 80:
#line 711 "cParser.y"
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
#line 2324 "cParser.cpp"
    break;

  case 81:
#line 726 "cParser.y"
                             {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2332 "cParser.cpp"
    break;

  case 82:
#line 729 "cParser.y"
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
#line 2347 "cParser.cpp"
    break;

  case 83:
#line 744 "cParser.y"
                                     {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2355 "cParser.cpp"
    break;

  case 84:
#line 747 "cParser.y"
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
#line 2370 "cParser.cpp"
    break;

  case 85:
#line 762 "cParser.y"
                                     {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2378 "cParser.cpp"
    break;

  case 86:
#line 765 "cParser.y"
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
#line 2396 "cParser.cpp"
    break;

  case 87:
#line 778 "cParser.y"
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
#line 2411 "cParser.cpp"
    break;

  case 88:
#line 793 "cParser.y"
                        {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2419 "cParser.cpp"
    break;

  case 89:
#line 796 "cParser.y"
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
#line 2437 "cParser.cpp"
    break;

  case 90:
#line 809 "cParser.y"
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
#line 2455 "cParser.cpp"
    break;

  case 91:
#line 822 "cParser.y"
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
#line 2473 "cParser.cpp"
    break;

  case 92:
#line 835 "cParser.y"
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
#line 2491 "cParser.cpp"
    break;

  case 93:
#line 853 "cParser.y"
                                {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2499 "cParser.cpp"
    break;

  case 94:
#line 856 "cParser.y"
                                                   {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFrom((yyvsp[-2].nodePtr));
            if(!(checkType((yyvsp[-2].nodePtr),Node::TYPE_INT)&&checkType((yyvsp[0].nodePtr),Node::TYPE_INT)) || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2512 "cParser.cpp"
    break;

  case 95:
#line 864 "cParser.y"
                                                    {
            (yyvsp[-1].nodePtr) = new BinaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFrom((yyvsp[-2].nodePtr));
            if(!(checkType((yyvsp[-2].nodePtr),Node::TYPE_INT)&&checkType((yyvsp[0].nodePtr),Node::TYPE_INT)) || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2525 "cParser.cpp"
    break;

  case 96:
#line 877 "cParser.y"
                                {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2533 "cParser.cpp"
    break;

  case 97:
#line 880 "cParser.y"
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
#line 2549 "cParser.cpp"
    break;

  case 98:
#line 891 "cParser.y"
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
#line 2565 "cParser.cpp"
    break;

  case 99:
#line 907 "cParser.y"
                        {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2573 "cParser.cpp"
    break;

  case 100:
#line 910 "cParser.y"
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
#line 2589 "cParser.cpp"
    break;

  case 101:
#line 921 "cParser.y"
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
#line 2605 "cParser.cpp"
    break;

  case 102:
#line 932 "cParser.y"
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
#line 2621 "cParser.cpp"
    break;

  case 103:
#line 949 "cParser.y"
                       {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2629 "cParser.cpp"
    break;

  case 104:
#line 964 "cParser.y"
                              {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2637 "cParser.cpp"
    break;

  case 105:
#line 967 "cParser.y"
                               {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2645 "cParser.cpp"
    break;

  case 106:
#line 973 "cParser.y"
                                   {/* ++a, especially ++a[i] is ++(a[i]) but not (++a)[i] */
            (yyvsp[-1].nodePtr) = new UnaryOperatorNode(std::string("pre")+(yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkKind((yyvsp[0].nodePtr), Node::KIND_VARIABLE) || (yyvsp[0].nodePtr)->isArray() || (yyvsp[0].nodePtr)->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError((yyvsp[0].nodePtr),(yyvsp[-1].nodePtr));
            }
        }
#line 2658 "cParser.cpp"
    break;

  case 107:
#line 981 "cParser.y"
                                   {/* --a, the same as ++a[i] */
            (yyvsp[-1].nodePtr) = new UnaryOperatorNode(std::string("pre")+(yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkKind((yyvsp[0].nodePtr), Node::KIND_VARIABLE) || (yyvsp[0].nodePtr)->isArray() || (yyvsp[0].nodePtr)->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError((yyvsp[0].nodePtr),(yyvsp[-1].nodePtr));
            }
        }
#line 2671 "cParser.cpp"
    break;

  case 108:
#line 989 "cParser.y"
                                   {/* logical NOT */
            (yyvsp[-1].nodePtr) = new UnaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkType((yyvsp[0].nodePtr), Node::TYPE_INT)){
                error_expressionTypeError((yyvsp[0].nodePtr),(yyvsp[-1].nodePtr));
            }
        }
#line 2684 "cParser.cpp"
    break;

  case 109:
#line 997 "cParser.y"
                                   {/* bitwise NOT */
            (yyvsp[-1].nodePtr) = new UnaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkType((yyvsp[0].nodePtr), Node::TYPE_INT)){
                error_expressionTypeError((yyvsp[0].nodePtr),(yyvsp[-1].nodePtr));
            }
        }
#line 2697 "cParser.cpp"
    break;

  case 110:
#line 1005 "cParser.y"
                                   {/* negative */
            (yyvsp[-1].nodePtr) = new UnaryOperatorNode((yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            if(checkType((yyvsp[0].nodePtr), Node::TYPE_STRUCT)){
                error_expressionTypeError((yyvsp[0].nodePtr),(yyvsp[-1].nodePtr));
            }
        }
#line 2709 "cParser.cpp"
    break;

  case 111:
#line 1015 "cParser.y"
                         {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2717 "cParser.cpp"
    break;

  case 112:
#line 1018 "cParser.y"
                                   {/* a++, espetially a[i]++ is allowed, (a[i])++ is not necessary */
            (yyvsp[0].nodePtr) = new UnaryOperatorNode(std::string("post")+(yyvsp[0].nodePtr)->getName(), 1, (yyvsp[-1].nodePtr));
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkKind((yyvsp[-1].nodePtr), Node::KIND_VARIABLE) || (yyvsp[-1].nodePtr)->isArray() || (yyvsp[-1].nodePtr)->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError((yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2730 "cParser.cpp"
    break;

  case 113:
#line 1026 "cParser.y"
                                   {/* a-- */
            (yyvsp[0].nodePtr) = new UnaryOperatorNode(std::string("post")+(yyvsp[0].nodePtr)->getName(), 1, (yyvsp[-1].nodePtr));
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkKind((yyvsp[-1].nodePtr), Node::KIND_VARIABLE) || (yyvsp[-1].nodePtr)->isArray() || (yyvsp[-1].nodePtr)->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError((yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2743 "cParser.cpp"
    break;

  case 114:
#line 1034 "cParser.y"
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
#line 2763 "cParser.cpp"
    break;

  case 115:
#line 1049 "cParser.y"
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
                    (dynamic_cast<FunctionCallNode *>((yyval.nodePtr)))->addArgument(child);
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
#line 2797 "cParser.cpp"
    break;

  case 116:
#line 1078 "cParser.y"
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
#line 2813 "cParser.cpp"
    break;

  case 117:
#line 1089 "cParser.y"
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
#line 2834 "cParser.cpp"
    break;

  case 118:
#line 1111 "cParser.y"
                                                     {
            error_missingRightBrancket2();
        }
#line 2842 "cParser.cpp"
    break;

  case 119:
#line 1117 "cParser.y"
                             {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("paramList"), 1, (yyvsp[0].nodePtr));
        }
#line 2850 "cParser.cpp"
    break;

  case 120:
#line 1120 "cParser.y"
                                           {/* 这里面不能填 expression，因为 expression 也是用逗号隔开的一串表达式 */
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[-1].nodePtr));
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 2860 "cParser.cpp"
    break;

  case 121:
#line 1130 "cParser.y"
                   {
            (yyval.nodePtr) = (yyvsp[0].identifierNodePtr);
            /* if(!symbolTableStack->lookUp($1->getTokenValue()())){
                error_variableNotDeclared($1->getTokenValue()());
                $$->setKind(Node::KIND_VARIABLE);
                $$->setType(Node::TYPE_INT);
            }else{
                $$->setAttribute(symbolTableStack->lookUp($1->getTokenValue()()));
                $$->setPosition(csLineCnt, csColumnCnt);
            } */
        }
#line 2876 "cParser.cpp"
    break;

  case 122:
#line 1141 "cParser.y"
                      {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2884 "cParser.cpp"
    break;

  case 123:
#line 1144 "cParser.y"
                   {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2892 "cParser.cpp"
    break;

  case 124:
#line 1147 "cParser.y"
               { /* 这个就不实现了吧 */
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2900 "cParser.cpp"
    break;

  case 125:
#line 1150 "cParser.y"
                           {
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
        }
#line 2908 "cParser.cpp"
    break;


#line 2912 "cParser.cpp"

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
#line 1156 "cParser.y"

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
static void error_illegalArraySize(Node * c){
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
static void error_returnValueTypeMismatch(Attribute* need, Node * give){
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

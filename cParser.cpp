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

#line 246 "cParser.cpp"

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
#define YYFINAL  86
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   717

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  166
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  307

#define YYUNDEFTOK  2
#define YYMAXUTOK   296


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
       2,     2,     2,    63,     2,     2,     2,    51,    53,     2,
      44,    45,    54,    42,    59,    43,    65,    61,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    62,    56,
      57,    55,    58,    60,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    46,     2,    47,    52,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,    64,    49,    50,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    58,    58,    64,    67,    77,    80,    83,    87,    95,
     110,   110,   122,   128,   132,   135,   141,   147,   153,   159,
     165,   171,   177,   189,   189,   203,   217,   220,   227,   242,
     245,   255,   258,   266,   270,   277,   280,   288,   291,   294,
     297,   303,   309,   324,   327,   333,   355,   358,   366,   369,
     372,   381,   384,   391,   394,   397,   400,   403,   406,   409,
     416,   419,   426,   429,   438,   438,   471,   474,   477,   480,
     483,   490,   493,   500,   503,   510,   513,   516,   516,   522,
     525,   528,   534,   537,   540,   546,   549,   552,   555,   555,
     556,   556,   563,   566,   569,   570,   577,   582,   583,   588,
     595,   603,   606,   609,   620,   624,   636,   639,   650,   661,
     672,   683,   699,   702,   720,   723,   738,   741,   756,   759,
     774,   777,   792,   795,   810,   813,   826,   841,   844,   857,
     870,   883,   901,   904,   912,   925,   928,   939,   955,   958,
     969,   980,   997,  1000,  1003,  1012,  1015,  1021,  1029,  1037,
    1045,  1053,  1063,  1066,  1074,  1082,  1097,  1125,  1136,  1152,
    1157,  1163,  1166,  1176,  1187,  1190,  1193
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "GOTO", "ADD_ASSIGN", "SUB_ASSIGN",
  "MUL_ASSIGN", "DIV_ASSIGN", "LOGICAL_OR", "LOGICAL_AND", "EQ", "NE",
  "GE", "LE", "SL", "SR", "INC", "DEC", "IDENTIFIER", "NUMBER", "STRING",
  "FOR", "DO", "WHILE", "CONTINUE", "BREAK", "IF", "ELSE", "SWITCH",
  "CASE", "RETURN", "STRUCT", "INT", "DOUBLE", "CHAR", "PTR", "CONST",
  "DEFAULT", "FLOAT", "STATIC", "UNSIGNED", "VOID", "'+'", "'-'", "'('",
  "')'", "'['", "']'", "'{'", "'}'", "'~'", "'%'", "'^'", "'&'", "'*'",
  "'='", "';'", "'<'", "'>'", "','", "'?'", "'/'", "':'", "'!'", "'|'",
  "'.'", "$accept", "cCode0", "cCode", "globalDeclaration", "declaration",
  "$@1", "type", "typeName", "structTypeName", "$@2",
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
     295,   296,    43,    45,    40,    41,    91,    93,   123,   125,
     126,    37,    94,    38,    42,    61,    59,    60,    62,    44,
      63,    47,    58,    33,   124,    46
};
# endif

#define YYPACT_NINF (-196)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-78)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     297,     9,    52,   156,   156,  -196,  -196,  -196,    30,    38,
      56,    87,    92,   111,   126,   145,    19,  -196,  -196,  -196,
     676,  -196,   676,   162,  -196,   156,   555,  -196,   156,  -196,
     156,   214,   247,  -196,  -196,   127,  -196,  -196,  -196,  -196,
     151,  -196,  -196,  -196,  -196,    33,  -196,  -196,    23,   235,
     212,   204,   271,   117,    64,   164,   218,    85,   113,  -196,
      88,  -196,    38,  -196,   196,    88,    88,   199,   303,    94,
    -196,  -196,   555,   555,  -196,   131,   284,  -196,    32,  -196,
    -196,  -196,    88,    26,    88,    88,  -196,  -196,  -196,   127,
     313,    47,  -196,    -6,   129,   161,   347,  -196,  -196,  -196,
     555,   555,   555,   555,   555,   555,   555,   555,   555,   555,
     555,   555,   555,   555,   555,   555,   555,   569,   569,   569,
     555,   555,   555,   555,   555,  -196,  -196,   316,   438,   555,
     321,  -196,  -196,   199,   307,  -196,    39,    95,   137,  -196,
     308,   665,  -196,  -196,   314,  -196,  -196,  -196,   127,   547,
     151,   325,   161,   635,   343,  -196,  -196,   127,   397,   447,
    -196,  -196,   235,  -196,   249,   212,   204,   271,   117,    64,
      64,   164,   164,   164,   164,   218,   218,    85,    85,   518,
    -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,
    -196,  -196,   152,    37,   327,  -196,   555,   555,   331,  -196,
      38,    38,   334,   665,   127,   189,  -196,  -196,  -196,   329,
     547,  -196,  -196,  -196,  -196,  -196,   112,   167,  -196,   342,
    -196,  -196,   497,  -196,  -196,   555,   298,  -196,   555,  -196,
    -196,   187,   192,    38,   348,  -196,   365,    78,  -196,   623,
     253,  -196,  -196,  -196,  -196,   225,   589,   352,  -196,   129,
    -196,   248,  -196,   665,  -196,    75,  -196,  -196,   606,   569,
     340,   356,  -196,    38,   346,  -196,    38,    38,   555,   344,
     355,   349,  -196,   127,  -196,   547,  -196,   194,   362,  -196,
     650,   389,  -196,  -196,  -196,   569,  -196,  -196,  -196,  -196,
     350,    38,  -196,  -196,  -196,  -196,  -196,  -196,  -196,   200,
     364,  -196,    38,  -196,  -196,  -196,  -196
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,   163,   164,   165,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    16,    20,    18,
       0,    19,     0,     0,    21,     0,     0,     8,     0,    82,
       0,     0,     0,     3,     5,     0,    13,    22,     6,     7,
       0,    75,    76,    79,    80,     0,   104,   106,   112,   114,
     116,   118,   120,   122,   124,   127,   132,   135,   138,   145,
     146,   152,     0,    81,     0,   147,   148,     0,     0,     0,
     101,   102,     0,     0,    99,     0,    25,    23,     0,    14,
      15,    17,   151,     0,   150,   149,     1,     4,    41,     0,
      37,     0,    31,    33,     0,    36,     0,    78,    84,    83,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   153,   154,     0,     0,     0,
       0,    95,   103,     0,     0,    90,     0,     0,     0,   100,
       0,     0,    25,   166,     0,    39,    12,     9,     0,     0,
       0,    38,    35,     0,     0,    66,    71,     0,     0,     0,
      73,   105,   115,   138,     0,   117,   119,   121,   123,   125,
     126,   131,   130,   128,   129,   133,   134,   136,   137,     0,
     141,   142,   139,   140,   108,   109,   110,   111,   107,   159,
     157,   161,     0,     0,   104,   158,     0,     0,     0,    88,
       0,     0,     0,     0,     0,     0,    26,    43,    32,    33,
       0,    34,    61,    65,    40,    44,    48,     0,    46,     0,
      68,    72,     0,    67,    74,     0,     0,   156,     0,   160,
     155,     0,     0,     0,     0,    86,    92,     0,    94,     0,
       0,    29,    24,    27,    62,     0,     0,     0,    50,    51,
      49,    52,    45,     0,    42,     0,    69,   113,     0,     0,
      51,     0,   162,     0,     0,    91,     0,     0,     0,     0,
       0,     0,    28,     0,    60,     0,    58,     0,     0,    57,
       0,     0,    47,    70,   143,     0,    85,    87,    89,    93,
       0,     0,    96,    11,    30,    63,    59,    54,    55,     0,
       0,   144,     0,    98,    56,    53,    97
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -196,  -196,  -196,   377,   -67,  -196,     1,   213,  -196,  -196,
     221,  -170,  -196,  -196,   278,   -32,  -117,   -72,  -128,   179,
      73,  -196,  -182,  -196,  -196,  -196,   289,  -196,   276,    -9,
    -196,   -43,  -196,  -196,  -196,  -196,  -196,  -196,  -196,     6,
     -77,  -195,  -196,   341,   358,   339,   354,   338,   250,   195,
     188,   239,   -92,   -99,  -196,   206,  -196,  -196
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    31,    32,    33,    34,   140,   216,    36,    37,   141,
     205,   206,   240,    91,    92,   144,    94,    95,   277,   218,
     278,   251,   211,   245,    38,   150,    97,   158,   159,    39,
      40,    41,    42,   234,   198,    43,   238,   270,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,   180,    58,    59,    60,   192,    61
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      68,    35,   163,    93,   163,   163,   163,   163,   163,   163,
     163,   163,   163,   163,   163,   163,   163,   163,   181,   181,
     181,    75,   152,   161,   133,   217,   182,   183,   244,   156,
     257,   101,    83,    35,    98,   243,    62,    76,   229,     1,
     199,     2,   -64,   184,   185,   186,   187,   188,   146,   149,
     142,   191,   194,   131,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    63,    14,    77,    15,   243,
      64,   143,   212,   290,    67,   136,   109,   110,   137,   138,
      77,    25,    26,   102,   200,   100,   -77,   160,    28,    99,
     196,   221,   100,   295,    29,   135,   100,   157,   100,   249,
      69,    30,    62,   147,   125,   126,   148,   268,   164,   260,
       3,     4,     5,     6,     7,   269,   209,   120,   121,   122,
     123,   111,   112,   127,   283,   209,   163,   107,   108,   249,
      88,    63,   128,   212,   129,   193,   117,    25,    26,   118,
     201,   260,   204,    70,    28,    88,   119,    88,    71,   160,
     224,   262,   299,   130,   100,    72,   246,    30,   247,   157,
     181,     3,     4,     5,     6,     7,    90,   284,   124,   163,
      73,    89,   241,    89,     5,     6,     7,   152,   113,   114,
     226,    90,   202,   151,   248,    83,   181,   139,    25,    26,
     100,   235,   236,   301,    81,    28,   100,   227,   212,    96,
      26,    74,   231,   232,   204,   153,   204,   154,    30,    65,
      66,   228,   252,   224,    86,     3,     4,     5,     6,     7,
      78,    17,    18,    19,   265,    20,   253,    21,    22,    23,
      24,    82,   263,    79,    84,    80,    85,   264,   242,   296,
     204,   294,    25,    26,   103,   304,   100,    -2,     1,    28,
       2,   100,   132,   253,   286,    29,   105,   288,   289,   253,
     115,   116,    30,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   274,    14,   104,    15,    16,    17,
      18,    19,   303,    20,   275,    21,    22,    23,    24,   250,
      25,    26,   280,   306,   281,   -77,    27,    28,     1,   261,
       2,   175,   176,    29,   171,   172,   173,   174,   100,   272,
      30,   225,   273,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   106,    14,   134,    15,    16,    17,
      18,    19,   -10,    20,   189,    21,    22,    23,    24,   195,
      25,    26,   258,   259,   247,   -77,    27,    28,     1,   145,
       2,   197,    90,    29,   177,   178,   203,   169,   170,   207,
      30,   214,   219,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   230,    14,   233,    15,    16,    17,
      18,    19,   237,    20,   149,    21,    22,    23,    24,   254,
      25,    26,   267,   266,   151,   -77,   155,    28,     1,   279,
       2,   285,   287,    29,   292,   293,   291,   297,   300,    87,
      30,   305,   302,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,   239,    14,   208,    15,    16,    17,
      18,    19,   282,    20,   222,    21,    22,    23,    24,   213,
      25,    26,   162,   166,   168,   -77,   220,    28,     1,     0,
       2,     0,     0,    29,     3,     4,     5,     6,     7,   167,
      30,   165,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,    14,     0,    15,     0,     0,
       0,    25,    26,   190,     0,     0,     0,     0,    28,     0,
      25,    26,     0,     0,     0,   -77,   223,    28,   255,     0,
       2,    30,     0,    29,     0,     0,     0,     0,     0,     0,
      30,     0,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,    14,     0,    15,     0,     0,
       0,     0,     0,     0,     3,     4,     5,     6,     7,     0,
      25,    26,     0,     0,     0,   -77,   256,    28,     0,    78,
      17,    18,    19,    29,    20,     0,    21,    22,    23,    24,
      30,    25,    26,     3,     4,     5,     6,     7,    28,     0,
       0,     3,     4,     5,     6,     7,     0,     0,     0,     0,
       0,    30,     0,     0,     0,     3,     4,     5,     6,     7,
      25,    26,     0,     0,     0,   210,     0,    28,    25,    26,
       0,     0,     0,     0,     0,    28,     0,    88,     0,     0,
      30,     0,    25,   179,     0,     0,     0,     0,    30,    28,
      78,    17,    18,    19,     0,    20,     0,    21,    22,    23,
      24,     0,    30,   246,   276,   247,     0,    78,    17,    18,
      19,     0,    20,    90,    21,    22,    23,    24,     0,     0,
     258,   276,   247,     0,    78,    17,    18,    19,     0,    20,
      90,    21,    22,    23,    24,     0,    78,    17,    18,    19,
       0,    20,   271,    21,    22,    23,    24,     0,     0,     0,
     215,    78,    17,    18,    19,     0,    20,     0,    21,    22,
      23,    24,     0,     0,     0,   298,    78,    17,    18,    19,
       0,    20,     0,    21,    22,    23,    24,    78,    17,    18,
      19,     0,     0,     0,    21,     0,    23,    24
};

static const yytype_int16 yycheck[] =
{
       9,     0,   101,    35,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,    15,    94,   100,    67,   153,   118,   119,   210,    96,
     225,     8,    26,    32,     1,   205,    27,    18,     1,     1,
       1,     3,    48,   120,   121,   122,   123,   124,     1,    55,
      18,   128,   129,    62,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    56,    28,    48,    30,   239,
      18,    45,   149,   268,    44,    69,    12,    13,    72,    73,
      48,    43,    44,    60,    45,    59,    48,    96,    50,    56,
     133,   158,    59,   275,    56,     1,    59,    96,    59,   216,
      44,    63,    27,    56,    16,    17,    59,    29,   102,   226,
      16,    17,    18,    19,    20,    37,   148,     4,     5,     6,
       7,    57,    58,    35,    49,   157,   225,    10,    11,   246,
      18,    56,    44,   210,    46,   129,    51,    43,    44,    54,
      45,   258,   141,    56,    50,    18,    61,    18,    56,   158,
     159,   228,   280,    65,    59,    44,    44,    63,    46,   158,
     259,    16,    17,    18,    19,    20,    54,   259,    55,   268,
      44,    44,   204,    44,    18,    19,    20,   249,    14,    15,
     179,    54,    45,    54,   216,   179,   285,    56,    43,    44,
      59,   200,   201,   285,    32,    50,    59,    45,   275,    48,
      44,    56,   196,   197,   203,    44,   205,    46,    63,     3,
       4,    59,    45,   222,     0,    16,    17,    18,    19,    20,
      31,    32,    33,    34,   233,    36,    59,    38,    39,    40,
      41,    25,    45,    20,    28,    22,    30,    45,    49,    45,
     239,   273,    43,    44,     9,    45,    59,     0,     1,    50,
       3,    59,    56,    59,   263,    56,    52,   266,   267,    59,
      42,    43,    63,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    49,    28,    64,    30,    31,    32,
      33,    34,   291,    36,    59,    38,    39,    40,    41,   216,
      43,    44,    44,   302,    46,    48,    49,    50,     1,   226,
       3,   113,   114,    56,   109,   110,   111,   112,    59,    56,
      63,    62,    59,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    53,    28,    23,    30,    31,    32,
      33,    34,    48,    36,    18,    38,    39,    40,    41,    18,
      43,    44,    44,    45,    46,    48,    49,    50,     1,    36,
       3,    44,    54,    56,   115,   116,    48,   107,   108,    45,
      63,    36,    19,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    47,    28,    45,    30,    31,    32,
      33,    34,    48,    36,    55,    38,    39,    40,    41,    47,
      43,    44,    27,    45,    54,    48,    49,    50,     1,    47,
       3,    45,    56,    56,    49,    56,    62,    45,    19,    32,
      63,    47,    62,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,   203,    28,   148,    30,    31,    32,
      33,    34,   253,    36,   158,    38,    39,    40,    41,   150,
      43,    44,   101,   104,   106,    48,    49,    50,     1,    -1,
       3,    -1,    -1,    56,    16,    17,    18,    19,    20,   105,
      63,   103,    -1,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    28,    -1,    30,    -1,    -1,
      -1,    43,    44,    45,    -1,    -1,    -1,    -1,    50,    -1,
      43,    44,    -1,    -1,    -1,    48,    49,    50,     1,    -1,
       3,    63,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      63,    -1,    -1,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    28,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    16,    17,    18,    19,    20,    -1,
      43,    44,    -1,    -1,    -1,    48,    49,    50,    -1,    31,
      32,    33,    34,    56,    36,    -1,    38,    39,    40,    41,
      63,    43,    44,    16,    17,    18,    19,    20,    50,    -1,
      -1,    16,    17,    18,    19,    20,    -1,    -1,    -1,    -1,
      -1,    63,    -1,    -1,    -1,    16,    17,    18,    19,    20,
      43,    44,    -1,    -1,    -1,    48,    -1,    50,    43,    44,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    18,    -1,    -1,
      63,    -1,    43,    44,    -1,    -1,    -1,    -1,    63,    50,
      31,    32,    33,    34,    -1,    36,    -1,    38,    39,    40,
      41,    -1,    63,    44,    45,    46,    -1,    31,    32,    33,
      34,    -1,    36,    54,    38,    39,    40,    41,    -1,    -1,
      44,    45,    46,    -1,    31,    32,    33,    34,    -1,    36,
      54,    38,    39,    40,    41,    -1,    31,    32,    33,    34,
      -1,    36,    49,    38,    39,    40,    41,    -1,    -1,    -1,
      45,    31,    32,    33,    34,    -1,    36,    -1,    38,    39,
      40,    41,    -1,    -1,    -1,    45,    31,    32,    33,    34,
      -1,    36,    -1,    38,    39,    40,    41,    31,    32,    33,
      34,    -1,    -1,    -1,    38,    -1,    40,    41
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    28,    30,    31,    32,    33,    34,
      36,    38,    39,    40,    41,    43,    44,    49,    50,    56,
      63,    67,    68,    69,    70,    72,    73,    74,    90,    95,
      96,    97,    98,   101,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   119,   120,
     121,   123,    27,    56,    18,   121,   121,    44,    95,    44,
      56,    56,    44,    44,    56,   105,    18,    48,    31,    73,
      73,    32,   121,   105,   121,   121,     0,    69,    18,    44,
      54,    79,    80,    81,    82,    83,    48,    92,     1,    56,
      59,     8,    60,     9,    64,    52,    53,    10,    11,    12,
      13,    57,    58,    14,    15,    42,    43,    51,    54,    61,
       4,     5,     6,     7,    55,    16,    17,    35,    44,    46,
      65,    95,    56,    97,    23,     1,   105,   105,   105,    56,
      71,    75,    18,    45,    81,    36,     1,    56,    59,    55,
      91,    54,    83,    44,    46,    49,    70,    72,    93,    94,
      95,   106,   109,   119,   105,   110,   111,   112,   113,   114,
     114,   115,   115,   115,   115,   116,   116,   117,   117,    44,
     118,   119,   118,   118,   106,   106,   106,   106,   106,    18,
      45,   106,   122,   105,   106,    18,    97,    44,   100,     1,
      45,    45,    45,    48,    72,    76,    77,    45,    80,    81,
      48,    88,   106,    92,    36,    45,    72,    84,    85,    19,
      49,    70,    94,    49,    95,    62,    72,    45,    59,     1,
      47,   105,   105,    45,    99,    95,    95,    48,   102,    76,
      78,    81,    49,    77,    88,    89,    44,    46,    81,    82,
      86,    87,    45,    59,    47,     1,    49,   107,    44,    45,
      82,    86,   106,    45,    45,    95,    45,    27,    29,    37,
     103,    49,    56,    59,    49,    59,    45,    84,    86,    47,
      44,    46,    85,    49,   118,    45,    95,    56,    95,    95,
     107,    62,    49,    56,    81,    88,    45,    45,    45,    84,
      19,   118,    62,    95,    45,    47,    95
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    66,    67,    68,    68,    69,    69,    69,    69,    70,
      71,    70,    70,    72,    72,    72,    73,    73,    73,    73,
      73,    73,    73,    75,    74,    74,    76,    76,    77,    78,
      78,    79,    79,    80,    80,    81,    81,    82,    82,    82,
      82,    83,    83,    83,    83,    83,    84,    84,    85,    85,
      85,    86,    86,    87,    87,    87,    87,    87,    87,    87,
      88,    88,    89,    89,    91,    90,    92,    92,    92,    92,
      92,    93,    93,    94,    94,    95,    95,    96,    95,    95,
      95,    95,    97,    97,    97,    98,    98,    98,    99,    98,
     100,    98,   101,   101,   101,   101,   102,   103,   103,   104,
     104,   104,   104,   104,   105,   105,   106,   106,   106,   106,
     106,   106,   107,   107,   108,   108,   109,   109,   110,   110,
     111,   111,   112,   112,   113,   113,   113,   114,   114,   114,
     114,   114,   115,   115,   115,   116,   116,   116,   117,   117,
     117,   117,   118,   118,   118,   119,   119,   120,   120,   120,
     120,   120,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   122,   122,   123,   123,   123,   123
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
       3,     3,     1,     4,     5,     1,     1,     2,     2,     2,
       2,     2,     1,     2,     2,     4,     4,     3,     3,     3,
       4,     1,     3,     1,     1,     1,     3
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
#line 58 "cParser.y"
              {
            treeRoot = (yyvsp[0].nodePtr);
        }
#line 1733 "cParser.cpp"
    break;

  case 3:
#line 64 "cParser.y"
                          {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("cCode"), 1, (yyvsp[0].nodePtr));
        }
#line 1741 "cParser.cpp"
    break;

  case 4:
#line 67 "cParser.y"
                                {
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
    }
#line 1750 "cParser.cpp"
    break;

  case 5:
#line 77 "cParser.y"
                    { /* 全局的变量定义，兼定义结构体。 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("globalDeclaration"), 1, (yyvsp[0].nodePtr));
        }
#line 1758 "cParser.cpp"
    break;

  case 6:
#line 80 "cParser.y"
                            { /* 语法上，所有的函数都必须要定义在全局。 */ 
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("globalDeclaration"), 1, (yyvsp[0].nodePtr));
        }
#line 1766 "cParser.cpp"
    break;

  case 7:
#line 83 "cParser.y"
                  { /* 不允许在全局范围内出现不是定义的语句。 */
            yyerror("syntax error");
            std::cout<<"C only supports statements within a function.\n";
        }
#line 1775 "cParser.cpp"
    break;

  case 8:
#line 87 "cParser.y"
            {
            yyerror("syntax error");
            std::cout<<"a '}' without its '{'.\n";
        }
#line 1784 "cParser.cpp"
    break;

  case 9:
#line 95 "cParser.y"
                                 { /* 定义变量 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("declaration"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            for(int i=0;i<(yyvsp[-1].nodePtr)->getChildrenNumber();i++){
                Node *child = (yyvsp[-1].nodePtr)->getChildrenById(i);
                //child->setType($1->getType());
                child->setType((yyvsp[-2].nodePtr));
            }
            for(int i=0;i<(yyvsp[-1].nodePtr)->getChildrenNumber();i++){
                Node *child = (yyvsp[-1].nodePtr)->getChildrenById(i);
                if(child->isTerminal() && child->getTokenValue().compare({","})==0)continue;
                if(symbolTableStack->insert(new Attribute(child)) == false){// insert fault.
                    error_duplicatedVariable(child);
                }
            }
        }
#line 1804 "cParser.cpp"
    break;

  case 10:
#line 110 "cParser.y"
                          { /* 定义结构体 */
            /* 取得结构体名之后，即使为该结构体构建符号表 */
            (yyvsp[0].nodePtr)->setType(Node::TYPE_STRUCT);
            (yyvsp[0].nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyvsp[0].nodePtr)->setStructTypeName((yyvsp[0].nodePtr)->getTokenValue());
            (yyvsp[0].nodePtr)->setVariableName((yyvsp[0].nodePtr)->getTokenValue());
            symbolTableStack->insert(new Attribute((yyvsp[0].nodePtr)));
            symbolTableStack->push(new SymbolTable((yyvsp[0].nodePtr)->getStructTypeName()));
        }
#line 1818 "cParser.cpp"
    break;

  case 11:
#line 118 "cParser.y"
                                               {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("declaration"), 6, (yyvsp[-6].nodePtr), (yyvsp[-5].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            symbolTableStack->pop();
        }
#line 1827 "cParser.cpp"
    break;

  case 12:
#line 122 "cParser.y"
                                    {
            error_missingSemicolon();
        }
#line 1835 "cParser.cpp"
    break;

  case 13:
#line 128 "cParser.y"
                 {           /* int */
            (yyval.nodePtr) = new AttributivedNode(nameCounter.getNumberedName("type"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->copyFromChild();
        }
#line 1844 "cParser.cpp"
    break;

  case 14:
#line 132 "cParser.y"
                       {     /* const int，不实现这一条。 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("type"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 1852 "cParser.cpp"
    break;

  case 15:
#line 135 "cParser.y"
                        {    /* static int，不实现这一条。 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("type"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 1860 "cParser.cpp"
    break;

  case 16:
#line 141 "cParser.y"
            { 
            (yyval.nodePtr) = new AttributivedNode(nameCounter.getNumberedName("typeName"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1871 "cParser.cpp"
    break;

  case 17:
#line 147 "cParser.y"
                     { /* 不实现这一条 */
            (yyval.nodePtr) = new AttributivedNode(nameCounter.getNumberedName("typeName"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1882 "cParser.cpp"
    break;

  case 18:
#line 153 "cParser.y"
             { 
            (yyval.nodePtr) = new AttributivedNode(nameCounter.getNumberedName("typeName"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_CHAR);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1893 "cParser.cpp"
    break;

  case 19:
#line 159 "cParser.y"
              { /* 不实现这一条 */
            (yyval.nodePtr) = new AttributivedNode(nameCounter.getNumberedName("typeName"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_FLOAT);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1904 "cParser.cpp"
    break;

  case 20:
#line 165 "cParser.y"
               { 
            (yyval.nodePtr) = new AttributivedNode(nameCounter.getNumberedName("typeName"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_DOUBLE);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1915 "cParser.cpp"
    break;

  case 21:
#line 171 "cParser.y"
             { 
            (yyval.nodePtr) = new AttributivedNode(nameCounter.getNumberedName("typeName"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_VOID);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 1926 "cParser.cpp"
    break;

  case 22:
#line 177 "cParser.y"
                       { 
            (yyval.nodePtr) = new AttributivedNode(nameCounter.getNumberedName("typeName"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_STRUCT);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setStructTypeName((yyvsp[0].nodePtr)->getStructTypeName());
            (yyval.nodePtr)->setPosition((yyvsp[0].nodePtr));
        }
#line 1938 "cParser.cpp"
    break;

  case 23:
#line 189 "cParser.y"
                   {
            /* 为该匿名结构体维护符号表 */
            std::string name = nameCounter.getNumberedName("`Unamed_Structure");
            symbolTableStack->insert(new Attribute(name, Node::TYPE_STRUCT, Node::KIND_ATTRIBUTE, std::vector<Node::Type>(), std::vector<std::string>(), 
                                     std::vector<int>(), name, csLineCnt, csColumnCnt-1));
            symbolTableStack->push(new SymbolTable(name));
        }
#line 1950 "cParser.cpp"
    break;

  case 24:
#line 195 "cParser.y"
                                       {
            (yyval.nodePtr) = new AttributivedNode(nameCounter.getNumberedName("structTypeName"), 4, (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_STRUCT);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setStructTypeName(symbolTableStack->top()->getName());
            (yyval.nodePtr)->setPosition((yyvsp[-4].nodePtr));
            symbolTableStack->pop();
        }
#line 1963 "cParser.cpp"
    break;

  case 25:
#line 203 "cParser.y"
                          { /* 一个之前已经定义过的结构体名字。 */
            (yyval.nodePtr) = new AttributivedNode(nameCounter.getNumberedName("structTypeName"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType(Node::TYPE_STRUCT);
            (yyval.nodePtr)->setKind(Node::KIND_ATTRIBUTE);
            (yyval.nodePtr)->setStructTypeName((yyvsp[0].nodePtr)->getTokenValue()/*nameCounter.getNumberedName($2->getTokenValue())*/);
            (yyval.nodePtr)->setPosition((yyvsp[-1].nodePtr));
            if(symbolTableStack->lookUp((yyvsp[0].nodePtr)->getTokenValue())==0){
                error_structNotDeclared((yyvsp[0].nodePtr)->getTokenValue());
            }
        }
#line 1978 "cParser.cpp"
    break;

  case 26:
#line 217 "cParser.y"
                                {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("structMemberDeclarations"), 1, (yyvsp[0].nodePtr));
        }
#line 1986 "cParser.cpp"
    break;

  case 27:
#line 220 "cParser.y"
                                                         {
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 1995 "cParser.cpp"
    break;

  case 28:
#line 227 "cParser.y"
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
#line 2012 "cParser.cpp"
    break;

  case 29:
#line 242 "cParser.y"
                 {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("structMembers"), 1, (yyvsp[0].nodePtr));
        }
#line 2020 "cParser.cpp"
    break;

  case 30:
#line 245 "cParser.y"
                                   {
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[-1].nodePtr));
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 2030 "cParser.cpp"
    break;

  case 31:
#line 255 "cParser.y"
                       {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("initializations"), 1, (yyvsp[0].nodePtr));
        }
#line 2038 "cParser.cpp"
    break;

  case 32:
#line 258 "cParser.y"
                                           {
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[-1].nodePtr));
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 2048 "cParser.cpp"
    break;

  case 33:
#line 266 "cParser.y"
                 {                       /* int a; 没有初始值 */
            (yyval.nodePtr) = new AttributivedNode(nameCounter.getNumberedName("initialization"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->copyFromChild();
        }
#line 2057 "cParser.cpp"
    break;

  case 34:
#line 270 "cParser.y"
                                  {   /* int a=10; 有初始值 */
            (yyval.nodePtr) = new AttributivedNode(nameCounter.getNumberedName("initialization"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr)->copyFromChild();
        }
#line 2066 "cParser.cpp"
    break;

  case 35:
#line 277 "cParser.y"
                                      {  /* int *a; 指针变量，这里不打算实现。 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variable"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2074 "cParser.cpp"
    break;

  case 36:
#line 280 "cParser.y"
                     { /* 不是指针的变量 */
            (yyval.nodePtr) = new AttributivedNode(nameCounter.getNumberedName("variable"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->copyFromChild();
        }
#line 2083 "cParser.cpp"
    break;

  case 37:
#line 288 "cParser.y"
            { /* a simple pointer */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("pointerSpecifier"), 1, (yyvsp[0].nodePtr));
        }
#line 2091 "cParser.cpp"
    break;

  case 38:
#line 291 "cParser.y"
                             { /* a pointer to another pointer variable */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("pointerSpecifier"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2099 "cParser.cpp"
    break;

  case 39:
#line 294 "cParser.y"
                  { /* a pointer to a const variable */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("pointerSpecifier"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2107 "cParser.cpp"
    break;

  case 40:
#line 297 "cParser.y"
                                   { /* a pointer to another pointer which is a pointer to a const value */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("pointerSpecifier"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2115 "cParser.cpp"
    break;

  case 41:
#line 303 "cParser.y"
                   { /* 一个普通的变量 */
            (yyval.nodePtr) = new AttributivedNode(nameCounter.getNumberedName("variableName"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setKind(Node::KIND_VARIABLE);
            (yyval.nodePtr)->setVariableName((yyvsp[0].nodePtr)->getTokenValue());
            (yyval.nodePtr)->setPosition(csLineCnt, csColumnCnt);
        }
#line 2126 "cParser.cpp"
    break;

  case 42:
#line 309 "cParser.y"
                                    {    /* 数组，可以是多维度的。其中 NUMBER 必须是整数。 */
            (yyval.nodePtr) = new AttributivedNode(nameCounter.getNumberedName("variableName"), 4, (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
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
#line 2146 "cParser.cpp"
    break;

  case 43:
#line 324 "cParser.y"
                         {              /* 这一条弃之不用，太复杂了 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableName"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2154 "cParser.cpp"
    break;

  case 44:
#line 327 "cParser.y"
                             {           /* 函数定义 */
            (yyval.nodePtr) = new AttributivedNode(nameCounter.getNumberedName("variableName"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr)->setKind(Node::KIND_FUNCTION);
            (yyval.nodePtr)->setVariableName((yyvsp[-2].nodePtr)->getVariableName());
            (yyval.nodePtr)->setPosition((yyvsp[-2].nodePtr));
        }
#line 2165 "cParser.cpp"
    break;

  case 45:
#line 333 "cParser.y"
                                        {    /* 函数定义 */
            (yyval.nodePtr) = new AttributivedNode(nameCounter.getNumberedName("variableName"), 4, (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
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
#line 2189 "cParser.cpp"
    break;

  case 46:
#line 355 "cParser.y"
                      {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("paramTypes"), 1, (yyvsp[0].nodePtr));
        }
#line 2197 "cParser.cpp"
    break;

  case 47:
#line 358 "cParser.y"
                                     {
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[-1].nodePtr));
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 2207 "cParser.cpp"
    break;

  case 48:
#line 366 "cParser.y"
             {   /* int (*f)(double,char); 不实现这一条，太复杂 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("paramTypeName"), 1, (yyvsp[0].nodePtr));
        }
#line 2215 "cParser.cpp"
    break;

  case 49:
#line 369 "cParser.y"
                                { /* 无名字的指针变量。不实现这一条，天复杂 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("paramTypeName"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2223 "cParser.cpp"
    break;

  case 50:
#line 372 "cParser.y"
                      {      /* 这一条是要正常实现的，定义函数用的 */
            (yyval.nodePtr) = new AttributivedNode(nameCounter.getNumberedName("paramTypeName"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr)->copyFrom((yyvsp[0].nodePtr));
            (yyval.nodePtr)->setType((yyvsp[-1].nodePtr));
        }
#line 2233 "cParser.cpp"
    break;

  case 51:
#line 381 "cParser.y"
                         {       /* 不实现指针 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoName"), 1, (yyvsp[0].nodePtr));
        }
#line 2241 "cParser.cpp"
    break;

  case 52:
#line 384 "cParser.y"
                               { 
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoName"), 1, (yyvsp[0].nodePtr));
        }
#line 2249 "cParser.cpp"
    break;

  case 53:
#line 391 "cParser.y"
                                              {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 4, (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2257 "cParser.cpp"
    break;

  case 54:
#line 394 "cParser.y"
                                   {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2265 "cParser.cpp"
    break;

  case 55:
#line 397 "cParser.y"
                                       {  /* a function taking another function as param... */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2273 "cParser.cpp"
    break;

  case 56:
#line 400 "cParser.y"
                                                  { /* a function taking another function as param... */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 4, (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2281 "cParser.cpp"
    break;

  case 57:
#line 403 "cParser.y"
                {            /* because it has no name, it must stop some way. Below is some terminators */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2289 "cParser.cpp"
    break;

  case 58:
#line 406 "cParser.y"
                {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2297 "cParser.cpp"
    break;

  case 59:
#line 409 "cParser.y"
                           { /* a function taking another function as param... */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("variableWithNoNameCore"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2305 "cParser.cpp"
    break;

  case 60:
#line 416 "cParser.y"
                              {          /* int a[10]={1}; 初始化列表 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("initialValue"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2313 "cParser.cpp"
    break;

  case 61:
#line 419 "cParser.y"
                             {          /* int a=5+6; int b=a=3; 普通的初始值 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("initialValue"), 1, (yyvsp[0].nodePtr));
    }
#line 2321 "cParser.cpp"
    break;

  case 62:
#line 426 "cParser.y"
                     {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("initialValues"), 1, (yyvsp[0].nodePtr));
        }
#line 2329 "cParser.cpp"
    break;

  case 63:
#line 429 "cParser.y"
                                       { /* int a[10]={1,2,3} */
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[-1].nodePtr));
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 2339 "cParser.cpp"
    break;

  case 64:
#line 438 "cParser.y"
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
#line 2369 "cParser.cpp"
    break;

  case 65:
#line 462 "cParser.y"
                         {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("functionDeclaration"), 3, (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            symbolTableStack->pop();
            /* parse 完一个函数之后，把这个函数的符号表出栈，维护变量的生命周期。 */
        }
#line 2379 "cParser.cpp"
    break;

  case 66:
#line 471 "cParser.y"
                { /* 可以 {} 这样而不必 {;} 这样 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("statementBlock"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2387 "cParser.cpp"
    break;

  case 67:
#line 474 "cParser.y"
                           {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("statementBlock"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2395 "cParser.cpp"
    break;

  case 68:
#line 477 "cParser.y"
                                  {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("statementBlock"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2403 "cParser.cpp"
    break;

  case 69:
#line 480 "cParser.y"
                                             { /* 如果要定义局部变量，必须要把所有的定义语句语句块的最前面。 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("statementBlock"), 4, (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2411 "cParser.cpp"
    break;

  case 70:
#line 483 "cParser.y"
                                                   {
            yyerror("Declaration after statements");
        }
#line 2419 "cParser.cpp"
    break;

  case 71:
#line 490 "cParser.y"
                    {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("localDeclarations"), 1, (yyvsp[0].nodePtr));
        }
#line 2427 "cParser.cpp"
    break;

  case 72:
#line 493 "cParser.y"
                                      {
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 2436 "cParser.cpp"
    break;

  case 73:
#line 500 "cParser.y"
                  {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("statements"), 1, (yyvsp[0].nodePtr));
        }
#line 2444 "cParser.cpp"
    break;

  case 74:
#line 503 "cParser.y"
                             {
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 2453 "cParser.cpp"
    break;

  case 75:
#line 510 "cParser.y"
                            { /* 表达式，也是最常见的语句 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("statement"), 1, (yyvsp[0].nodePtr));
        }
#line 2461 "cParser.cpp"
    break;

  case 76:
#line 513 "cParser.y"
                      { /* 循环 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("statement"), 1, (yyvsp[0].nodePtr));
        }
#line 2469 "cParser.cpp"
    break;

  case 77:
#line 516 "cParser.y"
        { symbolTableStack->push(new SymbolTable(nameCounter.getNumberedName("NestedBlock"))); }
#line 2475 "cParser.cpp"
    break;

  case 78:
#line 516 "cParser.y"
                                                                                                                { /* 语句块。 */
            /* 注：非函数体的语句块是管变量的生命周期的，所以这里要维护符号表。 */
            /* 不能把这个维护放在 statementBlock:'{'...'}' 这个产生式里面，因为这样的话函数体语句块会维护两次符号表。 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("statement"), 1, (yyvsp[0].nodePtr));
            symbolTableStack->pop();
        }
#line 2486 "cParser.cpp"
    break;

  case 79:
#line 522 "cParser.y"
                        {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("statement"), 1, (yyvsp[0].nodePtr));
        }
#line 2494 "cParser.cpp"
    break;

  case 80:
#line 525 "cParser.y"
                      {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("statement"), 1, (yyvsp[0].nodePtr));
        }
#line 2502 "cParser.cpp"
    break;

  case 81:
#line 528 "cParser.y"
                  {
        error_wrongStatement();
    }
#line 2510 "cParser.cpp"
    break;

  case 82:
#line 534 "cParser.y"
            { /* 注：空语句是一个 expressionStatement */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("expressionStatement"), 1, (yyvsp[0].nodePtr));
        }
#line 2518 "cParser.cpp"
    break;

  case 83:
#line 537 "cParser.y"
                       {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("expressionStatement"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2526 "cParser.cpp"
    break;

  case 84:
#line 540 "cParser.y"
                         {
            error_missingSemicolon();
        }
#line 2534 "cParser.cpp"
    break;

  case 85:
#line 546 "cParser.y"
                                                                                 { /* 不允许 for(int i;i<10;i++) 这样 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("loopStatement"), 7, (yyvsp[-6].nodePtr), (yyvsp[-5].nodePtr), (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2542 "cParser.cpp"
    break;

  case 86:
#line 549 "cParser.y"
                                           {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("loopStatement"), 5, (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2550 "cParser.cpp"
    break;

  case 87:
#line 552 "cParser.y"
                                                  {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("loopStatement"), 7, (yyvsp[-6].nodePtr), (yyvsp[-5].nodePtr), (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2558 "cParser.cpp"
    break;

  case 88:
#line 555 "cParser.y"
                                   { error_missingRightBrancket(); }
#line 2564 "cParser.cpp"
    break;

  case 90:
#line 556 "cParser.y"
                        { error_wrongExpression; }
#line 2570 "cParser.cpp"
    break;

  case 91:
#line 556 "cParser.y"
                                                                 { 

        }
#line 2578 "cParser.cpp"
    break;

  case 92:
#line 563 "cParser.y"
                                        {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("branchStatement"), 5, (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2586 "cParser.cpp"
    break;

  case 93:
#line 566 "cParser.y"
                                                       { /* （else悬挂问题）这一条和上一条不能颠倒。 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("branchStatement"), 7, (yyvsp[-6].nodePtr), (yyvsp[-5].nodePtr), (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2594 "cParser.cpp"
    break;

  case 95:
#line 570 "cParser.y"
                              {
            { error_elseWithNoIf(); }
        }
#line 2602 "cParser.cpp"
    break;

  case 99:
#line 588 "cParser.y"
                   { /* 函数返回，这里要检查返回类型 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("jumpStatement"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            /* TODO: check if the type of return value matches the function */
            if(symbolTableStack->lookUp(symbolTableStack->top()->getName())->type != Node::TYPE_VOID){
                error_returnValueTypeMismatch(symbolTableStack->lookUp(symbolTableStack->top()->getName()), symbolTableStack->lookUp(symbolTableStack->top()->getName())->type);
            }
        }
#line 2614 "cParser.cpp"
    break;

  case 100:
#line 595 "cParser.y"
                              { /* 函数返回，这里要检查返回类型 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("jumpStatement"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
            /* 因为这个语句出现时，符号表栈顶附近必定是一个函数的符号表。这个时候只需要先查到该函数的符号表的名字，然后再在全局符号表中看这个名字的类型即可。 */
            /* 因为符号表名和函数名永远是一样的。（在我们的设计中） */
            if(!typeMatch(symbolTableStack->lookUp(symbolTableStack->top()->getName()), (yyvsp[-1].nodePtr))){
                error_returnValueTypeMismatch(symbolTableStack->lookUp(symbolTableStack->top()->getName()), (yyvsp[-1].nodePtr));
            }
        }
#line 2627 "cParser.cpp"
    break;

  case 101:
#line 603 "cParser.y"
                     { /* 循环控制 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("jumpStatement"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2635 "cParser.cpp"
    break;

  case 102:
#line 606 "cParser.y"
                  { /* 循环控制 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("jumpStatement"), 2, (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2643 "cParser.cpp"
    break;

  case 103:
#line 609 "cParser.y"
                            { /* 太复杂了，不实现 */
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("jumpStatement"), 3, (yyvsp[-2].nodePtr), (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));
        }
#line 2651 "cParser.cpp"
    break;

  case 104:
#line 620 "cParser.y"
                             {
            (yyval.nodePtr) = new AttributivedNode(nameCounter.getNumberedName("expression"), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr)->copyFrom((yyvsp[0].nodePtr));
        }
#line 2660 "cParser.cpp"
    break;

  case 105:
#line 624 "cParser.y"
                                            {
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[-1].nodePtr));
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
            /* 一串逗号分隔的表达式的值，是最后一个表达式的值。 */
            (yyval.nodePtr)->copyFrom((yyval.nodePtr)->getChildrenById((yyval.nodePtr)->getChildrenNumber()-1));
        }
#line 2672 "cParser.cpp"
    break;

  case 106:
#line 636 "cParser.y"
                                  {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2680 "cParser.cpp"
    break;

  case 107:
#line 639 "cParser.y"
                                                 {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!(checkKind((yyvsp[-2].nodePtr),Node::KIND_VARIABLE)) || (yyvsp[-2].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
            if(!typeMatch((yyvsp[-2].nodePtr),(yyvsp[0].nodePtr))){
                error_typeMismatch((yyvsp[-2].nodePtr));
            }
        }
#line 2696 "cParser.cpp"
    break;

  case 108:
#line 650 "cParser.y"
                                                        {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!(checkKind((yyvsp[-2].nodePtr),Node::KIND_VARIABLE))){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
            if(!typeMatch((yyvsp[-2].nodePtr),(yyvsp[0].nodePtr))){
                error_typeMismatch((yyvsp[-2].nodePtr));
            }
        }
#line 2712 "cParser.cpp"
    break;

  case 109:
#line 661 "cParser.y"
                                                        {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!(checkKind((yyvsp[-2].nodePtr),Node::KIND_VARIABLE))){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
            if(!typeMatch((yyvsp[-2].nodePtr),(yyvsp[0].nodePtr))){
                error_typeMismatch((yyvsp[-2].nodePtr));
            }
        }
#line 2728 "cParser.cpp"
    break;

  case 110:
#line 672 "cParser.y"
                                                        {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!(checkKind((yyvsp[-2].nodePtr),Node::KIND_VARIABLE))){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
            if(!typeMatch((yyvsp[-2].nodePtr),(yyvsp[0].nodePtr))){
                error_typeMismatch((yyvsp[-2].nodePtr));
            }
        }
#line 2744 "cParser.cpp"
    break;

  case 111:
#line 683 "cParser.y"
                                                        {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!(checkKind((yyvsp[-2].nodePtr),Node::KIND_VARIABLE))){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
            if(!typeMatch((yyvsp[-2].nodePtr),(yyvsp[0].nodePtr))){
                error_typeMismatch((yyvsp[-2].nodePtr));
            }
        }
#line 2760 "cParser.cpp"
    break;

  case 112:
#line 699 "cParser.y"
                            {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2768 "cParser.cpp"
    break;

  case 113:
#line 702 "cParser.y"
                                                                         {/* Hint: right hand of ':' cannot be expression because no '=' should appear at the right hand of ':'. */
            (yyval.nodePtr) = new AttributivedNode({"?:"}, 3, (yyvsp[-4].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
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
#line 2786 "cParser.cpp"
    break;

  case 114:
#line 720 "cParser.y"
                             {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2794 "cParser.cpp"
    break;

  case 115:
#line 723 "cParser.y"
                                                            {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_CONSTANT);
            if(!(checkType((yyvsp[-2].nodePtr),Node::TYPE_INT)&&checkType((yyvsp[0].nodePtr),Node::TYPE_INT)) || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2809 "cParser.cpp"
    break;

  case 116:
#line 738 "cParser.y"
                            {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2817 "cParser.cpp"
    break;

  case 117:
#line 741 "cParser.y"
                                                             {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_CONSTANT);
            if(!(checkType((yyvsp[-2].nodePtr),Node::TYPE_INT)&&checkType((yyvsp[0].nodePtr),Node::TYPE_INT)) || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2832 "cParser.cpp"
    break;

  case 118:
#line 756 "cParser.y"
                                     {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2840 "cParser.cpp"
    break;

  case 119:
#line 759 "cParser.y"
                                                             {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_CONSTANT);
            if(!(checkType((yyvsp[-2].nodePtr),Node::TYPE_INT)&&checkType((yyvsp[0].nodePtr),Node::TYPE_INT)) || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2855 "cParser.cpp"
    break;

  case 120:
#line 774 "cParser.y"
                             {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2863 "cParser.cpp"
    break;

  case 121:
#line 777 "cParser.y"
                                                              {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_CONSTANT);
            if(!(checkType((yyvsp[-2].nodePtr),Node::TYPE_INT)&&checkType((yyvsp[0].nodePtr),Node::TYPE_INT)) || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2878 "cParser.cpp"
    break;

  case 122:
#line 792 "cParser.y"
                                     {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2886 "cParser.cpp"
    break;

  case 123:
#line 795 "cParser.y"
                                                              {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_CONSTANT);
            if(!(checkType((yyvsp[-2].nodePtr),Node::TYPE_INT)&&checkType((yyvsp[0].nodePtr),Node::TYPE_INT)) || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2901 "cParser.cpp"
    break;

  case 124:
#line 810 "cParser.y"
                                     {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2909 "cParser.cpp"
    break;

  case 125:
#line 813 "cParser.y"
                                                                     {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
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
#line 2927 "cParser.cpp"
    break;

  case 126:
#line 826 "cParser.y"
                                                                     {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            (yyval.nodePtr)->setType(Node::TYPE_INT);
            (yyval.nodePtr)->setKind(Node::KIND_CONSTANT);
            if(!typeMatch((yyvsp[-2].nodePtr),(yyvsp[0].nodePtr)) || (yyvsp[-2].nodePtr)->getType()==Node::TYPE_VOID || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 2942 "cParser.cpp"
    break;

  case 127:
#line 841 "cParser.y"
                        {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 2950 "cParser.cpp"
    break;

  case 128:
#line 844 "cParser.y"
                                                         {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
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
#line 2968 "cParser.cpp"
    break;

  case 129:
#line 857 "cParser.y"
                                                         {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
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
#line 2986 "cParser.cpp"
    break;

  case 130:
#line 870 "cParser.y"
                                                        {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
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
#line 3004 "cParser.cpp"
    break;

  case 131:
#line 883 "cParser.y"
                                                        {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
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
#line 3022 "cParser.cpp"
    break;

  case 132:
#line 901 "cParser.y"
                                {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3030 "cParser.cpp"
    break;

  case 133:
#line 904 "cParser.y"
                                                   {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFrom((yyvsp[-2].nodePtr));
            if(!(checkType((yyvsp[-2].nodePtr),Node::TYPE_INT)&&checkType((yyvsp[0].nodePtr),Node::TYPE_INT)) || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 3043 "cParser.cpp"
    break;

  case 134:
#line 912 "cParser.y"
                                                    {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFrom((yyvsp[-2].nodePtr));
            if(!(checkType((yyvsp[-2].nodePtr),Node::TYPE_INT)&&checkType((yyvsp[0].nodePtr),Node::TYPE_INT)) || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 3056 "cParser.cpp"
    break;

  case 135:
#line 925 "cParser.y"
                                {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3064 "cParser.cpp"
    break;

  case 136:
#line 928 "cParser.y"
                                                            {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFrom((yyvsp[0].nodePtr));
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_DOUBLE || (yyvsp[0].nodePtr)->getType()==Node::TYPE_DOUBLE){
                (yyval.nodePtr)->setType(Node::TYPE_DOUBLE);
            }
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_STRUCT || (yyvsp[0].nodePtr)->getType()==Node::TYPE_STRUCT || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 3080 "cParser.cpp"
    break;

  case 137:
#line 939 "cParser.y"
                                                            {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFrom((yyvsp[0].nodePtr));
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_DOUBLE || (yyvsp[0].nodePtr)->getType()==Node::TYPE_DOUBLE){
                (yyval.nodePtr)->setType(Node::TYPE_DOUBLE);
            }
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_STRUCT || (yyvsp[0].nodePtr)->getType()==Node::TYPE_STRUCT || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 3096 "cParser.cpp"
    break;

  case 138:
#line 955 "cParser.y"
                        {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3104 "cParser.cpp"
    break;

  case 139:
#line 958 "cParser.y"
                                                     {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFrom((yyvsp[0].nodePtr));
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_DOUBLE || (yyvsp[0].nodePtr)->getType()==Node::TYPE_DOUBLE){
                (yyval.nodePtr)->setType(Node::TYPE_DOUBLE);
            }
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_STRUCT || (yyvsp[0].nodePtr)->getType()==Node::TYPE_STRUCT || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 3120 "cParser.cpp"
    break;

  case 140:
#line 969 "cParser.y"
                                                     {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFrom((yyvsp[0].nodePtr));
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_DOUBLE || (yyvsp[0].nodePtr)->getType()==Node::TYPE_DOUBLE){
                (yyval.nodePtr)->setType(Node::TYPE_DOUBLE);
            }
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_STRUCT || (yyvsp[0].nodePtr)->getType()==Node::TYPE_STRUCT || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 3136 "cParser.cpp"
    break;

  case 141:
#line 980 "cParser.y"
                                                     {
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFrom((yyvsp[0].nodePtr));
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_DOUBLE || (yyvsp[0].nodePtr)->getType()==Node::TYPE_DOUBLE){
                (yyval.nodePtr)->setType(Node::TYPE_DOUBLE);
            }
            if((yyvsp[-2].nodePtr)->getType()==Node::TYPE_STRUCT || (yyvsp[0].nodePtr)->getType()==Node::TYPE_STRUCT || (yyvsp[-2].nodePtr)->isArray() || (yyvsp[0].nodePtr)->isArray()){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 3152 "cParser.cpp"
    break;

  case 142:
#line 997 "cParser.y"
                       {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3160 "cParser.cpp"
    break;

  case 143:
#line 1000 "cParser.y"
                                      {
            (yyval.nodePtr) = new AttributivedNode("castedExpression", 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
        }
#line 3168 "cParser.cpp"
    break;

  case 144:
#line 1003 "cParser.y"
                                                         {
            (yyval.nodePtr) = new AttributivedNode("castedExpression", 3, (yyvsp[-3].nodePtr), (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
        }
#line 3176 "cParser.cpp"
    break;

  case 145:
#line 1012 "cParser.y"
                              {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3184 "cParser.cpp"
    break;

  case 146:
#line 1015 "cParser.y"
                               {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3192 "cParser.cpp"
    break;

  case 147:
#line 1021 "cParser.y"
                                   {/* ++a, especially ++a[i] is ++(a[i]) but not (++a)[i] */
            (yyvsp[-1].nodePtr) = new AttributivedNode(std::string("pre")+(yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkKind((yyvsp[0].nodePtr), Node::KIND_VARIABLE) || (yyvsp[0].nodePtr)->isArray() || (yyvsp[0].nodePtr)->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError((yyvsp[0].nodePtr),(yyvsp[-1].nodePtr));
            }
        }
#line 3205 "cParser.cpp"
    break;

  case 148:
#line 1029 "cParser.y"
                                   {/* --a, the same as ++a[i] */
            (yyvsp[-1].nodePtr) = new AttributivedNode(std::string("pre")+(yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkKind((yyvsp[0].nodePtr), Node::KIND_VARIABLE) || (yyvsp[0].nodePtr)->isArray() || (yyvsp[0].nodePtr)->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError((yyvsp[0].nodePtr),(yyvsp[-1].nodePtr));
            }
        }
#line 3218 "cParser.cpp"
    break;

  case 149:
#line 1037 "cParser.y"
                                   {/* logical NOT */
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkType((yyvsp[0].nodePtr), Node::TYPE_INT)){
                error_expressionTypeError((yyvsp[0].nodePtr),(yyvsp[-1].nodePtr));
            }
        }
#line 3231 "cParser.cpp"
    break;

  case 150:
#line 1045 "cParser.y"
                                   {/* bitwise NOT */
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkType((yyvsp[0].nodePtr), Node::TYPE_INT)){
                error_expressionTypeError((yyvsp[0].nodePtr),(yyvsp[-1].nodePtr));
            }
        }
#line 3244 "cParser.cpp"
    break;

  case 151:
#line 1053 "cParser.y"
                                   {/* negative */
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[0].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
            if(checkType((yyvsp[0].nodePtr), Node::TYPE_STRUCT)){
                error_expressionTypeError((yyvsp[0].nodePtr),(yyvsp[-1].nodePtr));
            }
        }
#line 3256 "cParser.cpp"
    break;

  case 152:
#line 1063 "cParser.y"
                         {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3264 "cParser.cpp"
    break;

  case 153:
#line 1066 "cParser.y"
                                   {/* a++, espetially a[i]++ is allowed, (a[i])++ is not necessary */
            (yyvsp[0].nodePtr) = new AttributivedNode(std::string("post")+(yyvsp[0].nodePtr)->getName(), 1, (yyvsp[-1].nodePtr));
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkKind((yyvsp[-1].nodePtr), Node::KIND_VARIABLE) || (yyvsp[-1].nodePtr)->isArray() || (yyvsp[-1].nodePtr)->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError((yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 3277 "cParser.cpp"
    break;

  case 154:
#line 1074 "cParser.y"
                                   {/* a-- */
            (yyvsp[0].nodePtr) = new AttributivedNode(std::string("post")+(yyvsp[0].nodePtr)->getName(), 1, (yyvsp[-1].nodePtr));
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
            (yyval.nodePtr)->copyFromChild();
            if(!checkKind((yyvsp[-1].nodePtr), Node::KIND_VARIABLE) || (yyvsp[-1].nodePtr)->isArray() || (yyvsp[-1].nodePtr)->getType()==Node::TYPE_STRUCT){
                error_expressionTypeError((yyvsp[-1].nodePtr),(yyvsp[0].nodePtr));
            }
        }
#line 3290 "cParser.cpp"
    break;

  case 155:
#line 1082 "cParser.y"
                                                            {/* array a[10], corresponding to prefix ++ */
            (yyval.nodePtr) = new AttributivedNode({"[]"}, 2, (yyvsp[-3].nodePtr), (yyvsp[-1].nodePtr));
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
#line 3310 "cParser.cpp"
    break;

  case 156:
#line 1097 "cParser.y"
                                                 {/* function, f()[i], f[i](), f[i]()[j] are all allowed，但我们不=实现它。 */
            (yyval.nodePtr) = new AttributivedNode({"()"}, 2, (yyvsp[-3].nodePtr), (yyvsp[-1].nodePtr));
            (yyval.nodePtr)->copyFromChild();
            if(!(checkKind((yyvsp[-3].nodePtr), Node::KIND_FUNCTION))){
                error_expressionTypeError((yyvsp[-3].nodePtr),(yyvsp[-2].nodePtr));
            }else{
                std::vector<Node::Type> argList;
                std::vector<std::string> argListStructName;
                for(int i=0;i<(yyvsp[-1].nodePtr)->getChildrenNumber();i++){
                    auto child = (yyvsp[-1].nodePtr)->getChildrenById(i);
                    if(child->isTerminal() && child->getTokenValue().compare(",")==0)continue;
                    argList.push_back(child->getType());
                    if(child->getType()==Node::TYPE_STRUCT){
                        argListStructName.push_back(child->getStructTypeName());
                    }else{
                        argListStructName.push_back({""});
                    }
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
#line 3343 "cParser.cpp"
    break;

  case 157:
#line 1125 "cParser.y"
                                                 {/* function with no params. */
            (yyval.nodePtr) = new AttributivedNode({"()"}, 1, (yyvsp[-2].nodePtr));
            (yyval.nodePtr)->copyFromChild();
            if(!(checkKind((yyvsp[-2].nodePtr), Node::KIND_FUNCTION))){
                error_expressionTypeError((yyvsp[-2].nodePtr),(yyval.nodePtr));
            }else {
                if((yyvsp[-2].nodePtr)->getArgList().size()!=0){
                    error_argumentNumberNotMatch((yyvsp[-2].nodePtr),0);
                }
            }
        }
#line 3359 "cParser.cpp"
    break;

  case 158:
#line 1136 "cParser.y"
                                                 {/* struct's member (a.val) */
            Node *t=(yyvsp[-1].nodePtr);
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 2, (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
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
#line 3380 "cParser.cpp"
    break;

  case 159:
#line 1152 "cParser.y"
                                                 {/* struct's member, pointer (a->val) */
            (yyvsp[-1].nodePtr) = new AttributivedNode((yyvsp[-1].nodePtr)->getName(), 1, (yyvsp[-2].nodePtr));
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);

        }
#line 3390 "cParser.cpp"
    break;

  case 160:
#line 1157 "cParser.y"
                                                     {
            error_missingRightBrancket2();
        }
#line 3398 "cParser.cpp"
    break;

  case 161:
#line 1163 "cParser.y"
                             {
            (yyval.nodePtr) = new Node(nameCounter.getNumberedName("paramList"), 1, (yyvsp[0].nodePtr));
        }
#line 3406 "cParser.cpp"
    break;

  case 162:
#line 1166 "cParser.y"
                                           {/* 这里面不能填 expression，因为 expression 也是用逗号隔开的一串表达式 */
            (yyval.nodePtr) = (yyvsp[-2].nodePtr);
            (yyval.nodePtr)->addChild((yyvsp[-1].nodePtr));
            (yyval.nodePtr)->addChild((yyvsp[0].nodePtr));
        }
#line 3416 "cParser.cpp"
    break;

  case 163:
#line 1176 "cParser.y"
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
#line 3432 "cParser.cpp"
    break;

  case 164:
#line 1187 "cParser.y"
               {
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3440 "cParser.cpp"
    break;

  case 165:
#line 1190 "cParser.y"
               { /* 这个就不实现了吧 */
            (yyval.nodePtr) = (yyvsp[0].nodePtr);
        }
#line 3448 "cParser.cpp"
    break;

  case 166:
#line 1193 "cParser.y"
                           {
            (yyval.nodePtr) = (yyvsp[-1].nodePtr);
        }
#line 3456 "cParser.cpp"
    break;


#line 3460 "cParser.cpp"

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
#line 1199 "cParser.y"

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

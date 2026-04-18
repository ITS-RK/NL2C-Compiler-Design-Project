/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "nl2c.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void yyerror(const char *s);
int yylex();

FILE *out;
int had_error = 0;
char output_path[512] = "output/output.c";

char* wrap_binary(char* a, char* op, char* b) {
    char* res = malloc(200);
    sprintf(res, "%s %s %s", a, op, b);
    return res;
}

typedef struct {
    char expr[100];
    char type[10];
} ExprType;

ExprType expr_table[200];
int expr_count = 0;

void store_expr(char* code, char* type) {
    strcpy(expr_table[expr_count].expr, code);
    strcpy(expr_table[expr_count].type, type);
    expr_count++;
}

char* get_type(char* code) {
    for(int i = expr_count - 1; i >= 0; i--) {
        if(strcmp(expr_table[i].expr, code) == 0)
            return expr_table[i].type;
    }
    return "int";
}

typedef struct {
    char name[50];
    char type[10];
} Var;

Var vars[100];
int var_count = 0;

void add_var(char* name, char* type) {
    strcpy(vars[var_count].name, name);
    strcpy(vars[var_count].type, type);
    var_count++;
}

char* get_var_type(char* name) {
    for(int i = 0; i < var_count; i++)
        if(strcmp(vars[i].name, name) == 0)
            return vars[i].type;
    return NULL;
}

typedef struct {
    char name[50];
    int arity;
} FuncInfo;

FuncInfo funcs[100];
int func_count = 0;
int current_param_count = 0;
char current_function_name[50];

void add_func(char* name, int arity) {
    strcpy(funcs[func_count].name, name);
    funcs[func_count].arity = arity;
    func_count++;
}

int get_func_arity(char* name) {
    for(int i = 0; i < func_count; i++)
        if(strcmp(funcs[i].name, name) == 0)
            return funcs[i].arity;
    return -1;
}

int split_top_level_args(char* text, char parts[][100], int max_parts) {
    int depth = 0;
    int part = 0;
    int idx = 0;

    if(text == NULL || text[0] == '\0')
        return 0;

    for(int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];

        if(ch == '(')
            depth++;
        else if(ch == ')')
            depth--;

        if(ch == ',' && depth == 0) {
            parts[part][idx] = '\0';
            part++;
            idx = 0;

            while(text[i + 1] == ' ')
                i++;

            if(part >= max_parts)
                break;
            continue;
        }

        if(idx < 99)
            parts[part][idx++] = ch;
    }

    parts[part][idx] = '\0';
    return part + 1;
}

char* build_call_expr(char* name, char* raw_args) {
    char parts[20][100];
    int arg_count = split_top_level_args(raw_args, parts, 20);
    int arity = get_func_arity(name);
    int used_args = arg_count;
    char* tmp = malloc(400);
    tmp[0] = '\0';

    if(arity >= 0 && arg_count >= arity)
        used_args = arity;

    sprintf(tmp, "%s(", name);

    for(int i = 0; i < used_args; i++) {
        if(i > 0)
            strcat(tmp, ", ");
        strcat(tmp, parts[i]);
    }

    strcat(tmp, ")");

    if(arity >= 0 && arg_count > arity) {
        for(int i = arity; i < arg_count; i++) {
            strcat(tmp, ", ");
            strcat(tmp, parts[i]);
        }
    }

    return tmp;
}

void report_errorf(const char* fmt, ...) {
    va_list args;
    had_error = 1;
    va_start(args, fmt);
    vprintf(fmt, args);
    printf("\n");
    va_end(args);
}

#line 234 "nl2c.tab.c"

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

#include "nl2c.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CREATE = 3,                     /* CREATE  */
  YYSYMBOL_INTEGER = 4,                    /* INTEGER  */
  YYSYMBOL_SET = 5,                        /* SET  */
  YYSYMBOL_TO = 6,                         /* TO  */
  YYSYMBOL_PRINT = 7,                      /* PRINT  */
  YYSYMBOL_DEF = 8,                        /* DEF  */
  YYSYMBOL_PARAMS = 9,                     /* PARAMS  */
  YYSYMBOL_BEGINN = 10,                    /* BEGINN  */
  YYSYMBOL_ENDFUNC = 11,                   /* ENDFUNC  */
  YYSYMBOL_RETURN = 12,                    /* RETURN  */
  YYSYMBOL_CALL = 13,                      /* CALL  */
  YYSYMBOL_WITH = 14,                      /* WITH  */
  YYSYMBOL_PLUS = 15,                      /* PLUS  */
  YYSYMBOL_MINUS = 16,                     /* MINUS  */
  YYSYMBOL_MUL = 17,                       /* MUL  */
  YYSYMBOL_DIV = 18,                       /* DIV  */
  YYSYMBOL_LP = 19,                        /* LP  */
  YYSYMBOL_RP = 20,                        /* RP  */
  YYSYMBOL_FLOAT = 21,                     /* FLOAT  */
  YYSYMBOL_CAST = 22,                      /* CAST  */
  YYSYMBOL_IF = 23,                        /* IF  */
  YYSYMBOL_THEN = 24,                      /* THEN  */
  YYSYMBOL_ELSE = 25,                      /* ELSE  */
  YYSYMBOL_ENDIF = 26,                     /* ENDIF  */
  YYSYMBOL_WHILE = 27,                     /* WHILE  */
  YYSYMBOL_DO = 28,                        /* DO  */
  YYSYMBOL_ENDWHILE = 29,                  /* ENDWHILE  */
  YYSYMBOL_FOR = 30,                       /* FOR  */
  YYSYMBOL_FROM = 31,                      /* FROM  */
  YYSYMBOL_STEP = 32,                      /* STEP  */
  YYSYMBOL_ENDFOR = 33,                    /* ENDFOR  */
  YYSYMBOL_GT = 34,                        /* GT  */
  YYSYMBOL_LT = 35,                        /* LT  */
  YYSYMBOL_EQ = 36,                        /* EQ  */
  YYSYMBOL_NUMBER = 37,                    /* NUMBER  */
  YYSYMBOL_FLOAT_NUMBER = 38,              /* FLOAT_NUMBER  */
  YYSYMBOL_ID = 39,                        /* ID  */
  YYSYMBOL_ARG_END = 40,                   /* ARG_END  */
  YYSYMBOL_EXPR_TERM = 41,                 /* EXPR_TERM  */
  YYSYMBOL_YYACCEPT = 42,                  /* $accept  */
  YYSYMBOL_program = 43,                   /* program  */
  YYSYMBOL_44_1 = 44,                      /* $@1  */
  YYSYMBOL_functions = 45,                 /* functions  */
  YYSYMBOL_function = 46,                  /* function  */
  YYSYMBOL_47_2 = 47,                      /* $@2  */
  YYSYMBOL_48_3 = 48,                      /* $@3  */
  YYSYMBOL_param_list = 49,                /* param_list  */
  YYSYMBOL_id_list = 50,                   /* id_list  */
  YYSYMBOL_51_4 = 51,                      /* $@4  */
  YYSYMBOL_id_list_tail = 52,              /* id_list_tail  */
  YYSYMBOL_53_5 = 53,                      /* $@5  */
  YYSYMBOL_main_block = 54,                /* main_block  */
  YYSYMBOL_55_6 = 55,                      /* $@6  */
  YYSYMBOL_statements = 56,                /* statements  */
  YYSYMBOL_statement = 57,                 /* statement  */
  YYSYMBOL_declaration = 58,               /* declaration  */
  YYSYMBOL_assignment = 59,                /* assignment  */
  YYSYMBOL_print_stmt = 60,                /* print_stmt  */
  YYSYMBOL_return_stmt = 61,               /* return_stmt  */
  YYSYMBOL_if_stmt = 62,                   /* if_stmt  */
  YYSYMBOL_63_7 = 63,                      /* $@7  */
  YYSYMBOL_opt_else = 64,                  /* opt_else  */
  YYSYMBOL_65_8 = 65,                      /* $@8  */
  YYSYMBOL_while_stmt = 66,                /* while_stmt  */
  YYSYMBOL_67_9 = 67,                      /* $@9  */
  YYSYMBOL_for_stmt = 68,                  /* for_stmt  */
  YYSYMBOL_69_10 = 69,                     /* $@10  */
  YYSYMBOL_condition = 70,                 /* condition  */
  YYSYMBOL_opt_step = 71,                  /* opt_step  */
  YYSYMBOL_expr = 72,                      /* expr  */
  YYSYMBOL_term = 73,                      /* term  */
  YYSYMBOL_factor = 74,                    /* factor  */
  YYSYMBOL_func_expr = 75,                 /* func_expr  */
  YYSYMBOL_arg_list = 76,                  /* arg_list  */
  YYSYMBOL_arg_list_tail = 77              /* arg_list_tail  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   123

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  111

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   296


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       0,   194,   194,   194,   203,   204,   208,   214,   208,   225,
     227,   231,   231,   241,   241,   248,   252,   252,   264,   265,
     269,   270,   271,   272,   273,   274,   275,   279,   287,   298,
     317,   326,   332,   332,   343,   343,   347,   351,   351,   361,
     361,   371,   374,   377,   383,   384,   388,   402,   416,   420,
     434,   440,   444,   450,   454,   464,   470,   474,   483,   489,
     497,   503
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CREATE", "INTEGER",
  "SET", "TO", "PRINT", "DEF", "PARAMS", "BEGINN", "ENDFUNC", "RETURN",
  "CALL", "WITH", "PLUS", "MINUS", "MUL", "DIV", "LP", "RP", "FLOAT",
  "CAST", "IF", "THEN", "ELSE", "ENDIF", "WHILE", "DO", "ENDWHILE", "FOR",
  "FROM", "STEP", "ENDFOR", "GT", "LT", "EQ", "NUMBER", "FLOAT_NUMBER",
  "ID", "ARG_END", "EXPR_TERM", "$accept", "program", "$@1", "functions",
  "function", "$@2", "$@3", "param_list", "id_list", "$@4", "id_list_tail",
  "$@5", "main_block", "$@6", "statements", "statement", "declaration",
  "assignment", "print_stmt", "return_stmt", "if_stmt", "$@7", "opt_else",
  "$@8", "while_stmt", "$@9", "for_stmt", "$@10", "condition", "opt_step",
  "expr", "term", "factor", "func_expr", "arg_list", "arg_list_tail", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-66)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -66,    29,   -66,   -66,     8,    -7,   -66,   -66,   -66,   -66,
      63,    26,    21,     5,    79,    79,    79,    79,    23,   -66,
     -66,   -66,   -66,   -66,   -66,   -66,   -66,    28,    30,    38,
      60,    59,    61,    79,    79,   -66,   -66,   -66,     6,    35,
     -66,   -66,     6,    45,    87,    55,    73,   -66,   -66,   -66,
     -66,   -66,    79,    91,    -6,    44,    79,    79,    79,    79,
     -66,    79,    79,    79,   -66,    79,    70,   -66,     6,    79,
     -66,    89,    35,    35,   -66,   -66,   -66,     6,     6,     6,
     -66,    81,   -66,   -66,    34,    69,   -66,   -66,     1,    51,
      79,    70,   -66,    69,   -66,   -66,    85,   -66,     2,   -66,
     -66,   -66,   -66,    79,    84,    63,     6,   -66,   -66,     0,
     -66
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     5,     1,    16,     0,     4,     3,    19,     6,
      17,    10,     0,     0,     0,     0,     0,     0,     0,    18,
      20,    21,    22,    23,    24,    25,    26,     0,     0,     0,
       0,     0,     0,     0,     0,    52,    53,    54,    30,    48,
      51,    56,    31,     0,     0,     0,     0,    11,     9,     7,
      27,    28,     0,     0,     0,     0,     0,     0,     0,     0,
      32,     0,     0,     0,    37,     0,    15,    19,    29,     0,
      55,     0,    46,    47,    49,    50,    19,    41,    42,    43,
      19,     0,    13,    12,     0,    61,    58,    57,    36,     0,
       0,    15,     8,    61,    59,    34,     0,    38,    45,    14,
      60,    19,    33,     0,     0,    35,    44,    39,    19,     0,
      40
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,
      22,   -66,   -66,   -66,   -65,   -66,   -66,   -66,   -66,   -66,
     -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,    97,   -66,
     -14,    16,    36,   -66,   -66,    27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     4,     6,    11,    67,    28,    48,    66,
      83,    91,     7,     8,    10,    19,    20,    21,    22,    23,
      24,    76,    96,   101,    25,    80,    26,   108,    43,   104,
      44,    39,    40,    41,    86,    94
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      38,    42,    84,    12,    12,    13,    13,    14,    14,    56,
      57,    88,    15,    15,    70,    89,     5,    56,    57,    54,
      55,    56,    57,    16,    16,    29,    95,    17,    17,     3,
      18,    18,     9,   110,   103,    27,   105,    12,    68,    13,
      49,    14,    30,   109,    31,    92,    15,    77,    78,    79,
      71,    81,    58,    59,    12,    85,    13,    16,    14,    56,
      57,    17,    46,    15,    18,    52,    12,    47,    13,    60,
      14,    93,    72,    73,    16,    15,    98,    50,    17,    93,
      97,    18,    32,    64,    56,    57,    16,    90,    33,   106,
      17,    34,    32,    18,    74,    75,    56,    57,    33,    51,
      53,    34,    56,    57,    65,    69,    35,    36,    37,    82,
      87,   102,   107,    99,    45,     0,    35,    36,    37,     0,
     100,    61,    62,    63
};

static const yytype_int8 yycheck[] =
{
      14,    15,    67,     3,     3,     5,     5,     7,     7,    15,
      16,    76,    12,    12,    20,    80,     8,    15,    16,    33,
      34,    15,    16,    23,    23,     4,    25,    27,    27,     0,
      30,    30,    39,    33,    32,     9,   101,     3,    52,     5,
      10,     7,    21,   108,    39,    11,    12,    61,    62,    63,
       6,    65,    17,    18,     3,    69,     5,    23,     7,    15,
      16,    27,    39,    12,    30,     6,     3,    39,     5,    24,
       7,    85,    56,    57,    23,    12,    90,    39,    27,    93,
      29,    30,    13,    28,    15,    16,    23,     6,    19,   103,
      27,    22,    13,    30,    58,    59,    15,    16,    19,    39,
      39,    22,    15,    16,    31,    14,    37,    38,    39,    39,
      21,    26,    28,    91,    17,    -1,    37,    38,    39,    -1,
      93,    34,    35,    36
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    43,    44,     0,    45,     8,    46,    54,    55,    39,
      56,    47,     3,     5,     7,    12,    23,    27,    30,    57,
      58,    59,    60,    61,    62,    66,    68,     9,    49,     4,
      21,    39,    13,    19,    22,    37,    38,    39,    72,    73,
      74,    75,    72,    70,    72,    70,    39,    39,    50,    10,
      39,    39,     6,    39,    72,    72,    15,    16,    17,    18,
      24,    34,    35,    36,    28,    31,    51,    48,    72,    14,
      20,     6,    73,    73,    74,    74,    63,    72,    72,    72,
      67,    72,    39,    52,    56,    72,    76,    21,    56,    56,
       6,    53,    11,    72,    77,    25,    64,    29,    72,    52,
      77,    65,    26,    32,    71,    56,    72,    28,    69,    56,
      33
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    42,    44,    43,    45,    45,    47,    48,    46,    49,
      49,    51,    50,    53,    52,    52,    55,    54,    56,    56,
      57,    57,    57,    57,    57,    57,    57,    58,    58,    59,
      60,    61,    63,    62,    65,    64,    64,    67,    66,    69,
      68,    70,    70,    70,    71,    71,    72,    72,    72,    73,
      73,    73,    74,    74,    74,    74,    74,    74,    75,    76,
      77,    77
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     2,     0,     0,     0,     8,     2,
       0,     0,     3,     0,     3,     0,     0,     2,     2,     0,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     4,
       2,     2,     0,     7,     0,     3,     0,     0,     6,     0,
      11,     3,     3,     3,     2,     0,     3,     3,     1,     3,
       3,     1,     1,     1,     1,     3,     1,     4,     4,     2,
       2,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* $@1: %empty  */
#line 194 "nl2c.y"
    {
        out = fopen(output_path, "w");
        fprintf(out, "#include <stdio.h>\n");
    }
#line 1381 "nl2c.tab.c"
    break;

  case 6: /* $@2: %empty  */
#line 208 "nl2c.y"
           {
        current_param_count = 0;
        strcpy(current_function_name, (yyvsp[0].id));
        fprintf(out, "int %s(", (yyvsp[0].id));
    }
#line 1391 "nl2c.tab.c"
    break;

  case 7: /* $@3: %empty  */
#line 214 "nl2c.y"
           {
        add_func(current_function_name, current_param_count);
        fprintf(out, "){\n");
    }
#line 1400 "nl2c.tab.c"
    break;

  case 8: /* function: DEF ID $@2 param_list BEGINN $@3 statements ENDFUNC  */
#line 219 "nl2c.y"
            {
        fprintf(out, "}\n");
    }
#line 1408 "nl2c.tab.c"
    break;

  case 10: /* param_list: %empty  */
#line 227 "nl2c.y"
    { fprintf(out, "void"); }
#line 1414 "nl2c.tab.c"
    break;

  case 11: /* $@4: %empty  */
#line 231 "nl2c.y"
       {
        current_param_count++;
        if(get_var_type((yyvsp[0].id)) == NULL)
            add_var((yyvsp[0].id), "int");
        fprintf(out, "int %s", (yyvsp[0].id));
    }
#line 1425 "nl2c.tab.c"
    break;

  case 13: /* $@5: %empty  */
#line 241 "nl2c.y"
       {
        current_param_count++;
        if(get_var_type((yyvsp[0].id)) == NULL)
            add_var((yyvsp[0].id), "int");
        fprintf(out, ", int %s", (yyvsp[0].id));
    }
#line 1436 "nl2c.tab.c"
    break;

  case 16: /* $@6: %empty  */
#line 252 "nl2c.y"
    {
        fprintf(out, "int main(){\n");
    }
#line 1444 "nl2c.tab.c"
    break;

  case 17: /* main_block: $@6 statements  */
#line 256 "nl2c.y"
    {
        fprintf(out, "return 0;\n}\n");
        fclose(out);
        out = NULL;
    }
#line 1454 "nl2c.tab.c"
    break;

  case 27: /* declaration: CREATE INTEGER ID  */
#line 279 "nl2c.y"
                      {
        if(get_var_type((yyvsp[0].id)) != NULL) {
            report_errorf("Semantic Error: redeclaration of %s", (yyvsp[0].id));
        } else {
            add_var((yyvsp[0].id), "int");
            fprintf(out, "int %s;\n", (yyvsp[0].id));
        }
    }
#line 1467 "nl2c.tab.c"
    break;

  case 28: /* declaration: CREATE FLOAT ID  */
#line 287 "nl2c.y"
                      {
        if(get_var_type((yyvsp[0].id)) != NULL) {
            report_errorf("Semantic Error: redeclaration of %s", (yyvsp[0].id));
        } else {
            add_var((yyvsp[0].id), "float");
            fprintf(out, "float %s;\n", (yyvsp[0].id));
        }
    }
#line 1480 "nl2c.tab.c"
    break;

  case 29: /* assignment: SET ID TO expr  */
#line 298 "nl2c.y"
                   {
        char* varType = get_var_type((yyvsp[-2].id));
        char* exprType = get_type((yyvsp[0].expr));

        if(varType == NULL) {
            report_errorf("Semantic Error: undeclared variable %s", (yyvsp[-2].id));
        } else if(strcmp(varType, exprType) != 0) {
            if(strcmp(varType, "float") == 0 && strcmp(exprType, "int") == 0) {
                fprintf(out, "%s = (float)(%s);\n", (yyvsp[-2].id), (yyvsp[0].expr));
            } else {
                report_errorf("Type Error: %s <- %s", varType, exprType);
            }
        } else {
            fprintf(out, "%s = %s;\n", (yyvsp[-2].id), (yyvsp[0].expr));
        }
    }
#line 1501 "nl2c.tab.c"
    break;

  case 30: /* print_stmt: PRINT expr  */
#line 317 "nl2c.y"
               {
        if(strcmp(get_type((yyvsp[0].expr)), "float") == 0)
            fprintf(out, "printf(\"%%f\\n\", %s);\n", (yyvsp[0].expr));
        else
            fprintf(out, "printf(\"%%d\\n\", %s);\n", (yyvsp[0].expr));
    }
#line 1512 "nl2c.tab.c"
    break;

  case 31: /* return_stmt: RETURN expr  */
#line 326 "nl2c.y"
                {
        fprintf(out, "return %s;\n", (yyvsp[0].expr));
    }
#line 1520 "nl2c.tab.c"
    break;

  case 32: /* $@7: %empty  */
#line 332 "nl2c.y"
                      {
        fprintf(out, "if (%s) {\n", (yyvsp[-1].expr));
    }
#line 1528 "nl2c.tab.c"
    break;

  case 33: /* if_stmt: IF condition THEN $@7 statements opt_else ENDIF  */
#line 337 "nl2c.y"
          {
        fprintf(out, "}\n");
    }
#line 1536 "nl2c.tab.c"
    break;

  case 34: /* $@8: %empty  */
#line 343 "nl2c.y"
         {
        fprintf(out, "} else {\n");
    }
#line 1544 "nl2c.tab.c"
    break;

  case 37: /* $@9: %empty  */
#line 351 "nl2c.y"
                       {
        fprintf(out, "while (%s) {\n", (yyvsp[-1].expr));
    }
#line 1552 "nl2c.tab.c"
    break;

  case 38: /* while_stmt: WHILE condition DO $@9 statements ENDWHILE  */
#line 355 "nl2c.y"
             {
        fprintf(out, "}\n");
    }
#line 1560 "nl2c.tab.c"
    break;

  case 39: /* $@10: %empty  */
#line 361 "nl2c.y"
                                         {
        fprintf(out, "for (%s = %s; %s <= %s; %s += %s) {\n", (yyvsp[-6].id), (yyvsp[-4].expr), (yyvsp[-6].id), (yyvsp[-2].expr), (yyvsp[-6].id), (yyvsp[-1].expr));
    }
#line 1568 "nl2c.tab.c"
    break;

  case 40: /* for_stmt: FOR ID FROM expr TO expr opt_step DO $@10 statements ENDFOR  */
#line 365 "nl2c.y"
           {
        fprintf(out, "}\n");
    }
#line 1576 "nl2c.tab.c"
    break;

  case 41: /* condition: expr GT expr  */
#line 371 "nl2c.y"
                 {
        (yyval.expr) = wrap_binary((yyvsp[-2].expr), ">", (yyvsp[0].expr));
    }
#line 1584 "nl2c.tab.c"
    break;

  case 42: /* condition: expr LT expr  */
#line 374 "nl2c.y"
                   {
        (yyval.expr) = wrap_binary((yyvsp[-2].expr), "<", (yyvsp[0].expr));
    }
#line 1592 "nl2c.tab.c"
    break;

  case 43: /* condition: expr EQ expr  */
#line 377 "nl2c.y"
                   {
        (yyval.expr) = wrap_binary((yyvsp[-2].expr), "==", (yyvsp[0].expr));
    }
#line 1600 "nl2c.tab.c"
    break;

  case 44: /* opt_step: STEP expr  */
#line 383 "nl2c.y"
              { (yyval.expr) = (yyvsp[0].expr); }
#line 1606 "nl2c.tab.c"
    break;

  case 45: /* opt_step: %empty  */
#line 384 "nl2c.y"
      { (yyval.expr) = "1"; }
#line 1612 "nl2c.tab.c"
    break;

  case 46: /* expr: expr PLUS term  */
#line 388 "nl2c.y"
                   {
        char* t1 = get_type((yyvsp[-2].expr));
        char* t2 = get_type((yyvsp[0].expr));
        char* res = malloc(100);

        if(strcmp(t1, "float") == 0 || strcmp(t2, "float") == 0) {
            sprintf(res, "(float)%s + (float)%s", (yyvsp[-2].expr), (yyvsp[0].expr));
            store_expr(res, "float");
        } else {
            sprintf(res, "%s + %s", (yyvsp[-2].expr), (yyvsp[0].expr));
            store_expr(res, "int");
        }
        (yyval.expr) = res;
    }
#line 1631 "nl2c.tab.c"
    break;

  case 47: /* expr: expr MINUS term  */
#line 402 "nl2c.y"
                      {
        char* t1 = get_type((yyvsp[-2].expr));
        char* t2 = get_type((yyvsp[0].expr));
        char* res = malloc(100);

        if(strcmp(t1, "float") == 0 || strcmp(t2, "float") == 0) {
            sprintf(res, "(float)%s - (float)%s", (yyvsp[-2].expr), (yyvsp[0].expr));
            store_expr(res, "float");
        } else {
            sprintf(res, "%s - %s", (yyvsp[-2].expr), (yyvsp[0].expr));
            store_expr(res, "int");
        }
        (yyval.expr) = res;
    }
#line 1650 "nl2c.tab.c"
    break;

  case 48: /* expr: term  */
#line 416 "nl2c.y"
                           { (yyval.expr) = (yyvsp[0].expr); }
#line 1656 "nl2c.tab.c"
    break;

  case 49: /* term: term MUL factor  */
#line 420 "nl2c.y"
                    {
        char* t1 = get_type((yyvsp[-2].expr));
        char* t2 = get_type((yyvsp[0].expr));
        char* res = malloc(100);

        if(strcmp(t1, "float") == 0 || strcmp(t2, "float") == 0) {
            sprintf(res, "(float)%s * (float)%s", (yyvsp[-2].expr), (yyvsp[0].expr));
            store_expr(res, "float");
        } else {
            sprintf(res, "%s * %s", (yyvsp[-2].expr), (yyvsp[0].expr));
            store_expr(res, "int");
        }
        (yyval.expr) = res;
    }
#line 1675 "nl2c.tab.c"
    break;

  case 50: /* term: term DIV factor  */
#line 434 "nl2c.y"
                      {
        char* res = malloc(100);
        sprintf(res, "(float)%s / (float)%s", (yyvsp[-2].expr), (yyvsp[0].expr));
        store_expr(res, "float");
        (yyval.expr) = res;
    }
#line 1686 "nl2c.tab.c"
    break;

  case 51: /* term: factor  */
#line 440 "nl2c.y"
             { (yyval.expr) = (yyvsp[0].expr); }
#line 1692 "nl2c.tab.c"
    break;

  case 52: /* factor: NUMBER  */
#line 444 "nl2c.y"
           {
        char* tmp = malloc(20);
        sprintf(tmp, "%d", (yyvsp[0].num));
        store_expr(tmp, "int");
        (yyval.expr) = tmp;
    }
#line 1703 "nl2c.tab.c"
    break;

  case 53: /* factor: FLOAT_NUMBER  */
#line 450 "nl2c.y"
                   {
        store_expr((yyvsp[0].expr), "float");
        (yyval.expr) = strdup((yyvsp[0].expr));
    }
#line 1712 "nl2c.tab.c"
    break;

  case 54: /* factor: ID  */
#line 454 "nl2c.y"
         {
        char* varType = get_var_type((yyvsp[0].id));
        if(varType == NULL) {
            report_errorf("Semantic Error: undeclared variable %s", (yyvsp[0].id));
            store_expr((yyvsp[0].id), "int");
        } else {
            store_expr((yyvsp[0].id), varType);
        }
        (yyval.expr) = strdup((yyvsp[0].id));
    }
#line 1727 "nl2c.tab.c"
    break;

  case 55: /* factor: LP expr RP  */
#line 464 "nl2c.y"
                 {
        char* tmp = malloc(100);
        sprintf(tmp, "(%s)", (yyvsp[-1].expr));
        store_expr(tmp, get_type((yyvsp[-1].expr)));
        (yyval.expr) = tmp;
    }
#line 1738 "nl2c.tab.c"
    break;

  case 56: /* factor: func_expr  */
#line 470 "nl2c.y"
                {
        store_expr((yyvsp[0].expr), "int");
        (yyval.expr) = (yyvsp[0].expr);
    }
#line 1747 "nl2c.tab.c"
    break;

  case 57: /* factor: CAST expr TO FLOAT  */
#line 474 "nl2c.y"
                         {
        char* tmp = malloc(100);
        sprintf(tmp, "(float)(%s)", (yyvsp[-2].expr));
        store_expr(tmp, "float");
        (yyval.expr) = tmp;
    }
#line 1758 "nl2c.tab.c"
    break;

  case 58: /* func_expr: CALL ID WITH arg_list  */
#line 483 "nl2c.y"
                          {
        (yyval.expr) = build_call_expr((yyvsp[-2].id), (yyvsp[0].expr));
    }
#line 1766 "nl2c.tab.c"
    break;

  case 59: /* arg_list: expr arg_list_tail  */
#line 489 "nl2c.y"
                       {
        char* tmp = malloc(100);
        sprintf(tmp, "%s%s", (yyvsp[-1].expr), (yyvsp[0].expr));
        (yyval.expr) = tmp;
    }
#line 1776 "nl2c.tab.c"
    break;

  case 60: /* arg_list_tail: expr arg_list_tail  */
#line 497 "nl2c.y"
                       {
        char* tmp = malloc(100);
        sprintf(tmp, ", %s%s", (yyvsp[-1].expr), (yyvsp[0].expr));
        (yyval.expr) = tmp;
    }
#line 1786 "nl2c.tab.c"
    break;

  case 61: /* arg_list_tail: %empty  */
#line 503 "nl2c.y"
                  { (yyval.expr) = ""; }
#line 1792 "nl2c.tab.c"
    break;


#line 1796 "nl2c.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 506 "nl2c.y"


void yyerror(const char *s) {
    had_error = 1;
    printf("Error: %s\n", s);
}

extern FILE *yyin;

int main(int argc, char *argv[]) {
    if(argc > 1) {
        char *filename = strrchr(argv[1], '/');
        char *alt_filename = strrchr(argv[1], '\\');
        char *basename = argv[1];
        char *dot;

        if(filename != NULL)
            basename = filename + 1;
        if(alt_filename != NULL && alt_filename + 1 > basename)
            basename = alt_filename + 1;

        dot = strrchr(basename, '.');
        if(dot != NULL) {
            int len = (int)(dot - basename);
            sprintf(output_path, "output/%.*s.c", len, basename);
        } else {
            sprintf(output_path, "output/%s.c", basename);
        }

        yyin = fopen(argv[1], "r");
        if(!yyin) {
            printf("File not found\n");
            return 1;
        }
    }

    yyparse();

    if(out) {
        fclose(out);
        out = NULL;
    }

    if(had_error) {
        remove(output_path);
        printf("Code generation failed\n");
        return 1;
    }

    printf("C code generated in %s\n", output_path);
    return 0;
}

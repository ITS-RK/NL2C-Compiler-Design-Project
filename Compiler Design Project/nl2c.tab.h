/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_NL2C_TAB_H_INCLUDED
# define YY_YY_NL2C_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CREATE = 258,                  /* CREATE  */
    INTEGER = 259,                 /* INTEGER  */
    SET = 260,                     /* SET  */
    TO = 261,                      /* TO  */
    PRINT = 262,                   /* PRINT  */
    DEF = 263,                     /* DEF  */
    PARAMS = 264,                  /* PARAMS  */
    BEGINN = 265,                  /* BEGINN  */
    ENDFUNC = 266,                 /* ENDFUNC  */
    RETURN = 267,                  /* RETURN  */
    CALL = 268,                    /* CALL  */
    WITH = 269,                    /* WITH  */
    PLUS = 270,                    /* PLUS  */
    MINUS = 271,                   /* MINUS  */
    MUL = 272,                     /* MUL  */
    DIV = 273,                     /* DIV  */
    LP = 274,                      /* LP  */
    RP = 275,                      /* RP  */
    FLOAT = 276,                   /* FLOAT  */
    CAST = 277,                    /* CAST  */
    IF = 278,                      /* IF  */
    THEN = 279,                    /* THEN  */
    ELSE = 280,                    /* ELSE  */
    ENDIF = 281,                   /* ENDIF  */
    WHILE = 282,                   /* WHILE  */
    DO = 283,                      /* DO  */
    ENDWHILE = 284,                /* ENDWHILE  */
    FOR = 285,                     /* FOR  */
    FROM = 286,                    /* FROM  */
    STEP = 287,                    /* STEP  */
    ENDFOR = 288,                  /* ENDFOR  */
    GT = 289,                      /* GT  */
    LT = 290,                      /* LT  */
    EQ = 291,                      /* EQ  */
    NUMBER = 292,                  /* NUMBER  */
    FLOAT_NUMBER = 293,            /* FLOAT_NUMBER  */
    ID = 294,                      /* ID  */
    ARG_END = 295,                 /* ARG_END  */
    EXPR_TERM = 296                /* EXPR_TERM  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 164 "nl2c.y"

    int num;
    char *id;
    char *expr;

#line 111 "nl2c.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_NL2C_TAB_H_INCLUDED  */

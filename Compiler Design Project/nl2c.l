%{
#include "nl2c.tab.h"
#include <stdlib.h>
%}

%option noyywrap

%%
"create"            { return CREATE; }
"integer"           { return INTEGER; }
"set"               { return SET; }
"to"                { return TO; }
"print"             { return PRINT; }

"float"             { return FLOAT; }
"cast"              { return CAST; }

"if"                { return IF; }
"then"              { return THEN; }
"else"              { return ELSE; }
"end if"            { return ENDIF; }

"while"             { return WHILE; }
"do"                { return DO; }
"end while"         { return ENDWHILE; }

"for"               { return FOR; }
"from"              { return FROM; }
"step"              { return STEP; }
"end for"           { return ENDFOR; }

"define function"   { return DEF; }
"with parameters"   { return PARAMS; }
"begin"             { return BEGINN; }
"end function"      { return ENDFUNC; }
"return"            { return RETURN; }
"call"              { return CALL; }
"with"              { return WITH; }

"greater than"      { return GT; }
"less than"         { return LT; }
"equals"            { return EQ; }

"+"                 { return PLUS; }
"-"                 { return MINUS; }
"*"                 { return MUL; }
"/"                 { return DIV; }
"("                 { return LP; }
")"                 { return RP; }

[0-9]+\.[0-9]+      { yylval.expr = strdup(yytext); return FLOAT_NUMBER; }
[0-9]+              { yylval.num = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.id = strdup(yytext); return ID; }

[ \t\n]+            ;
.                   ;
%%

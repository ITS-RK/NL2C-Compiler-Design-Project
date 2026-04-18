%{
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
%}

%union {
    int num;
    char *id;
    char *expr;
}

%token CREATE INTEGER SET TO PRINT
%token DEF PARAMS BEGINN ENDFUNC RETURN CALL WITH
%token PLUS MINUS MUL DIV LP RP
%token FLOAT CAST
%token IF THEN ELSE ENDIF
%token WHILE DO ENDWHILE
%token FOR FROM STEP ENDFOR
%token GT LT EQ

%token <num> NUMBER
%token <expr> FLOAT_NUMBER
%token <id> ID

%type <expr> expr term factor func_expr arg_list arg_list_tail condition opt_step

%precedence ARG_END
%precedence EXPR_TERM
%precedence CALL LP CAST NUMBER FLOAT_NUMBER ID
%left PLUS MINUS
%left MUL DIV

%%

program:
    {
        out = fopen(output_path, "w");
        fprintf(out, "#include <stdio.h>\n");
    }
    functions
    main_block
;

functions:
    functions function
    |
;

function:
    DEF ID {
        current_param_count = 0;
        strcpy(current_function_name, $2);
        fprintf(out, "int %s(", $2);
    }
    param_list
    BEGINN {
        add_func(current_function_name, current_param_count);
        fprintf(out, "){\n");
    }
    statements
    ENDFUNC {
        fprintf(out, "}\n");
    }
;

param_list:
    PARAMS id_list
    |
    { fprintf(out, "void"); }
;

id_list:
    ID {
        current_param_count++;
        if(get_var_type($1) == NULL)
            add_var($1, "int");
        fprintf(out, "int %s", $1);
    }
    id_list_tail
;

id_list_tail:
    ID {
        current_param_count++;
        if(get_var_type($1) == NULL)
            add_var($1, "int");
        fprintf(out, ", int %s", $1);
    }
    id_list_tail
    |
;

main_block:
    {
        fprintf(out, "int main(){\n");
    }
    statements
    {
        fprintf(out, "return 0;\n}\n");
        fclose(out);
        out = NULL;
    }
;

statements:
    statements statement
    |
;

statement:
    declaration
    | assignment
    | print_stmt
    | return_stmt
    | if_stmt
    | while_stmt
    | for_stmt
;

declaration:
    CREATE INTEGER ID {
        if(get_var_type($3) != NULL) {
            report_errorf("Semantic Error: redeclaration of %s", $3);
        } else {
            add_var($3, "int");
            fprintf(out, "int %s;\n", $3);
        }
    }
    | CREATE FLOAT ID {
        if(get_var_type($3) != NULL) {
            report_errorf("Semantic Error: redeclaration of %s", $3);
        } else {
            add_var($3, "float");
            fprintf(out, "float %s;\n", $3);
        }
    }
;

assignment:
    SET ID TO expr {
        char* varType = get_var_type($2);
        char* exprType = get_type($4);

        if(varType == NULL) {
            report_errorf("Semantic Error: undeclared variable %s", $2);
        } else if(strcmp(varType, exprType) != 0) {
            if(strcmp(varType, "float") == 0 && strcmp(exprType, "int") == 0) {
                fprintf(out, "%s = (float)(%s);\n", $2, $4);
            } else {
                report_errorf("Type Error: %s <- %s", varType, exprType);
            }
        } else {
            fprintf(out, "%s = %s;\n", $2, $4);
        }
    }
;

print_stmt:
    PRINT expr {
        if(strcmp(get_type($2), "float") == 0)
            fprintf(out, "printf(\"%%f\\n\", %s);\n", $2);
        else
            fprintf(out, "printf(\"%%d\\n\", %s);\n", $2);
    }
;

return_stmt:
    RETURN expr {
        fprintf(out, "return %s;\n", $2);
    }
;

if_stmt:
    IF condition THEN {
        fprintf(out, "if (%s) {\n", $2);
    }
    statements
    opt_else
    ENDIF {
        fprintf(out, "}\n");
    }
;

opt_else:
    ELSE {
        fprintf(out, "} else {\n");
    }
    statements
    |
;

while_stmt:
    WHILE condition DO {
        fprintf(out, "while (%s) {\n", $2);
    }
    statements
    ENDWHILE {
        fprintf(out, "}\n");
    }
;

for_stmt:
    FOR ID FROM expr TO expr opt_step DO {
        fprintf(out, "for (%s = %s; %s <= %s; %s += %s) {\n", $2, $4, $2, $6, $2, $7);
    }
    statements
    ENDFOR {
        fprintf(out, "}\n");
    }
;

condition:
    expr GT expr {
        $$ = wrap_binary($1, ">", $3);
    }
    | expr LT expr {
        $$ = wrap_binary($1, "<", $3);
    }
    | expr EQ expr {
        $$ = wrap_binary($1, "==", $3);
    }
;

opt_step:
    STEP expr { $$ = $2; }
    | { $$ = "1"; }
;

expr:
    expr PLUS term {
        char* t1 = get_type($1);
        char* t2 = get_type($3);
        char* res = malloc(100);

        if(strcmp(t1, "float") == 0 || strcmp(t2, "float") == 0) {
            sprintf(res, "(float)%s + (float)%s", $1, $3);
            store_expr(res, "float");
        } else {
            sprintf(res, "%s + %s", $1, $3);
            store_expr(res, "int");
        }
        $$ = res;
    }
    | expr MINUS term {
        char* t1 = get_type($1);
        char* t2 = get_type($3);
        char* res = malloc(100);

        if(strcmp(t1, "float") == 0 || strcmp(t2, "float") == 0) {
            sprintf(res, "(float)%s - (float)%s", $1, $3);
            store_expr(res, "float");
        } else {
            sprintf(res, "%s - %s", $1, $3);
            store_expr(res, "int");
        }
        $$ = res;
    }
    | term %prec EXPR_TERM { $$ = $1; }
;

term:
    term MUL factor {
        char* t1 = get_type($1);
        char* t2 = get_type($3);
        char* res = malloc(100);

        if(strcmp(t1, "float") == 0 || strcmp(t2, "float") == 0) {
            sprintf(res, "(float)%s * (float)%s", $1, $3);
            store_expr(res, "float");
        } else {
            sprintf(res, "%s * %s", $1, $3);
            store_expr(res, "int");
        }
        $$ = res;
    }
    | term DIV factor {
        char* res = malloc(100);
        sprintf(res, "(float)%s / (float)%s", $1, $3);
        store_expr(res, "float");
        $$ = res;
    }
    | factor { $$ = $1; }
;

factor:
    NUMBER {
        char* tmp = malloc(20);
        sprintf(tmp, "%d", $1);
        store_expr(tmp, "int");
        $$ = tmp;
    }
    | FLOAT_NUMBER {
        store_expr($1, "float");
        $$ = strdup($1);
    }
    | ID {
        char* varType = get_var_type($1);
        if(varType == NULL) {
            report_errorf("Semantic Error: undeclared variable %s", $1);
            store_expr($1, "int");
        } else {
            store_expr($1, varType);
        }
        $$ = strdup($1);
    }
    | LP expr RP {
        char* tmp = malloc(100);
        sprintf(tmp, "(%s)", $2);
        store_expr(tmp, get_type($2));
        $$ = tmp;
    }
    | func_expr {
        store_expr($1, "int");
        $$ = $1;
    }
    | CAST expr TO FLOAT {
        char* tmp = malloc(100);
        sprintf(tmp, "(float)(%s)", $2);
        store_expr(tmp, "float");
        $$ = tmp;
    }
;

func_expr:
    CALL ID WITH arg_list {
        $$ = build_call_expr($2, $4);
    }
;

arg_list:
    expr arg_list_tail {
        char* tmp = malloc(100);
        sprintf(tmp, "%s%s", $1, $2);
        $$ = tmp;
    }
;

arg_list_tail:
    expr arg_list_tail {
        char* tmp = malloc(100);
        sprintf(tmp, ", %s%s", $1, $2);
        $$ = tmp;
    }
    |
    %prec ARG_END { $$ = ""; }
;

%%

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

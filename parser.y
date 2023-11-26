%{
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <iostream>

#include "location.h"
#include "ast.h"
#define YYLTYPE Location

#define MAX_LINE_LENG      256
extern int line_no, col_no, opt_list;
extern char buffer[MAX_LINE_LENG];
extern FILE *yyin;        /* declared by lex */
extern char *yytext;      /* declared by lex */
extern int yyleng;

Node *root = NULL;

extern int yylex(void);
static void yyerror(const char *msg);
extern int yylex_destroy(void);

%}

%token KPROGRAM
%token IDENTIFIER
%token LPAREN RPAREN
%token SEMICOLON COLON DOT COMMA
%token KVAR
%token KARRAY
%token LBRAC RBRAC
%token NUM
%token REAL
%token INTEGER
%token SCIENTIFIC
%token KSTRING
%token STRINGCONST
%token KOF
%token KINTEGER
%token KREAL
%token KFUNCTION
%token KPROCEDURE
%token KBEGIN KEND
%token ASSIGNMENT
%token KIF KTHEN KELSE
%token KWHILE KDO
%token LESS GREATER LESSEQUAL GREATEREQUAL EQUAL NOTEQUAL
%token PLUS MINUS
%token STAR SLASH
%token KNOT DOTDOT
%token KAND KOR

%left PLUS MINUS
%left STAR SLASH
%left Uaddop

%code requires {
    #include "ast.h"
    #include "declaration.h"
    #include "type.h"
    #include <iostream>
    using std::cout, std::endl;
}

%union {
  int val;
  char *text;
  std::list<std::string> *text_list_p;
  double dval;
  Type *type_p;

  DeclarationNodeList *decl_list_p;
}

%type <text> IDENTIFIER
%type <val> INTEGER
%type <text_list_p> identifier_list
%type <type_p> standard_type type
%type <decl_list_p> declarations

%%

    /* define your snytax here */
program: KPROGRAM IDENTIFIER LPAREN identifier_list RPAREN SEMICOLON
         declarations
         subprogram_declarations
         compound_statement
         DOT
        {
            root = NULL;
            for (auto decl: *$7) {
                cout << decl->getName() << " " << decl->getType()->name() << endl;
            }
            /*
            printf("program node is @ line: %d, column: %d\n",
                        @1.first_line, @1.first_column);
            yylval.val, yylval.text, yylval.dval to get the data (type defined in %union) you assigned by scanner.
            */
        };

identifier_list: IDENTIFIER { $$ = new std::list<std::string>(); $$->emplace_back($1); }
               | identifier_list COMMA IDENTIFIER { $$->emplace_back($3); }
               ;

declarations: declarations KVAR identifier_list COLON type SEMICOLON
            {
                for (auto &id : *$3) {
                    $1->emplace_back(new DeclarationNode($5, id));
                }
                $$ = $1;
            }
            | { $$ = new DeclarationNodeList(); }
            ;

type: standard_type { $$ = $1; }
    | KARRAY LBRAC INTEGER DOTDOT INTEGER RBRAC KOF type { $$ = new ArrayType($8, $3, $5); }
    ;

standard_type: KINTEGER {$$ = new StandardType(StandardTypeEnum::Integer); } 
             | KREAL {$$ = new StandardType(StandardTypeEnum::Real); } 
             | KSTRING{$$ = new StandardType(StandardTypeEnum::String); } 
             ;

subprogram_declarations: subprogram_declarations subprogram_declaration SEMICOLON
                       |
                       ;
 
subprogram_declaration: subprogram_head
                        declarations
                        subprogram_declarations
                        compound_statement
                        {
                            for (auto decl: *$2) {
                                cout << decl->getName() << " " << decl->getType()->name() << endl;
                            }
                        }
                      ;

subprogram_head: KFUNCTION IDENTIFIER arguments COLON standard_type SEMICOLON
               | KPROCEDURE IDENTIFIER arguments SEMICOLON
               ;

arguments: LPAREN parameter_list RPAREN
         |
         ;

parameter_list: optional_var identifier_list COLON type
              | optional_var identifier_list COLON type SEMICOLON parameter_list
              ;

optional_var: KVAR
            |
            ;

compound_statement: KBEGIN
                    statement_list
                    KEND
                  ;

statement_list: statement_list SEMICOLON statement
              | statement
              ;

statement: variable ASSIGNMENT expression
         | procedure_statement
         | compound_statement
         | KIF expression KTHEN statement KELSE statement
         | KWHILE expression KDO statement
         |
         ;

variable: IDENTIFIER tail
        ;
      
tail: LBRAC expression RBRAC tail
    |
    ;

procedure_statement: IDENTIFIER
                   | IDENTIFIER LPAREN expression_list RPAREN
                   ;

expression_list: expression 
               | expression_list COMMA expression
               ;

expression: boolexpression
          | boolexpression KAND boolexpression
          | boolexpression KOR boolexpression
          ;

boolexpression: simple_expression
              | simple_expression relop simple_expression
              ;

simple_expression: term
                 | simple_expression addop term
                 ;

term: factor
    | addop %prec Uaddop
    | term mulop factor
    ;

factor: IDENTIFIER tail
      | IDENTIFIER LPAREN expression_list RPAREN
      | number
      | addop number
      | STRINGCONST
      | LPAREN expression RPAREN
      | KNOT factor
      ;

number: INTEGER
      | REAL
      | SCIENTIFIC
      ;

addop: PLUS | MINUS;

mulop: STAR | SLASH;

relop: LESS | GREATER | EQUAL | LESSEQUAL | GREATEREQUAL | NOTEQUAL;

%%

void yyerror(const char *msg) {
    fprintf(stderr,
            "[ERROR] line %4d:%3d %s, Unmatched token: %s\n",
            line_no, col_no - yyleng, buffer, yytext);
}

int main(int argc, const char *argv[]) {

    if(argc > 2)
        fprintf( stderr, "Usage: ./parser [filename]\n" ), exit(0);

    FILE *fp = argc == 1 ? stdin : fopen(argv[1], "r");

    if(fp == NULL)
        fprintf(stderr, "Open file error\n" ), exit(-1);

    yyin = fp;
    yyparse();
    if(root){
        // do pass here
    }
    return 0;
}
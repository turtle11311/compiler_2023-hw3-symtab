%{
/*
 * scanner.l
 *
 * lex input file for pascal scanner
 *
 * extensions: two ways to spell "external" and "->" ok for "^".
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include "ast.h"
#include "parser.h"

#define MAX_LINE_LENG      256

#define YY_USER_ACTION { if (yytext[0]=='\n') { line_no++; col_no=1; } else { col_no+=strlen(yytext); } }

#define LIST       strcat(buffer, yytext)
#define LIST_FLUSH do{ if(opt_list) printf("%s", buffer); *buffer = 0; }while(0)
#define LOG(TYPE) do{ LIST; if(opt_token) fprintf(stderr, "token(type:%-10s) on line %4d, %3d : %s\n", #TYPE, line_no, col_no - yyleng, yytext); } while(0)

int opt_list = 1, opt_token = 0;
int line_no = 1, col_no = 1;
char buffer[MAX_LINE_LENG];
static int commentStack = 0;

void scannerLog(const char* format, ...) {
  if (!opt_token) return;
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
}

%}

%option nounput
%option noinput

INTEGER [0-9]+
REAL {INTEGER}("."0*{INTEGER})?
SCIENTIFIC {REAL}(?i:e)[+-]?{INTEGER}
NQUOTE [^']
ALPHA [a-zA-Z]
ALPHANUM [a-zA-Z0-9]
ALNUMUNDER [a-zA-Z0-9_]
IDENTIFIER {ALPHA}|{ALPHA}{ALNUMUNDER}*{ALPHANUM}

%x CXXCOMMENT

%%

#\ *pragma\ +list\ +on        { opt_list = true; LIST; }
#\ *pragma\ +list\ +off       { opt_list = false; LIST; }

(?i:program)                  { LOG(KEYWORD); return(KPROGRAM); }
"("                           { LOG(KEYWORD); return(LPAREN); }
")"                           { LOG(KEYWORD); return(RPAREN); }
";"                           { LOG(KEYWORD); return(SEMICOLON); }
":"                           { LOG(KEYWORD); return(COLON); }
"."                           { LOG(KEYWORD); return(DOT); }
","                           { LOG(KEYWORD); return(COMMA); }
(?i:var)                      { LOG(KEYWORD); return(KVAR); }
(?i:array)                    { LOG(KEYWORD); return(KARRAY); }
"["                           { LOG(KEYWORD); return(LBRAC); }
"]"                           { LOG(KEYWORD); return(RBRAC); }
({REAL}|{SCIENTIFIC})         { LOG(NUMBER); return(NUM); }
(?i:string)                   { LOG(KEYWORD); return(KSTRING); }
\"([^"])*\"                   { LOG(STRING); return(STRINGCONST); }
(?i:of)                       { LOG(KEYWORD); return(KOF); }
(?i:integer)                  { LOG(KEYWORD); return(KINTEGER); }
(?i:real)                     { LOG(KEYWORD); return(KREAL); }
(?i:function)                 { LOG(KEYWORD); return(KFUNCTION); }
(?i:procedure)                { LOG(KEYWORD); return(KPROCEDURE); }
(?i:begin)                    { LOG(KEYWORD); return(KBEGIN); }
(?i:end)                      { LOG(KEYWORD); return(KEND); }
":="                          { LOG(KEYWORD); return(ASSIGNMENT); }
(?i:if)                       { LOG(KEYWORD); return(KIF); }
(?i:then)                     { LOG(KEYWORD); return(KTHEN); }
(?i:else)                     { LOG(KEYWORD); return(KELSE); }
(?i:while)                    { LOG(KEYWORD); return(KWHILE); }
(?i:do)                       { LOG(KEYWORD); return(KDO); }
"<"                           { LOG(KEYWORD); return(LESS); }
">"                           { LOG(KEYWORD); return(GREATER); }
"<="                          { LOG(KEYWORD); return(LESSEQUAL); }
">="                          { LOG(KEYWORD); return(GREATEREQUAL); }
"="                           { LOG(KEYWORD); return(EQUAL); }
"!="                          { LOG(KEYWORD); return(NOTEQUAL); }
"+"                           { LOG(KEYWORD); return(PLUS); }
"-"                           { LOG(KEYWORD); return(MINUS); }
"*"                           { LOG(KEYWORD); return(STAR); }
"/"                           { LOG(KEYWORD); return(SLASH); }
(?i:not)                      { LOG(KEYWORD); return(KNOT); }
".."                          { LOG(KEYWORD); return(DOTDOT); }
(?i:and)                      { LOG(KEYWORD); return(KAND); }
(?i:or)                       { LOG(KEYWORD); return(KOR); }

{IDENTIFIER}                  { LOG(IDENTIFIER); return(IDENTIFIER); }

"//".*                        { LIST; scannerLog("[INFO ] line%5d:%3lu comment string\n", line_no, col_no - yyleng); }
"/*"                          { LIST; BEGIN(CXXCOMMENT); commentStack=1; 
                                scannerLog("[INFO ] line%5d:%3lu comment string start\n", 
                                  line_no, col_no-strlen(yytext), yytext);
                              }
<CXXCOMMENT>"/*"              { LIST; commentStack++; }
<CXXCOMMENT>"*/"              { 
                                LIST;
                                commentStack--;
                                if (commentStack <= 0) {
                                  BEGIN(INITIAL);
                                  scannerLog("[INFO ] line%5d:%3lu comment string end\n", line_no, col_no - yyleng);
                                }
                              }
<CXXCOMMENT>.|\n              { LIST; LIST_FLUSH; }

[ \t\f]                       { LIST; }

\r                            { LIST; }
<INITIAL>\n                   { LIST; LIST_FLUSH; }


.    { LIST; fprintf(stderr, "[ERROR] line %4d:%3d lexical analyzer error %s\n", line_no, col_no - yyleng, yytext); }

%%
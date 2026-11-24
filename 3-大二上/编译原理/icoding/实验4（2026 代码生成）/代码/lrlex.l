%{
#include "ast.h"
#include "lrparser.tab.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
int cur_line_num = 1;
int atoi_octal(char* oct);
int atoi_hex(char* hex);
char* save_id(const char* source);
void lex_error(char* msg, int line);
void count();
%}

SINGLE_COMMENT      ("
MULTI_COMMENT       ("/*"([^*]|[*][^/])*"*/")
DECIMAL             ("0"|[1-9][0-9]*)
HEXADECIMAL         ("0"[Xx]{1}[0-9a-fA-F]+)
OCTAL               ("0"[0-7]*)
STRING              (\042[^\042\n]*\042)
UNTERM_STRING       (\042[^\042\n]*)
IDENTIFIER          ([_a-zA-Z][_a-zA-Z0-9]*)

%%
"auto"			{ count(); return(AUTO); }
"break"			{ count(); yylval.v_string = "break"; return(BREAK); }
"case"			{ count(); return(CASE); }
"char"			{ count(); return(CHAR); }
"const"			{ count(); return(CONST); }
"continue"		{ count(); yylval.v_string = "continue"; return(CONTINUE); }
"default"		{ count(); return(DEFAULT); }
"do"			{ count(); return(DO); }
"double"		{ count(); return(DOUBLE); }
"else"			{ count(); yylval.v_string = "else"; return(ELSE); }
"enum"			{ count(); return(ENUM); }
"extern"		{ count(); return(EXTERN); }
"float"			{ count(); return(FLOAT); }
"for"			{ count(); return(FOR); }
"goto"			{ count(); return(GOTO); }
"if"			{ count(); yylval.v_string = "if"; return(IF); }
"int"			{ count(); yylval.v_string = "int"; return(INT); }
"long"			{ count(); return(LONG); }
"register"		{ count(); return(REGISTER); }
"return"		{ count(); yylval.v_string = "return"; return(RETURN); }
"short"			{ count(); return(SHORT); }
"signed"		{ count(); return(SIGNED); }
"sizeof"		{ count(); return(SIZEOF); }
"static"		{ count(); return(STATIC); }
"struct"		{ count(); return(STRUCT); }
"switch"		{ count(); return(SWITCH); }
"typedef"		{ count(); return(TYPEDEF); }
"union"			{ count(); return(UNION); }
"unsigned"		{ count(); return(UNSIGNED); }
"void"			{ count(); yylval.v_string = "void"; return(VOID); }
"volatile"		{ count(); return(VOLATILE); }
"while"			{ count(); yylval.v_string = "while"; return(WHILE); }
"putint"        { count(); yylval.v_string = "putint"; return(PUTINT); }
"..."			{ count(); return(ELLIPSIS); }
">>="			{ count(); return(RIGHT_ASSIGN); }
"<<="			{ count(); return(LEFT_ASSIGN); }
"+="			{ count(); return(ADD_ASSIGN); }
"-="			{ count(); return(SUB_ASSIGN); }
"*="			{ count(); return(MUL_ASSIGN); }
"/="			{ count(); return(DIV_ASSIGN); }
"%="			{ count(); return(MOD_ASSIGN); }
"&="			{ count(); return(AND_ASSIGN); }
"^="			{ count(); return(XOR_ASSIGN); }
"|="			{ count(); return(OR_ASSIGN); }
">>"			{ count(); return(RIGHT_OP); }
"<<"			{ count(); return(LEFT_OP); }
"++"			{ count(); return(INC_OP); }
"--"			{ count(); return(DEC_OP); }
"->"			{ count(); return(PTR_OP); }
"&&"			{ count(); return(AND_OP); }
"||"			{ count(); return(OR_OP); }
"<="			{ count(); return(LE_OP); }
">="			{ count(); return(GE_OP); }
"=="			{ count(); return(EQ_OP); }
"!="			{ count(); return(NE_OP); }
";"			{ count(); return(';'); }
("{"|"<%")		{ count(); return('{'); }
("}"|"%>")		{ count(); return('}'); }
","			{ count(); return(','); }
":"			{ count(); return(':'); }
"="			{ count(); return('='); }
"("			{ count(); return('('); }
")"			{ count(); return(')'); }
("["|"<:")		{ count(); return('['); }
("]"|":>")		{ count(); return(']'); }
"."			{ count(); return('.'); }
"&"			{ count(); return('&'); }
"!"			{ count(); return('!'); }
"~"			{ count(); return('~'); }
"-"			{ count(); return('-'); }
"+"			{ count(); return('+'); }
"*"			{ count(); return('*'); }
"/"			{ count(); return('/'); }
"%"			{ count(); return('%'); }
"<"			{ count(); return('<'); }
">"			{ count(); return('>'); }
"^"			{ count(); return('^'); }
"|"			{ count(); return('|'); }
"?"			{ count(); return('?'); }
[ \t\v\f]		{ count(); }
[\n]                { count(); cur_line_num++; }
{SINGLE_COMMENT}    { }
{MULTI_COMMENT}     { }
{DECIMAL}           { count(); yylval.v_int = atoi(yytext); return DECIMAL; }
{OCTAL}             { count(); yylval.v_int = atoi_octal(yytext); return OCTAL; }
{HEXADECIMAL}       { count(); yylval.v_int = atoi_hex(yytext); return HEXADECIMAL; }
{STRING}            { count(); return STRING_LITERAL; }
{IDENTIFIER}        { count(); yylval.v_string = save_id(yytext); return IDENTIFIER; }
<<EOF>>             { return 0; }
{UNTERM_STRING}     { lex_error("Unterminated string constant", cur_line_num); }
.                   { lex_error("Unrecognized character", cur_line_num); }

%%

int atoi_octal(char* oct) {
    int octal=0;
    for(int i=strlen(oct)-1;i>0;i--)
    {
        octal+=(oct[i]-48)*pow(8,strlen(oct)-i-1);
    }

    return octal;
}

int atoi_hex(char* hex) {
    int hexadecimal=0;
    
    for(int i = 2; i < strlen(hex); i++) {
        hexadecimal *= 16;
        if(hex[i] >= '0' && hex[i] <= '9')
            hexadecimal += hex[i] - '0';
        else if(hex[i] >= 'a' && hex[i] <= 'f')
            hexadecimal += hex[i] - 'a' + 10;
        else if(hex[i] >= 'A' && hex[i] <= 'F')
            hexadecimal += hex[i] - 'A' + 10;
    }
    return hexadecimal;
}

char* save_id(const char* source) {
    int len = strlen(source); 
    char* des = (char*)malloc(len + 1); 
    strcpy(des, source); 
    return des;
}

void lex_error(char* msg, int line) {
    printf("\nError at line %-3d: %s\n\n", line, msg);
}

int yywrap(void) {
    return 1;
}

int column = 0;

void count() {
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;
}

%{

#include <stdio.h>
#include "ast.h"
#include <stdlib.h>
int yylex(void);
void yyerror(char *);
extern ast* ast_root;

%}

%token SIZEOF STRING_LITERAL
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT SWITCH DO FOR GOTO

%union{
	int	v_int;
	char*	v_string;
	ast*	p_ast;
}

%token <v_int> DECIMAL OCTAL HEXADECIMAL
%token <v_string> IDENTIFIER INT VOID IF ELSE WHILE CONTINUE BREAK RETURN PUTINT
%type  <v_string> BType
%type  <p_ast> AddExp Exp Number MulExp UnaryExp LVal PrimaryExp LVal_A UnaryOp
%type  <p_ast> FuncFParams_A FuncFParams FuncFParam_A FuncFParam FuncRParams_A FuncRParams
%type  <p_ast> CompUnit Decl ConstDecl_A ConstDecl ConstDef_A ConstDef ConstInitVal_A ConstInitVal VarDecl
%type  <p_ast> VarDef_A VarDef InitVal_A InitVal FuncDef Block_A Block BlockItem Stmt
%type  <p_ast> RelExp EqExp LAndExp LOrExp ConstExp Cond VarDecl_A Start
%type  <p_ast> ConstAddExp ConstMulExp ConstUnaryExp ConstPrimaryExp

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%start Start

%%

Start
    : CompUnit		{$$=$1;ast_root=$1;}
    ;

CompUnit
    : Decl		{$$ = new_comp_unit(NULL,$1);}
    | FuncDef		{$$ = new_comp_unit(NULL,$1);}
    | Decl CompUnit  	{$$ = new_comp_unit($2,$1);}
    | FuncDef CompUnit 	{$$ = new_comp_unit($2,$1);}
    ;

Decl
    : ConstDecl		{$$ = $1;}
    | VarDecl		{$$ = $1;}
    ;

ConstDecl_A
    : ',' ConstDef		{$$ = new_const_decl("",$2,NULL);}
    | ',' ConstDef ConstDecl_A	{$$ = new_const_decl("",$2,$3);}
    ;


ConstDecl
    : CONST BType ConstDef ';'		{$$ = new_const_decl($2,$3,NULL);}
    | CONST BType ConstDef ConstDecl_A ';'{$$ = new_const_decl($2,$3,$4);}
    ;

BType
    : INT			{$$ = $1;}
    ;


ConstDef_A
    : '[' ConstExp ']'			{$$ = new_const_def_a(NULL,$2);}
    | '[' ConstExp ']' ConstDef_A	{$$ = new_const_def_a($4,$2);}
    ;


ConstDef
    : IDENTIFIER '=' ConstInitVal		{$$ = new_const_def($1,NULL,$3);}
    | IDENTIFIER ConstDef_A '=' ConstInitVal	{$$ = new_const_def($1,$2,$4);}
    ;

ConstInitVal_A
    : ',' ConstInitVal			{$$ = new_const_init(NULL,$2,"");}
    | ',' ConstInitVal ConstInitVal_A 	{$$ = new_const_init($3,$2,"");}
    ;


ConstInitVal
    : ConstExp			{$$ = new_const_init(NULL,$1,"");}
    | '{' ConstInitVal '}'	{$$ = new_const_init(NULL,$2,"{}");}
    | '{' '}'			{$$ = new_const_init(NULL,NULL,"{}");}
    | '{' ConstInitVal ConstInitVal_A '}'	{$$ = new_const_init($3,$2,"{}");}
    ;


VarDecl_A
    : ',' VarDef		{$$ = new_var_decl("",NULL,$2);}
    | ',' VarDef VarDecl_A 	{$$ = new_var_decl("",$3,$2);}
    ;


VarDecl
    : BType VarDef ';'		{$$ = new_var_decl($1,NULL,$2);}
    | BType VarDef VarDecl_A ';'{$$ = new_var_decl($1,$3,$2);}
    ;


VarDef_A
    : '[' ConstExp ']'		{$$ = new_var_def_a(NULL,$2);}
    | '[' ConstExp ']' VarDef_A {$$ = new_var_def_a($4,$2);}
    ;


VarDef
    : IDENTIFIER			{$$ = new_var_def($1,NULL,NULL);}
    | IDENTIFIER VarDef_A		{$$ = new_var_def($1,$2,NULL);}
    | IDENTIFIER '=' InitVal		{$$ = new_var_def($1,NULL,$3);}
    | IDENTIFIER VarDef_A '=' InitVal	{$$ = new_var_def($1,$2,$4);}
    ;

InitVal_A
    : ',' InitVal			{$$ = new_init_var($2,"",NULL);}
    | ',' InitVal InitVal_A 		{$$ = new_init_var($2,"",$3);}
    ;


InitVal
    : Exp				{$$ = new_init_var($1,"",NULL);}
    | '{' InitVal '}'			{$$ = new_init_var($2,"{}",NULL);}
    | '{' '}'				{$$ = new_init_var(NULL,"{}",NULL);}
    | '{' InitVal InitVal_A '}'		{$$ = new_init_var($2,"{}",$3);}
    ;


FuncDef
    : VOID IDENTIFIER '(' ')' Block		{$$ = new_func_def($1,$2,NULL,$5);}
    | VOID IDENTIFIER '(' FuncFParams ')' Block {$$ = new_func_def($1,$2,$4,$6);}
    | BType IDENTIFIER '(' ')' Block		{$$ = new_func_def($1,$2,NULL,$5);}
    | BType IDENTIFIER '(' FuncFParams ')' Block{$$ = new_func_def($1,$2,$4,$6);}
    ;

FuncFParams_A
    : ',' FuncFParam		{$$ = new_func_params(NULL, $2);}
    | ',' FuncFParam FuncFParams_A {$$ = new_func_params($3, $2);}
    ;


FuncFParams
    : FuncFParam		{$$ = new_func_params(NULL, $1);}
    | FuncFParam FuncFParams_A	{$$ = new_func_params($2, $1);}
    ;

FuncFParam_A
    : '[' ']'				{$$ = new_square_brackets(NULL,NULL);}
    | '[' Exp ']'			{$$ = new_square_brackets(NULL,$2);}
    | '[' ']' FuncFParam_A 		{$$ = new_square_brackets($3,NULL);}
    | '[' Exp ']' FuncFParam_A 		{$$ = new_square_brackets($4,$2);}
    ;


FuncFParam
    : BType IDENTIFIER			{$$ = new_func_param($1, $2, NULL);}
    | BType IDENTIFIER FuncFParam_A	{$$ = new_func_param($1, $2, $3);}
    ;


Block_A
    : BlockItem				{$$ = new_block_item(NULL,$1);}
    | BlockItem Block_A			{$$ = new_block_item($2,$1);}
    ;


Block
    : '{' '}'				{$$ = new_block(NULL,NULL);}
    | '{' Block_A '}'			{$$ = new_block(NULL,$2);}
    ;

BlockItem
    : Decl	{$$=$1;}
    | Stmt	{$$=$1;}
    ;


Stmt
    : LVal '=' Exp ';'			{$$=new_stmt("=","",$1,$3,NULL);}
    | ';'				{$$=new_stmt("","",NULL,NULL,NULL);}
    | Exp ';'				{$$=new_stmt("","",$1,NULL,NULL);}
    | Block				{$$=new_stmt("","",$1,NULL,NULL);}
    | IF '(' Cond ')' Stmt %prec LOWER_THAN_ELSE		{$$=new_stmt($1,"",$3,$5,NULL);}
    | IF '(' Cond ')' Stmt ELSE Stmt	{$$=new_stmt($1,$6,$3,$5,$7);}
    | WHILE '(' Cond ')' Stmt		{$$=new_stmt($1,"",$3,$5,NULL);}
    | BREAK ';'				{$$=new_stmt($1,"",NULL,NULL,NULL);}
    | CONTINUE ';'			{$$=new_stmt($1,"",NULL,NULL,NULL);}
    | RETURN ';'			{$$=new_stmt($1,"",NULL,NULL,NULL);}
    | RETURN Exp ';'			{$$=new_stmt($1,"",$2,NULL,NULL);}
    | PUTINT '(' Exp ')' ';'	{$$=new_stmt($1,"",$3,NULL,NULL);}
    ;

Exp
    : AddExp	{$$=$1;}
    ;

Cond
    : LOrExp	{$$=$1;}
    ;

LVal_A
    : '[' Exp ']'	{$$ = new_subscript(NULL, $2);}
    | '[' Exp ']' LVal_A{$$ = new_subscript($4, $2);}
    ;

LVal
    : IDENTIFIER	{$$ = new_id($1);}
    | IDENTIFIER LVal_A {$$ = new_id_with_subscript($1,$2);}
    ;

PrimaryExp
    : '(' Exp ')'	{$$ = $2;}
    | LVal		{$$ = $1;}
    | Number		{$$ = $1;}
    ;


Number
    : DECIMAL 		{$$ = new_dec($1);}
    | OCTAL		{$$ = new_oct($1);}
    | HEXADECIMAL	{$$ = new_hex($1);}
    ;


UnaryExp
    : PrimaryExp			{$$ = $1;}
    | IDENTIFIER '(' ')'		{$$ = new_func_call_id($1,NULL);}
    | IDENTIFIER '(' FuncRParams ')'	{$$ = new_func_call_id($1,$3);}
    | UnaryOp UnaryExp			{$$ = new_exp_with_unary_op($1,$2);}
    ;


UnaryOp
    : '+'				{$$ = new_unary_op('+');}
    | '-'				{$$ = new_unary_op('-');}
    | '!'				{$$ = new_unary_op('!');}
    ;

FuncRParams_A
    : ',' Exp			{$$ = new_func_call_param(NULL, $2);}
    | ',' Exp FuncRParams_A	{$$ = new_func_call_param($3, $2);}
    ;


FuncRParams
    : Exp			{$$ = new_func_call_param(NULL,$1);}
    | Exp FuncRParams_A		{$$ = new_func_call_param($2, $1);}
    ;

MulExp
    : UnaryExp			{$$ = $1;}
    | MulExp '*' UnaryExp	{$$ = new_expr_mul('*', $1, $3);}
    | MulExp '/' UnaryExp	{$$ = new_expr_mul('/', $1, $3);}
    | MulExp '%' UnaryExp	{$$ = new_expr_mul('%', $1, $3);}
    ;


AddExp
    : MulExp			{$$ = $1;}
    | AddExp '+' MulExp		{$$ = new_expr('+', $1, $3);}
    | AddExp '-' MulExp		{$$ = new_expr('-', $1, $3);}
    ;

RelExp
    : AddExp			{$$ = new_rel_exp("",$1,NULL);}
    | RelExp '<' AddExp		{$$ = new_rel_exp("<",$1,$3);}
    | RelExp '>' AddExp		{$$ = new_rel_exp(">",$1,$3);}
    | RelExp LE_OP AddExp	{$$ = new_rel_exp("<=",$1,$3);}
    | RelExp GE_OP AddExp	{$$ = new_rel_exp(">=",$1,$3);}
    ;

EqExp
    : RelExp			{$$ = new_eq_exp("",$1,NULL);}
    | EqExp EQ_OP RelExp	{$$ = new_eq_exp("==",$1,$3);}
    | EqExp NE_OP RelExp  	{$$ = new_eq_exp("!=",$1,$3);}
    ;

LAndExp
    : EqExp			{$$ = new_l_and_exp("",$1,NULL);}
    | LAndExp AND_OP EqExp	{$$ = new_l_and_exp("&&",$1,$3);}
    ;

LOrExp
    : LAndExp			{$$ = new_l_or_exp("",$1,NULL);}
    | LOrExp OR_OP LAndExp	{$$ = new_l_or_exp("||",$1,$3);}
    ;

ConstExp
    : ConstAddExp		{$$ = $1;}
    ;

ConstAddExp
    : ConstMulExp			{$$ = $1;}
    | ConstAddExp '+' ConstMulExp		{$$ = new_expr('+', $1, $3);}
    | ConstAddExp '-' ConstMulExp		{$$ = new_expr('-', $1, $3);}
    ;

ConstMulExp
    : ConstUnaryExp			{$$ = $1;}
    | ConstMulExp '*' ConstUnaryExp	{$$ = new_expr_mul('*', $1, $3);}
    | ConstMulExp '/' ConstUnaryExp	{$$ = new_expr_mul('/', $1, $3);}
    | ConstMulExp '%' ConstUnaryExp	{$$ = new_expr_mul('%', $1, $3);}
    ;


ConstUnaryExp
    : ConstPrimaryExp			{$$ = $1;}
    | UnaryOp ConstUnaryExp			{$$ = new_exp_with_unary_op($1,$2);}
    ;

ConstPrimaryExp
    : '(' ConstExp ')'	{$$ = $2;}
    | Number		{$$ = $1;}
    ;
%%
extern char yytext[];
extern int column;

void yyerror(char *s) {
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
	exit(0);
}
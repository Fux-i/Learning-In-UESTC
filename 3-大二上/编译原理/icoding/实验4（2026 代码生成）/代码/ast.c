#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"

void show_ast(ast* node, int nest) {
	if(node == NULL)
		return;
    if(nest == 0)
        printf("\n");
	for(int i=0; i<nest; i++)
		printf("  ");
	if(strcmp(node->node_type, "DECIMAL") == 0)
		printf("%s %d\n", node->node_type, node->value_int);
    else if(strcmp(node->node_type, "OCTAL") == 0)
        printf("%s '%#o'\n", node->node_type, node->value_int);
    else if(strcmp(node->node_type, "HEXADECIMAL") == 0)
        printf("%s '%#x'\n", node->node_type, node->value_int);
	else if(strcmp(node->node_type, "EXPR") == 0)
		printf("%s '%c'\n", node->node_type, (char)node->value_int);
    else if(strcmp(node->node_type, "EXPR_MUL") == 0)
        printf("%s '%c'\n", node->node_type, (char)node->value_int);
    else if(strcmp(node->node_type, "IDENTIFIER") == 0)
        printf("%s '%s'\n", node->node_type, node->value_string);
    else if(strcmp(node->node_type, "SUBSCRIPT") == 0)
        printf("%s '%s'\n", node->node_type, node->value_string);
    else if(strcmp(node->node_type, "ID_WITH_SUBSCRIPT") == 0)
        printf("%s '%s'\n", node->node_type, node->value_string);
    else if(strcmp(node->node_type, "NEW_UNARY_OP") == 0)
        printf("%s '%s'\n", node->node_type, node->value_string);
    else if(strcmp(node->node_type, "EXP_WITH_UNARY_OP") == 0)
        printf("%s\n", node->node_type);
    else if(strcmp(node->node_type, "FUNC_PARAMS") == 0)
        printf("%s\n", node->node_type);
    else if(strcmp(node->node_type, "SQUARE_BRACKETS") == 0)
        printf("%s '%s'\n", node->node_type, node->value_string);
    else if(strcmp(node->node_type, "FUNC_PARAM") == 0)
        printf("%s '%s' '%s'\n", node->node_type, node->value_string, node->value_string1);
    else if(strcmp(node->node_type, "FUNC_CALL_ID") == 0)
        printf("%s '%s'\n", node->node_type, node->value_string);
    else if(strcmp(node->node_type, "FUNC_CALL_PARAM") == 0)
        printf("%s\n", node->node_type);
    else if(strcmp(node->node_type, "CONST_INIT") == 0)
        printf("%s '%s'\n", node->node_type, node->value_string);
    else if(strcmp(node->node_type, "CONST_DEF_A") == 0)
        printf("%s '%s'\n", node->node_type, node->value_string);
    else if(strcmp(node->node_type, "CONST_DEF") == 0)
        printf("%s '%s'\n", node->node_type, node->value_string);
    else if(strcmp(node->node_type, "CONST_DECL") == 0)
        printf("%s '%s'\n", node->node_type, node->value_string);
    else if(strcmp(node->node_type, "VAR_DECL") == 0)
        printf("%s '%s'\n", node->node_type, node->value_string);
    else if(strcmp(node->node_type, "VAR_DEF_A") == 0)
        printf("%s '%s'\n", node->node_type, node->value_string);
    else if(strcmp(node->node_type, "VAR_DEF") == 0)
        printf("%s '%s'\n", node->node_type, node->value_string);
    else if(strcmp(node->node_type, "INIT_VAL") == 0)
        printf("%s\n", node->node_type);
    else if(strcmp(node->node_type, "INIT_VAR") == 0)
        printf("%s '%s'\n", node->node_type, node->value_string);
    else if(strcmp(node->node_type, "FUNC_DEF") == 0)
        printf("%s '%s' '%s'\n", node->node_type, node->value_string, node->value_string1);
    else if(strcmp(node->node_type, "BLOCK_ITEM") == 0)
        printf("%s\n", node->node_type);
    else if(strcmp(node->node_type, "BLOCK") == 0)
        printf("%s\n", node->node_type);
    else if(strcmp(node->node_type, "STMT") == 0)
        print_support(node->node_type, node->value_string, &nest);
    else if(strcmp(node->node_type, "L_OR_EXP") == 0)
        print_support(node->node_type, node->value_string, &nest);
    else if(strcmp(node->node_type, "L_AND_EXP") == 0)
        print_support(node->node_type, node->value_string, &nest);
    else if(strcmp(node->node_type, "EQ_EXP") == 0)
        print_support(node->node_type, node->value_string, &nest);
    else if(strcmp(node->node_type, "REL_EXP") == 0)
        print_support(node->node_type, node->value_string, &nest);
    else if(strcmp(node->node_type, "COMP_UNIT") == 0)
        printf("%s\n", node->node_type);

    else printf("\ncannot match node_type.\n");

    show_ast(node->left, nest+1);
    show_ast(node->right, nest+1);
    show_ast(node->extend, nest+1);
    show_ast(node->next, nest);
}

void print_support(char* type, char* string, int* nest) {
    if(strcmp(string, "") == 0) {
        for(int i=0; i<(*nest); i++)
            printf("\b\b");
        (*nest)--;
    }
    else printf("%s '%s'\n", type, string);
}

ast* new_node() {
    ast* new_node = (ast *)malloc(sizeof(ast));
	if(new_node == NULL)
	{
		printf("run out of memory.\n");
		exit(0);
	}
	memset(new_node, 0, sizeof(ast));
	return new_node;
}

ast* new_dec(int value) {
	ast* var = new_node();
	var->node_type = "DECIMAL";
	var->value_int = value;
	return var;
}

ast* new_oct(int value) {
    ast* var = new_node();
    var->node_type = "OCTAL";
    var->value_int = value;
    return var;
}

ast* new_hex(int value) {
    ast* var = new_node();
    var->node_type = "HEXADECIMAL";
    var->value_int = value;
    return var;
}

ast* new_expr(int op, ast* left, ast* right) {
    ast* var = new_node();
	var->node_type = "EXPR";
	var->value_int = op;
	var->left = left;
	var->right = right;
	return var;
}

ast* new_expr_mul(int op, ast* left, ast* right) {
    ast* var = new_node();
    var->node_type = "EXPR_MUL";
    var->value_int = op;
    var->left = left;
    var->right = right;
    return var;
}

ast* new_id(char* value) {
    ast* var = new_node();
    var->node_type = "IDENTIFIER";
    var->value_string = value;
    return var;
}

ast* new_subscript(ast* next, ast* right) {
    ast* var = new_node();
    var->node_type = "SUBSCRIPT";
    var->value_string = "[ ]";
    var->next = next;
    var->right = right;
    return var;
}

ast* new_id_with_subscript(char* value, ast* right) {
    ast* var = new_node();
    var->node_type = "ID_WITH_SUBSCRIPT";
    var->value_string = value;
    var->right = right;
    return var;
}

ast* new_unary_op(int value) {
    ast* var = new_node();
    var->node_type = "NEW_UNARY_OP";
    var->value_int = value;
    return var;
}

ast* new_exp_with_unary_op(ast* left, ast* right) {
    ast* var = new_node();
    var->node_type = "EXP_WITH_UNARY_OP";
    var->left = left;
    var->right = right;
    return var;
}

ast* new_func_params(ast* next, ast* right) {
    ast* var = new_node();
    var->node_type = "FUNC_PARAMS";
    var->next = next;
    var->right = right;
    return var;
}

ast* new_square_brackets(ast* next, ast* right) {
    ast* var = new_node();
    var->node_type = "SQUARE_BRACKETS";
    var->value_string = "[ ]";
    var->next = next;
    var->right = right;
    return var;
}

ast* new_func_param(char* value1, char* value2, ast* left) {
    ast* var = new_node();
    var->node_type = "FUNC_PARAM";
    var->value_string = value1;
    var->value_string1 = value2;
    var->left = left;
    return var;
}

ast* new_func_call_id(char* value, ast* right) {
    ast* var = new_node();
    var->node_type = "FUNC_CALL_ID";
    var->value_string = value;
    var->right = right;
    return var;
}

ast* new_func_call_param(ast* next, ast* right) {
    ast* var = new_node();
    var->node_type = "FUNC_CALL_PARAM";
    var->next = next;
    var->right = right;
    return var;
}

ast* new_const_init(ast* next, ast* right, char* indicator) {
    ast* var = new_node();
    var->node_type = "CONST_INIT";
    var->value_string = indicator;
    var->next = next;
    var->right = right;
    return var;
}

ast* new_const_def_a(ast* next, ast* right) {
    ast* var = new_node();
    var->node_type = "CONST_DEF_A";
    var->value_string = "[]";
    var->next = next;
    var->right = right;
    return var;
}

ast* new_const_def(char* value, ast* left, ast* right) {
    ast* var = new_node();
    var->node_type = "CONST_DEF";
    var->value_string = value;
    var->left = left;
    var->right = right;
    return var;
}

ast* new_const_decl(char* value, ast* right, ast* next) {
    ast* var = new_node();
    var->node_type = "CONST_DECL";
    var->value_string = value;
    var->right = right;
    var->next = next;
    return var;
}

ast* new_var_decl(char* value, ast* next, ast* right) {
    ast* var = new_node();
    var->node_type = "VAR_DECL";
    var->value_string = value;
    var->next = next;
    var->right = right;
    return var;
}

ast* new_var_def_a(ast* next, ast* right) {
    ast* var = new_node();
    var->node_type = "VAR_DEF_A";
    var->value_string = "[]";
    var->next = next;
    var->right = right;
    return var;
}

ast* new_var_def(char* value, ast* left, ast* right) {
    ast* var = new_node();
    var->node_type = "VAR_DEF";
    var->value_string = value;
    var->left = left;
    var->right = right;
    return var;
}

ast* new_init_var(ast* right, char* indicator, ast* next) {
    ast* var = new_node();
    var->node_type = "INIT_VAR";
    var->value_string = indicator;
    var->right = right;
    var->next = next;
    return var;
}

ast* new_func_def(char* value1, char* value2, ast* left, ast* right) {
    ast* var = new_node();
    var->node_type = "FUNC_DEF";
    var->value_string = value1;
    var->value_string1 = value2;
    var->left = left;
    var->right = right;
    return var;
}

ast* new_block_item(ast* next, ast* right) {
    ast* var = new_node();
    var->node_type = "BLOCK_ITEM";
    var->next = next;
    var->right = right;
    return var;
}

ast* new_block(ast* next, ast* right) {
    ast* var = new_node();
    var->node_type = "BLOCK";
    var->next = next;
    var->right = right;
    return var;
}

ast* new_stmt(char* value1,char* value2,ast* left,ast* right,ast* extend) {
    ast* var = new_node();
    var->node_type = "STMT";
    var->value_string = value1;
    var->value_string1 = value2;
    var->left = left;
    var->right = right;
    var->extend = extend;
    return var;
}

ast* new_l_or_exp(char* value, ast* left, ast* right) {
    ast* var = new_node();
    var->node_type = "L_OR_EXP";
    var->value_string = value;
    var->left = left;
    var->right = right;
    return var;
}

ast* new_l_and_exp(char* value, ast* left, ast* right) {
    ast* var = new_node();
    var->node_type = "L_AND_EXP";
    var->value_string = value;
    var->left = left;
    var->right = right;
    return var;
}

ast* new_eq_exp(char* value, ast* left, ast* right) {
    ast* var = new_node();
    var->node_type = "EQ_EXP";
    var->value_string = value;
    var->left = left;
    var->right = right;
    return var;
}

ast* new_rel_exp(char* value, ast* left, ast* right) {
    ast* var = new_node();
    var->node_type = "REL_EXP";
    var->value_string = value;
    var->left = left;
    var->right = right;
    return var;
}

ast* new_comp_unit(ast* next, ast* right) {
    ast* var = new_node();
    var->node_type = "COMP_UNIT";
    var->next = next;
    var->right = right;
    return var;
}

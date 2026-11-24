#ifndef GENLLVM_H
#define GENLLVM_H

#include "ast.h"

int genllvm(ast* root);

/* 题目要求的代码生成接口: 指令逐行写入 result */
int genArithmeticExpr(ast* node, char* result);
int genLogicExpr(ast* node, char* result);
int genAssignStmt(ast* node, char* result);
int genIfStmt(ast* node, char* result);
int genWhileStmt(ast* node, char* result);

#endif

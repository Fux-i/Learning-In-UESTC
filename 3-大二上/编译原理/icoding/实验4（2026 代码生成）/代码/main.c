#include "genllvm.h"
#include <stdio.h>
#include "ast.h"

ast *ast_root;
extern int yyparse(void);

int main()
{
    yyparse();
    // show_ast(ast_root,0);
    genllvm(ast_root);

    return 0;
}
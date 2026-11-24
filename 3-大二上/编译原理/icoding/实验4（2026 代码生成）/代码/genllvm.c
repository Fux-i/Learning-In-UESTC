#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "genllvm.h"


#define BUFFER_SIZE 120000  
char* output_buffer = NULL;
size_t buffer_pos = 0; 
size_t buffer_capacity = 0; 


void init_buffer() {
    if (output_buffer == NULL) {
        buffer_capacity = BUFFER_SIZE;
        output_buffer = (char*)malloc(buffer_capacity);
        if (output_buffer == NULL) {
            fprintf(stderr, "Failed to allocate output buffer\n");
            exit(1);
        }
    }
    buffer_pos = 0;
    output_buffer[0] = '\0';
}

void ensure_buffer_space(size_t needed) {
    if (buffer_pos + needed >= buffer_capacity) {
        buffer_capacity *= 2;
        output_buffer = (char*)realloc(output_buffer, buffer_capacity);
        if (output_buffer == NULL) {
            fprintf(stderr, "Failed to reallocate output buffer\n");
            exit(1);
        }
    }
}


void buf_printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    
    int needed = vsnprintf(output_buffer + buffer_pos, 
                          buffer_capacity - buffer_pos, 
                          format, args);
    va_end(args);
    
    if (needed < 0) {
        fprintf(stderr, "vsnprintf error\n");
        exit(1);
    }
    
    if ((size_t)needed >= buffer_capacity - buffer_pos) {
        ensure_buffer_space(needed + 1000);
        va_start(args, format);
        needed = vsnprintf(output_buffer + buffer_pos, 
                          buffer_capacity - buffer_pos, 
                          format, args);
        va_end(args);
    }
    
    buffer_pos += needed;
}

void flush_buffer() {
    printf("%s", output_buffer);
    fflush(stdout);
}

/*
    把 output_buffer 从 start 开始新增的指令复制到调用者提供的 result
    不删除 output_buffer 中的内容 (genllvm 仍然需要整体输出)
*/
void copy_output_to_result(size_t start, char* result) {
    if (result == NULL) return;
    size_t len = buffer_pos - start;
    memcpy(result, output_buffer + start, len);
    result[len] = '\0';
}

void backpatch_label(const char* placeholder, int value) {
    char val_str[32];
    sprintf(val_str, "%d", value);
    size_t val_len = strlen(val_str);
    size_t place_len = strlen(placeholder);
    
    
    for (size_t i = 0; i < buffer_pos; ) {
        if (buffer_pos - i >= place_len && 
            strncmp(output_buffer + i, placeholder, place_len) == 0) {
            
            if (val_len > place_len) {
                size_t grow = val_len - place_len;
                ensure_buffer_space(grow);
                memmove(output_buffer + i + val_len,
                        output_buffer + i + place_len,
                        buffer_pos - (i + place_len) + 1);
                memcpy(output_buffer + i, val_str, val_len);
                buffer_pos += grow;
            } else {
                memcpy(output_buffer + i, val_str, val_len);
                if (val_len < place_len) {
                    memmove(output_buffer + i + val_len, 
                            output_buffer + i + place_len, 
                            buffer_pos - (i + place_len) + 1);
                    buffer_pos -= (place_len - val_len);
                }
            }
            i += val_len;
        } else {
            i++;
        }
    }
}


void cleanup_buffer() {
    if (output_buffer) {
        free(output_buffer);
        output_buffer = NULL;
    }
}


#define ERROR_llvm_CONST_EXPR -1  



struct KeyValuePair {
    char* key; 
    int value; 
};



struct Map {
    struct KeyValuePair* data;
    size_t size;
};


struct ArrayInfo {
    char* key; 
    int* dims; 
    int dim_count; 
};


struct ArrayMap {
    struct ArrayInfo* data;
    size_t size;
};



struct PendingAlloca {
    int slot; 
    struct PendingAlloca* next; 
};

/*
    全局变量
*/


int evalGlobalConstExpr(ast* pointer);
int evalGlobalAddExpr(ast* pointer);
int evalGlobalMulExpr(ast* pointer);
int evalGlobalUnaryExpr(ast* pointer);


int evalLocalConstExpr(ast* pointer); 


int isRuntimeExpr(ast* pointer);
int isRuntimeMulExpr(ast* pointer);
int isRuntimeUnaryExpr(ast* pointer);


void enqueue_alloca(int slot);
void flush_pending_allocas(void);
void print_operand(ast* node);


int genArithmeticExprImpl(ast* pointer);
int genMulExpr(ast* pointer);
int genUnaryExpr(ast* pointer);
int genLogicExprImpl(ast* pointer);
int genEqualityExpr(ast* pointer);
int genLogicalAndExpr(ast* pointer);
int genLogicalOrExpr(ast* pointer);
int genCondition(ast* pointer);

/*
    题目要求的对外接口: 生成对应结点的 LLVM 指令
    每行只放一条指令, 指令写入 result
*/
int genArithmeticExpr(ast* node, char* result);
int genLogicExpr(ast* node, char* result);
int genAssignStmt(ast* node, char* result);
int genIfStmt(ast* node, char* result);
int genWhileStmt(ast* node, char* result);

int genAssignStmtImpl(ast* pointer);
int genIfStmtImpl(ast* pointer);
int genWhileStmtImpl(ast* pointer);


void genCondWithJumpPlaceholder(ast* pointer, const char* true_label_ph, const char* false_label_ph);
void genCondWithJump(ast* pointer, int true_label, int false_label);


int genFuncCallArgs(ast* pointer, char* buffer);


int genStmt(ast* pointer);
void genIfElseChain(ast* pointer, const char* end_label);


int genGlobalConstDecl(ast* pointer);
int genGlobalConstDef(ast* pointer);
int genGlobalVarDecl(ast* pointer);
int genGlobalVarDef(ast* pointer);


int genFuncDef(ast* pointer);
int genFuncParams(ast* pointer, int* num);
int genFuncParam(ast* pointer, int* num);
int genBlock(ast* pointer);
int genBlock_A(ast* pointer);
int genBlockItem(ast* pointer);


int genLocalConstDecl(ast* pointer);
int genLocalConstDef(ast* pointer);
int genLocalVarDecl(ast* pointer);
int genLocalVarDef(ast* pointer);

int func_exit_label = -1; 


struct Map id_global; 
struct Map id_local;  
struct Map const_global; 
struct Map const_local;  

struct ArrayMap array_global; 


struct PendingAlloca* pending_allocas_head = NULL;
struct PendingAlloca* pending_allocas_tail = NULL;

/*
    符号表操作函数
*/


void initializeMap(struct Map* map) {
    map->data = NULL;
    map->size = 0;
}





void insertKeyValuePair(struct Map* map, const char* key, int value) {
    map->data = realloc(map->data, (map->size + 1) * sizeof(struct KeyValuePair));
    map->data[map->size].key = strdup(key);
    map->data[map->size].value = value;
    map->size++;
}


void cleanupMap(struct Map* map) {
    for (size_t i = 0; i < map->size; ++i) {
        free(map->data[i].key);
    }
    free(map->data);
    map->data = NULL;
    map->size = 0;
}



int getValueFromMap(struct Map* map, const char* key) {
    for (size_t i = 0; i < map->size; ++i) {
        if (strcmp(map->data[i].key, key) == 0) {
            return i;
        }
    }
    return -1;
}



int getVal(struct Map* map, const char* key, int error_code) {
    int idx = getValueFromMap(map, key);
    if (idx != -1) return map->data[idx].value;
    return error_code;
}


void initializeArrayMap(struct ArrayMap* map) {
    map->data = NULL;
    map->size = 0;
}





void insertArrayInfo(struct ArrayMap* map, const char* key, int* dims, int dim_count) {
    map->data = realloc(map->data, (map->size + 1) * sizeof(struct ArrayInfo));
    map->data[map->size].key = strdup(key);
    map->data[map->size].dim_count = dim_count;
    map->data[map->size].dims = (int*)malloc(sizeof(int) * dim_count);
    memcpy(map->data[map->size].dims, dims, sizeof(int) * dim_count);
    map->size++;
}



struct ArrayInfo* getArrayInfo(struct ArrayMap* map, const char* key) {
    for (size_t i = 0; i < map->size; ++i) {
        if (strcmp(map->data[i].key, key) == 0) {
            return &map->data[i];
        }
    }
    return NULL;
}


void cleanupArrayMap(struct ArrayMap* map) {
    for (size_t i = 0; i < map->size; ++i) {
        free(map->data[i].key);
        free(map->data[i].dims);
    }
    free(map->data);
    map->data = NULL;
    map->size = 0;
}

/*
    数组处理辅助函数
*/





void collect_const_dims(ast* node, int** dims, int* dim_count) {
    ast* cursor = node;
    while (cursor != NULL) {
        (*dim_count)++;
        *dims = realloc(*dims, sizeof(int) * (*dim_count));
        (*dims)[(*dim_count) - 1] = evalGlobalConstExpr(cursor->right);
        cursor = cursor->next;
    }
}


void flatten_const_init(ast* node, int* values, int total, int* index) {
    if (node == NULL || *index >= total) {
        return;
    }
    
    if (strcmp(node->node_type, "CONST_INIT") != 0) {
        
        values[(*index)++] = evalLocalConstExpr(node);
        return;
    }
    
    if (strcmp(node->value_string, "{}") == 0) {
        
        if (node->right != NULL) {
            flatten_const_init(node->right, values, total, index);
        }
        ast* tail = node->next;
        while (tail != NULL && *index < total) {
            flatten_const_init(tail->right, values, total, index);
            tail = tail->next;
        }
    } else {
        
        values[(*index)++] = evalLocalConstExpr(node->right);
        if (node->next != NULL) {
            flatten_const_init(node->next, values, total, index);
        }
    }
}

void build_array_type_string_internal(int* dims, int dim_count, int level, char* buffer, size_t len) {
    if (level == dim_count - 1) {
        
        snprintf(buffer + strlen(buffer), len - strlen(buffer), "[%d x i32]", dims[level]);
        return;
    }
    
    snprintf(buffer + strlen(buffer), len - strlen(buffer), "[%d x ", dims[level]);
    build_array_type_string_internal(dims, dim_count, level + 1, buffer, len);
    snprintf(buffer + strlen(buffer), len - strlen(buffer), "]");
}


void build_array_type_string(int* dims, int dim_count, char* buffer, size_t len) {
    buffer[0] = '\0';
    build_array_type_string_internal(dims, dim_count, 0, buffer, len);
}


void print_array_literal_internal(int* values, int level, int dim_count, int* dims, int* index) {
    buf_printf("[");
    for (int i = 0; i < dims[level]; ++i) {
        if (i > 0) {
            buf_printf(", ");
        }
        if (level == dim_count - 1) {
            
            buf_printf("i32 %d", values[(*index)++]);
        } else {
            
            print_array_literal_internal(values, level + 1, dim_count, dims, index);
        }
    }
    buf_printf("]");
}

void print_array_literal(int* values, int level, int dim_count, int* dims, int* index) {
    print_array_literal_internal(values, level, dim_count, dims, index);
}

/*
    局部变量管理
*/

static char* func_param_names[256]; 
int scout; 




int create_local_slot(const char* name) {
    int slot = scout++;
    enqueue_alloca(slot); 
    if (name != NULL) {
        char* temp = strdup(name);
        insertKeyValuePair(&id_local, temp, slot);
    }
    return slot;
}



int get_local_slot(const char* name) {
    int index = getValueFromMap(&id_local, name);
    if (index == -1) {
        return -1;
    }
    return id_local.data[index].value;
}



void enqueue_alloca(int slot) {
    struct PendingAlloca* node = (struct PendingAlloca*)malloc(sizeof(struct PendingAlloca));
    node->slot = slot;
    node->next = NULL;
    if (pending_allocas_tail == NULL) {
        pending_allocas_head = pending_allocas_tail = node;
    } else {
        pending_allocas_tail->next = node;
        pending_allocas_tail = node;
    }
}



void flush_pending_allocas(void) {
    struct PendingAlloca* cursor = pending_allocas_head;
    while (cursor != NULL) {
        buf_printf("  %%%d = alloca i32, align 4\n", cursor->slot);
        struct PendingAlloca* temp = cursor;
        cursor = cursor->next;
        free(temp);
    }
    pending_allocas_head = pending_allocas_tail = NULL;
}

/*
    变量提升(Hoisting)
    在生成函数体代码前, 先遍历AST收集所有局部变量声明
    为每个变量预分配槽位, 避免代码生成时才分配导致的顺序问题
*/


void hoist_block(ast* pointer);
void hoist_block_a(ast* pointer);
void hoist_block_item(ast* pointer);
void hoist_const_decl(ast* pointer);
void hoist_const_def(ast* pointer);
void hoist_var_decl(ast* pointer);
void hoist_var_def(ast* pointer);
void hoist_stmt(ast* pointer);


int is_token(const char* value, const char* token) {
    if (value == NULL || token == NULL) return 0;
    return strcmp(value, token) == 0;
}


void hoist_block(ast* pointer) {
    if (pointer == NULL) return;
    if (pointer->right != NULL) hoist_block_a(pointer->right);
}


void hoist_block_a(ast* pointer) {
    if (pointer == NULL) return;
    hoist_block_item(pointer->right);
    if (pointer->next != NULL) hoist_block_a(pointer->next);
}


void hoist_block_item(ast* pointer) {
    if (pointer == NULL) return;
    if (strcmp(pointer->node_type, "CONST_DECL") == 0) 
        hoist_const_decl(pointer);
    else if (strcmp(pointer->node_type, "VAR_DECL") == 0) 
        hoist_var_decl(pointer);
    else if (strcmp(pointer->node_type, "STMT") == 0) 
        hoist_stmt(pointer);
    else if (strcmp(pointer->node_type, "BLOCK") == 0) 
        hoist_block(pointer);
}


void hoist_const_decl(ast* pointer) {
    if (pointer == NULL) return;
    hoist_const_def(pointer->right);
    if (pointer->next != NULL) hoist_const_decl(pointer->next);
}



void hoist_const_def(ast* pointer) {
    if (pointer == NULL) return;
    if (pointer->left == NULL) {
        
        if (get_local_slot(pointer->value_string) == -1) {
            create_local_slot(pointer->value_string);
        }
    }
    
}


void hoist_var_decl(ast* pointer) {
    if (pointer == NULL) return;
    hoist_var_def(pointer->right);
    if (pointer->next != NULL) hoist_var_decl(pointer->next);
}



void hoist_var_def(ast* pointer) {
    if (pointer == NULL) return;
    if (pointer->left == NULL) {
        
        if (get_local_slot(pointer->value_string) == -1) {
            create_local_slot(pointer->value_string);
        }
    }
}



void hoist_stmt(ast* pointer) {
    if (pointer == NULL) return;

    if (strcmp(pointer->node_type, "BLOCK") == 0) {
        hoist_block(pointer);
        return;
    }
    if (pointer->value_string == NULL) return;
    
    if (strcmp(pointer->value_string, "") == 0) {
        
        if (pointer->left != NULL && strcmp(pointer->left->node_type, "BLOCK") == 0) {
            hoist_block(pointer->left);
        }
    } else if (is_token(pointer->value_string, "if") || is_token(pointer->value_string, "IF")) {
        
        if (pointer->right != NULL) hoist_stmt(pointer->right);
        if (pointer->extend != NULL) hoist_stmt(pointer->extend);
    } else if (is_token(pointer->value_string, "while") || is_token(pointer->value_string, "WHILE")) {
        
        if (pointer->right != NULL) hoist_stmt(pointer->right);
    } else if (strcmp(pointer->value_string, "Block") == 0) {
        if (pointer->left != NULL) hoist_block(pointer->left);
    }
}

/*
    辅助函数
*/


char* generate_label() {
    char* label = (char*)malloc(20);
    sprintf(label, "%d", scout++);
    return label;
}

/*
    生成具名基本块标签, 不占用匿名临时值的编号空间
*/
static int named_label_counter = 0;
char* generate_named_label(const char* prefix) {
    char* label = (char*)malloc(64);
    sprintf(label, "%s.%d", prefix, named_label_counter++);
    return label;
}



int zext_i1_to_i32(int reg) {
    int res = scout++;
    buf_printf("  %%%d = zext i1 %%%d to i32\n", res, reg);
    return res;
}



void print_operand(ast* node); 



int ends_with_return(ast* node) {
    if (!node) return 0;
    
    if (strcmp(node->node_type, "STMT") == 0) {
        if (strcmp(node->value_string, "return") == 0) {
            return 1;
        }
        if (strcmp(node->value_string, "if") == 0) {
            
            int then_returns = ends_with_return(node->right);
            int else_returns = node->extend ? ends_with_return(node->extend) : 0;
            return then_returns && else_returns;
        }
        if (strcmp(node->value_string, "") == 0 && node->left) {
            
            if (strcmp(node->left->node_type, "BLOCK") == 0) {
                return ends_with_return(node->left);
            }
        }
    } else if (strcmp(node->node_type, "BLOCK") == 0) {
        
        if (node->right) {
            ast* item = node->right;
            while (item->next) item = item->next; 
            if (item->right) {
                return ends_with_return(item->right);
            }
        }
    }
    
    return 0;
}



int string_ends_with_terminator(const char* str) {
    if (!str || strlen(str) == 0) return 0;
    
    
    const char* ptr = str + strlen(str) - 1;
    while (ptr > str && (*ptr == '\n' || *ptr == ' ')) ptr--;
    
    
    while (ptr > str && *ptr != '\n') ptr--;
    if (*ptr == '\n') ptr++;
    
    if (strncmp(ptr, "  br", 4) == 0) return 1;
    if (strncmp(ptr, "  ret", 5) == 0) return 1;
    return 0;
}



int count_return(ast* node) {
    if (!node) return 0;
    int cnt = 0;
    if (strcmp(node->node_type, "STMT") == 0 && strcmp(node->value_string, "return") == 0)
        cnt++;
    if (node->left) cnt += count_return(node->left);
    if (node->right) cnt += count_return(node->right);
    if (node->extend) cnt += count_return(node->extend);
    if (node->next) cnt += count_return(node->next);
    return cnt;
}

/*
    判断函数体内是否存在 if / while
    存在控制流时需要把 return 统一汇合到函数出口, 否则某些路径可能没有终结指令
*/
int contains_control_flow(ast* node) {
    if (!node) return 0;
    if (strcmp(node->node_type, "STMT") == 0 &&
        (strcmp(node->value_string, "if") == 0 ||
         strcmp(node->value_string, "while") == 0))
        return 1;
    if (contains_control_flow(node->left)) return 1;
    if (contains_control_flow(node->right)) return 1;
    if (contains_control_flow(node->extend)) return 1;
    if (contains_control_flow(node->next)) return 1;
    return 0;
}

/*
    表达式类型检查
    判断表达式是编译时常量还是运行时计算值
    返回0表示常量 (可以在编译时求值), 返回1表示需要生成代码
*/


int isRuntimeExpr(ast* pointer);
int isRuntimeMulExpr(ast* pointer);
int isRuntimeUnaryExpr(ast* pointer);



int isRuntimeUnaryExpr(ast* pointer) {
    if (!pointer) return 0;

    
    if (strcmp(pointer->node_type, "REL_EXP") == 0 || 
        strcmp(pointer->node_type, "EQ_EXP") == 0 ||
        strcmp(pointer->node_type, "L_AND_EXP") == 0 || 
        strcmp(pointer->node_type, "L_OR_EXP") == 0) {
        if (strcmp(pointer->value_string, "") == 0) {
            
            return isRuntimeUnaryExpr(pointer->left);
        }
        
        return 1;
    }

    if (strcmp(pointer->node_type, "EXP_WITH_UNARY_OP") == 0) {
        return isRuntimeUnaryExpr(pointer->right);
    } else if (strcmp(pointer->node_type, "FUNC_CALL_ID") == 0) {
        return 1; 
    } else if (strcmp(pointer->node_type, "ID_WITH_SUBSCRIPT") == 0) {
        return 1; 
    } else {
        if (strcmp(pointer->node_type, "EXPR") == 0) 
            return isRuntimeExpr(pointer);
        else if (strcmp(pointer->node_type, "EXPR_MUL") == 0) 
            return isRuntimeMulExpr(pointer);
        else if (strcmp(pointer->node_type, "IDENTIFIER") == 0) {
            
            if (getValueFromMap(&const_local, pointer->value_string) != -1) return 0;
            if (getValueFromMap(&const_global, pointer->value_string) != -1) return 0;
            return 1; 
        } else if (strcmp(pointer->node_type, "DECIMAL") == 0 || 
                   strcmp(pointer->node_type, "OCTAL") == 0 || 
                   strcmp(pointer->node_type, "HEXADECIMAL") == 0) {
            return 0; 
        }
    }
    return 0;
}


int isRuntimeExpr(ast* pointer) {
    if (strcmp(pointer->node_type, "EXPR") == 0) 
        return isRuntimeExpr(pointer->left) + isRuntimeMulExpr(pointer->right);
    return isRuntimeMulExpr(pointer);
}


int isRuntimeMulExpr(ast* pointer) {
    if (strcmp(pointer->node_type, "EXPR_MUL") == 0)
        return isRuntimeMulExpr(pointer->left) + isRuntimeUnaryExpr(pointer->right);
    return isRuntimeUnaryExpr(pointer);
}



void print_operand(ast* node) {
    if (isRuntimeExpr(node)) {
        
        buf_printf("%%%d", genArithmeticExprImpl(node));
    } else {
        
        buf_printf("%d", evalLocalConstExpr(node));
    }
}

/*
    全局常量表达式求值
    在编译时计算常量表达式的值 (用于全局常量/变量初始化)
*/



int evalGlobalConstExpr(ast* pointer) {
    if (!pointer) return ERROR_llvm_CONST_EXPR;
    
    
    if (strcmp(pointer->node_type, "DECIMAL") == 0) return pointer->value_int;
    if (strcmp(pointer->node_type, "OCTAL") == 0) return pointer->value_int;
    if (strcmp(pointer->node_type, "HEXADECIMAL") == 0) return pointer->value_int;
    
    
    if (strcmp(pointer->node_type, "IDENTIFIER") == 0) {
        return getVal(&const_global, pointer->value_string, 0);
    }
    
    
    if (strcmp(pointer->node_type, "EXPR") == 0 || strcmp(pointer->node_type, "EXPR_MUL") == 0) {
        int l = evalGlobalConstExpr(pointer->left);
        int r = evalGlobalConstExpr(pointer->right);
        switch (pointer->value_int) {
            case '+': return l + r;
            case '-': return l - r;
            case '*': return l * r;
            case '/': return r ? l / r : 0;
            case '%': return r ? l % r : 0;
        }
    }
    
    
    if (strcmp(pointer->node_type, "EXP_WITH_UNARY_OP") == 0) {
        int r = evalGlobalConstExpr(pointer->right);
        switch (pointer->left->value_int) {
            case '+': return r;
            case '-': return -r;
            case '!': return !r;
        }
    }
    
    
    if (strcmp(pointer->node_type, "REL_EXP") == 0 || 
        strcmp(pointer->node_type, "EQ_EXP") == 0 ||
        strcmp(pointer->node_type, "L_AND_EXP") == 0 || 
        strcmp(pointer->node_type, "L_OR_EXP") == 0) {
        if (strcmp(pointer->value_string, "") == 0) {
            return evalGlobalConstExpr(pointer->left);
        }
    }

    return ERROR_llvm_CONST_EXPR;
}



int evalLocalConstExpr(ast* pointer) {
    if (!pointer) return 0;
    
    if (strcmp(pointer->node_type, "DECIMAL") == 0) return pointer->value_int;
    if (strcmp(pointer->node_type, "OCTAL") == 0) return pointer->value_int;
    if (strcmp(pointer->node_type, "HEXADECIMAL") == 0) return pointer->value_int;
    
    
    if (strcmp(pointer->node_type, "IDENTIFIER") == 0) {
        int idx = getValueFromMap(&const_local, pointer->value_string);
        if (idx != -1) return const_local.data[idx].value;
        idx = getValueFromMap(&const_global, pointer->value_string);
        if (idx != -1) return const_global.data[idx].value;
        return 0;
    }

    
    if (strcmp(pointer->node_type, "EXPR") == 0 || strcmp(pointer->node_type, "EXPR_MUL") == 0) {
        int l = evalLocalConstExpr(pointer->left);
        int r = evalLocalConstExpr(pointer->right);
        switch (pointer->value_int) {
            case '+': return l + r;
            case '-': return l - r;
            case '*': return l * r;
            case '/': return r ? l / r : 0;
            case '%': return r ? l % r : 0;
        }
    }
    
    
    if (strcmp(pointer->node_type, "EXP_WITH_UNARY_OP") == 0) {
        int r = evalLocalConstExpr(pointer->right);
        switch (pointer->left->value_int) {
            case '+': return r;
            case '-': return -r;
            case '!': return !r;
        }
    }

    
    if (strcmp(pointer->node_type, "REL_EXP") == 0 || 
        strcmp(pointer->node_type, "EQ_EXP") == 0 ||
        strcmp(pointer->node_type, "L_AND_EXP") == 0 || 
        strcmp(pointer->node_type, "L_OR_EXP") == 0) {
        if (strcmp(pointer->value_string, "") == 0) {
            return evalLocalConstExpr(pointer->left);
        }
    }
    
    return 0;
}

/*
    全局变量 和 常量 代码生成
*/


int genGlobalConstDecl(ast* pointer) {
    genGlobalConstDef(pointer->right);
    if (pointer->next != NULL) {
        genGlobalConstDecl(pointer->next);
    }
    return 0;
}



int genGlobalConstDef(ast* pointer) {
    if (pointer->left == NULL) {
        
        int value = evalGlobalConstExpr(pointer->right->right);
        buf_printf("@%s = constant i32 %d, align 4\n", pointer->value_string, value);
        char* temp = strdup(pointer->value_string);
        
        insertKeyValuePair(&id_global, temp, value);
        insertKeyValuePair(&const_global, temp, value); 
    } else {
        
        int* dims = NULL;
        int dim_count = 0;
        collect_const_dims(pointer->left, &dims, &dim_count);
        
        
        int total = 1;
        for (int i = 0; i < dim_count; ++i) {
            total *= dims[i];
        }
        
        
        int* values = (int*)calloc(total, sizeof(int));
        int index = 0;
        flatten_const_init(pointer->right, values, total, &index);
        while (index < total) {
            values[index++] = 0; 
        }
        
        
        char type_buffer[256];
        build_array_type_string(dims, dim_count, type_buffer, sizeof(type_buffer));
        buf_printf("@%s = constant %s ", pointer->value_string, type_buffer);
        
        int literal_index = 0;
        print_array_literal(values, 0, dim_count, dims, &literal_index);
        buf_printf(", align 16\n");
        
        insertArrayInfo(&array_global, pointer->value_string, dims, dim_count);
        free(values);
        free(dims);
    }
    return 0;
}


int genGlobalVarDecl(ast* pointer) {
    genGlobalVarDef(pointer->right);
    if (pointer->next != NULL) {
        genGlobalVarDecl(pointer->next);
    }
    return 0;
}



int genGlobalVarDef(ast* pointer) {
    
    if (pointer->left != NULL) {
        int* dims = NULL;
        int dim_count = 0;
        collect_const_dims(pointer->left, &dims, &dim_count);
        char type_buffer[256];
        build_array_type_string(dims, dim_count, type_buffer, sizeof(type_buffer));
        
        
        buf_printf("@%s = global %s zeroinitializer, align 16\n", pointer->value_string, type_buffer);
        
        insertArrayInfo(&array_global, pointer->value_string, dims, dim_count);
        if(dims) free(dims);
        return 0;
    }

    
    if (pointer->right == NULL) {
        
        buf_printf("@%s = global i32 0, align 4\n", pointer->value_string);
        char* temp = strdup(pointer->value_string);
        insertKeyValuePair(&id_global, temp, 0);
    } else {
        
        int value = evalGlobalAddExpr(pointer->right->right);
        buf_printf("@%s = global i32 %d, align 4\n", pointer->value_string, value);
        char* temp = strdup(pointer->value_string);
        insertKeyValuePair(&id_global, temp, value);
    }
    return 0;
}


int evalGlobalAddExpr(ast* pointer) {
    if (strcmp(pointer->node_type, "EXPR") == 0) {
        if (pointer->value_int == '+') 
            return evalGlobalAddExpr(pointer->left) + evalGlobalMulExpr(pointer->right);
        else if (pointer->value_int == '-') 
            return evalGlobalAddExpr(pointer->left) - evalGlobalMulExpr(pointer->right);
    }
    return evalGlobalMulExpr(pointer);
}


int evalGlobalMulExpr(ast* pointer) {
    if (strcmp(pointer->node_type, "EXPR_MUL") == 0) {
        if (pointer->value_int == '*') 
            return evalGlobalMulExpr(pointer->left) * evalGlobalUnaryExpr(pointer->right);
        else if (pointer->value_int == '/') 
            return evalGlobalMulExpr(pointer->left) / evalGlobalUnaryExpr(pointer->right);
        else if (pointer->value_int == '%') 
            return evalGlobalMulExpr(pointer->left) % evalGlobalUnaryExpr(pointer->right);
    }
    return evalGlobalUnaryExpr(pointer);
}


int evalGlobalUnaryExpr(ast* pointer) {
    if (strcmp(pointer->node_type, "EXP_WITH_UNARY_OP") == 0) {
        switch (pointer->left->value_int) {
            case '+': return evalGlobalUnaryExpr(pointer->right);
            case '-': return -evalGlobalUnaryExpr(pointer->right);
            case '!': return evalGlobalUnaryExpr(pointer->right) == 0 ? 1 : 0;
        }
    } else if (strcmp(pointer->node_type, "IDENTIFIER") == 0) {
        
        if (getValueFromMap(&const_global, pointer->value_string) != -1)
             return getVal(&const_global, pointer->value_string, 0);
        
        if (getValueFromMap(&id_global, pointer->value_string) != -1)
             return getVal(&id_global, pointer->value_string, 0);
        exit(-1);
    } else if (strcmp(pointer->node_type, "DECIMAL") == 0) {
        return pointer->value_int;
    }
    return 0;
}

/*
    函数代码生成
*/


int genFuncDef(ast* pointer);
int genFuncParams(ast* pointer, int* num);
int genFuncParam(ast* pointer, int* num);
int genBlock(ast* pointer);
int genBlock_A(ast* pointer);
int genBlockItem(ast* pointer);
int genLocalConstDecl(ast* pointer);
int genLocalConstDef(ast* pointer);
int genLocalVarDecl(ast* pointer);
int genLocalVarDef(ast* pointer);








int genFuncDef(ast* pointer) {
    
    if (strcmp(pointer->value_string, "int") == 0) {
        buf_printf("define i32 @%s(", pointer->value_string1);
    } else if (strcmp(pointer->value_string, "void") == 0) {
        buf_printf("define void @%s(", pointer->value_string1);
    }

    
    cleanupMap(&id_local);
    initializeMap(&id_local);
    initializeMap(&const_local);
    memset(func_param_names, 0, sizeof(func_param_names));

    
    int num = 0;
    if (pointer->left != NULL) {
        genFuncParams(pointer->left, &num);
    }
    buf_printf(") {\n");

    scout = num + 1; 
    
    
    
    
    int ret_slot = -1;
    int is_complex = 0;
    int return_count = count_return(pointer->right);
    
    if (return_count > 1 || contains_control_flow(pointer->right)) {
        is_complex = 1;
    }

    
    
    if (is_complex && strcmp(pointer->value_string, "void") != 0) {
        ret_slot = create_local_slot("__ret");
    } else if (strcmp(pointer->value_string1, "main") == 0 && 
               strcmp(pointer->value_string, "void") != 0) {
        ret_slot = create_local_slot("__ret");
    }
    
    
    for (int i = 0; i < num; ++i) {
        if (func_param_names[i] == NULL) continue;
        create_local_slot(func_param_names[i]);
    }

    
    hoist_block(pointer->right);
    flush_pending_allocas(); 

    
    if (ret_slot != -1 && strcmp(pointer->value_string1, "main") == 0) {
        buf_printf("  store i32 0, i32* %%%d, align 4\n", ret_slot);
    }

    
    for (int i = 0; i < num; ++i) {
        if (func_param_names[i] == NULL) continue;
        int slot = get_local_slot(func_param_names[i]);
        buf_printf("  store i32 %%%d, i32* %%%d, align 4\n", i, slot);
    }

    
    
    if (is_complex && strcmp(pointer->value_string, "void") != 0) {
        func_exit_label = -99;
    } else {
        func_exit_label = -1;
    }

    
    genBlock(pointer->right);

    
    if (func_exit_label == -99) {
        
        int real_exit = scout++;
        backpatch_label("{{EXIT}}", real_exit);
        
        buf_printf("\n%d:\n", real_exit);
        int ret_reg = scout++;
        buf_printf("  %%%d = load i32, i32* %%%d, align 4\n", ret_reg, ret_slot);
        buf_printf("  ret i32 %%%d\n", ret_reg);
        
    } else if (strcmp(pointer->value_string1, "main") == 0 && 
               strcmp(pointer->value_string, "void") != 0) {
        
        if (!string_ends_with_terminator(output_buffer)) {
            buf_printf("  ret i32 0\n");
        }
        buf_printf("}\n");
        
        flush_pending_allocas();
        cleanupMap(&id_local);
        cleanupMap(&const_local);
        return 0;
        
    } else if (strcmp(pointer->value_string, "void") == 0) {
        
        if (!string_ends_with_terminator(output_buffer)) {
            buf_printf("  ret void\n");
        }
    }
    
    buf_printf("}\n");
    flush_pending_allocas();
    cleanupMap(&id_local);
    cleanupMap(&const_local);
    return 0;
}



int genFuncParams(ast* pointer, int* num) {
    if (pointer == NULL) return 0;
    if (*num > 0) buf_printf(", ");
    genFuncParam(pointer->right, num);
    (*num)++;
    if (pointer->next != NULL) genFuncParams(pointer->next, num);
    return 0;
}



int genFuncParam(ast* pointer, int* num) {
    int index = *num;
    buf_printf("i32 %%%d", index);
    if (index < (int)(sizeof(func_param_names) / sizeof(func_param_names[0]))) {
        func_param_names[index] = pointer->value_string1;
    }
    return 0;
}


int genBlock(ast* pointer) {
    if (pointer->right != NULL) genBlock_A(pointer->right);
    return 0;
}


int genBlock_A(ast* pointer) {
    genBlockItem(pointer->right);
    if (pointer->next != NULL) genBlock_A(pointer->next);
    return 0;
}


int genBlockItem(ast* pointer) {
    if (strcmp(pointer->node_type, "CONST_DECL") == 0) 
        genLocalConstDecl(pointer);
    else if (strcmp(pointer->node_type, "VAR_DECL") == 0) 
        genLocalVarDecl(pointer);
    else if (strcmp(pointer->node_type, "STMT") == 0) 
        genStmt(pointer);
    return 0;
}


int genLocalConstDecl(ast* pointer) {
    genLocalConstDef(pointer->right);
    if (pointer->next != NULL) genLocalConstDecl(pointer->next);
    return 0;
}



int genLocalConstDef(ast* pointer) {
    if (pointer->left == NULL) {
        
        int slot = get_local_slot(pointer->value_string);
        if (slot == -1) slot = create_local_slot(pointer->value_string);
        flush_pending_allocas();
        
        int val = evalLocalConstExpr(pointer->right->right);
        buf_printf("  store i32 %d, i32* %%%d, align 4\n", val, slot);
        
        
        insertKeyValuePair(&const_local, pointer->value_string, val);
    } else {
        
        int* dims = NULL;
        int dim_count = 0;
        collect_const_dims(pointer->left, &dims, &dim_count);
        
        int total = 1;
        for(int i=0; i<dim_count; ++i) total *= dims[i];
        
        int* values = (int*)calloc(total, sizeof(int));
        int index = 0;
        flatten_const_init(pointer->right, values, total, &index);
        
        
        char type_buffer[256];
        build_array_type_string(dims, dim_count, type_buffer, sizeof(type_buffer));
        
        
        int slot = scout++; 
        buf_printf("  %%%d = alloca %s, align 16\n", slot, type_buffer);
        
        
        insertArrayInfo(&array_global, pointer->value_string, dims, dim_count);
        char* name_dup = strdup(pointer->value_string);
        insertKeyValuePair(&id_local, name_dup, slot);

        
        for(int i=0; i<total; ++i) {
            int temp = i;
            int ptr_reg = scout++;
            buf_printf("  %%%d = getelementptr inbounds %s, %s* %%%d, i64 0", 
                       ptr_reg, type_buffer, type_buffer, slot);
            
            
            int* indices = malloc(sizeof(int) * dim_count);
            for(int d = dim_count - 1; d >= 0; d--) {
                indices[d] = temp % dims[d];
                temp /= dims[d];
            }
            for(int d = 0; d < dim_count; d++) {
                buf_printf(", i64 %d", indices[d]);
            }
            buf_printf("\n");
            free(indices);
            
            buf_printf("  store i32 %d, i32* %%%d, align 4\n", values[i], ptr_reg);
        }

        free(dims);
        free(values);
    }
    return 0;
}


int genLocalVarDecl(ast* pointer) {
    genLocalVarDef(pointer->right);
    if (pointer->next != NULL) genLocalVarDecl(pointer->next);
    return 0;
}



int genLocalVarDef(ast* pointer) {
    if (pointer->left == NULL) {
        int slot = get_local_slot(pointer->value_string);
        if (slot == -1) slot = create_local_slot(pointer->value_string);
        flush_pending_allocas();
        
        if (pointer->right != NULL) {
            if (isRuntimeExpr(pointer->right->right)) {
                
                int reg = genArithmeticExprImpl(pointer->right->right);
                buf_printf("  store i32 %%%d, i32* %%%d, align 4\n", reg, slot);
            } else {
                
                buf_printf("  store i32 %d, i32* %%%d, align 4\n", 
                           evalLocalConstExpr(pointer->right->right), slot);
            }
        }
    }
    
    return 0;
}

/*
    表达式代码生成
*/




int genArithmeticExprImpl(ast* pointer) {
    if (strcmp(pointer->node_type, "EXPR") == 0) {
        int lhs_reg = -1, rhs_reg = -1;
        int lhs_val = 0, rhs_val = 0;
        int lhs_is_reg = 0, rhs_is_reg = 0;

        
        if (isRuntimeExpr(pointer->left)) {
            lhs_reg = genArithmeticExprImpl(pointer->left);
            lhs_is_reg = 1;
        } else {
            lhs_val = evalLocalConstExpr(pointer->left);
        }

        
        if (isRuntimeMulExpr(pointer->right)) {
            rhs_reg = genMulExpr(pointer->right);
            rhs_is_reg = 1;
        } else {
            rhs_val = evalLocalConstExpr(pointer->right);
        }

        
        int res_reg = scout++;
        if (pointer->value_int == '+') 
            buf_printf("  %%%d = add nsw i32 ", res_reg);
        else 
            buf_printf("  %%%d = sub nsw i32 ", res_reg);

        if (lhs_is_reg) buf_printf("%%%d", lhs_reg); 
        else buf_printf("%d", lhs_val);
        buf_printf(", ");
        if (rhs_is_reg) buf_printf("%%%d", rhs_reg); 
        else buf_printf("%d", rhs_val);
        buf_printf("\n");

        return res_reg;
    } else {
        return genMulExpr(pointer);
    }
}



int genMulExpr(ast* pointer) {
    if (strcmp(pointer->node_type, "EXPR_MUL") == 0) {
        int lhs_reg = -1, rhs_reg = -1;
        int lhs_val = 0, rhs_val = 0;
        int lhs_is_reg = 0, rhs_is_reg = 0;

        if (isRuntimeMulExpr(pointer->left)) {
            lhs_reg = genMulExpr(pointer->left);
            lhs_is_reg = 1;
        } else {
            lhs_val = evalLocalConstExpr(pointer->left);
        }

        if (isRuntimeUnaryExpr(pointer->right)) {
            rhs_reg = genUnaryExpr(pointer->right);
            rhs_is_reg = 1;
        } else {
            rhs_val = evalLocalConstExpr(pointer->right);
        }

        int res_reg = scout++;
        switch (pointer->value_int) {
            case '*': buf_printf("  %%%d = mul nsw i32 ", res_reg); break;
            case '/': buf_printf("  %%%d = sdiv i32 ", res_reg); break;
            case '%': buf_printf("  %%%d = srem i32 ", res_reg); break;
        }

        if (lhs_is_reg) buf_printf("%%%d", lhs_reg); 
        else buf_printf("%d", lhs_val);
        buf_printf(", ");
        if (rhs_is_reg) buf_printf("%%%d", rhs_reg); 
        else buf_printf("%d", rhs_val);
        buf_printf("\n");

        return res_reg;
    } else {
        return genUnaryExpr(pointer);
    }
}



int genUnaryExpr(ast* pointer) {
    if (pointer == NULL) return 0;

    
    
    if (strcmp(pointer->node_type, "REL_EXP") == 0 || 
        strcmp(pointer->node_type, "EQ_EXP") == 0 ||
        strcmp(pointer->node_type, "L_AND_EXP") == 0 || 
        strcmp(pointer->node_type, "L_OR_EXP") == 0) {
        
        if (strcmp(pointer->value_string, "") == 0) {
            
            return genUnaryExpr(pointer->left);
        }
        
        
        
        int cond_reg = genCondition(pointer);
        int res_reg = scout++;
        buf_printf("  %%%d = zext i1 %%%d to i32\n", res_reg, cond_reg);
        return res_reg;
    }

    if (strcmp(pointer->node_type, "EXP_WITH_UNARY_OP") == 0) {
        
        int reg = -1;
        int val = 0;
        int is_reg = 0;
        
        if(isRuntimeUnaryExpr(pointer->right)) {
            reg = genUnaryExpr(pointer->right);
            is_reg = 1;
        } else {
            val = evalLocalConstExpr(pointer->right);
        }
        
        if (pointer->left->value_int == '+') {
            return is_reg ? reg : val; 
        }
        
        int res_reg = scout++; 
        if (pointer->left->value_int == '-') {
            
            buf_printf("  %%%d = sub nsw i32 0, ", res_reg);
            if(is_reg) buf_printf("%%%d", reg); 
            else buf_printf("%d", val);
            buf_printf("\n");
        } else if (pointer->left->value_int == '!') {
            
            buf_printf("  %%%d = icmp eq i32 ", res_reg);
            if(is_reg) buf_printf("%%%d", reg); 
            else buf_printf("%d", val);
            buf_printf(", 0\n");
            
            int zext_reg = scout++;
            buf_printf("  %%%d = zext i1 %%%d to i32\n", zext_reg, res_reg);
            res_reg = zext_reg; 
        }
        return res_reg;

    } else if (strcmp(pointer->node_type, "FUNC_CALL_ID") == 0) {
        
        char buffer[1024] = {0};
        
        if (pointer->right != NULL) {
            genFuncCallArgs(pointer->right, buffer);
            int res_reg = scout++;
            buf_printf("  %%%d = call i32 @%s(%s)\n", res_reg, pointer->value_string, buffer);
            return res_reg;
        } else {
            int res_reg = scout++;
            buf_printf("  %%%d = call i32 @%s()\n", res_reg, pointer->value_string);
            return res_reg;
        }

    } else if (strcmp(pointer->node_type, "ID_WITH_SUBSCRIPT") == 0) {
        
        struct ArrayInfo* info = getArrayInfo(&array_global, pointer->value_string);
        if (info == NULL) {
            buf_printf("unsupported array identifier %s\n", pointer->value_string);
            exit(1);
        }
        
        char type_buffer[256];
        build_array_type_string(info->dims, info->dim_count, type_buffer, sizeof(type_buffer));
        
        
        int all_const = 1;
        ast* check_sub = pointer->right;
        while (check_sub != NULL) {
            if (isRuntimeExpr(check_sub->right)) { 
                all_const = 0; 
                break; 
            }
            check_sub = check_sub->next;
        }

        int is_global = (getValueFromMap(&id_local, pointer->value_string) == -1);

        
        if (is_global && all_const) {
            int res_reg = scout++;
            buf_printf("  %%%d = load i32, i32* getelementptr inbounds (%s, %s* @%s, i64 0", 
                   res_reg, type_buffer, type_buffer, pointer->value_string);
            ast* sub = pointer->right;
            while (sub != NULL) {
                buf_printf(", i64 %d", evalLocalConstExpr(sub->right));
                sub = sub->next;
            }
            buf_printf("), align 16\n"); 
            return res_reg;
        }

        
        int ptr_reg = scout++;
        buf_printf("  %%%d = getelementptr inbounds %s, %s* ", 
                   ptr_reg, type_buffer, type_buffer);
        if (!is_global) buf_printf("%%%d", get_local_slot(pointer->value_string)); 
        else buf_printf("@%s", pointer->value_string);
        buf_printf(", i64 0");
        
        
        ast* sub = pointer->right;
        while (sub != NULL) {
            if (isRuntimeExpr(sub->right)) {
                int idx_reg = genArithmeticExprImpl(sub->right);
                buf_printf(", i64 %%%d", idx_reg);
            } else {
                buf_printf(", i64 %d", evalLocalConstExpr(sub->right));
            }
            sub = sub->next;
        }
        buf_printf("\n");
        
        
        int res_reg = scout++;
        buf_printf("  %%%d = load i32, i32* %%%d, align 4\n", res_reg, ptr_reg);
        return res_reg;

    } else {
        
        if (strcmp(pointer->node_type, "EXPR") == 0) {
            return genArithmeticExprImpl(pointer);
        } 
        else if (strcmp(pointer->node_type, "IDENTIFIER") == 0) {
            char* temp = pointer->value_string;
            int res_reg = scout++;

            
            if (getValueFromMap(&id_local, temp) != -1) {
                int slot = get_local_slot(temp);
                buf_printf("  %%%d = load i32, i32* %%%d, align 4\n", res_reg, slot);
            } 
            else if (getValueFromMap(&id_global, temp) != -1) {
                buf_printf("  %%%d = load i32, i32* @%s, align 4\n", res_reg, temp);
            } 
            else {
                fprintf(stderr, "Error: Identifier '%s' not found.\n", temp);
                exit(1);
            }
            return res_reg;
        } 
        else if (strcmp(pointer->node_type, "DECIMAL") == 0) {
            return pointer->value_int;
        }
    }
    return 0;
}



int genFuncCallArgs(ast* pointer, char* buffer) {
    int len = strlen(buffer);
    int reg = -1;
    int val = 0;
    int is_reg = 0;

    if (isRuntimeExpr(pointer->right)) {
        reg = genArithmeticExprImpl(pointer->right);
        is_reg = 1;
    } else {
        val = evalLocalConstExpr(pointer->right);
    }

    if (is_reg) sprintf(buffer + len, "i32 %%%d", reg);
    else sprintf(buffer + len, "i32 %d", val);

    if (pointer->next != NULL) {
        sprintf(buffer + strlen(buffer), ", ");
        genFuncCallArgs(pointer->next, buffer);
    }
    return 0;
}

/*
    逻辑表达式代码生成
*/




int genLogicExprImpl(ast* pointer) {
    if (!pointer) return 0;
    
    
    if (strcmp(pointer->node_type, "REL_EXP") != 0) 
        return genArithmeticExprImpl(pointer);
    if (strcmp(pointer->value_string, "") == 0) 
        return genLogicExprImpl(pointer->left);

    
    int lhs_is_reg = isRuntimeExpr(pointer->left);
    int lhs_reg = lhs_is_reg ? genArithmeticExprImpl(pointer->left) : 0;
    
    int rhs_is_reg = isRuntimeExpr(pointer->right);
    int rhs_reg = rhs_is_reg ? genArithmeticExprImpl(pointer->right) : 0;

    
    int res_reg = scout++;
    buf_printf("  %%%d = ", res_reg);
    
    if (strcmp(pointer->value_string, "<") == 0) 
        buf_printf("icmp slt i32 ");
    else if (strcmp(pointer->value_string, ">") == 0) 
        buf_printf("icmp sgt i32 ");
    else if (strcmp(pointer->value_string, "<=") == 0) 
        buf_printf("icmp sle i32 ");
    else if (strcmp(pointer->value_string, ">=") == 0) 
        buf_printf("icmp sge i32 ");
    
    
    if (lhs_is_reg) buf_printf("%%%d, ", lhs_reg); 
    else { print_operand(pointer->left); buf_printf(", "); }

    if (rhs_is_reg) buf_printf("%%%d", rhs_reg); 
    else print_operand(pointer->right);
    
    buf_printf("\n");
    return res_reg;
}



/*
    把任意表达式结点求值成 i32 类型
    is_reg 返回 1 表示返回值是寄存器编号, 0 表示是立即数
    关系/相等/逻辑表达式的结果是 i1, 这里统一 zext 到 i32
*/
static int genValueAsI32(ast* node, int* is_reg) {
    *is_reg = 0;
    if (!node) return 0;

    const char* type = node->node_type;
    if (strcmp(type, "REL_EXP") == 0 && strcmp(node->value_string, "") != 0) {
        int r = genLogicExprImpl(node);
        int z = scout++;
        buf_printf("  %%%d = zext i1 %%%d to i32\n", z, r);
        *is_reg = 1;
        return z;
    }
    if (strcmp(type, "EQ_EXP") == 0 && strcmp(node->value_string, "") != 0) {
        int r = genEqualityExpr(node);
        int z = scout++;
        buf_printf("  %%%d = zext i1 %%%d to i32\n", z, r);
        *is_reg = 1;
        return z;
    }
    if ((strcmp(type, "L_AND_EXP") == 0 || strcmp(type, "L_OR_EXP") == 0) &&
        strcmp(node->value_string, "") != 0) {
        int r = genCondition(node);
        int z = scout++;
        buf_printf("  %%%d = zext i1 %%%d to i32\n", z, r);
        *is_reg = 1;
        return z;
    }

    if (isRuntimeExpr(node)) {
        *is_reg = 1;
        return genArithmeticExprImpl(node);
    }
    return evalLocalConstExpr(node);
}

int genEqualityExpr(ast* pointer) {
    if (!pointer) return 0;
    if (strcmp(pointer->node_type, "EQ_EXP") != 0) 
        return genLogicExprImpl(pointer);
    if (strcmp(pointer->value_string, "") == 0) 
        return genLogicExprImpl(pointer->left);

    int lhs_is_reg = 0, rhs_is_reg = 0;
    int lhs_reg = genValueAsI32(pointer->left, &lhs_is_reg);
    int rhs_reg = genValueAsI32(pointer->right, &rhs_is_reg);

    int res_reg = scout++;
    buf_printf("  %%%d = ", res_reg);
    
    if (strcmp(pointer->value_string, "==") == 0) 
        buf_printf("icmp eq i32 ");
    else if (strcmp(pointer->value_string, "!=") == 0) 
        buf_printf("icmp ne i32 ");

    if (lhs_is_reg) buf_printf("%%%d", lhs_reg);
    else buf_printf("%d", lhs_reg);
    buf_printf(", ");
    if (rhs_is_reg) buf_printf("%%%d", rhs_reg);
    else buf_printf("%d", rhs_reg);
    
    buf_printf("\n");
    return res_reg;
}




int genLogicalAndExpr(ast* pointer) {
    if (strcmp(pointer->value_string, "") == 0) {
        return genEqualityExpr(pointer->left);
    }
    
    
    
    
    
    
    
    
    int lhs_reg = genCondition(pointer->left);
    
    char* label_lhs_true = generate_named_label("land.true");
    char* label_end = generate_named_label("land.end");
    
    int res_ptr = create_local_slot(NULL); 
    flush_pending_allocas();
    
    
    buf_printf("  store i32 0, i32* %%%d, align 4\n", res_ptr); 
    
    
    buf_printf("  br i1 %%%d, label %%%s, label %%%s\n", lhs_reg, label_lhs_true, label_end);
    
    
    buf_printf("%s:\n", label_lhs_true);
    int rhs_reg = genCondition(pointer->right);
    int rhs_val = scout++;
    buf_printf("  %%%d = zext i1 %%%d to i32\n", rhs_val, rhs_reg);
    buf_printf("  store i32 %%%d, i32* %%%d, align 4\n", rhs_val, res_ptr);
    buf_printf("  br label %%%s\n", label_end);
    
    
    buf_printf("%s:\n", label_end);
    int final_val = scout++;
    buf_printf("  %%%d = load i32, i32* %%%d, align 4\n", final_val, res_ptr);
    int final_res = scout++;
    buf_printf("  %%%d = icmp ne i32 %%%d, 0\n", final_res, final_val);
    
    free(label_lhs_true);
    free(label_end);
    return final_res;
}




int genLogicalOrExpr(ast* pointer) {
    if (strcmp(pointer->value_string, "") == 0) {
        return genLogicalAndExpr(pointer->left);
    }
    
    int lhs_reg = genCondition(pointer->left);
    
    char* label_lhs_false = generate_named_label("lor.false");
    char* label_end = generate_named_label("lor.end");
    
    int res_ptr = create_local_slot(NULL);
    flush_pending_allocas();
    
    
    buf_printf("  store i32 1, i32* %%%d, align 4\n", res_ptr);
    
    
    buf_printf("  br i1 %%%d, label %%%s, label %%%s\n", lhs_reg, label_end, label_lhs_false);
    
    buf_printf("%s:\n", label_lhs_false);
    int rhs_reg = genCondition(pointer->right);
    int rhs_val = scout++;
    buf_printf("  %%%d = zext i1 %%%d to i32\n", rhs_val, rhs_reg);
    buf_printf("  store i32 %%%d, i32* %%%d, align 4\n", rhs_val, res_ptr);
    buf_printf("  br label %%%s\n", label_end);
    
    buf_printf("%s:\n", label_end);
    int final_val = scout++;
    buf_printf("  %%%d = load i32, i32* %%%d, align 4\n", final_val, res_ptr);
    int final_res = scout++;
    buf_printf("  %%%d = icmp ne i32 %%%d, 0\n", final_res, final_val);
    
    free(label_lhs_false);
    free(label_end);
    return final_res;
}




int genCondition(ast* pointer) {
    if (!pointer) return 0;
    
    if (strcmp(pointer->node_type, "L_OR_EXP") == 0) 
        return genLogicalOrExpr(pointer);
    if (strcmp(pointer->node_type, "L_AND_EXP") == 0) 
        return genLogicalAndExpr(pointer);
    
    if (strcmp(pointer->node_type, "EQ_EXP") == 0) {
        int reg = genEqualityExpr(pointer);
        
        
        int is_val = 0;
        if (strcmp(pointer->value_string, "") == 0) {
            ast* rel = pointer->left;
            if (rel && strcmp(rel->node_type, "REL_EXP") == 0 && 
                strcmp(rel->value_string, "") == 0) {
                is_val = 1;
            }
        }
        
        if (is_val) {
            
            int res = scout++;
            buf_printf("  %%%d = icmp ne i32 %%%d, 0\n", res, reg);
            return res;
        }
        return reg;
    }
    
    if (strcmp(pointer->node_type, "REL_EXP") == 0) {
        int reg = genLogicExprImpl(pointer);
        if (strcmp(pointer->value_string, "") == 0) {
            
            int res = scout++;
            buf_printf("  %%%d = icmp ne i32 %%%d, 0\n", res, reg);
            return res;
        }
        return reg;
    }
    
    
    int val_reg;
    if (isRuntimeExpr(pointer)) {
        val_reg = genArithmeticExprImpl(pointer);
    } else {
        val_reg = scout++;
        buf_printf("  %%%d = add i32 0, %d\n", val_reg, evalLocalConstExpr(pointer));
    }
    int res = scout++;
    buf_printf("  %%%d = icmp ne i32 %%%d, 0\n", res, val_reg);
    return res;
}

/*
    带跳转的条件生成 (用于 if 和 while)
*/


int ph_counter = 0;





void genCondWithJumpPlaceholder(ast* pointer, const char* true_label_ph, const char* false_label_ph) {
    if (!pointer) return;

    
    if (strcmp(pointer->node_type, "L_OR_EXP") == 0) {
        if (strcmp(pointer->value_string, "") == 0) {
            genCondWithJumpPlaceholder(pointer->left, true_label_ph, false_label_ph);
            return;
        }
        
        int left_is_simple = (strcmp(pointer->left->node_type, "L_OR_EXP") != 0 && 
                              strcmp(pointer->left->node_type, "L_AND_EXP") != 0);
        
        if (left_is_simple) {
            
            int cond = genCondition(pointer->left);
            int check_b = scout++;
            buf_printf("  br i1 %%%d, label %%%s, label %%%d\n", cond, true_label_ph, check_b);
            buf_printf("\n%d:\n", check_b);
        } else {
            
            char check_b_ph[20];
            sprintf(check_b_ph, "{{CB_%d}}", scout);
            genCondWithJumpPlaceholder(pointer->left, true_label_ph, check_b_ph);
            
            int check_b = scout++;
            backpatch_label(check_b_ph, check_b);
            buf_printf("\n%d:\n", check_b);
        }
        
        
        genCondWithJumpPlaceholder(pointer->right, true_label_ph, false_label_ph);
        return;
    }

    
    if (strcmp(pointer->node_type, "L_AND_EXP") == 0) {
        if (strcmp(pointer->value_string, "") == 0) {
            genCondWithJumpPlaceholder(pointer->left, true_label_ph, false_label_ph);
            return;
        }
        
        int left_is_simple = (strcmp(pointer->left->node_type, "L_OR_EXP") != 0 && 
                              strcmp(pointer->left->node_type, "L_AND_EXP") != 0);
        
        if (left_is_simple) {
            int cond = genCondition(pointer->left);
            int check_b = scout++;
            buf_printf("  br i1 %%%d, label %%%d, label %%%s\n", cond, check_b, false_label_ph);
            buf_printf("\n%d:\n", check_b);
        } else {
            char check_b_ph[20];
            sprintf(check_b_ph, "{{CB_%d}}", scout);
            genCondWithJumpPlaceholder(pointer->left, check_b_ph, false_label_ph);
            
            int check_b = scout++;
            backpatch_label(check_b_ph, check_b);
            buf_printf("\n%d:\n", check_b);
        }
        
        genCondWithJumpPlaceholder(pointer->right, true_label_ph, false_label_ph);
        return;
    }

    
    int cond_reg = genCondition(pointer);
    buf_printf("  br i1 %%%d, label %%%s, label %%%s\n", cond_reg, true_label_ph, false_label_ph);
}



void genCondWithJump(ast* pointer, int true_label, int false_label) {
    if (!pointer) return;

    
    #define PRINT_LABEL_REF(lbl, type) \
        do { \
            if (lbl == -100) buf_printf("%%{{T}}"); \
            else if (lbl == -101) buf_printf("%%{{F}}"); \
            else if (lbl == -102) buf_printf("%%{{E}}"); \
            else buf_printf("%%%d", lbl); \
        } while(0)

    
    if (strcmp(pointer->node_type, "L_OR_EXP") == 0) {
        if (strcmp(pointer->value_string, "") == 0) {
            genCondWithJump(pointer->left, true_label, false_label);
            return;
        }
        
        int left_is_simple = (strcmp(pointer->left->node_type, "L_OR_EXP") != 0 && 
                              strcmp(pointer->left->node_type, "L_AND_EXP") != 0);
        
        if (left_is_simple) {
            int left_cond = genCondition(pointer->left);
            int check_b = scout++;
            buf_printf("  br i1 %%%d, label ", left_cond);
            PRINT_LABEL_REF(true_label, 0);
            buf_printf(", label %%%d\n", check_b);
            
            buf_printf("\n%d:\n", check_b);
            genCondWithJump(pointer->right, true_label, false_label);
        } else {
            int check_b = scout++;
            genCondWithJump(pointer->left, true_label, check_b);
            buf_printf("\n%d:\n", check_b);
            genCondWithJump(pointer->right, true_label, false_label);
        }
        return;
    }

    
    if (strcmp(pointer->node_type, "L_AND_EXP") == 0) {
        if (strcmp(pointer->value_string, "") == 0) {
            genCondWithJump(pointer->left, true_label, false_label);
            return;
        }
        
        int left_is_simple = (strcmp(pointer->left->node_type, "L_OR_EXP") != 0 && 
                              strcmp(pointer->left->node_type, "L_AND_EXP") != 0);
        
        if (left_is_simple) {
            int left_cond = genCondition(pointer->left);
            int check_b = scout++;
            buf_printf("  br i1 %%%d, label %%%d, label ", left_cond, check_b);
            PRINT_LABEL_REF(false_label, 1);
            buf_printf("\n");
            
            buf_printf("\n%d:\n", check_b);
            genCondWithJump(pointer->right, true_label, false_label);
        } else {
            int check_b = scout++;
            genCondWithJump(pointer->left, check_b, false_label);
            buf_printf("\n%d:\n", check_b);
            genCondWithJump(pointer->right, true_label, false_label);
        }
        return;
    }

    
    int cond_reg = genCondition(pointer);
    buf_printf("  br i1 %%%d, label ", cond_reg);
    PRINT_LABEL_REF(true_label, 0);
    buf_printf(", label ");
    PRINT_LABEL_REF(false_label, 1);
    buf_printf("\n");
    
    #undef PRINT_LABEL_REF
}

/*
    语句代码生成
*/


int genStmt(ast* pointer);
void genIfElseChain(ast* pointer, const char* end_label);


void genIfElseChain(ast* pointer, const char* end_label) {
    if (pointer == NULL) return;
    if (strcmp(pointer->value_string, "if") == 0) {
        int then_label = scout++;
        int else_label = scout++;

        int cond_reg = genCondition(pointer->left);
        buf_printf("  br i1 %%%d, label %%%d, label %%%d\n", cond_reg, then_label, else_label);

        
        buf_printf("\n%d:\n", then_label);
        genStmt(pointer->right);
        buf_printf("  br label %%%s\n", end_label);

        
        buf_printf("\n%d:\n", else_label);
        if (pointer->extend && strcmp(pointer->extend->value_string, "if") == 0) {
            
            genIfElseChain(pointer->extend, end_label);
        } else if (pointer->extend) {
            
            genStmt(pointer->extend);
            buf_printf("  br label %%%s\n", end_label);
        }
    }
}




int genStmt(ast* pointer) {
    if (pointer == NULL) return 0;
    if (strcmp(pointer->node_type, "BLOCK") == 0) { 
        genBlock(pointer); 
        return 0; 
    }
    if (pointer->value_string == NULL) return 0;
    
    
    if (strcmp(pointer->value_string, "") == 0) {
        if (pointer->left) {
            if (strcmp(pointer->left->node_type, "BLOCK") == 0) 
                genBlock(pointer->left);
            else if (isRuntimeExpr(pointer->left)) 
                genArithmeticExprImpl(pointer->left);
        }
        return 0;
    }

    if (strcmp(pointer->value_string, "if") == 0) {
        genIfStmt(pointer, NULL);
        return 0;
    } else if (strcmp(pointer->value_string, "while") == 0) {
        genWhileStmt(pointer, NULL);
        return 0;
    } else if (strcmp(pointer->value_string, "return") == 0) {
        /*
            RETURN语句
        */

        int ret_slot = get_local_slot("__ret");
        
        if (func_exit_label == -99) {
            
            if (pointer->left == NULL) {
                buf_printf("  br label %%{{EXIT}} \n");
            } else if (isRuntimeExpr(pointer->left)) {
                int reg = genArithmeticExprImpl(pointer->left);
                buf_printf("  store i32 %%%d, i32* %%%d, align 4\n", reg, ret_slot);
                buf_printf("  br label %%{{EXIT}} \n");
            } else {
                buf_printf("  store i32 %d, i32* %%%d, align 4\n", 
                           evalLocalConstExpr(pointer->left), ret_slot);
                buf_printf("  br label %%{{EXIT}} \n");
            }
        } else {
            
            if (pointer->left == NULL) 
                buf_printf("  ret void\n");
            else if (isRuntimeExpr(pointer->left)) 
                buf_printf("  ret i32 %%%d\n", genArithmeticExprImpl(pointer->left));
            else 
                buf_printf("  ret i32 %d\n", evalLocalConstExpr(pointer->left));
        }
        return 0;
    } else if (strcmp(pointer->value_string, "=") == 0) {
        genAssignStmt(pointer, NULL);
        return 0;
    } else if (strcmp(pointer->value_string, "{") == 0) {
        /*
            代码块语句
        */

        genBlock(pointer);
        return 0;
    } else if (strcmp(pointer->value_string, "putint") == 0) {
        /*
            PUTINT语句
        */

        if (pointer->left == NULL) {
            fprintf(stderr, "Error: putint without argument\n");
            exit(1);
        }
        
        ast* arg = pointer->left;
        
        
        int is_func_call = (strcmp(arg->node_type, "FUNC_CALL_ID") == 0);
        
        
        int arg_reg = -1;
        int arg_val = 0;
        int is_const = 0;
        
        if (isRuntimeExpr(arg)) {
            arg_reg = genArithmeticExprImpl(arg);
        } else {
            arg_val = evalLocalConstExpr(arg);
            is_const = 1;
        }
        
        
        int res_reg = scout++;
        
        
        if (is_func_call) {
            
            if (is_const) {
                buf_printf("  %%%d = call i32 @putint(i32 %d)\n", res_reg, arg_val);
            } else {
                buf_printf("  %%%d = call i32 @putint(i32 %%%d)\n", res_reg, arg_reg);
            }
        } else {
            
            if (is_const) {
                buf_printf("  %%%d = call i32 @putint(i32 %d)\n", res_reg, arg_val);
            } else {
                buf_printf("  %%%d = call i32 @putint(i32 %%%d)\n", res_reg, arg_reg);
            }
        }
        return 0;
    } else if (strcmp(pointer->value_string, "") != 0 && 
             strcmp(pointer->value_string, ";") != 0) {
        /*
            其他语句
        */

        
        if (pointer->left != NULL && isRuntimeExpr(pointer->left)) 
            genArithmeticExprImpl(pointer->left);
    }
    
    return 0;
}

/*
    题目要求的五个对外接口实现
    这些函数只负责生成对应结点的 LLVM 指令, 并把指令逐行写入 result
    返回值: 表达式返回结果寄存器编号, 语句返回 0
*/

int genIfStmtImpl(ast* pointer) {
    int has_complex = (pointer->left && 
                      (strcmp(pointer->left->node_type, "L_OR_EXP") == 0 || 
                       strcmp(pointer->left->node_type, "L_AND_EXP") == 0));
    int has_else = (pointer->extend != NULL);

    int current_id = ph_counter++;
    char t_ph[32], f_ph[32], e_ph[32];
    sprintf(t_ph, "{{T_%d_______}}", current_id);
    sprintf(f_ph, "{{F_%d_______}}", current_id);
    sprintf(e_ph, "{{E_%d_______}}", current_id);

    const char* target_false_ph = has_else ? f_ph : e_ph;

    if (!has_complex) {
        int cond_reg = genCondition(pointer->left);
        buf_printf("  br i1 %%%d, label %%%s, label %%%s\n", 
                   cond_reg, t_ph, target_false_ph);
    } else {
        genCondWithJumpPlaceholder(pointer->left, t_ph, target_false_ph);
    }

    int real_true_label = scout++;
    buf_printf("\n%d:\n", real_true_label);
    genStmt(pointer->right);

    if (!ends_with_return(pointer->right)) {
        buf_printf("  br label %%%s\n", e_ph);
    }

    int real_false_label = -1;
    if (has_else) {
        real_false_label = scout++;
        buf_printf("\n%d:\n", real_false_label);

        if (strcmp(pointer->extend->node_type, "BLOCK") == 0) 
            genBlock(pointer->extend);
        else 
            genStmt(pointer->extend);

        if (!ends_with_return(pointer->extend)) {
            buf_printf("  br label %%%s\n", e_ph);
        }
    }

    int real_end_label = scout++;
    buf_printf("\n%d:\n", real_end_label);

    backpatch_label(t_ph, real_true_label);
    if (has_else) backpatch_label(f_ph, real_false_label);
    backpatch_label(e_ph, real_end_label);

    return 0;
}

int genWhileStmtImpl(ast* pointer) {
    int real_start_label = scout++;
    buf_printf("  br label %%%d\n", real_start_label);
    buf_printf("\n%d:\n", real_start_label);

    int current_id = ph_counter++;
    char wb_ph[32], we_ph[32];
    sprintf(wb_ph, "{{WB_%d_______}}", current_id);
    sprintf(we_ph, "{{WE_%d_______}}", current_id);

    int has_complex = (pointer->left && 
                      (strcmp(pointer->left->node_type, "L_OR_EXP") == 0 || 
                       strcmp(pointer->left->node_type, "L_AND_EXP") == 0));

    if (!has_complex) {
        int cond_reg = genCondition(pointer->left);
        buf_printf("  br i1 %%%d, label %%%s, label %%%s\n", 
                   cond_reg, wb_ph, we_ph);
    } else {
        genCondWithJumpPlaceholder(pointer->left, wb_ph, we_ph);
    }

    int real_body_label = scout++;
    buf_printf("\n%d:\n", real_body_label);

    genStmt(pointer->right);

    if (!ends_with_return(pointer->right)) {
        buf_printf("  br label %%%d\n", real_start_label);
    }

    int real_end_label = scout++;
    buf_printf("\n%d:\n", real_end_label);

    backpatch_label(wb_ph, real_body_label);
    backpatch_label(we_ph, real_end_label);

    return 0;
}

int genAssignStmtImpl(ast* pointer) {
    ast* lval = pointer->left;
    int is_local = 1; 
    int slot = -1; 
    char* name = NULL;

    if (strcmp(lval->node_type, "IDENTIFIER") == 0) {
        name = lval->value_string;
        slot = get_local_slot(name);
        if (slot == -1) { 
            if (getValueFromMap(&id_global, name) != -1) {
                is_local = 0; 
            } else {
                slot = create_local_slot(name); 
                flush_pending_allocas();
            }
        }
    } else if (strcmp(lval->node_type, "ID_WITH_SUBSCRIPT") == 0) {
        struct ArrayInfo* info = getArrayInfo(&array_global, lval->value_string);
        if (info == NULL) {
            fprintf(stderr, "Error: array '%s' not declared.\n", lval->value_string);
            exit(1);
        }

        char type_buffer[256]; 
        build_array_type_string(info->dims, info->dim_count, 
                               type_buffer, sizeof(type_buffer));

        int ptr_reg = scout++;
        int is_g = (get_local_slot(lval->value_string) == -1);
        buf_printf("  %%%d = getelementptr inbounds %s, %s* ", 
                   ptr_reg, type_buffer, type_buffer);

        if (!is_g) 
            buf_printf("%%%d", get_local_slot(lval->value_string)); 
        else 
            buf_printf("@%s", lval->value_string);
        buf_printf(", i64 0");

        ast* sub = lval->right;
        while(sub != NULL) {
            if(isRuntimeExpr(sub->right)) 
                buf_printf(", i64 %%%d", genArithmeticExprImpl(sub->right)); 
            else 
                buf_printf(", i64 %d", evalLocalConstExpr(sub->right));
            sub = sub->next;
        }
        buf_printf("\n");

        if (isRuntimeExpr(pointer->right)) 
            buf_printf("  store i32 %%%d, i32* %%%d, align 4\n", 
                       genArithmeticExprImpl(pointer->right), ptr_reg);
        else 
            buf_printf("  store i32 %d, i32* %%%d, align 4\n", 
                       evalLocalConstExpr(pointer->right), ptr_reg);
        return 0;
    }

    if (isRuntimeExpr(pointer->right)) {
        int reg = genArithmeticExprImpl(pointer->right);
        if (is_local) 
            buf_printf("  store i32 %%%d, i32* %%%d, align 4\n", reg, slot); 
        else 
            buf_printf("  store i32 %%%d, i32* @%s, align 4\n", reg, name);
    } else {
        int value = evalLocalConstExpr(pointer->right);
        if (is_local) 
            buf_printf("  store i32 %d, i32* %%%d, align 4\n", value, slot); 
        else 
            buf_printf("  store i32 %d, i32* @%s, align 4\n", value, name);
    }
    return 0;
}

static size_t begin_public_call(void) {
    if (output_buffer == NULL) init_buffer();
    return buffer_pos;
}

int genArithmeticExpr(ast* node, char* result) {
    size_t start = begin_public_call();
    int reg = genArithmeticExprImpl(node);
    copy_output_to_result(start, result);
    return reg;
}

int genLogicExpr(ast* node, char* result) {
    size_t start = begin_public_call();
    int reg = genLogicExprImpl(node);
    copy_output_to_result(start, result);
    return reg;
}

int genAssignStmt(ast* node, char* result) {
    size_t start = begin_public_call();
    genAssignStmtImpl(node);
    copy_output_to_result(start, result);
    return 0;
}

int genIfStmt(ast* node, char* result) {
    size_t start = begin_public_call();
    genIfStmtImpl(node);
    copy_output_to_result(start, result);
    return 0;
}

int genWhileStmt(ast* node, char* result) {
    size_t start = begin_public_call();
    genWhileStmtImpl(node);
    copy_output_to_result(start, result);
    return 0;
}

/*
    主代码
    LLVM IR代码生成主函数
    参数 root: AST根节点
    返回值: 0表示成功
*/

int genllvm(ast* root) {
    
    init_buffer();
    
    
    ast* cruiser = root;
    initializeMap(&id_global);
    initializeMap(&const_global);
    initializeArrayMap(&array_global);
    
    
    while (cruiser != NULL) {
        if (strcmp(cruiser->node_type, "COMP_UNIT") == 0) {
            if (strcmp(cruiser->right->node_type, "CONST_DECL") == 0) {
                genGlobalConstDecl(cruiser->right);
            } else if (strcmp(cruiser->right->node_type, "VAR_DECL") == 0) {
                genGlobalVarDecl(cruiser->right);
            } else if (strcmp(cruiser->right->node_type, "FUNC_DEF") == 0) {
                genFuncDef(cruiser->right);
            }
        } else {
            fprintf(stderr, "DO NOT DETECT COMP_UNIT\n");
            exit(0);
        }
        cruiser = cruiser->next;
    }
    
    
    flush_buffer();
    
    
    cleanup_buffer();
    cleanupArrayMap(&array_global);
    cleanupMap(&const_global);
    
    return 0;
}
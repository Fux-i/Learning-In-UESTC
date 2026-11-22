#include <stdio.h>
#include <stdlib.h>
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过

void destory_list_and_file(GoodsList **L) {
    destory_list(L);
    remove("goodsinfo.txt");
}

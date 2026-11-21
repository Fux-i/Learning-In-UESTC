#include <stdio.h>
#include <stdlib.h>
#include "lab52.h" // 请不要删除本行头文件，否则检查不通过

int main() {
    GoodsList *L = NULL;
    GoodsInfo info;
    GoodsList *found;
    char id[MAX_ID_LEN];
    int choice;

    init_list(&L);

    if (L == NULL) {
        L = (GoodsList *)malloc(sizeof(GoodsList));
        if (L == NULL) {
            return 0;
        }
        L->next = NULL;
    }

    for (;;) {
        printf("  1.显示所有商品的信息\n");
        printf("  2.修改某个商品的信息\n");
        printf("  3.插入某个商品的信息\n");
        printf("  4.删除某个商品的信息\n");
        printf("  5.查找某个商品的信息\n");
        printf("  6.商品存盘并退出系统\n");
        printf("  7.对商品价格进行排序\n");
        printf("  8.(慎用)删除所有内容\n");
        printf("  其他.不存盘并退出系统\n");

        if (scanf("%d", &choice) != 1) {
            destory_list(&L);
            break;
        }

        if (choice == 1) {
            output_all_items(L);
        } else if (choice == 2) {
            read_line(id, MAX_ID_LEN);
            info = read_goods_info();
            change_item(L, id, info);
        } else if (choice == 3) {
            int pos;
            info = read_goods_info();
            if (scanf("%d", &pos) != 1) {
                break;
            }
            insert_item(L, info, pos);
        } else if (choice == 4) {
            read_line(id, MAX_ID_LEN);
            delete_item(L, id);
        } else if (choice == 5) {
            read_line(id, MAX_ID_LEN);
            found = search_item(L, id);
            if (found != NULL) {
                output_one_item(found);
            }
        } else if (choice == 6) {
            save_to_file(L);
            destory_list(&L);
            break;
        } else if (choice == 7) {
            bubble_sort(L);
        } else if (choice == 8) {
            destory_list_and_file(&L);
            L = (GoodsList *)malloc(sizeof(GoodsList));
            if (L == NULL) {
                break;
            }
            L->next = NULL;
        } else {
            destory_list(&L);
            break;
        }
    }

    return 0;
}

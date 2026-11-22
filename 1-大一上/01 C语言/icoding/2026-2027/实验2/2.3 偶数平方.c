#include <stdio.h>

int main(void) {
    int n, i, first = 1;

    printf("Enter a number: ");
    scanf("%d", &n);

    for (i = 2; i * i <= n; i += 2) {
        if (!first)
            printf(" ");
        printf("%d", i * i);
        first = 0;
    }
    printf("\n");

    return 0;
}

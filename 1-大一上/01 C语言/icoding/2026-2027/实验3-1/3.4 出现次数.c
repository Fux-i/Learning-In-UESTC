#include <stdio.h>

int main(void) {
    char num[256];
    int cnt[10] = {0}, i;

    printf("Enter a number: ");
    scanf("%255s", num);

    for (i = 0; num[i]; i++) {
        if (num[i] >= '0' && num[i] <= '9') {
            cnt[num[i] - '0']++;
        }
    }

    printf("Digit: ");
    for (i = 0; i < 10; i++) {
        if (i)
            printf(" ");
        printf("%d", i);
    }
    printf("\n");

    printf("Occurrences:");
    for (i = 0; i < 10; i++) {
        printf(" %d", cnt[i]);
    }
    printf("\n");

    return 0;
}

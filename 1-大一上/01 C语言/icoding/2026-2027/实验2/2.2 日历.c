#include <stdio.h>

int main(void) {
    int days, start, i, pos;

    printf("Enter number of days in month: ");
    scanf("%d", &days);
    printf("Enter starting day of the week(1=Sun, 7=Sat): ");
    scanf("%d", &start);

    printf("日\t一\t二\t三\t四\t五\t六\n");

    pos = 1;
    for (i = 1; i < start; i++, pos++) {
        printf("\t");
    }
    for (i = 1; i <= days; i++, pos++) {
        printf("%2d\t", i);
        if (pos % 7 == 0) {
            printf("\n");
        }
    }
    if ((pos - 1) % 7 != 0) {
        printf("\n");
    }

    return 0;
}

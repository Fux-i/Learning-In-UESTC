#include <stdio.h>

int main(void) {
    int amount, b20, b10, b5, b1;

    printf("Enter a dollar amount: ");
    scanf("%d", &amount);

    b20 = amount / 20;
    amount %= 20;
    b10 = amount / 10;
    amount %= 10;
    b5 = amount / 5;
    amount %= 5;
    b1 = amount;

    printf("$20 bills: %d\n", b20);
    printf("$10 bills: %d\n", b10);
    printf("$5 bills: %d\n", b5);
    printf("$1 bills: %d\n", b1);

    return 0;
}

#include <stdio.h>

int main(void) {
    double amount;

    printf("Enter an amount: ");
    scanf("%lf", &amount);
    printf("with tax added: $%.2f\n", amount * 1.05);

    return 0;
}

#include <stdio.h>

int main(void) {
    double loan, rate, payment, monthly, balance;
    int i;

    printf("Enter amout of loan: ");
    scanf("%lf", &loan);
    printf("Enter interest rate: ");
    scanf("%lf", &rate);
    printf("Enter monthly payment: ");
    scanf("%lf", &payment);

    monthly = rate / 100.0 / 12.0;
    balance = loan;

    for (i = 0; i < 3; i++) {
        balance = balance - payment + balance * monthly;
        if (i == 0) {
            printf("Balance remaining after first payment: $%.2f\n", balance);
        } else if (i == 1) {
            printf("Balance remaining after second payment: $%.2f\n", balance);
        } else {
            printf("Balance remaining after third payment: $%.2f\n", balance);
        }
    }

    return 0;
}

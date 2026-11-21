#include <stdio.h>

int main(void) {
    double value, operand;
    int c;

    printf("Enter an expression: ");
    if (scanf("%lf", &value) != 1) {
        return 1;
    }

    for (;;) {
        do {
            c = getchar();
        } while (c == ' ' || c == '\t' || c == '\r');

        if (c == EOF || c == '\n') {
            break;
        }

        if (scanf("%lf", &operand) != 1) {
            break;
        }

        switch (c) {
        case '+':
            value += operand;
            break;
        case '-':
            value -= operand;
            break;
        case '*':
            value *= operand;
            break;
        case '/':
            value /= operand;
            break;
        default:
            break;
        }
    }

    printf("Value of expression: %g\n", value);

    return 0;
}

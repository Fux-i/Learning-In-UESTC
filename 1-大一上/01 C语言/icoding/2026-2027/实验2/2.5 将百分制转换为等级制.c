#include <stdio.h>

int main(void) {
    int g;

    printf("Enter numerical grade: ");
    scanf("%d", &g);

    if (g < 0 || g > 100) {
        printf("Error, grade must be between 0 and 100.\n");
        return 0;
    }

    switch (g / 10) {
    case 10:
    case 9:
        printf("Letter grade: A\n");
        break;
    case 8:
        printf("Letter grade: B\n");
        break;
    case 7:
        printf("Letter grade: C\n");
        break;
    case 6:
        printf("Letter grade: D\n");
        break;
    default:
        printf("Letter grade: F\n");
        break;
    }

    return 0;
}

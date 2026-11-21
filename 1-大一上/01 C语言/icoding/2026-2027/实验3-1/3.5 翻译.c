#include <stdio.h>

int main(void) {
    char line[1024];
    int i;
    static const char map[] = "22233344455566677778889999";

    printf("Enter phone number: ");
    if (!fgets(line, sizeof(line), stdin))
        return 1;

    for (i = 0; line[i]; i++) {
        if (line[i] >= 'A' && line[i] <= 'Z') {
            putchar(map[line[i] - 'A']);
        } else {
            putchar(line[i]);
        }
    }

    return 0;
}

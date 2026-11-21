#include <stdio.h>

int main(void) {
    char msg[1024];
    int shift, i;

    printf("Enter message to be encrypted: ");
    if (!fgets(msg, sizeof(msg), stdin))
        return 1;
    printf("Enter shift amount (1-25): ");
    scanf("%d", &shift);

    for (i = 0; msg[i]; i++) {
        if (msg[i] >= 'A' && msg[i] <= 'Z') {
            msg[i] = (char)((msg[i] - 'A' + shift) % 26 + 'A');
        } else if (msg[i] >= 'a' && msg[i] <= 'z') {
            msg[i] = (char)((msg[i] - 'a' + shift) % 26 + 'a');
        }
    }

    printf("Encrypted message: %s", msg);

    return 0;
}

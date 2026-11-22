#include <stdio.h>
#include <string.h>

int main(void) {
    char word[32], smallest[32] = "", largest[32] = "";
    int first = 1;

    for (;;) {
        printf("Enter word: ");
        if (scanf("%31s", word) != 1)
            break;
        if (first) {
            strcpy(smallest, word);
            strcpy(largest, word);
            first = 0;
        } else {
            if (strcmp(word, smallest) < 0)
                strcpy(smallest, word);
            if (strcmp(word, largest) > 0)
                strcpy(largest, word);
        }
        if (strlen(word) == 4)
            break;
    }

    printf("Smallest word: %s\n", smallest);
    printf("Largest word: %s\n", largest);

    return 0;
}

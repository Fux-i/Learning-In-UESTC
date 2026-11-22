#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    char grid[10][10];
    int i, j, r, c, steps, dir;
    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, 1, 0, -1};

    srand((unsigned)time(NULL));

    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++)
            grid[i][j] = '.';

    r = 0;
    c = 0;
    grid[0][0] = 'A';

    for (steps = 1; steps < 26; steps++) {
        int order[4] = {0, 1, 2, 3};
        int moved = 0;

        for (i = 3; i > 0; i--) {
            int k = rand() % (i + 1);
            int t = order[i];
            order[i] = order[k];
            order[k] = t;
        }

        for (i = 0; i < 4; i++) {
            dir = order[i];
            int nr = r + dr[dir];
            int nc = c + dc[dir];
            if (nr >= 0 && nr < 10 && nc >= 0 && nc < 10 && grid[nr][nc] == '.') {
                r = nr;
                c = nc;
                grid[r][c] = (char)('A' + steps);
                moved = 1;
                break;
            }
        }

        if (!moved)
            break;
    }

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 140
#define COL 140

#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

void check_adj(char grid[ROW][COL], int i, int j, int next[2]) {
    int dir[][2] = {
        {-1, 0},
        {1, 0},
        {0, 1},
        {0, -1},
    };

    for (int d = 0; d < 8; d++) {
        int m = dir[d][0] + i;
        int n = dir[d][1] + j;
        if (0 <= m && m < ROW && 0 <= n && n < COL) {
            if (d == 0 &&
                (grid[m][n] == 'L' || grid[m][n] == 'F' || grid[m][n] == '-')) {
                next[0] = m;
                next[1] = n;
                return;
            }
            if (d == 1 &&
                (grid[m][n] == 'F' || grid[m][n] == '7' || grid[m][n] == '|')) {
                next[0] = m;
                next[1] = n;
                return;
            }
            if (d == 2 &&
                (grid[m][n] == '7' || grid[m][n] == 'J' || grid[m][n] == '-')) {
                next[0] = m;
                next[1] = n;
                return;
            }
            if (d == 3 &&
                (grid[m][n] == 'L' || grid[m][n] == 'J' || grid[m][n] == '|')) {
                next[0] = m;
                next[1] = n;
                return;
            }
        }
    }
}

int main() {
    FILE *f = NULL;
    fopen_s(&f, "input.txt", "r");

    char grid[ROW][COL];
    int si = 0, sj = 0;

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            grid[i][j] = fgetc(f);
            if (grid[i][j] == 'S') {
                si = i;
                sj = j;
            }
        }
        fgetc(f);
    }

    int next[] = {0, 0};
    check_adj(grid, si, sj, next);
    printf("%d %d", next[0], next[1]);

    int dir = -1;

    if (next[0] == si) {
        if (next[1] < sj) {
            dir = LEFT;
        } else {
            dir = RIGHT;
        }
    } else {
        if (next[0] < si) {
            dir = UP;
        } else {
            dir = DOWN;
        }
    }

    char pipe;
    int moves = 1;
    do {
        moves++;
        pipe = grid[next[0]][next[1]];
        if (dir == LEFT) {
            if (pipe == '-') {
                next[1]--;
            } else if (pipe == 'F') {
                next[0]++;
                dir = DOWN;
            } else if (pipe == 'L') {
                next[0]--;
                dir = UP;
            }
        } else if (dir == RIGHT) {
            if (pipe == '-') {
                next[1]++;
            } else if (pipe == '7') {
                next[0]++;
                dir = DOWN;
            } else if (pipe == 'J') {
                next[0]--;
                dir = UP;
            }
        } else if (dir == UP) {
            if (pipe == '|') {
                next[0]--;
            } else if (pipe == '7') {
                next[1]--;
                dir = LEFT;
            } else if (pipe == 'F') {
                next[1]++;
                dir = RIGHT;
            }
        } else {
            if (pipe == '|') {
                next[0]++;
            } else if (pipe == 'J') {
                next[1]--;
                dir = LEFT;
            } else if (pipe == 'L') {
                next[1]++;
                dir = RIGHT;
            }
        }

    } while (pipe != 'S');

    printf("\n%d", moves / 2);

    fclose(f);
    return 0;
}

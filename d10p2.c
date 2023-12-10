#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 140
#define COL 140

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3

int dir[][2] = {
    {-1, 0},
    {1, 0},
    {0, 1},
    {0, -1},
};
int area = 0;

void flood_fill(char vis[ROW][COL], char path[ROW][COL], int i, int j) {
    vis[i][j] = '*';
    area++;
    for (int d = 0; d < 4; d++) {
        int m = dir[d][0] + i;
        int n = dir[d][1] + j;

        if (0 <= m && m < ROW && 0 <= n && n < COL && vis[m][n] != '*' &&
            path[m][n] == '.') {
            flood_fill(vis, path, m, n);
        }
    }
}

void check_adj(char vis[ROW][COL], char path[ROW][COL], int i, int j) {
    for (int d = 0; d < 8; d++) {
        int m = dir[d][0] + i;
        int n = dir[d][1] + j;
        int boundaries = 0;
        if (0 <= m && m < ROW && 0 <= n && n < COL && path[m][n] == '.' &&
            vis[m][n] != '*') {
            vis[m][n] = '*';

            while (n-- > 0) {
                if (path[m][n] != '.' && path[m][n] != '-') {

                    if (path[m][n] == '7' || path[m][n] == 'J') {
                        char end = path[m][n] == '7' ? 'F' : 'L';
                        while (n-- > 0 && path[m][n] == '-') {
                        }
                        if (path[m][n] == end) {
                            boundaries++;
                        }
                    }
                    boundaries++;
                }
            }
            if (boundaries % 2 != 0) {
                flood_fill(vis, path, m, dir[d][1] + j);
            }
        }
    }
}

void get_start(char grid[ROW][COL], int i, int j, int next[2]) {

    for (int d = 0; d < 4; d++) {
        int m = dir[d][0] + i;
        int n = dir[d][1] + j;
        if (0 <= m && m < ROW && 0 <= n && n < COL) {
            if (d == 0 &&
                (grid[m][n] == 'F' || grid[m][n] == '7' || grid[m][n] == '|')) {
                next[0] = m;
                next[1] = n;
                return;
            }
            if (d == 1 &&
                (grid[m][n] == 'L' || grid[m][n] == 'J' || grid[m][n] == '|')) {
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
                (grid[m][n] == 'L' || grid[m][n] == 'F' || grid[m][n] == '-')) {
                next[0] = m;
                next[1] = n;
                return;
            }
        }
    }
}

void move(int *dir, char pipe, int next[2]) {
    if (*dir == LEFT) {
        if (pipe == '-') {
            next[1]--;
        } else if (pipe == 'F') {
            next[0]++;
            *dir = DOWN;
        } else if (pipe == 'L') {
            next[0]--;
            *dir = UP;
        }
    } else if (*dir == RIGHT) {
        if (pipe == '-') {
            next[1]++;
        } else if (pipe == '7') {
            next[0]++;
            *dir = DOWN;
        } else if (pipe == 'J') {
            next[0]--;
            *dir = UP;
        }
    } else if (*dir == UP) {
        if (pipe == '|') {
            next[0]--;
        } else if (pipe == '7') {
            next[1]--;
            *dir = LEFT;
        } else if (pipe == 'F') {
            next[1]++;
            *dir = RIGHT;
        }
    } else {
        if (pipe == '|') {
            next[0]++;
        } else if (pipe == 'J') {
            next[1]--;
            *dir = LEFT;
        } else if (pipe == 'L') {
            next[1]++;
            *dir = RIGHT;
        }
    }
}

int main() {
    FILE *f = NULL;
    fopen_s(&f, "input.txt", "r");

    char grid[ROW][COL];
    char path[ROW][COL];
    int si = 0, sj = 0;

    for (int i = 0; i < ROW; i++) {
        memset(path[i], '.', COL);
        for (int j = 0; j < COL; j++) {
            grid[i][j] = fgetc(f);
            if (grid[i][j] == 'S') {
                si = i;
                sj = j;
            }
        }
        fgetc(f);
    }
    int start[2], next[2];
    get_start(grid, si, sj, start);

    next[0] = start[0];
    next[1] = start[1];
    int start_dir;

    if (next[0] == si) {
        if (next[1] < sj) {
            start_dir = LEFT;
        } else {
            start_dir = RIGHT;
        }
    } else {
        if (next[0] < si) {
            start_dir = UP;
        } else {
            start_dir = DOWN;
        }
    }

    int dir = start_dir;

    char pipe;
    do {
        path[next[0]][next[1]] = grid[next[0]][next[1]];
        pipe = grid[next[0]][next[1]];
        move(&dir, pipe, next);
    } while (pipe != 'S');

    path[si][sj] = '|'; // in the array we're storing only the path, change the
                        // start symbol to a regular direction

    next[0] = start[0];
    next[1] = start[1];
    dir = start_dir;

    do {
        pipe = grid[next[0]][next[1]];

        check_adj(grid, path, next[0], next[1]);
        pipe = grid[next[0]][next[1]];
        move(&dir, pipe, next);
    } while (pipe != 'S');

    printf("Area = %d", area);

    fclose(f);
    return 0;
}

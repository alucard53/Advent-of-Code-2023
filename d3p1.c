#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 140
#define COL 140

int is_digit(char c) { return '0' <= c && c <= '9'; }

int is_symbol(char c) { return !is_digit(c) && c != '.'; }

int check_adj_symbol(int i, int j, char input[ROW][COL]) {
    int count = 0, dir[][2] = {
                       {-1, 0},  // top
                       {-1, -1}, // top left
                       {0, -1},  // left
                       {1, -1},  // bottom left
                       {1, 0},   // bottom
                       {1, 1},   // bottom right
                       {0, 1},   // right
                       {-1, 1},  // top right
                   };

    for (int k = 0; k < 9; k++) {
        int m = i + dir[k][0], n = j + dir[k][1];

        if (m >= 0 && m < ROW && n >= 0 && n < COL && is_symbol(input[m][n])) {
            return 1;
        }
    }

    return 0;
}

int get_num(int i, int j, char input[ROW][COL]) {
    int num = 0;
    int k;
    int part = 0;
    while (j < COL && is_digit(input[i][j])) {
        num = num * 10 + (input[i][j] - '0');
        if (!part) {
            part = check_adj_symbol(i, j, input);
        }
        j += 1;
    }
    if (part) {
        return num;
    }
    return 0;
}

int main() {
    FILE *f = fopen("input.txt", "r");

    char input[ROW][COL];

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            input[i][j] = fgetc(f);
        }
        fgetc(f);
    }

    fclose(f);

    int sum = 0;

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (is_digit(input[i][j])) {
                int n = get_num(i, j, input);
                sum += n;
                while (j < COL && is_digit(input[i][++j])) {
                }
            }
        }
    }
    printf("sum = %d", sum);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 140
#define COL 140

int is_digit(char c) { return '0' <= c && c <= '9'; }

int is_symbol(char c) { return !is_digit(c) && c != '.'; }

int get_num(int i, int j, char input[ROW][COL]) {
    int num = 0;

    while (j >= 0 && is_digit(input[i][j])) {
        j--;
    }

    while (j < COL && is_digit(input[i][++j])) {
        num = num * 10 + (input[i][j] - '0');
        input[i][j] = '.'; // the same number might span two+ adjacents positions of a *
                           // so mark a number with a . after reading it
                           // wouldn't have worked if the same number was shared by 2 *s but lmao
    }
    return num;
}

long long int check_adj_num(int i, int j, char input[ROW][COL]) {

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

    int nums[2];

    for (int x = 0; x < 8; x++) {
        int m = i + dir[x][0], n = j + dir[x][1];
        
        if (m >= 0 && m < ROW && n >= 0 && n < COL && is_digit(input[m][n])) {
            if (count >= 2) {
                return 0;
            }
            nums[count++] = get_num(m, n, input);
        }
    }

    if (count == 2) {
        return nums[0] * nums[1];
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
            if (input[i][j] == '*') {
                sum += check_adj_num(i, j, input);
            }
        }
    }

    printf("sum = %d", sum);
    return 0;
}

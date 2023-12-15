#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *f = fopen("input.txt", "r");

    int sum = 0;
    while (!feof(f)) {
        char s[10];
        bzero(s, 10);
        int len = 0;

        char c = fgetc(f);
        while (c != ',' && c != '\n') {
            s[len++] = c;
            c = fgetc(f);
        }
        printf("%s => ", s);

        int curr_val = 0;
        for (int i = 0; i < len; i++) {
            curr_val = ((curr_val + s[i]) * 17) % 256;
        }

        sum += curr_val;
        printf("%d\n", curr_val);
        if (c == '\n') {
            break;
        }
    }
    printf("%d", sum);
    fclose(f);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SET_SIZE 40
#define CARDS 198

void insert(int set[SET_SIZE], int key) {
    int hash = key % SET_SIZE;

    while (set[hash] != -1) {
        hash = (hash + 1) % SET_SIZE;
    }
    set[hash] = key;
}

int contains(int set[SET_SIZE], int key) {
    int hash = key % SET_SIZE;

    int i = 0;
    while (i++ < SET_SIZE) {
        if (set[hash] == key) {
            return 1;
        } else if (set[hash++] == -1) {
            return 0;
        }
    }

    return 0;
}

int is_digit(char c) { return '0' <= c && c <= '9'; }

void seek(FILE *f, char c) {
    char next = fgetc(f);
    while (!feof(f) && next != c) {
        next = fgetc(f);
    }
}

int main() {

    FILE *f = fopen("input.txt", "r");

    int set[SET_SIZE], sum = 0;

    memset(set, -1, SET_SIZE * sizeof(int));

    while (!feof(f)) {
        seek(f, ':');
        char c = fgetc(f);

        while (!feof(f) && c != '|') {
            int num;
            fscanf(f, "%d", &num);
            c = fgetc(f);
            insert(set, num);
        }

        int count = 0;

        while (!feof(f) && c != '\n') {
            int num;
            fscanf(f, "%d", &num);
            c = fgetc(f);

            if (contains(set, num)) {
                if (count == 0) {
                    count = 1;
                } else {
                    count *= 2;
                }
            }
        }

        sum += count;

        memset(set, -1, SET_SIZE * sizeof(int));
    }

    printf("\nsum = %d", sum);

    fclose(f);

    return 0;
}

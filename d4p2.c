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

int min(int a, int b) { return a < b ? a : b; }

int main() {

    FILE *f = fopen("input.txt", "r");

    int set[SET_SIZE], cards[CARDS], sum = 0, card = 0;
    for (int i = 0; i < CARDS; i++) {
        cards[i] = 1;
    }

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

            count += contains(set, num);
        }

        for (int i = card + 1; i < min(card + 1 + count, CARDS); i++) {
            cards[i] += cards[card];
        }
        card++;

        memset(set, -1, SET_SIZE * sizeof(int));
    }

    for (int i = 0; i < CARDS; i++) {
        sum += cards[i];
    }
    printf("\nsum = %d", sum);

    fclose(f);

    return 0;
}

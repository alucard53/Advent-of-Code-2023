#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED 12
#define GREEN 13
#define BLUE 14

#define RED_SEEK 2
#define GREEN_SEEK 4
#define BLUE_SEEK 3

int is_digit(char c) { return ('0' <= c && c <= '9'); }

void seek(FILE *f, char c) {
  if (c == 'r') {
    fseek(f, RED_SEEK, SEEK_CUR);
  } else if (c == 'g') {
    fseek(f, GREEN_SEEK, SEEK_CUR);
  } else {
    fseek(f, BLUE_SEEK, SEEK_CUR);
  }
}

int possible(int n, char c) {
  if (c == 'r') {
    return n <= RED;
  } else if (c == 'g') {
    return n <= GREEN;
  } else {
    return n <= BLUE;
  }
}

int main() {
  FILE *f = fopen("input.txt", "r");

  int id = 1, sum = 0;
  while (!feof(f)) {
    while (fgetc(f) != ':') {
    }

    fgetc(f);
    char c = fgetc(f);

    if (c == -1) {
      break;
    }

    int poss = 1;

    while (c != '\n') {
      char nbuf[4];
      bzero(nbuf, 4);

      int j = 0;

      while (is_digit(c)) {
        nbuf[j++] = c;
        c = fgetc(f);
      }

      c = fgetc(f);

      if (!possible(atoi(nbuf), c)) {
        poss = 0;
        break;
      }

      seek(f, c);
      c = fgetc(f);

      if (c != '\n') {
        fseek(f, 1, SEEK_CUR);
        c = fgetc(f);
      }
    }

    if (!poss) {
      while (c != '\n') {
        c = fgetc(f);
      }

      fseek(f, 1, SEEK_CUR);
    } else {
      printf("Valid %d %d", id, c);
      sum += id;
      fseek(f, 1, SEEK_CUR);
    }

    printf("\n");
    id++;
  }

  printf("sum = %d", sum);

  fclose(f);
  return 0;
}

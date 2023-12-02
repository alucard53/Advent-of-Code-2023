#include <math.h>
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

int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

int main() {
  FILE *f = fopen("input.txt", "r");

  int sum = 0;
  while (!feof(f)) {
    while (fgetc(f) != ':') {
    }
    fgetc(f);
    char c = fgetc(f);
    if (c == -1) {
      break;
    }
    int poss = 1;

    int min_red = 0, min_green = 0, min_blue = 0;

    while (c != '\n') {
      char nbuf[4];
      bzero(nbuf, 4);
      int j = 0;
      while (is_digit(c)) {
        nbuf[j++] = c;
        c = fgetc(f);
      }
      c = fgetc(f);
      printf("%c %d\n", c, atoi(nbuf));

      if (c == 'r') {
        min_red = max(min_red, atoi(nbuf));
      } else if (c == 'g') {
        min_green = max(min_green, atoi(nbuf));
      } else {
        min_blue = max(min_blue, atoi(nbuf));
      }

      seek(f, c);
      c = fgetc(f);
      if (c == '\n') {
        break;
      } else {
        fseek(f, 1, SEEK_CUR);
        c = fgetc(f);
      }
    }

    printf("%d, %d, %d \n", min_red, min_green, min_blue);
    sum += (min_red * min_green * min_blue);

    fgetc(f);
    printf("\n");
  }

  printf("sum = %d", sum);

  fclose(f);
  return 0;
}

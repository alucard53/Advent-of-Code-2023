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

int main() {
  FILE *f = fopen("input.txt", "r");
  int sum = 0;

  while (!feof(f)) {
    char line[69], c = fgetc(f);
    bzero(line, 69);
    int i = 0, end = 0;

    while (c != '\n') {
      if (feof(f)) {
        end = 1;
        break;
      }
      line[i++] = c;
      c = fgetc(f);
    }

    if (end == 1) {
      break;
    }

    int n = i + 1;

    int num = 0;

    for (int i = 0; i < n; i++) {
      if (is_digit(line[i])) {
        num = line[i] - 48;
        break;
      }
    }

    for (int i = n - 1; i >= 0; i--) {
      if (is_digit(line[i])) {
        num = num * 10 + line[i] - 48;
        break;
      }
    }

    printf("%d\n", num);

    sum += num;
  }

  printf("%d", sum);

  fclose(f);
  return 0;
}

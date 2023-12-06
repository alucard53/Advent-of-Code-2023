>
#include <stdlib.h>
#include <string.h>

#define N 1

void seek(FILE *f, char c) {
    while (fgetc(f) != c) {
    }
}

int main() {
    FILE *f = fopen("input.txt", "r");

    long long int time[N];
    long long int dist[N];

    fseek(f, 5, SEEK_CUR);

    for (int i = 0; i < N; i++) {
        fscanf(f, "%lld", &time[i]);
    }
    seek(f, '\n');
    fseek(f, 10, SEEK_CUR);

    for (int i = 0; i < N; i++) {
        fscanf(f, "%lld", &dist[i]);
    }

    long long int ans = 1;
    for (int i = 0; i < N; i++) {
        long long int count = 0;
        for (int hold = 1; hold < time[i]; hold++) {
            if (hold * (time[i] - hold) >
                dist[i]) { // quadratic inequality could be calculate in O(1)

                count = time[i] - hold - hold + 1;
                break;
            }
        }
        printf("%lld ", count);
        ans *= count;
    }
    printf("%lld, ", ans);

    fclose(f);
    return 0;
}

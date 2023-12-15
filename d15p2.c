#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *label;
    int focus;
    struct Node *next;
};

struct Node *new(const char *label, int focus) {
    struct Node *new = (struct Node *)malloc(sizeof(struct Node));

    new->label = (char *)malloc(strlen(label));
    strcpy(new->label, label);
    new->focus = focus;
    new->next = NULL;

    return new;
}

void del(struct Node *head) {
    free(head->label);
    free(head);
}

int hash(const char *s) {
    int curr_val = 0;
    for (int i = 0; i < (int)strlen(s); i++) {
        curr_val = ((curr_val + s[i]) * 17) % 256;
    }
    return curr_val;
}

int main() {
    FILE *f = fopen("input.txt", "r");

    struct Node *boxes[256];

    memset(boxes, 0, 256 * sizeof(long));

    while (!feof(f)) {
        char s[10];
        bzero(s, 10);
        int len = 0;

        char c = fgetc(f);
        while (c != ',' && c != '\n') {
            s[len++] = c;
            c = fgetc(f);
        }

        if (s[len - 1] == '-') {
            char label[len - 1];
            bzero(label, len);
            memcpy(label, s, len - 1);

            int box = hash(label);
            struct Node *head = boxes[box];

            if (head) {
                if (!strcmp(head->label, label)) {
                    boxes[box] = head->next;
                    del(head);
                } else {
                    while (head->next && strcmp(head->next->label, label)) {
                        head = head->next;
                    }
                    if (head->next) {
                        struct Node *temp = head->next;
                        head->next = head->next->next;
                        del(temp);
                    }
                }
            }
        } else {
            char label[len - 2];
            bzero(label, len - 1);
            memcpy(label, s, len - 2);
            int focus = s[len - 1] - '0';

            int box = hash(label);
            struct Node *head = boxes[box];

            if (!head) {
                boxes[box] = new (label, focus);
            } else {
                while (head->next && strcmp(head->label, label)) {
                    head = head->next;
                }
                if (!strcmp(head->label, label)) {
                    head->focus = focus;
                } else {
                    head->next = new (label, focus);
                }
            }
        }

        if (c == '\n') {
            break;
        }
    }

    fclose(f);

    int sum = 0;
    for (int i = 0; i < 256; i++) {
        struct Node *head = boxes[i];
        if (head != NULL) {
            int j = 1;
            while (head != NULL) {
                struct Node *temp = head->next;
                sum += (i + 1) * (j++) * head->focus;
                del(head);
                head = temp;
            }
        }
    }
    printf("%d", sum);

    return 0;
}

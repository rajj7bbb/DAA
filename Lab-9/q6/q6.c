#include <stdio.h>
#include <string.h>

typedef struct {
    char ch;
    int freq;
} Node;

void swap(Node *a, Node *b) {
    Node t = *a;
    *a = *b;
    *b = t;
}

void push(Node heap[], int *n, Node x) {
    int i = (*n)++;
    heap[i] = x;

    while (i > 0) {
        int p = (i - 1) / 2;

        if (heap[p].freq >= heap[i].freq)
            break;

        swap(&heap[p], &heap[i]);
        i = p;
    }
}

Node pop(Node heap[], int *n) {
    Node ans = heap[0];

    heap[0] = heap[--(*n)];

    int i = 0;

    while (1) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int largest = i;

        if (l < *n && heap[l].freq > heap[largest].freq)
            largest = l;

        if (r < *n && heap[r].freq > heap[largest].freq)
            largest = r;

        if (largest == i)
            break;

        swap(&heap[i], &heap[largest]);
        i = largest;
    }

    return ans;
}

int main() {
    char s[1000];
    int K;

    scanf("%s", s);
    scanf("%d", &K);

    if (K <= 1) {
        printf("%s\n", s);
        return 0;
    }

    int freq[256] = {0};

    for (int i = 0; s[i]; i++)
        freq[(unsigned char)s[i]]++;

    Node heap[256];
    int hsize = 0;

    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            Node x = {(char)i, freq[i]};
            push(heap, &hsize, x);
        }
    }

    Node queue[1000];
    int front = 0, rear = 0;

    char ans[1000];
    int len = 0;

    while (len < (int)strlen(s)) {

        if (hsize == 0) {
            printf("Impossible\n");
            return 0;
        }

        Node cur = pop(heap, &hsize);

        ans[len++] = cur.ch;
        cur.freq--;

        queue[rear++] = cur;

        if (rear - front >= K) {
            Node ready = queue[front++];

            if (ready.freq > 0)
                push(heap, &hsize, ready);
        }
    }

    ans[len] = '\0';

    printf("%s\n", ans);

    return 0;
}
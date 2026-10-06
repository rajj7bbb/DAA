#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
} Node;

typedef struct {
    Node *a[100];
    int size;
} MinHeap;

Node* createNode(char ch, int freq) {
    Node *p = malloc(sizeof(Node));
    p->ch = ch;
    p->freq = freq;
    p->left = p->right = NULL;
    return p;
}

void swap(Node **x, Node **y) {
    Node *t = *x;
    *x = *y;
    *y = t;
}

void push(MinHeap *h, Node *x) {
    int i = h->size++;
    h->a[i] = x;

    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->a[p]->freq <= h->a[i]->freq)
            break;
        swap(&h->a[p], &h->a[i]);
        i = p;
    }
}

Node* pop(MinHeap *h) {
    Node *res = h->a[0];
    h->a[0] = h->a[--h->size];

    int i = 0;

    while (1) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int smallest = i;

        if (l < h->size && h->a[l]->freq < h->a[smallest]->freq)
            smallest = l;

        if (r < h->size && h->a[r]->freq < h->a[smallest]->freq)
            smallest = r;

        if (smallest == i)
            break;

        swap(&h->a[i], &h->a[smallest]);
        i = smallest;
    }

    return res;
}

void printCodes(Node *root, char code[], int depth) {
    if (!root)
        return;

    if (!root->left && !root->right) {
        code[depth] = '\0';
        printf("%c : %s\n", root->ch, code);
        return;
    }

    code[depth] = '0';
    printCodes(root->left, code, depth + 1);

    code[depth] = '1';
    printCodes(root->right, code, depth + 1);
}

int main() {
    int n;
    scanf("%d", &n);

    MinHeap heap = { .size = 0 };

    for (int i = 0; i < n; i++) {
        char ch;
        int freq;

        scanf(" %c %d", &ch, &freq);
        push(&heap, createNode(ch, freq));
    }

    while (heap.size > 1) {
        Node *x = pop(&heap);
        Node *y = pop(&heap);

        Node *z = createNode('$', x->freq + y->freq);
        z->left = x;
        z->right = y;

        push(&heap, z);
    }

    char code[100];

    printf("Huffman Codes:\n");
    printCodes(heap.a[0], code, 0);

    return 0;
}
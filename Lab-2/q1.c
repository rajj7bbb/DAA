#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <direct.h>
#define MKDIR(d) _mkdir(d)
static double get_time_us(void) {
    LARGE_INTEGER freq, count;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&count);
    return (double)count.QuadPart * 1000000.0 / (double)freq.QuadPart;
}
#else
#include <sys/stat.h>
#define MKDIR(d) mkdir(d, 0755)
static double get_time_us(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec * 1000000.0 + (double)ts.tv_nsec / 1000.0;
}
#endif

// UNSORTED ARRAY
typedef struct { int *data; int capacity; int size; } UnsortedArray;

static UnsortedArray* ua_create(int cap) {
    UnsortedArray *ua = (UnsortedArray*)malloc(sizeof(UnsortedArray));
    ua->capacity = cap; ua->size = 0;
    ua->data = (int*)malloc(sizeof(int) * cap);
    return ua;
}
static void ua_free(UnsortedArray *ua) { if (ua) { free(ua->data); free(ua); } }

static int ua_search(UnsortedArray *ua, int key) {
    for (int i = 0; i < ua->size; i++) if (ua->data[i] == key) return i;
    return -1;
}
static void ua_insert(UnsortedArray *ua, int key) {
    if (ua->size >= ua->capacity) {
        ua->capacity *= 2;
        ua->data = (int*)realloc(ua->data, sizeof(int) * ua->capacity);
    }
    ua->data[ua->size++] = key;
}
static void ua_delete(UnsortedArray *ua, int idx) {
    if (idx >= 0 && idx < ua->size) { ua->data[idx] = ua->data[--ua->size]; }
}
static int ua_min(UnsortedArray *ua) {
    if (!ua->size) return -1;
    int m = ua->data[0];
    for (int i = 1; i < ua->size; i++) if (ua->data[i] < m) m = ua->data[i];
    return m;
}
static int ua_max(UnsortedArray *ua) {
    if (!ua->size) return -1;
    int m = ua->data[0];
    for (int i = 1; i < ua->size; i++) if (ua->data[i] > m) m = ua->data[i];
    return m;
}
static int ua_predecessor(UnsortedArray *ua, int idx) {
    if (idx < 0 || idx >= ua->size) return -1;
    int k = ua->data[idx], p = -1; bool found = false;
    for (int i = 0; i < ua->size; i++) {
        if (ua->data[i] < k && (!found || ua->data[i] > p)) { p = ua->data[i]; found = true; }
    }
    return found ? p : -1;
}
static int ua_successor(UnsortedArray *ua, int idx) {
    if (idx < 0 || idx >= ua->size) return -1;
    int k = ua->data[idx], s = -1; bool found = false;
    for (int i = 0; i < ua->size; i++) {
        if (ua->data[i] > k && (!found || ua->data[i] < s)) { s = ua->data[i]; found = true; }
    }
    return found ? s : -1;
}

// SORTED ARRAY
typedef struct { int *data; int capacity; int size; } SortedArray;

static SortedArray* sa_create(int cap) {
    SortedArray *sa = (SortedArray*)malloc(sizeof(SortedArray));
    sa->capacity = cap; sa->size = 0;
    sa->data = (int*)malloc(sizeof(int) * cap);
    return sa;
}
static void sa_free(SortedArray *sa) { if (sa) { free(sa->data); free(sa); } }

static int sa_search(SortedArray *sa, int key) {
    int l = 0, r = sa->size - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (sa->data[m] == key) return m;
        if (sa->data[m] < key) l = m + 1; else r = m - 1;
    }
    return -1;
}
static void sa_insert(SortedArray *sa, int key) {
    if (sa->size >= sa->capacity) {
        sa->capacity *= 2;
        sa->data = (int*)realloc(sa->data, sizeof(int) * sa->capacity);
    }
    int pos = 0;
    while (pos < sa->size && sa->data[pos] < key) pos++;
    for (int i = sa->size; i > pos; i--) sa->data[i] = sa->data[i - 1];
    sa->data[pos] = key; sa->size++;
}
static void sa_delete(SortedArray *sa, int idx) {
    if (idx < 0 || idx >= sa->size) return;
    for (int i = idx; i < sa->size - 1; i++) sa->data[i] = sa->data[i + 1];
    sa->size--;
}
static int sa_min(SortedArray *sa) { return sa->size ? sa->data[0] : -1; }
static int sa_max(SortedArray *sa) { return sa->size ? sa->data[sa->size - 1] : -1; }
static int sa_predecessor(SortedArray *sa, int idx) { return (idx > 0 && idx < sa->size) ? sa->data[idx - 1] : -1; }
static int sa_successor(SortedArray *sa, int idx) { return (idx >= 0 && idx < sa->size - 1) ? sa->data[idx + 1] : -1; }

// SINGLY LINKED LIST (UNSORTED & SORTED)
typedef struct SNode { int key; struct SNode *next; } SNode;

typedef struct { SNode *head; int size; } SinglyUnsortedList;

static SinglyUnsortedList* su_create(void) {
    SinglyUnsortedList *l = (SinglyUnsortedList*)malloc(sizeof(SinglyUnsortedList));
    l->head = NULL; l->size = 0; return l;
}
static void su_free(SinglyUnsortedList *l) {
    if (!l) return;
    SNode *c = l->head;
    while (c) { SNode *n = c->next; free(c); c = n; }
    free(l);
}
static SNode* su_search(SinglyUnsortedList *l, int key) {
    for (SNode *c = l->head; c; c = c->next) if (c->key == key) return c;
    return NULL;
}
static SNode* su_insert(SinglyUnsortedList *l, int key) {
    SNode *n = (SNode*)malloc(sizeof(SNode));
    n->key = key; n->next = l->head; l->head = n; l->size++;
    return n;
}
static void su_delete(SinglyUnsortedList *l, SNode *node) {
    if (!l || !l->head || !node) return;
    if (l->head == node) { l->head = node->next; free(node); l->size--; return; }
    SNode *c = l->head;
    while (c && c->next != node) c = c->next;
    if (c) { c->next = node->next; free(node); l->size--; }
}
static SNode* su_min(SinglyUnsortedList *l) {
    if (!l || !l->head) return NULL;
    SNode *m = l->head;
    for (SNode *c = l->head->next; c; c = c->next) if (c->key < m->key) m = c;
    return m;
}
static SNode* su_max(SinglyUnsortedList *l) {
    if (!l || !l->head) return NULL;
    SNode *m = l->head;
    for (SNode *c = l->head->next; c; c = c->next) if (c->key > m->key) m = c;
    return m;
}
static SNode* su_predecessor(SinglyUnsortedList *l, SNode *node) {
    if (!l || !node) return NULL;
    SNode *p = NULL;
    for (SNode *c = l->head; c; c = c->next) {
        if (c->key < node->key && (!p || c->key > p->key)) p = c;
    }
    return p;
}
static SNode* su_successor(SinglyUnsortedList *l, SNode *node) {
    if (!l || !node) return NULL;
    SNode *s = NULL;
    for (SNode *c = l->head; c; c = c->next) {
        if (c->key > node->key && (!s || c->key < s->key)) s = c;
    }
    return s;
}

typedef struct { SNode *head; SNode *tail; int size; } SinglySortedList;

static SinglySortedList* ss_create(void) {
    SinglySortedList *l = (SinglySortedList*)malloc(sizeof(SinglySortedList));
    l->head = l->tail = NULL; l->size = 0; return l;
}
static void ss_free(SinglySortedList *l) {
    if (!l) return;
    SNode *c = l->head;
    while (c) { SNode *n = c->next; free(c); c = n; }
    free(l);
}
static SNode* ss_search(SinglySortedList *l, int key) {
    for (SNode *c = l->head; c && c->key <= key; c = c->next) if (c->key == key) return c;
    return NULL;
}
static SNode* ss_insert(SinglySortedList *l, int key) {
    SNode *n = (SNode*)malloc(sizeof(SNode));
    n->key = key; n->next = NULL;
    if (!l->head) { l->head = l->tail = n; }
    else if (key < l->head->key) { n->next = l->head; l->head = n; }
    else {
        SNode *c = l->head;
        while (c->next && c->next->key <= key) c = c->next;
        n->next = c->next; c->next = n;
        if (!n->next) l->tail = n;
    }
    l->size++; return n;
}
static void ss_delete(SinglySortedList *l, SNode *node) {
    if (!l || !l->head || !node) return;
    if (l->head == node) {
        l->head = node->next; if (!l->head) l->tail = NULL;
        free(node); l->size--; return;
    }
    SNode *c = l->head;
    while (c && c->next != node) c = c->next;
    if (c) {
        c->next = node->next; if (!c->next) l->tail = c;
        free(node); l->size--;
    }
}
static SNode* ss_min(SinglySortedList *l) { return l ? l->head : NULL; }
static SNode* ss_max(SinglySortedList *l) { return l ? l->tail : NULL; }
static SNode* ss_predecessor(SinglySortedList *l, SNode *node) {
    if (!l || !node || l->head == node) return NULL;
    SNode *c = l->head;
    while (c && c->next != node) c = c->next;
    return c;
}
static SNode* ss_successor(SinglySortedList *l, SNode *node) {
    (void)l; return node ? node->next : NULL;
}

// DOUBLY LINKED LIST (UNSORTED & SORTED)
typedef struct DNode { int key; struct DNode *prev; struct DNode *next; } DNode;

typedef struct { DNode *head; DNode *tail; int size; } DoublyUnsortedList;

static DoublyUnsortedList* du_create(void) {
    DoublyUnsortedList *l = (DoublyUnsortedList*)malloc(sizeof(DoublyUnsortedList));
    l->head = l->tail = NULL; l->size = 0; return l;
}
static void du_free(DoublyUnsortedList *l) {
    if (!l) return;
    DNode *c = l->head;
    while (c) { DNode *n = c->next; free(c); c = n; }
    free(l);
}
static DNode* du_search(DoublyUnsortedList *l, int key) {
    for (DNode *c = l->head; c; c = c->next) if (c->key == key) return c;
    return NULL;
}
static DNode* du_insert(DoublyUnsortedList *l, int key) {
    DNode *n = (DNode*)malloc(sizeof(DNode));
    n->key = key; n->prev = NULL; n->next = l->head;
    if (l->head) l->head->prev = n; else l->tail = n;
    l->head = n; l->size++; return n;
}
static void du_delete(DoublyUnsortedList *l, DNode *node) {
    if (!l || !node) return;
    if (node->prev) node->prev->next = node->next; else l->head = node->next;
    if (node->next) node->next->prev = node->prev; else l->tail = node->prev;
    free(node); l->size--;
}
static DNode* du_min(DoublyUnsortedList *l) {
    if (!l || !l->head) return NULL;
    DNode *m = l->head;
    for (DNode *c = l->head->next; c; c = c->next) if (c->key < m->key) m = c;
    return m;
}
static DNode* du_max(DoublyUnsortedList *l) {
    if (!l || !l->head) return NULL;
    DNode *m = l->head;
    for (DNode *c = l->head->next; c; c = c->next) if (c->key > m->key) m = c;
    return m;
}
static DNode* du_predecessor(DoublyUnsortedList *l, DNode *node) {
    if (!l || !node) return NULL;
    DNode *p = NULL;
    for (DNode *c = l->head; c; c = c->next) {
        if (c->key < node->key && (!p || c->key > p->key)) p = c;
    }
    return p;
}
static DNode* du_successor(DoublyUnsortedList *l, DNode *node) {
    if (!l || !node) return NULL;
    DNode *s = NULL;
    for (DNode *c = l->head; c; c = c->next) {
        if (c->key > node->key && (!s || c->key < s->key)) s = c;
    }
    return s;
}

typedef struct { DNode *head; DNode *tail; int size; } DoublySortedList;

static DoublySortedList* ds_create(void) {
    DoublySortedList *l = (DoublySortedList*)malloc(sizeof(DoublySortedList));
    l->head = l->tail = NULL; l->size = 0; return l;
}
static void ds_free(DoublySortedList *l) {
    if (!l) return;
    DNode *c = l->head;
    while (c) { DNode *n = c->next; free(c); c = n; }
    free(l);
}
static DNode* ds_search(DoublySortedList *l, int key) {
    for (DNode *c = l->head; c && c->key <= key; c = c->next) if (c->key == key) return c;
    return NULL;
}
static DNode* ds_insert(DoublySortedList *l, int key) {
    DNode *n = (DNode*)malloc(sizeof(DNode));
    n->key = key; n->prev = n->next = NULL;
    if (!l->head) { l->head = l->tail = n; }
    else if (key < l->head->key) { n->next = l->head; l->head->prev = n; l->head = n; }
    else {
        DNode *c = l->head;
        while (c->next && c->next->key <= key) c = c->next;
        n->next = c->next; n->prev = c;
        if (c->next) c->next->prev = n; else l->tail = n;
        c->next = n;
    }
    l->size++; return n;
}
static void ds_delete(DoublySortedList *l, DNode *node) {
    if (!l || !node) return;
    if (node->prev) node->prev->next = node->next; else l->head = node->next;
    if (node->next) node->next->prev = node->prev; else l->tail = node->prev;
    free(node); l->size--;
}
static DNode* ds_min(DoublySortedList *l) { return l ? l->head : NULL; }
static DNode* ds_max(DoublySortedList *l) { return l ? l->tail : NULL; }
static DNode* ds_predecessor(DoublySortedList *l, DNode *node) {
    (void)l; return node ? node->prev : NULL;
}
static DNode* ds_successor(DoublySortedList *l, DNode *node) {
    (void)l; return node ? node->next : NULL;
}

// GNUPLOT SCRIPT & PLOT GENERATOR
static const char *OPS[7] = {"search", "insert", "delete", "min", "max", "predecessor", "successor"};
static const char *TITLES[7] = {
    "Dictionary Search Operation - Order of Growth (Worst-Case)",
    "Dictionary Insert Operation - Order of Growth (Worst-Case)",
    "Dictionary Delete Operation - Order of Growth (Given Pointer, Worst-Case)",
    "Dictionary Min Operation - Order of Growth (Worst-Case)",
    "Dictionary Max Operation - Order of Growth (Worst-Case)",
    "Dictionary Predecessor Operation - Order of Growth (Given Pointer, Worst-Case)",
    "Dictionary Successor Operation - Order of Growth (Given Pointer, Worst-Case)"
};
static const char *CMPLX[7][6] = {
    {"O(n)", "O(log n)", "O(n)", "O(n)", "O(n)", "O(n)"},
    {"O(1)", "O(n)",     "O(1)", "O(n)", "O(1)", "O(n)"},
    {"O(1)", "O(n)",     "O(n)", "O(n)", "O(1)", "O(1)"},
    {"O(n)", "O(1)",     "O(n)", "O(1)", "O(n)", "O(1)"},
    {"O(n)", "O(1)",     "O(n)", "O(1)", "O(n)", "O(1)"},
    {"O(n)", "O(1)",     "O(n)", "O(n)", "O(n)", "O(1)"},
    {"O(n)", "O(1)",     "O(n)", "O(1)", "O(n)", "O(1)"}
};
static const char *DS_NAMES[6] = {
    "Unsorted Array", "Sorted Array", "Singly Unsorted List",
    "Singly Sorted List", "Doubly Unsorted List", "Doubly Sorted List"
};

static void generate_plots_gnuplot(void) {
    FILE *gp = fopen("scripts/plot_all.gp", "w");
    if (!gp) return;

    fprintf(gp, "set key top left box\nset grid linecolor rgb '#cccccc' lw 1\n");
    fprintf(gp, "set style line 1 lc rgb '#e41a1c' pt 7 ps 1.2 lw 2.5 # Unsorted Array (Red)\n");
    fprintf(gp, "set style line 2 lc rgb '#377eb8' pt 5 ps 1.2 lw 2.5 # Sorted Array (Blue)\n");
    fprintf(gp, "set style line 3 lc rgb '#4daf4a' pt 9 ps 1.2 lw 2.5 # Singly Unsorted (Green)\n");
    fprintf(gp, "set style line 4 lc rgb '#984ea3' pt 11 ps 1.2 lw 2.5 # Singly Sorted (Purple)\n");
    fprintf(gp, "set style line 5 lc rgb '#ff7f00' pt 13 ps 1.2 lw 2.5 # Doubly Unsorted (Orange)\n");
    fprintf(gp, "set style line 6 lc rgb '#a65628' pt 15 ps 1.2 lw 2.5 # Doubly Sorted (Brown)\n\n");

    for (int i = 0; i < 7; i++) {
        fprintf(gp, "set terminal pngcairo size 1000, 650 font 'Sans,12' linewidth 2\n");
        fprintf(gp, "set output 'plots/%s_performance.png'\n", OPS[i]);
        fprintf(gp, "set title '%s' font 'Sans-Bold,14'\n", TITLES[i]);
        fprintf(gp, "set xlabel 'Input Size (N)' font 'Sans-Bold,12'\n");
        fprintf(gp, "set ylabel 'Execution Time (microseconds)' font 'Sans-Bold,12'\n");
        fprintf(gp, "plot ");
        for (int ds = 0; ds < 6; ds++) {
            fprintf(gp, "'data/%s.dat' using 1:%d with linespoints ls %d title '%s [%s]'%s",
                    OPS[i], ds + 2, ds + 1, DS_NAMES[ds], CMPLX[i][ds], (ds == 5) ? "\n\n" : ", \\\n     ");
        }
    }
    fprintf(gp, "print 'GNUplot: All 7 PNG plots generated successfully!'\n");
    fclose(gp);

    system("gnuplot scripts/plot_all.gp");
}

// BENCHMARK HARNESS & MAIN
static const int SIZES[] = {1000, 2000, 4000, 6000, 8000, 10000, 15000, 20000};
static const int NUM_SIZES = sizeof(SIZES) / sizeof(SIZES[0]);

int main(void) {
    MKDIR("data"); MKDIR("plots"); MKDIR("scripts");

    printf("===============================================================================\n");
    printf("        Dictionary Operations Benchmark & Automated PNG Plot Generator         \n");
    printf("===============================================================================\n\n");

    FILE *files[7];
    for (int i = 0; i < 7; i++) {
        char path[64]; snprintf(path, sizeof(path), "data/%s.dat", OPS[i]);
        files[i] = fopen(path, "w");
        if (files[i]) {
            fprintf(files[i], "# N UnsortedArray SortedArray SinglyUnsorted SinglySorted DoublyUnsorted DoublySorted\n");
        }
    }

    printf("[1/3] Benchmarking 6 Data Structures across %d Input Sizes...\n", NUM_SIZES);

    for (int s = 0; s < NUM_SIZES; s++) {
        int N = SIZES[s];
        printf("      -> Processing N = %5d elements... ", N); fflush(stdout);

        double t[6][7] = {{0}};
        int R1 = 10000, RN = 50;

        // 1. Unsorted Array
        {
            UnsortedArray *ua = ua_create(N + 100);
            for (int i = 0; i < N; i++) ua_insert(ua, i * 2);
            double st = get_time_us(); for (int r = 0; r < RN; r++) ua_search(ua, -1); t[0][0] = (get_time_us() - st) / RN;
            st = get_time_us(); for (int r = 0; r < R1; r++) { ua_insert(ua, 999999); ua->size--; } t[0][1] = (get_time_us() - st) / R1;
            st = get_time_us(); for (int r = 0; r < R1; r++) { int lv = ua->data[ua->size - 1]; ua_delete(ua, N / 2); ua_insert(ua, lv); } t[0][2] = (get_time_us() - st) / R1;
            st = get_time_us(); for (int r = 0; r < RN; r++) ua_min(ua); t[0][3] = (get_time_us() - st) / RN;
            st = get_time_us(); for (int r = 0; r < RN; r++) ua_max(ua); t[0][4] = (get_time_us() - st) / RN;
            st = get_time_us(); for (int r = 0; r < RN; r++) ua_predecessor(ua, N / 2); t[0][5] = (get_time_us() - st) / RN;
            st = get_time_us(); for (int r = 0; r < RN; r++) ua_successor(ua, N / 2); t[0][6] = (get_time_us() - st) / RN;
            ua_free(ua);
        }

        // 2. Sorted Array
        {
            SortedArray *sa = sa_create(N + 100);
            for (int i = 0; i < N; i++) sa_insert(sa, i * 2);
            double st = get_time_us(); for (int r = 0; r < R1; r++) sa_search(sa, -1); t[1][0] = (get_time_us() - st) / R1;
            st = get_time_us(); for (int r = 0; r < RN; r++) { sa_insert(sa, -1); sa_delete(sa, 0); } t[1][1] = (get_time_us() - st) / RN;
            st = get_time_us(); for (int r = 0; r < RN; r++) { sa_delete(sa, 0); sa_insert(sa, 0); } t[1][2] = (get_time_us() - st) / RN;
            st = get_time_us(); for (int r = 0; r < R1; r++) sa_min(sa); t[1][3] = (get_time_us() - st) / R1;
            st = get_time_us(); for (int r = 0; r < R1; r++) sa_max(sa); t[1][4] = (get_time_us() - st) / R1;
            st = get_time_us(); for (int r = 0; r < R1; r++) sa_predecessor(sa, N / 2); t[1][5] = (get_time_us() - st) / R1;
            st = get_time_us(); for (int r = 0; r < R1; r++) sa_successor(sa, N / 2); t[1][6] = (get_time_us() - st) / R1;
            sa_free(sa);
        }

        // 3. Singly Unsorted List
        {
            SinglyUnsortedList *su = su_create();
            for (int i = 0; i < N; i++) su_insert(su, i * 2);
            double st = get_time_us(); for (int r = 0; r < RN; r++) su_search(su, -1); t[2][0] = (get_time_us() - st) / RN;
            st = get_time_us(); for (int r = 0; r < R1; r++) { SNode *n = su_insert(su, -1); su_delete(su, n); } t[2][1] = (get_time_us() - st) / R1;
            SNode *tail = su_search(su, 0);
            st = get_time_us(); for (int r = 0; r < RN; r++) su_predecessor(su, tail); t[2][2] = (get_time_us() - st) / RN;
            st = get_time_us(); for (int r = 0; r < RN; r++) su_min(su); t[2][3] = (get_time_us() - st) / RN;
            st = get_time_us(); for (int r = 0; r < RN; r++) su_max(su); t[2][4] = (get_time_us() - st) / RN;
            SNode *mid = su_search(su, N);
            st = get_time_us(); for (int r = 0; r < RN; r++) su_predecessor(su, mid); t[2][5] = (get_time_us() - st) / RN;
            st = get_time_us(); for (int r = 0; r < RN; r++) su_successor(su, mid); t[2][6] = (get_time_us() - st) / RN;
            su_free(su);
        }

        // 4. Singly Sorted List
        {
            SinglySortedList *ss = ss_create();
            for (int i = 0; i < N; i++) ss_insert(ss, i * 2);
            double st = get_time_us(); for (int r = 0; r < RN; r++) ss_search(ss, -1); t[3][0] = (get_time_us() - st) / RN;
            st = get_time_us(); for (int r = 0; r < RN; r++) { SNode *n = ss_insert(ss, 2 * N + 2); ss_delete(ss, n); } t[3][1] = (get_time_us() - st) / RN;
            SNode *tail = ss->tail;
            st = get_time_us(); for (int r = 0; r < RN; r++) ss_predecessor(ss, tail); t[3][2] = (get_time_us() - st) / RN;
            st = get_time_us(); for (int r = 0; r < R1; r++) ss_min(ss); t[3][3] = (get_time_us() - st) / R1;
            st = get_time_us(); for (int r = 0; r < R1; r++) ss_max(ss); t[3][4] = (get_time_us() - st) / R1;
            SNode *mid = ss_search(ss, N);
            st = get_time_us(); for (int r = 0; r < RN; r++) ss_predecessor(ss, mid); t[3][5] = (get_time_us() - st) / RN;
            st = get_time_us(); for (int r = 0; r < R1; r++) ss_successor(ss, mid); t[3][6] = (get_time_us() - st) / R1;
            ss_free(ss);
        }

        // 5. Doubly Unsorted List
        {
            DoublyUnsortedList *du = du_create();
            for (int i = 0; i < N; i++) du_insert(du, i * 2);
            double st = get_time_us(); for (int r = 0; r < RN; r++) du_search(du, -1); t[4][0] = (get_time_us() - st) / RN;
            st = get_time_us(); for (int r = 0; r < R1; r++) { DNode *n = du_insert(du, -1); du_delete(du, n); } t[4][1] = (get_time_us() - st) / R1;
            DNode *mid = du_search(du, N);
            st = get_time_us(); for (int r = 0; r < R1; r++) { DNode *n = du_insert(du, 999999); du_delete(du, n); } t[4][2] = (get_time_us() - st) / R1;
            st = get_time_us(); for (int r = 0; r < RN; r++) du_min(du); t[4][3] = (get_time_us() - st) / RN;
            st = get_time_us(); for (int r = 0; r < RN; r++) du_max(du); t[4][4] = (get_time_us() - st) / RN;
            st = get_time_us(); for (int r = 0; r < RN; r++) du_predecessor(du, mid); t[4][5] = (get_time_us() - st) / RN;
            st = get_time_us(); for (int r = 0; r < RN; r++) du_successor(du, mid); t[4][6] = (get_time_us() - st) / RN;
            du_free(du);
        }

        // 6. Doubly Sorted List
        {
            DoublySortedList *ds = ds_create();
            for (int i = 0; i < N; i++) ds_insert(ds, i * 2);
            double st = get_time_us(); for (int r = 0; r < RN; r++) ds_search(ds, -1); t[5][0] = (get_time_us() - st) / RN;
            st = get_time_us(); for (int r = 0; r < RN; r++) { DNode *n = ds_insert(ds, 2 * N + 2); ds_delete(ds, n); } t[5][1] = (get_time_us() - st) / RN;
            st = get_time_us(); for (int r = 0; r < R1; r++) { DNode *n = ds_insert(ds, 2 * N + 2); ds_delete(ds, n); } t[5][2] = (get_time_us() - st) / R1;
            st = get_time_us(); for (int r = 0; r < R1; r++) ds_min(ds); t[5][3] = (get_time_us() - st) / R1;
            st = get_time_us(); for (int r = 0; r < R1; r++) ds_max(ds); t[5][4] = (get_time_us() - st) / R1;
            DNode *mid = ds_search(ds, N);
            st = get_time_us(); for (int r = 0; r < R1; r++) ds_predecessor(ds, mid); t[5][5] = (get_time_us() - st) / R1;
            st = get_time_us(); for (int r = 0; r < R1; r++) ds_successor(ds, mid); t[5][6] = (get_time_us() - st) / R1;
            ds_free(ds);
        }

        // Write row to each of the 7 .dat files
        for (int op = 0; op < 7; op++) {
            fprintf(files[op], "%-7d %-12.4f %-12.4f %-12.4f %-12.4f %-12.4f %-12.4f\n",
                    N, t[0][op], t[1][op], t[2][op], t[3][op], t[4][op], t[5][op]);
        }

        printf("done.\n"); fflush(stdout);
    }

    for (int i = 0; i < 7; i++) if (files[i]) fclose(files[i]);

    printf("\n[2/3] .dat Datasets successfully saved to data/\n"); fflush(stdout);
    printf("\n[3/3] Generating 7 High-Resolution PNG Plots in plots/...\n"); fflush(stdout);

    generate_plots_gnuplot();

    printf("\n===============================================================================\n");
    printf(" SUCCESS! All 7 PNG files generated in plots/:\n");
    for (int i = 0; i < 7; i++) printf("   %d. plots/%s_performance.png\n", i + 1, OPS[i]);
    printf("===============================================================================\n");

    return 0;
}

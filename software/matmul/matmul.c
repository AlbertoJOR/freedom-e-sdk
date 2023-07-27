//
// Created by albertojor on 2/07/23.
//
#include <stdio.h>
#include <stdlib.h>
#include "../RoCCcommon/csr.h"

#define PFDEBUG
#define N 10
#define zero 0
#define pi 3
#define one 1
typedef unsigned element_t;
//#define WITH_MALLOC

#ifndef WITH_MALLOC
static element_t sa[N * N], sb[N * N], sc[N * N];
#endif
#ifdef PFDEBUG

void print_matrix(element_t *a, int n, int m) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            printf("%x ", a[i * n + j]);
        printf("\n");
    }
    printf("\n");
}

#endif

void init_matrix(element_t **a, element_t **b, element_t **c, int n) {
    int i, j;

#ifdef WITH_MALLOC
    *a = (element_t*)malloc(n * n * sizeof(element_t));
    *b = (element_t*)malloc(n * n * sizeof(element_t));
    *c = (element_t*)malloc(n * n * sizeof(element_t));
#else
    *a = &(sa[0]);
    *b = &(sb[0]);
    *c = &(sc[0]);
#endif

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            (*a)[i * n + j] = zero;
            (*b)[i * n + j] = pi;
        }

    for (i = 0; i < n; i++)
        (*a)[i * n + i] = one;
}

void mm(element_t *a, element_t *b, element_t *c, int n, int m, int p) {
    int i, j, k;
    unsigned r = 0;

    for (i = 0; i < n; i++) {
        printf("round %d %d\n", i, r);
        for (j = 0; j < p; j++) {
            r = 0;
            for (k = 0; k < m; k++) {
                r = r + a[i * m + k] * b[k * p + j];
            }
            c[i * p + j] = r;
            printf("round %d %d\n", i, r);
        }
    }
}


int main() {
    printf("hola inicio\n");
    element_t *a, *b, *c;
    // init matrix
    printf("hola 2\n");
    init_matrix(&a, &b, &c, N);
    // multiply
    printf("hola 3\n");
    unsigned startc = rdcycle();
    printf("hola 4\n");
    mm(a, b, c, N, N, N);
    printf("hola 5\n");
    unsigned endc = rdcycle();
    endc = endc - startc;
    printf("hola");
#ifdef PFDEBUG
    printf("Cycles %x\n", endc);
    print_matrix(a, N, N);
    print_matrix(b, N, N);
    print_matrix(c, N, N);
#endif
#ifdef WITH_MALLOC
    free(a);
    free(b);
    free(c);
#endif

    return 0;
}
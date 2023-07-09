//
// Created by albertojor on 17/05/23.
//
#include "word.h"
#include "stdio.h"
#include "word.h"

int main() {
    uint64_t a = 0x123456789abcdef0;
    uint64_t res;
    for (int i = 0; i < 9; i++) {
        res = CLEARBYTES(a, i);
        printf("i = %d   res = %lx \n", i, res);
    }
    return 0;
}
//
// Created by albertojor on 12/05/23.
//
#include "permutations.h"
#include "ascon.h"
#include "constants.h"
#include "printstate.h"
#include "round.h"
#include <stdio.h>

void printS(ascon_state_t *s) {
    for (int i = 0; i < 5; i++) {
        printf("%lX\n",s->x[i]);
    }
}

int main() {
    ascon_state_t S;
    S.x[0] = 0;
    S.x[1] = 0;
    S.x[2] = 0;
    S.x[3] = 0;
    S.x[4] = 0;
    printf("Before the round:\n");
    printS(&S);
   /* ROUND(&S,0xf0);
    printf("\n");
    printS(&S);
    ROUND(&S,0xe1);
    printf("\n");
    printS(&S);
    ROUND(&S,0xd2);
    printf("\n");
    printS(&S);
    ROUND(&S,0xc3);
    printf("\n")
    printS(&S);
    ROUND(&S,0xb4);
    printf("\n");
    printS(&S);
    ROUND(&S,0xa5);
    printf("\n");*/
    printS(&S);
    ROUND(&S,0x96);
    printf("\n");
    printS(&S);
    ROUND(&S,0x87);
    printf("\n");
    printS(&S);
    ROUND(&S,0x78);
    printf("\n");
    printS(&S);
    ROUND(&S,0x69);
    printf("\n");
    printS(&S);
    ROUND(&S,0x5a);
    printf("\n");
    printS(&S);
    ROUND(&S,0x4b);
    printf("\n");
    // P12(&S);
    printS(&S);


    return 0;
}

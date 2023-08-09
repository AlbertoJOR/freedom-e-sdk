//
// Created by albertojor on 31/07/23.
//

#ifndef FREEDOM_E_SDK_UTIL_H
#define FREEDOM_E_SDK_UTIL_H
#include "state.h"
/*u64 rightMask(int shift) {
    shift = shift % 64; // Ensure shift is in the range [0, 63]

    u64 mask;

    if (shift == 0) {
        // Mask is all 1s when shift is 0
        mask.xh = 0xFFFFFFFF;
        mask.xl = 0xFFFFFFFF;
    } else if (shift >= 32) {
        // Mask covers only the low part when shift is >= 32
        mask.xh = 0;
        mask.xl = 0xFFFFFFFF >> (shift - 32);
    } else {
        // Mask spans both high and low parts when shift is < 32
        mask.xh = 0xFFFFFFFF >> shift;
        mask.xl = 0xFFFFFFFF;
    }
    return mask;
}


u64 leftMask(int shift){
    u64 mask = rightMask(shift);
    mask.xl = ~ mask.xl;
    mask.xh = ~ mask.xh;
    return  mask;
}
u64 pad(int shift){
   shift = shift % 64; // Ensure shift is in the range [0, 63]

    u64 mask;

    if (shift == 0) {
        // Mask is all 1s when shift is 0
        mask.xh = 0x80000000;
        mask.xl = 0x00000000;
    } else if (shift >= 32) {
        // Mask covers only the low part when shift is >= 32
        mask.xh = 0;
        mask.xl = 0x80000000 >> (shift - 32);
    } else {
        // Mask spans both high and low parts when shift is < 32
        mask.xh = 0x80000000 >> shift;
        mask.xl = 0x00000000;
    }
    return mask;
}*/

void printstate(const char *text, const ascon_state_t *s, int debug) {
    if(debug){
    printf("%s\n", text);
    for (int i = 0; i < 5; i++) {
        printf("%08X %08X \n", s->xh[i], s->xl[i]);
    }
    printf("\n");}
}

#endif //FREEDOM_E_SDK_UTIL_H

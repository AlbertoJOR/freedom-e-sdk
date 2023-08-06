//
// Created by albertojor on 31/07/23.
//
#include "round.h"
#include "state.h"
#include "util.h"


int main() {
    u32 high = 0x12345678;
    u32 low = 0x9abcdef0;
    u64 result;
    ascon_state_t T;
    for(int j = 0 ; j < 5 ; j ++){
        T.xh[j] = j + 1;
        T.xl[j] = (j + 2) * 2;
    }
    printstate("Hola",&T,1);
    printf("%08x %08x\n", high, low);
    for (int i = 0; i < 16; i++) {
        result = ROR32(high, low, i);
        u32 resh = RORH(i % 64, high,low);
        u32 resl = RORL(i % 64, high, low);
        u32 yes = result.xh == resh && result.xl == resl;
        u32 TH = TRUNH(i%9, high);
        u32 TL = TRUNL(i%9, low);
        u32 PH = PADH(i%9);
        u32 PL = PADL(i%9);
        printf("i = %d   %08x %08x    %08x %08x\n", i, TH,TL, PH, PL);
        //printf("r=%d : %08x %08x       %08x %08x  %u\n", i, result.xh, result.xl, resh, resl, yes);
    }
    return 0;
}

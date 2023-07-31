//
// Created by albertojor on 31/07/23.
//
#include "round.h"
int main(){
   u32 high = 0x12345678;
   u32 low =  0x9abcdef0;
   u64 result;
    printf("%08x %08x\n", high, low);
    for (int i = 0; i < 70; i++){
        result =  ROR32(high, low, i);
        printf("r=%d : %08x %08x\n",i, result.xh, result.xl);
    }
    return  0;
}

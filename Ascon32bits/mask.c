#include "stdio.h"
#include "util.h"
#include "state.h"

int main(){
   u64 mask;
    u64 mask2;
    u64 padr;
   for(int i = 0; i < 70; i++){
       mask = rightMask(i);
       mask2 = leftMask(i);
       padr = pad(i);
       printf("%08x %08x  :  %08x %08x   :   %08x %08x\n", mask.xh, mask.xl, mask2.xh, mask2.xl, padr.xh, padr.xl);
   }
    return  0;
}
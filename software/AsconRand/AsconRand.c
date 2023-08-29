#include "../AsconHW/AEAD_HW.h"
#include "../Asconref/aead.h"
#include <stdio.h>
#include "../RoCCcommon/csr.h"

int main(void) {
    u32 num_rand = 32;
    static u32 rand_arr[500] = {0};


    unsigned start, end;
    // RoCC
    write_csr(mstatus, MSTATUS_XS);
printf("Rand Seed: \n");
    start = rdcycle();
    // SEED();
    end = rdcycle();
    u32 st, en ;
    st = RDCycle();
    en = RDCycle();
    printf("Total time no Instruction HW = %d cycles\n",end-start);
    printf("Total time no Instruction HW = %d cycles, my count\n",en-st);


    printf("Rand HW: \n");
    start = rdcycle();
    RAND( rand_arr, num_rand);
    end = rdcycle();
    st = RDCycle();
    RAND( rand_arr, num_rand);
    en = RDCycle();
    printf("Total time HW = %d cycles\n",end-start);
    printf("Total time HW = %d cycles my count\n",en-st);
    printC(rand_arr, num_rand *4 , 0, 1);
    printf("\nX\n");



    return 0;


}
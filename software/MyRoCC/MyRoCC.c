#include "../RoCCcommon/csr.h"
#include "../RoCCcommon/rocc.h"

#include <stdio.h>
#define ARRAY_LEN 10

unsigned xorSW(unsigned arr[], unsigned res[], unsigned init_val){
    unsigned xor_val = init_val;
    unsigned aux_val = 0;
    for(int i = 0; i < 10 ; i++){
       aux_val = xor_val ^ arr[i];
       xor_val = aux_val;
       res[i] = xor_val;

    }
    return 0;
}

int main(void){
    unsigned arrSW [ARRAY_LEN] = {0,1,2,3,4,5,6,7,8,9};
    unsigned resSW [ARRAY_LEN] = {0};
    unsigned arrHW [ARRAY_LEN] = {0,1,2,3,4,5,6,7,8,9};
    unsigned resHW [ARRAY_LEN] = {0};

    unsigned init_xor = 12;

    printf("Init SW \n");
    unsigned start, end;
    unsigned SWcycles, HWcycles;

    xorSW(arrSW, resSW, init_xor);
    int i = 0;
    start = rdcycle();
    for(i = 0; i< ARRAY_LEN; i ++){
        printf("resSW[%d]  =  %d \n", i, resSW[i]);
    }
    end = rdcycle();
    SWcycles = end - start;
    printf("SW cycles = %d \n", SWcycles);
    printf("Init HW \n");
    printf("%x  %x \n", arrSW, arrHW);
    printf("%x  \n", arrHW + 1);

    unsigned rd = 0;
    // RoCC
    start = rdcycle();
    write_csr(mstatus, MSTATUS_XS); // Always initialize the CSR such that the accelerator is recognized
    asm volatile("fence"); // always add it, this instrucction waits till all memory acceses have finished
    ROCC_INSTRUCTION_DSS(0,rd,arrHW,resHW,0); // Destiny, Source, Source = xd = 1, xs1 = 1, xs2 = 1
    // 0 = Custom_opcode0 := 0b, rd = return value most be 1, rs1 = addr, rs2 = addr, func7 = 0
    asm volatile("fence" ::: "memory");
    printf("Second instruction \n");

    asm volatile("fence"); // always add it, this instrucction waits till all memory acceses have finished
    ROCC_INSTRUCTION_DSS(0,rd,ARRAY_LEN,init_xor,1); // Destiny, Source, Source = xd = 1, xs1 = 1, xs2 = 1
    asm volatile("fence" ::: "memory");
    end = rdcycle();
    HWcycles = end - start;

    printf("Hw finish %d \n", rd); // most be 2
    for(i = 0; i< ARRAY_LEN; i ++){
        printf("resHW[%d]  =  %d \n", i, resHW[i]);
    }
     printf("HW cycles = %d \n", HWcycles);
    printf("Acc = %dX", SWcycles/HWcycles);
    return 0;
}
#include "../RoCCcommon/csr.h"
#include "../RoCCcommon/rocc.h"

#include <stdio.h>


#define  mlen 1280
int main(void){
    printf("Hi");

   static unsigned arrHW [mlen * 2 +1] = {0};
//                0x778899aa, 0x33445566, 0x1100ffee, 0x22334455,
//    0x12fad895, 0x0934af66, 0x8922fade, 0x67e34ead,0};
    static unsigned resHW [mlen * 2+1] = {0};
    //unsigned prueba [1000] = {0};


    printf("Init SofftW \n");
    unsigned start, end;
    unsigned HWcycles;


    int i = 0;


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
    ROCC_INSTRUCTION_DSS(0,rd,mlen,0,1); // Destiny, Source, Source = xd = 1, xs1 = 1, xs2 = 1
    // 0 = custom0 , rd= destination, 2 message len , 0 from the other source, function 1 =
    asm volatile("fence" ::: "memory");
    printf("Third instruction \n");

    end = rdcycle();
    HWcycles = end - start;

    printf("Hw finish %d \n", rd); // most be 2
    for(i = 0; i< mlen *2+1 ; i ++){
        printf("arrHW[%d]  =  %x \n", i, arrHW[i]);
    }
    for(i = 0; i<mlen *2+1; i ++){
        printf("resHW[%d]  =  %x \n", i, resHW[i]);
    }
    printf("cycles %d \n", HWcycles);

//    for(i = 0; i<1000; i ++){
//        printf("prueba[%d]  =  %x \n", i, prueba[i]);
//    }
    return 0;
}
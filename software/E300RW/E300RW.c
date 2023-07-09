#include "../RoCCcommon/csr.h"
#include "../RoCCcommon/rocc.h"
#include "AEAD_HW.h"

#include <stdio.h>



int main(void) {
    static unsigned plain_text []={0x1234, 0x5678, 0x2389, 0x2342};
    static unsigned cipher_text []= {0x0, 0x0, 0x0 , 0x0};
    static unsigned dumm_array []= {0x0, 0x0, 0x0, 0x0};
    unsigned plain_len = 2;


    printf("Init AEAD \n");
    unsigned start, end, HWcycles;
    int rd = 0;
    // RoCC
    start = rdcycle();
    write_csr(mstatus, MSTATUS_XS); // Always initialize the CSR such that the accelerator is recognized

    //rd = AEAD_E_Set_P( plain_text, plain_len);
    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0,rd, plain_text, plain_len, Enc_Set_P );
    asm volatile("fence" ::: "memory");
    printf("Set Plain text finish : %d \n", rd);

    //rd = AEAD_E_Set_AD(plain_text, plain_len );
    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0, rd,plain_text, plain_len, Enc_Set_AD );
    asm volatile("fence" ::: "memory");
    printf("Set Associated Data finish : %d \n", rd);

    // rd = AEAD_E_Set_C_Tag(cipher_text,dumm_array);
    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0,rd, cipher_text, dumm_array, Enc_Set_C_Tag );
    asm volatile("fence" ::: "memory");
    printf("Set Tag and C finish : %d \n", rd);

    // rd = AEAD_E_Set_Nonce(dumm_array );
    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0,rd, dumm_array, Enc_Set_Nonce );
    asm volatile("fence" ::: "memory");
    printf("Set Nonce finish : %d \n", rd);

    // rd = AEAD_E_Set_Key(rd);
    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0,rd,  rd, Enc_Set_Key );
    asm volatile("fence" ::: "memory");
    printf("Set Key  finish : %d \n", rd);

    //rd = AEAD_E_Set_Init();
    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0,rd, rd,  Enc_Init );
    asm volatile("fence" ::: "memory");
    printf("Finish AEAD : %x \n", rd);

    end = rdcycle();
    HWcycles = end - start;
    printf("Total time = %d cycles\n",HWcycles);
    for(int i = 0; i < plain_len *2; i ++){
       if(i%2==0 ){
            printf("\n");
        }
        printf("%x ",cipher_text[i]);

    }
    printf("\n");


    return 0;
}
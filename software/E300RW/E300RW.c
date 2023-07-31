#include "../RoCCcommon/csr.h"
#include "../RoCCcommon/rocc.h"
#include "AEAD_HW.h"

#include <stdio.h>

int main(void) {
    static unsigned plain_text[500] = {0x11121314, 0x25262728, 0x393a3b3c, 0x0d0e0f00,
                                       0x41424344, 0x55565758, 0x696a6b6c, 0x7d7e7f70};
    static unsigned asso_text[500] = {0x91929394, 0xa5a6a7a8, 0xb9babbbc, 0xcdcecfc0,
                                      0xd1d2d3d4, 0xe5e6e7e8, 0xf9fafbfc, 0x8d8e8f80};
    static unsigned cipher_text[500 + 4] = {0};
    static unsigned Nonce[4] = {0x76777777, 0xeeeeeeee, 0xffffffff, 0x33333332};
    // static unsigned Nonce [4]= {0};
    static unsigned Key[4] = {0x11111111,0x22222222,0x33333333,0x44444445};
    static unsigned dummy_array[4] = {0};
    unsigned plain_len = 32;
    unsigned asso_len = 32; /// CReo que asignaste a memoria
    unsigned plain_len_int = plain_len / 4;
    plain_len_int = (plain_len % 4 == 0) ? plain_len_int : plain_len_int + 1;


    // printf("Init AEAD \n");
    printf("Init hola\n");
    printf("Ad addr = %08x\n", asso_text);
    printf("Pl addr = %08x\n", plain_text);
    printf("Ct addr = %08x\n", cipher_text);
    printf("Ke addr = %08x\n", Key);
    printf("Np addr = %08x\n", Nonce);
    unsigned start, end, HWcycles;
    int rd = 0;
    // RoCC
    start = rdcycle();
    write_csr(mstatus, MSTATUS_XS); // Always initialize the CSR such that the accelerator is recognized

    //rd = AEAD_E_Set_P( plain_text, plain_len);
    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, Nonce, Enc_Set_Nonce);
    asm volatile("fence":: : "memory");
    printf("Set Nonce finish : %08x \n", rd);

    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, Key, Enc_Set_Key);
    asm volatile("fence":: : "memory");
    printf("Set Key  finish : %07x \n", rd);
    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0, rd, plain_text, plain_len, Enc_Set_P);
    asm volatile("fence":: : "memory");
    printf("Set Plain text finish length : %08x \n", rd);




    // rd = AEAD_E_Set_AD(plain_text, plain_len );
    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0, rd, asso_text, asso_len, Enc_Set_AD);
    asm volatile("fence":: : "memory");
    printf("Set Associated Data finish length: %08x \n", rd);



    // rd = AEAD_E_Set_C_Tag(cipher_text,dumm_array);
    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0, rd, cipher_text, dummy_array, Enc_Set_C_Tag);
    asm volatile("fence":: : "memory");
    // printf("Set Tag and C finish : %d \n", rd);
    printf("Set Cipher addr: %08x \n", rd);

    // rd = AEAD_E_Set_Nonce(dumm_array );
// rd = AEAD_E_Set_Key(rd);



    //rd = AEAD_E_Set_Init();
    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, rd, Enc_Init);
    asm volatile("fence":: : "memory");
    printf("Finish AEAD : %08x \n", rd);

    end = rdcycle();
    HWcycles = end - start;
    //  printf("Total time = %d cycles\n",HWcycles);
    printf("C");
    for (int i = 0; i < plain_len_int + 4; i++) {
        if (i % 2 == 0) {
            printf("\n");
        }
        printf("%08x ", cipher_text[i], i);
        cipher_text[i] = 0;
    }
    printf("\n");
    printf("X\n\n");

        //rd = AEAD_E_Set_P( plain_text, plain_len);
    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, Nonce, Enc_Set_Nonce);
    asm volatile("fence":: : "memory");
    printf("Set Nonce finish : %08x \n", rd);

    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, Key, Enc_Set_Key);
    asm volatile("fence":: : "memory");
    printf("Set Key  finish : %07x \n", rd);
    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0, rd, plain_text, plain_len, Enc_Set_P);
    asm volatile("fence":: : "memory");
    printf("Set Plain text finish length : %08x \n", rd);




    // rd = AEAD_E_Set_AD(plain_text, plain_len );
    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0, rd, asso_text, asso_len, Enc_Set_AD);
    asm volatile("fence":: : "memory");
    printf("Set Associated Data finish length: %08x \n", rd);



    // rd = AEAD_E_Set_C_Tag(cipher_text,dumm_array);
    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0, rd, cipher_text, dummy_array, Enc_Set_C_Tag);
    asm volatile("fence":: : "memory");
    // printf("Set Tag and C finish : %d \n", rd);
    printf("Set Cipher addr: %08x \n", rd);

    // rd = AEAD_E_Set_Nonce(dumm_array );
// rd = AEAD_E_Set_Key(rd);



    //rd = AEAD_E_Set_Init();
    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, rd, Enc_Init);
    asm volatile("fence":: : "memory");
    printf("Finish AEAD : %08x \n", rd);

    end = rdcycle();
    HWcycles = end - start;
    //  printf("Total time = %d cycles\n",HWcycles);
    printf("C");
    for (int i = 0; i < plain_len_int + 4; i++) {
        if (i % 2 == 0) {
            printf("\n");
        }
        printf("%08x ", cipher_text[i], i);
        cipher_text[i] = 0;
    }
    printf("\n");
    printf("X\n\n");
   plain_len = 18;
   asso_len = 29;
        //rd = AEAD_E_Set_P( plain_text, plain_len);
    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, Nonce, Enc_Set_Nonce);
    asm volatile("fence":: : "memory");
    printf("Set Nonce finish : %08x \n", rd);

    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, Key, Enc_Set_Key);
    asm volatile("fence":: : "memory");
    printf("Set Key  finish : %07x \n", rd);
    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0, rd, plain_text, plain_len, Enc_Set_P);
    asm volatile("fence":: : "memory");
    printf("Set Plain text finish length : %08x \n", rd);




    // rd = AEAD_E_Set_AD(plain_text, plain_len );
    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0, rd, asso_text, asso_len, Enc_Set_AD);
    asm volatile("fence":: : "memory");
    printf("Set Associated Data finish length: %08x \n", rd);



    // rd = AEAD_E_Set_C_Tag(cipher_text,dumm_array);
    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0, rd, cipher_text, dummy_array, Enc_Set_C_Tag);
    asm volatile("fence":: : "memory");
    // printf("Set Tag and C finish : %d \n", rd);
    printf("Set Cipher addr: %08x \n", rd);

    // rd = AEAD_E_Set_Nonce(dumm_array );
// rd = AEAD_E_Set_Key(rd);



    //rd = AEAD_E_Set_Init();
    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, rd, Enc_Init);
    asm volatile("fence":: : "memory");
    printf("Finish AEAD : %08x \n", rd);

    end = rdcycle();
    HWcycles = end - start;
    //  printf("Total time = %d cycles\n",HWcycles);
    printf("C");
    for (int i = 0; i < plain_len_int + 4; i++) {
        if (i % 2 == 0) {
            printf("\n");
        }
        printf("%08x ", cipher_text[i], i);
        cipher_text[i] = 0;
    }
    printf("\n");
    printf("X\n\n");
}
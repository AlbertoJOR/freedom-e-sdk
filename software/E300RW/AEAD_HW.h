//
// Created by albertojor on 4/06/23.
//

#ifndef FREEDOM_E_SDK_AEAD_HW_H
#define FREEDOM_E_SDK_AEAD_HW_H
#include "../RoCCcommon/rocc.h"
#include <stdio.h>

#define Enc_Set_P 0x11
#define Enc_Set_AD 0x12
#define Enc_Set_C_Tag 0x13
#define Enc_Set_Nonce 0x14
#define Enc_Set_Key 0x15
#define Enc_Init 0x16
#define Dec_Load_Tag 0x17

// AEAD Encryption


int AEAD_ENC(unsigned *ad_addr, unsigned ad_len,
             unsigned *p_addr , unsigned p_len,
             unsigned *c_addr, unsigned * nonce_addr,
             unsigned *key_addr);

void printC(unsigned *arr, unsigned a_len, int cipher){
   int len = (cipher)? a_len + 4 : a_len;
    for (int i = 0; i <  len; i++) {
        if (i % 2 == 0) {
            printf("\n");
        }
        printf("%08x ", arr[i], i);
        arr[i] = 0;
    }
}


int AEAD_ENC(unsigned *ad_addr, unsigned ad_len,
             unsigned *p_addr , unsigned p_len,
             unsigned *c_addr, unsigned * nonce_addr,
             unsigned *key_addr){
    int rd = 0;
      asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, nonce_addr, Enc_Set_Nonce);
    asm volatile("fence":: : "memory");
    printf("Set Nonce finish : %08x \n", rd);

    /*asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, Nonce, Dec_Load_Tag);
    asm volatile("fence":: : "memory");
    printf("Load Tag finish : %08x \n", rd);*/

    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, key_addr, Enc_Set_Key);
    asm volatile("fence":: : "memory");
    printf("Set Key  finish : %07x \n", rd);

    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0, rd, p_addr, p_len, Enc_Set_P);
    asm volatile("fence":: : "memory");
    printf("Set Plain text finish length : %08x \n", rd);

    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0, rd, ad_addr, ad_len, Enc_Set_AD);
    asm volatile("fence":: : "memory");
    printf("Set Associated Data finish length: %08x \n", rd);

    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, c_addr,  Enc_Set_C_Tag);
    asm volatile("fence":: : "memory");
    printf("Set Cipher addr: %08x \n", rd);

    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, rd, Enc_Init);
    asm volatile("fence":: : "memory");
    printf("Finish AEAD : %08x \n", rd);
    return rd;
}


#endif //FREEDOM_E_SDK_AEAD_HW_H

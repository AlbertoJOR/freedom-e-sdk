//
// Created by albertojor on 4/06/23.
//

#ifndef FREEDOM_E_SDK_AEAD_HW_H
#define FREEDOM_E_SDK_AEAD_HW_H

#include "../RoCCcommon/rocc.h"
#include "../Asconref/state.h"
#include <stdio.h>

#define Enc_Set_P 0x11
#define Enc_Set_AD 0x12
#define Enc_Set_C_Tag 0x13
#define Enc_Set_Nonce 0x14
#define Enc_Set_Key 0x15
#define Enc_Init 0x16
#define Dec_Load_Tag 0x17
#define Dec_Init 0x18
#define Hash_Set_M 0x31
#define Hash_Init 0x32

// AEAD Encryption


u32 AEAD_ENC(u32 *ad_addr, u32 ad_len,
             u32 *p_addr, u32 p_len,
             u32 *c_addr, u32 *nonce_addr,
             u32 *key_addr);

u32 AEAD_DEC(u32 *ad_addr, u32 ad_len,
             u32 *c_addr, u32 c_len,
             u32 *d_addr, u32 *nonce_addr,
             u32 *key_addr, u32 *tag_addr);
u32 HASH(u32 *m_addr, u32 m_len,
             u32 *c_addr );

void printC(u32 *arr, u32 a_len, int cipher, int del) {
    int len = (a_len % 8 == 0)? (a_len /4)*2 : (a_len/4)*2 +2 ;
    len =  (cipher) ? len + 4 : len;
    for (int i = 0; i < len; i++) {
        if (i % 2 == 0) {
            printf("\n");
        }
        printf("%08x ", arr[i], i);
        if (del) {
            arr[i] = 0;
        }
    }
    printf("\n");
}
u32 tagAddr(u32 mlenbytes){
    u32 mlenU32 = (mlenbytes %8 ==0)? mlenbytes / 4 : mlenbytes/4 +2;
    return mlenU32;
}
u32 AEAD_ENC(u32 *ad_addr, u32 ad_len,
             u32 *p_addr, u32 p_len,
             u32 *c_addr, u32 *nonce_addr,
             u32 *key_addr) {
    u32 rd = 0;
    //printf("Init Enc\n");
    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, nonce_addr, Enc_Set_Nonce);
    asm volatile("fence":: : "memory");
    //printf("Set Nonce finish : %08x \n", rd);


    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, key_addr, Enc_Set_Key);
    asm volatile("fence":: : "memory");
    //printf("Set Key  finish : %07x \n", rd);

    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0, rd, p_addr, p_len, Enc_Set_P);
    asm volatile("fence":: : "memory");
    //printf("Set Plain text finish length : %08x \n", rd);

    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0, rd, ad_addr, ad_len, Enc_Set_AD);
    asm volatile("fence":: : "memory");
    //printf("Set Associated Data finish length: %08x \n", rd);

    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, c_addr, Enc_Set_C_Tag);
    asm volatile("fence":: : "memory");
    //printf("Set Dec addr: %08x \n", rd);

    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, rd, Enc_Init);
    asm volatile("fence":: : "memory");
    //printf("Finish AEAD Dec %08x \n", rd);
    return rd;
}

u32 AEAD_DEC(u32 *ad_addr, u32 ad_len,
             u32 *c_addr, u32 c_len,
             u32 *d_addr, u32 *nonce_addr,
             u32 *key_addr, u32 *tag_addr){
    u32 rd = 0;
   // printf("Init DEC\n");
    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, nonce_addr, Enc_Set_Nonce);
    asm volatile("fence":: : "memory");
    //printf("Set Nonce finish : %08x \n", rd);

    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, tag_addr, Dec_Load_Tag);
    asm volatile("fence":: : "memory");
    //printf("Load Tag finish : %08x \n", rd);

    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, key_addr, Enc_Set_Key);
    asm volatile("fence":: : "memory");
    //printf("Set Key  finish : %07x \n", rd);

    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0, rd, c_addr, c_len, Enc_Set_P);
    asm volatile("fence":: : "memory");
    //printf("Set Plain text finish length : %08x \n", rd);

    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0, rd, ad_addr, ad_len, Enc_Set_AD);
    asm volatile("fence":: : "memory");
    //printf("Set Associated Data finish length: %08x \n", rd);

    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, d_addr, Enc_Set_C_Tag);
    asm volatile("fence":: : "memory");
    //printf("Set Dec addr: %08x \n", rd);

    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, rd, Dec_Init);
    asm volatile("fence":: : "memory");
    //printf("Finish AEAD Dec %08x \n", rd);
    return rd;
}
u32 HASH(u32 *m_addr, u32 m_len,
             u32 *h_addr ){
    u32 rd;
    //printf("Init Hash\n");
     asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0, rd, m_addr, m_len, Hash_Set_M);
    asm volatile("fence":: : "memory");
    //printf("Set M : %08x \n", rd);

    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, h_addr, Hash_Init);
    asm volatile("fence":: : "memory");
    //printf(" Finish Hash: %08x \n", rd);
    return 0;
}

#endif //FREEDOM_E_SDK_AEAD_HW_H

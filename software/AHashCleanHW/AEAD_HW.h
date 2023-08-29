//
// Created by albertojor on 4/06/23.
//

#ifndef FREEDOM_E_SDK_AEAD_HW_H
#define FREEDOM_E_SDK_AEAD_HW_H

#include "../RoCCcommon/rocc.h"
#include "state.h"
#include "printf.h"

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
#define R_Seed  0x41
#define R_Rand  0x42
#define C_Count  0x61

// AEAD Encryption




u32 HASH(u32 *m_addr, u32 m_len,
         u32 *c_addr);


void printC(u32 *arr, u32 a_len, int cipher, int del) {
    int len = (a_len % 8 == 0) ? (a_len / 4) * 2 : (a_len / 4) * 2 + 2;
    len = (cipher) ? len + 4 : len;
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



u32 HASH(u32 *m_addr, u32 m_len,
         u32 *h_addr) {
    u32 rd;
    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0, rd, m_addr, m_len, Hash_Set_M);

    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0, rd, h_addr, Hash_Init);
    asm volatile("fence":: : "memory");
    return 0;
}

#endif //FREEDOM_E_SDK_AEAD_HW_H

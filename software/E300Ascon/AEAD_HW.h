//
// Created by albertojor on 4/06/23.
//

#ifndef FREEDOM_E_SDK_AEAD_HW_H
#define FREEDOM_E_SDK_AEAD_HW_H
#include "../RoCCcommon/rocc.h"
#define opcode0 0x0
#define Enc_Set_P 0x11
#define Enc_Set_AD 0x12
#define Enc_Set_C_Tag 0x13
#define Enc_Set_Nonce 0x14
#define Enc_Set_Key 0x15
#define Enc_Init 0x16

// AEAD Encryption


int AEAD_E_Set_P(unsigned * p_addr, unsigned p_len );
int AEAD_E_Set_AD(unsigned * ad_addr, unsigned ad_len );
int AEAD_E_Set_C_Tag(unsigned * c_addr, unsigned * tag_addr );
int AEAD_E_Set_Nonce(unsigned * Nonce_addr );
int AEAD_E_Set_Key(unsigned Key_ID  );
int AEAD_E_Set_Init( );


//int AEAD_E_Set_P(unsigned * p_addr, unsigned p_len ) {
//    asm volatile("fence");
//    ROCC_INSTRUCTION_SS(opcode0, p_addr, p_len, Enc_Set_P );
//    asm volatile("fence" ::: "memory");
//    return 1;
//}
//int AEAD_E_Set_AD(unsigned * ad_addr, unsigned ad_len ){
//    asm volatile("fence");
//    ROCC_INSTRUCTION_SS(opcode0, ad_addr, ad_len, Enc_Set_AD );
//    return 2;
//}
//int AEAD_E_Set_C_Tag(unsigned * c_addr, unsigned *tag_addr ){
//    asm volatile("fence" ::: "memory");
//    asm volatile("fence");
//    ROCC_INSTRUCTION_SS(opcode0, c_addr, tag_addr, Enc_Set_C_Tag );
//    return 3;
//}
//int AEAD_E_Set_Nonce(unsigned * Nonce_addr ){
//    asm volatile("fence" ::: "memory");
//    asm volatile("fence");
//    ROCC_INSTRUCTION_S(opcode0, Nonce_addr, Enc_Set_Nonce);
//    return 4;
//}
//int AEAD_E_Set_Key(unsigned Key_ID  ){
//    asm volatile("fence" ::: "memory");
//   asm volatile("fence");
//    ROCC_INSTRUCTION_S(opcode0, Key_ID, Enc_Set_Key);
//    return 5;
//
//}
//int AEAD_E_Set_Init( ){
//    asm volatile("fence" ::: "memory");
//    asm volatile("fence");
//    unsigned return_value = 0;
//    ROCC_INSTRUCTION_D(opcode0, return_value, Enc_Init);
//    asm volatile("fence" ::: "memory");
//    return return_value;
//}
#endif //FREEDOM_E_SDK_AEAD_HW_H

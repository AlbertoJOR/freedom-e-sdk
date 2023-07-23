//
// Created by albertojor on 17/05/23.
//
#include "aead.h"
#include "stdio.h"
#include "word.h"
int main () {

   /* crypto_aead_encrypt(unsigned char* c, unsigned long long* clen,
                        const unsigned char* m, unsigned long long mlen,
                        const unsigned char* ad, unsigned long long adlen,
                        const unsigned char* npub,
                        const unsigned char* k) */

   unsigned char c [80] = {0};
   unsigned long long clen = 0;
    unsigned long long mlen = 32;
    unsigned long long adlen = 1;
   unsigned char m [32] ={0x11,0x12,0x13,0x14,
                          0x25,0x26,0x27,0x28,
                          0x39,0x3a,0x3b,0x3c,
                          0x0d,0x0e,0x0f,0x00,
                          0x41,0x42,0x43,0x44,
                          0x55,0x56,0x57,0x58,
                          0x69,0x6a,0x6b,0x6c,
                          0x7d,0x7e,0x7f,0x70};
   unsigned char ad[32] = {0x91,0x92,0x93,0x94,
                           0xa5,0xa6,0xa7,0xa8,
                           0xb9,0xba,0xbb,0xbc,
                           0xcd,0xce,0xcf,0xc0,
                           0xd1,0xd2,0xd3,0xd4,
                           0xe5,0xe6,0xe7,0xe8,
                           0xf9,0xfa,0xfb,0xfc,
                           0x8d,0x8e,0x8f,0x80};
   unsigned char npub[16] = {0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0x00};
   unsigned char k [16] = {0x00, 0x00, 0x00, 0x00,
                           0x00, 0x00, 0x00, 0x00,
                           0x00, 0x00, 0x00, 0x00,
                           0x00, 0x00, 0x00, 0x00};
   crypto_aead_encrypt(c,&clen,m,mlen,ad, adlen,npub,k);
    // crypto_aead_decrypt(m,&mlen,npub,clen,ad,adlen,npub,k);
    printf("hola");
    for(int i = 0; i < 48; i ++){
       if(i%8==0 ){
            printf("\n");
        }
        printf("%02x",c[i]);

    }
    printf("\n");

    return 0;
}
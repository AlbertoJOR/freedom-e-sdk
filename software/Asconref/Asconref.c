//
// Created by albertojor on 17/05/23.
//
#include "aead.h"
#include "printf.h"
//#include "stdio.h"
#include "word.h"
#define len 1280
int main () {

   /* crypto_aead_encrypt(unsigned char* c, unsigned long long* clen,
                        const unsigned char* m, unsigned long long mlen,
                        const unsigned char* ad, unsigned long long adlen,
                        const unsigned char* npub,
                        const unsigned char* k) */

   unsigned long long clen = len;
    static unsigned char c [len+16] = {0};
   /*unsigned char m [16] = {0x00, 0x00, 0x00, 0x00,
                           0x00, 0x00, 0x00, 0x00,
                           0x00, 0x00, 0x00, 0x00,
                           0x00, 0x00, 0x00, 0x00
                           };*/
   unsigned  long long mlen = len;
   static unsigned char m [len] = {0};
   static unsigned char ad[32] = {0};
   unsigned long long adlen = 0;
   static unsigned char npub[16] = {0x12, 0x34, 0x00, 0x00,
                           0x00, 0x00, 0x43, 0x21,
                            0x43, 0x21, 0x00, 0x00,
                           0x00, 0x00, 0x12, 0x34  };
   static unsigned char k [16] = {0xab, 0xcd, 0x00, 0x00,
                           0x00, 0x00, 0xdc, 0xba,
                            0x56, 0x78, 0x00, 0x00,
                           0x00, 0x00, 0x87, 0x65
   };
   printf("Holas\n");
   crypto_aead_encrypt(c,&clen,m,mlen,ad, adlen,npub,k);
    //crypto_aead_decrypt(m,&mlen,npub,clen,ad,adlen,npub,k);
    printf("hola");
    for(int i = 0; i < len+16; i ++){
       if(i%8==0 ){
            printf("\n");
        }
        printf("%02x",c[i]);

    }
    printf("\n");

    return 0;
}
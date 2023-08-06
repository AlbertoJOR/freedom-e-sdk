//
// Created by albertojor on 17/05/23.
//
#include "aead.h"

int main() {

    /* crypto_aead_encrypt(unsigned char* c, unsigned long long* clen,
                         const unsigned char* m, unsigned long long mlen,
                         const unsigned char* ad, unsigned long long adlen,
                         const unsigned char* npub,
                         const unsigned char* k) */

    u32 c[2000] = {0};
    u32 d[2000] = {0};
    u32 clen = 0;
    u32 mlen = 13;
    u32 adlen = 3;
    u32 clen2 = mlen;
    u32 dlen = 0;
    u32 m[2000] = {0x11121314,
                   0x25262728,
                   0x393a3b3c,
                   0x0d0e0f00,
                   0x41424344,
                   0x55565758,
                   0x696a6b6c,
                   0x7d7e7f70};
    u32 ad[2000] = {0x91929394,
                    0xa5a6a7a8,
                    0xb9babbbc,
                    0xcdcecfc0,
                    0xd1d2d3d4,
                    0xe5e6e7e8,
                    0xf9fafbfc,
                    0x8d8e8f80};
    u32 npub[16] = {0x76777777,
                    0xeeeeeeee,
                    0xffffffff,
                    0x33333332};
    u32 k[16] = {0x11111111,
                 0x22222222,
                 0x33333333,
                 0x44444445};
    crypto_aead_encrypt(c, &clen, m, mlen, ad, adlen, npub, k, 1);
    // crypto_aead_decrypt(m,&mlen,npub,clen,ad,adlen,npub,k);
    printf("hola");
    for (int i = 0; i < mlen/4 + 6 ; i++) {
        if (i % 2 == 0) {
            printf("\n");
        }
        printf("%08x ", c[i]);
    }
    int res = 0;
    res = crypto_aead_decrypt(d,&dlen,c,clen2,ad,adlen,npub,k,1);
    printf("\n");
    printf("hola");
    for (int i = 0; i < mlen/4 + 6 ; i++) {
        if (i % 2 == 0) {
            printf("\n");
        }
        printf("%08x ", d[i]);
    }
    printf("res := %08x \n", res);

    return 0;
}
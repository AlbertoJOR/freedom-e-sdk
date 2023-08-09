//
// Created by albertojor on 5/08/23.
//

#ifndef FREEDOM_E_SDK_AEAD_H
#define FREEDOM_E_SDK_AEAD_H

#include "round.h"
#include "state.h"
#include "util.h"

#define A_128_IV_H 0x80400c06
#define A_128_IV_L 0x00000000

int crypto_aead_encrypt(u32 *c, u32 *clen, u32 *m, u32 mlen, u32 *ad, u32 adlen, u32 *npub, u32 *k, int debug) {
    /* set plaintext size */
    *clen = mlen + 16;

    /* load key and nonce */
    u64 K0, K1, N0, N1;
    K0.xh = k[0];
    K0.xl = k[1];
    K1.xh = k[2];
    K1.xl = k[3];
    N0.xh = npub[0];
    N0.xl = npub[1];
    N1.xh = npub[2];
    N1.xl = npub[3];

    /* initialize */
    ascon_state_t s;
    s.xh[0] = A_128_IV_H;
    s.xl[0] = A_128_IV_L;
    s.xh[1] = K0.xh;
    s.xl[1] = K0.xl;
    s.xh[2] = K1.xh;
    s.xl[2] = K1.xl;
    s.xh[3] = N0.xh;
    s.xl[3] = N0.xl;
    s.xh[4] = N1.xh;
    s.xl[4] = N1.xl;
    printstate("After init", &s, debug);
    P12(&s);

    s.xh[3] ^= K0.xh;
    s.xl[3] ^= K0.xl;
    s.xh[4] ^= K1.xh;
    s.xl[4] ^= K1.xl;
    printstate("Xor 2 key", &s, debug);

    if (adlen) {
        while (adlen >= 8) {
            s.xh[0] ^= *ad;
            ad++;
            s.xl[0] ^= *ad;
            ad++;
            P6(&s);
            printstate("Absorb AD", &s, debug);
            adlen -= 8;
        }
        s.xh[0] ^= TRUNH(adlen, *ad);
        ad++;
        s.xl[0] ^= TRUNL(adlen, *ad);

        s.xh[0] ^= PADH(adlen);
        s.xl[0] ^= PADL(adlen);
        printstate("Padded AD", &s, debug);
        P6(&s);
    }
    /* domain separation */
    s.xl[4] ^= 1;
    printstate("Domain Separation", &s, debug);

    while (mlen >= 8) {
        s.xh[0] ^= *m;
        m++;
        s.xl[0] ^= *m;
        m++;
        *c = s.xh[0];
        c++;
        *c = s.xl[0];
        c++;
        mlen -= 8;
        printstate("Absorb M", &s, debug);
        P6(&s);
    }
    /* final block*/
    s.xh[0] ^= TRUNH(mlen, *m);
    m++;
    s.xl[0] ^= TRUNL(mlen, *m);

    if (mlen) {
        *c = TRUNH(mlen, s.xh[0]);
        c++;
        *c = TRUNL(mlen, s.xl[0]);
        c++;
    }
    s.xh[0] ^= PADH(mlen);
    s.xl[0] ^= PADL(mlen);
    printstate("Pad M", &s, debug);
    /* Ending */
    s.xh[1] ^= K0.xh;
    s.xl[1] ^= K0.xl;
    s.xh[2] ^= K1.xh;
    s.xl[2] ^= K1.xl;
    printstate("Xor key 1", &s, debug);

    P12(&s);
    s.xh[3] ^= K0.xh;
    s.xl[3] ^= K0.xl;
    s.xh[4] ^= K1.xh;
    s.xl[4] ^= K1.xl;
    printstate("Xor key 2", &s, debug);

    /* TAG*/
    *c = s.xh[3];
    c++;
    *c = s.xl[3];
    c++;
    *c = s.xh[4];
    c++;
    *c = s.xl[4];
    return 0;
}

int crypto_aead_decrypt(u32 *m, u32 *mlen, u32 *c, u32 clen, u32 *ad, u32 adlen, u32 *npub, u32 *k, int debug) {
    /* set plaintext size */
    *mlen = clen;
    /* load key and nonce */
    u64 K0, K1, N0, N1;
    K0.xh = k[0];
    K0.xl = k[1];
    K1.xh = k[2];
    K1.xl = k[3];
    N0.xh = npub[0];
    N0.xl = npub[1];
    N1.xh = npub[2];
    N1.xl = npub[3];

    /* initialize */
    ascon_state_t s;
    s.xh[0] = A_128_IV_H;
    s.xl[0] = A_128_IV_L;
    s.xh[1] = K0.xh;
    s.xl[1] = K0.xl;
    s.xh[2] = K1.xh;
    s.xl[2] = K1.xl;
    s.xh[3] = N0.xh;
    s.xl[3] = N0.xl;
    s.xh[4] = N1.xh;
    s.xl[4] = N1.xl;
    printstate("After init", &s, debug);
    P12(&s);

    s.xh[3] ^= K0.xh;
    s.xl[3] ^= K0.xl;
    s.xh[4] ^= K1.xh;
    s.xl[4] ^= K1.xl;
    printstate("Xor 2 key", &s, debug);

    if (adlen) {
        while (adlen >= 8) {
            s.xh[0] ^= *ad;
            ad++;
            s.xl[0] ^= *ad;
            ad++;
            P6(&s);
            printstate("Absorb AD", &s, debug);
            adlen -= 8;
        }
        s.xh[0] ^= TRUNH(adlen, *ad);
        ad++;
        s.xl[0] ^= TRUNL(adlen, *ad);

        s.xh[0] ^= PADH(adlen);
        s.xl[0] ^= PADL(adlen);
        printstate("Padded AD", &s, debug);
        P6(&s);
    }
    /* domain separation */
    s.xl[4] ^= 1;
    printstate("Domain Separation", &s, debug);
    u32 ch, cl;
    while (clen >= 8) {
        // printf("clen %d\n", clen);
        ch = *c;
        c++;
        cl = *c;
        c++;
        *m = s.xh[0] ^ ch;
        m++;
        *m = s.xl[0] ^ cl;
        m++;

        s.xh[0] = ch;
        s.xl[0] = cl;
        clen -= 8;
        printstate("Absorb M", &s, debug);
        P6(&s);
    }
    /* final block*/
    ch = 0;
    cl = 0;
    if (clen) {
        ch = TRUNH(clen, *c);
        c++;
        cl = TRUNL(clen, *c);
        c++;
        *m = TRUNH(clen, s.xh[0] ^ ch);
        m++;
        *m = TRUNL(clen, s.xl[0] ^ cl);
        m++;
    }
    s.xh[0] = CLEARH(clen, s.xh[0]);
    s.xl[0] = CLEARL(clen, s.xl[0]);
    printstate("clear bytes", &s, debug);
    s.xh[0] |= ch;
    s.xl[0] |= cl;
    s.xh[0] ^= PADH(clen);
    s.xl[0] ^= PADL(clen);
    printstate("Pad M", &s, debug);
    /* Ending */
    s.xh[1] ^= K0.xh;
    s.xl[1] ^= K0.xl;
    s.xh[2] ^= K1.xh;
    s.xl[2] ^= K1.xl;
    printstate("Xor key 1", &s, debug);

    P12(&s);
    s.xh[3] ^= K0.xh;
    s.xl[3] ^= K0.xl;
    s.xh[4] ^= K1.xh;
    s.xl[4] ^= K1.xl;
    printstate("Xor key 2", &s, debug);

    /* TAG*/
    u32 Tag[4];
    Tag[0] = s.xh[3];
    Tag[1] = s.xl[3];
    Tag[2] = s.xh[4];
    Tag[3] = s.xl[4];
    int res = 0;
    /*for(int i = 0 ; i < 4; i ++){
        res |= c[i] ^ Tag[i];
        printf("%08x  %08x\n", c[i], Tag[i]);
    }*/
    return res;
}

int crypto_hash(u32 *m, u32 mlen, u32 *h, int debug) {

    /* initialize */
    ascon_state_t s;
    s.xh[0] = 0x00400c00;
    s.xl[0] = 0x00000100;
    s.xh[1] = 0;
    s.xl[1] = 0;
    s.xh[2] = 0;
    s.xl[2] = 0;
    s.xh[3] = 0;
    s.xl[3] = 0;
    s.xh[4] = 0;
    s.xl[4] = 0;
    printstate("After init", &s, debug);
    P12(&s);


    if (mlen) {
        while (mlen >= 8) {
            s.xh[0] ^= *m;
            m++;
            s.xl[0] ^= *m;
            m++;
            P12(&s);
            printstate("Absorb AD", &s, debug);
            mlen -= 8;
        }
        s.xh[0] ^= TRUNH(mlen, *m);
        m++;
        s.xl[0] ^= TRUNL(mlen, *m);

        s.xh[0] ^= PADH(mlen);
        s.xl[0] ^= PADL(mlen);
        printstate("Padded AD", &s, debug);
        P12(&s);
    }
    for(int i = 0 ; i < 4 ; i++){
        h[i*2] = s.xh[0] ;
        h[i*2+1] = s.xl[0] ;
        if(i < 3){
            P12(&s);
        }
        printstate("Hash Round",&s,debug);
    }
    return 0;
}

#endif //FREEDOM_E_SDK_AEAD_H

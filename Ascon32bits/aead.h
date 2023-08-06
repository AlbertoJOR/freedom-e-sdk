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

#endif //FREEDOM_E_SDK_AEAD_H

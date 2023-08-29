//
// Created by albertojor on 5/08/23.
//

#ifndef FREEDOM_E_SDK_AEAD_H
#define FREEDOM_E_SDK_AEAD_H

#include "round.h"
#include "state.h"

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
    P12(&s);


    if (mlen) {
        while (mlen >= 8) {
            s.xh[0] ^= *m;
            m++;
            s.xl[0] ^= *m;
            m++;
            P12(&s);
            mlen -= 8;
        }
        s.xh[0] ^= TRUNH(mlen, *m);
        m++;
        s.xl[0] ^= TRUNL(mlen, *m);

        s.xh[0] ^= PADH(mlen);
        s.xl[0] ^= PADL(mlen);
        P12(&s);
    }
    for(int i = 0 ; i < 4 ; i++){
        h[i*2] = s.xh[0] ;
        h[i*2+1] = s.xl[0] ;
        if(i < 3){
            P12(&s);
        }
    }
    return 0;
}

#endif //FREEDOM_E_SDK_AEAD_H

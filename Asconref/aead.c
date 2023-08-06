#include "api.h"
#include "ascon.h"
// #include "crypto_aead.h"
#include "permutations.h"
// #include "printstate.h"
#include "word.h"
#include "aead.h"
#include "stdio.h"

void printS(ascon_state_t *s) {
    for (int i = 0; i < 5; i++) {
        printf("%lX\n", s->x[i]);
    }
    printf("\n");
}

void printstate(const char *text, const ascon_state_t *s) {
    printf("%s\n", text);
    for (int i = 0; i < 5; i++) {
        printf("%lX\n", s->x[i]);
    }
    printf("\n");
}

int crypto_aead_encrypt(unsigned char *c, unsigned long long *clen,
                        const unsigned char *m, unsigned long long mlen,
                        const unsigned char *ad, unsigned long long adlen,
                        const unsigned char *npub,
                        const unsigned char *k) {


    /* set ciphertext size */
    *clen = mlen + CRYPTO_ABYTES;

    /* load key and nonce */
    const uint64_t K0 = LOADBYTES(k, 8);
    const uint64_t K1 = LOADBYTES(k + 8, 8);
    const uint64_t N0 = LOADBYTES(npub, 8);
    const uint64_t N1 = LOADBYTES(npub + 8, 8);

    /* initialize */
    ascon_state_t s;
    s.x[0] = ASCON_128_IV;
    s.x[1] = K0;
    s.x[2] = K1;
    s.x[3] = N0;
    s.x[4] = N1;
    printf("init 1st key xor\n");
    printS(&s);
    P12(&s);
    s.x[3] ^= K0;
    s.x[4] ^= K1;
    printf("init 2nd key xor \n");
    printS(&s);

    if (adlen) {
        /* full associated data blocks */
        while (adlen >= ASCON_128_RATE) {
            s.x[0] ^= LOADBYTES(ad, 8);
            printf("pad ad %lx \n", LOADBYTES(ad, 8));
            P6(&s);
            printf("absorb adata \n");
            printS(&s);
            ad += ASCON_128_RATE;
            adlen -= ASCON_128_RATE;
        }
        /* final associated data block */
        s.x[0] ^= LOADBYTES(ad, adlen);
        // printf("ad %lx \n",*ad);
        printf("pad %lld ad %lx \n", adlen, LOADBYTES(ad, adlen));
        s.x[0] ^= PAD(adlen);
        P6(&s);

    }
    /* domain separation */
    s.x[4] ^= 1;
    printf("AD Domain separation \n");
    printS(&s);

    /* full plaintext blocks */
    while (mlen >= ASCON_128_RATE) {
        s.x[0] ^= LOADBYTES(m, 8);
        STOREBYTES(c, s.x[0], 8);

        printf("absorb plain \n");
        printS(&s);

        P6(&s);
        m += ASCON_128_RATE;
        c += ASCON_128_RATE;
        mlen -= ASCON_128_RATE;
    }
    /* final plaintext block */
    s.x[0] ^= LOADBYTES(m, mlen);
    printf("C: %lx\n", LOADBYTES(m, mlen));
    printf("C S_0: %lx\n", s.x[0]);

    STOREBYTES(c, s.x[0], mlen);
    printf("\n");
    for (int ax; ax < 8; ax++) {
        printf("%x", *(c + ax));
    }
    printf("\n");
    s.x[0] ^= PAD(mlen);
    c += mlen;

    printf("pad plain \n");
    printS(&s);

    /* finalize */
    s.x[1] ^= K0;
    s.x[2] ^= K1;

    printf("key xor 1 \n");
    printS(&s);

    P12(&s);
    s.x[3] ^= K0;
    s.x[4] ^= K1;

    printf("key kor 2 \n");
    printS(&s);

    /* set tag */
    STOREBYTES(c, s.x[3], 8);
    STOREBYTES(c + 8, s.x[4], 8);

    return 0;
}

int crypto_aead_decrypt(unsigned char *m, unsigned long long *mlen,
                        const unsigned char *c,
                        unsigned long long clen, const unsigned char *ad,
                        unsigned long long adlen, const unsigned char *npub,
                        const unsigned char *k) {
    printf("Holaaaa\n");

//if (clen < CRYPTO_ABYTES) return -1;

    /* set plaintext size */
    *mlen = clen;

    /* load key and nonce */
    const uint64_t K0 = LOADBYTES(k, 8);
    const uint64_t K1 = LOADBYTES(k + 8, 8);
    const uint64_t N0 = LOADBYTES(npub, 8);
    const uint64_t N1 = LOADBYTES(npub + 8, 8);

    /* initialize */
    ascon_state_t s;
    s.x[0] = ASCON_128_IV;
    s.x[1] = K0;
    s.x[2] = K1;
    s.x[3] = N0;
    s.x[4] = N1;
    printf("init 1st key xor\n");
    printS(&s);
    P12(&s);
    s.x[3] ^= K0;
    s.x[4] ^= K1;
    printstate("init 2nd key xor", &s);

    if (adlen) {
        printf("holalalal\n");
        /* full associated data blocks */
        while (adlen >= ASCON_128_RATE) {
            s.x[0] ^= LOADBYTES(ad, 8);
            printstate("absorb adata", &s);
            P6(&s);
            ad += ASCON_128_RATE;
            adlen -= ASCON_128_RATE;
        }
        /* final associated data block */
        s.x[0] ^= LOADBYTES(ad, adlen);
        s.x[0] ^= PAD(adlen);
        printstate("pad adata", &s);
        P6(&s);
    }
    /* domain separation */
    s.x[4] ^= 1;
    printstate("domain separation", &s);

    /* full ciphertext blocks */
    //clen -= CRYPTO_ABYTES;
    while (clen >= ASCON_128_RATE) {
        printf("clen %ld\n", clen);
        uint64_t c0 = LOADBYTES(c, 8);
        STOREBYTES(m, s.x[0] ^ c0, 8);
        s.x[0] = c0;
        printstate("insert ciphertext", &s);
        P6(&s);
        m += ASCON_128_RATE;
        c += ASCON_128_RATE;
        clen -= ASCON_128_RATE;
    }
    /* final ciphertext block */
    uint64_t c0 = LOADBYTES(c, clen);
    STOREBYTES(m, s.x[0] ^ c0, clen);
    s.x[0] = CLEARBYTES(s.x[0], clen);
    printstate("clear bytes", &s);
    s.x[0] |= c0;
    s.x[0] ^= PAD(clen);
    c += clen;
    printstate("pad ciphertext", &s);

    /* finalize */
    s.x[1] ^= K0;
    s.x[2] ^= K1;
    printstate("final 1st key xor", &s);
    P12(&s);
    s.x[3] ^= K0;
    s.x[4] ^= K1;
    printstate("final 2nd key xor", &s);

    /* set tag */
    uint8_t t[16];
    STOREBYTES(t, s.x[3], 8);
    STOREBYTES(t + 8, s.x[4], 8);

    /* verify tag (should be constant time, check compiler output) */
    int i;
    int result = 0;
    for (i = 0; i < CRYPTO_ABYTES; ++i) result |= c[i] ^ t[i];
    result = (((result - 1) >> 8) & 1) - 1;

    return result;
}

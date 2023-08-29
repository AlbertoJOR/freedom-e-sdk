#include "../Asconref/aead.h"
#include <stdio.h>
#include "../RoCCcommon/csr.h"

#define  REP 30
#define PLEN 2500

int main(void) {
    u32 clen = 0;

    static u32 plain_text[PLEN+12];
    for(int j = 0 ; j < PLEN; j ++){
        plain_text [j] = j * PLEN + j;
    }
    static u32 Nonce[4] = {0x76777777, 0xeeeeeeee, 0xffffffff, 0x33333332};
    static u32 Key[4] = {0x11111111, 0x22222222, 0x33333333, 0x44444445};
    static u32 performance2[REP] = {0};
    static u32 bytes[7] = {0,8, 96, 496, 1000, 5000, 10000};
    static u32 bytesr[7] = {0,1, 12, 62, 125,625, 1250};



    unsigned start, end;

    // ENC

    int i = 0;
    printf("ENC \n");
    for (int j = 0; j < 7; j++) {
        for (i = 0; i < REP; i++) {
            start = rdcycle();
            crypto_aead_encrypt(plain_text+2, &clen, plain_text, bytes[j], plain_text, 0, Nonce, Key);
            end = rdcycle();
            performance2[i] = end - start;
        }
        printf("ENC bytes %d \n", bytes[j]);
        for (i = 0; i < REP; i++) {
            printf("%d:   SWcycles : %u   \n", i, performance2[i] );
        }
    }

    printf("ENC 100 A\n");
    for (int j = 0; j < 7; j++) {
        for (i = 0; i < REP; i++) {
            start = rdcycle();
            crypto_aead_encrypt(plain_text+2, &clen, plain_text, 0, plain_text, bytes[j], Nonce, Key);
            end = rdcycle();
            performance2[i] = end - start;
        }
        printf("ENC 100 A bytes %d \n", bytes[j]);
        for (i = 0; i < REP; i++) {
            printf("%d:   SWcycles : %u  \n", i, performance2[i]);
        }
    }



    /// DEC
    printf("DEC \n");
    for (int j = 0; j < 7; j++) {
        for (i = 0; i < REP; i++) {
            start = rdcycle();
            crypto_aead_decrypt(plain_text+2, &clen, plain_text, bytes[j], plain_text, 0, Nonce, Key);
            end = rdcycle();
            performance2[i] = end - start;
        }
        printf("DEC bytes %d \n", bytes[j]);
        for (i = 0; i < REP; i++) {
            printf("%d:   SWcycles : %u   \n", i, performance2[i] );
        }
    }

    printf("DEC 100 A\n");
    for (int j = 0; j < 7; j++) {
        for (i = 0; i < REP; i++) {
            start = rdcycle();
            crypto_aead_decrypt(plain_text+2, &clen, plain_text, bytes[0], plain_text, bytes[j], Nonce, Key);
            end = rdcycle();
            performance2[i] = end - start;
        }
        printf("DEC 100 A bytes %d \n", bytes[j]);
        for (i = 0; i < REP; i++) {
           printf("%d:   SWcycles : %u   \n", i, performance2[i] );
        }
    }

   //// HASH

    printf("HASH \n");
    for (int j = 0; j < 7; j++) {
        for (i = 0; i < REP; i++) {
            start = rdcycle();
            crypto_hash(plain_text, bytes[j], plain_text);
            end = rdcycle();
            performance2[i] = end - start;
        }
        printf("HASH 100 A bytes %d \n", bytes[j]);
        for (i = 0; i < REP; i++) {
            printf("%d:   SWcycles : %u   \n", i, performance2[i] );
        }
    }
    //// RANDOM



    printf("Random \n");
    for (int j = 0; j < 7; j++) {
        ascon_state_t s;
        u64 seed;
        seed.xh = plain_text[0];
        seed.xl = plain_text[1];
        for (i = 0; i < REP; i++) {
            start = rdcycle();
            init_seed(&s,seed);
            if(bytesr[j] > 0) rand_ascon(&s, plain_text,bytesr[j]);
            end = rdcycle();
            performance2[i] = end - start;
        }
        printf("RANDOM bytes %d \n", bytesr[j]);
        for (i = 0; i < REP; i++) {
            printf("%d:   SWcycles : %u   \n", i, performance2[i] );
        }
    }
    return 0;
}
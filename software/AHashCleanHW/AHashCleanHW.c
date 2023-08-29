
#include "aead.h"
#include "printf.h"
#include "csr.h"
#include "AEAD_HW.h"
#include "../RoCCcommon/csr.h"
#define REP 50
int main(void) {
    static u32 plain_text[2500] = {0x11121314, 0x25262728, 0x393a3b3c, 0x0d0e0f00,
                                  0x41424344, 0x55565758, 0x696a6b6c, 0x7d7e7f70};
    static u32 performance[REP] = {0};
    static u32 performance2[REP] = {0};
    static u32 bytes[7] = {8, 96, 400, 1000, 5000, 10000, 15000};
    static u32 hash[8] = {0};
    static u32 hash2[8] = {0};
    unsigned start, end;
    int i = 0;
    printf("Hash\n");
    write_csr(mstatus, MSTATUS_XS);
    for (int j = 0; j < 6; j++) {
        for (i = 0; i < REP; i++) {
            start = rdcycle();
            crypto_hash(plain_text, bytes[j], hash, 0);
            end = rdcycle();
            performance[i] = end - start;
        }
        for (i = 0; i < REP; i++) {
            start = rdcycle();
            HASH(plain_text, bytes[j], hash2);
            end = rdcycle();
            performance2[i] = end - start;
        }
        printf_("performance Hash bytes %d \n", bytes[j]);
        for (i = 0; i < REP; i++) {
            printf_("%d:   SWcycles : %u   HWcycles : %u\n", i, performance[i]);
        }

        /*for (i = 0; i < 8; i++) {
            printf_("%08x  %08x\n", hash[i], hash2[i]);

            if (hash2[i] != hash[i]) {
                printf_("not equal\n");
                // return 0;
            }

        }*/
    }
    printf_("equal \n");


    return 0;


}
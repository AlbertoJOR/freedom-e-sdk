#include "../AsconHW/AEAD_HW.h"
#include "../Asconref/aead.h"
#include <stdio.h>
#include "../RoCCcommon/csr.h"

int main(void) {
    u32 plain_len = 32;
    u32 asso_len = 32; /// CReo que asignaste a memoria
    u32 clen = 0;

    u32 plain_len_int = plain_len / 8;
    plain_len_int = (plain_len % 8 == 0) ? plain_len_int*2 : plain_len_int*2 +2;

    static u32 plain_text[500] = {0x11121314, 0x25262728, 0x393a3b3c, 0x0d0e0f00,
                                       0x41424344, 0x55565758, 0x696a6b6c, 0x7d7e7f70};
    static u32 asso_text[500] = {0x91929394, 0xa5a6a7a8, 0xb9babbbc, 0xcdcecfc0,
                                      0xd1d2d3d4, 0xe5e6e7e8, 0xf9fafbfc, 0x8d8e8f80};
    static u32 cipher_text[500 + 4] = {0};
    static u32 Nonce[4] = {0x76777777, 0xeeeeeeee, 0xffffffff, 0x33333332};
    static u32 dec_text[500 + 4] = {0};
    static u32 hash[10] = {0};
    static u32 Key[4] = {0x11111111, 0x22222222, 0x33333333, 0x44444445};

    static u32 *tag_addr;


    printf("Init Ascon Dec \n");
    printf("Ad addr = %08x\n", asso_text);
    printf("Pl addr = %08x\n", plain_text);
    printf("Ct addr = %08x\n", cipher_text);
    printf("Ke addr = %08x\n", Key);
    printf("Np addr = %08x\n", Nonce);
    printf("hash addr = %08x\n", hash);
    unsigned start, end;
    int rd = 0;
    // RoCC
    write_csr(mstatus, MSTATUS_XS);

    /*printf("Init Hash\n");
    HASH(plain_text,plain_len,hash);
    printf(" Finish Hash: %07x \n", rd);
    printC(hash,9,0,1);*/


    printf("Dec HW: \n");
    start = rdcycle();
    HASH( plain_text, plain_len, hash);
    end = rdcycle();
    printf("Total time HW = %d cycles\n",end-start);
    printC(hash, 8 , 1, 1);
    printf("\nX\n");
    printf("Dec SW: \n");
    start = rdcycle();
    crypto_hash(plain_text,plain_len,hash,0);
    end = rdcycle();
    printf("Total time SW = %d cycles\n",end-start);
    printC(hash, 8, 1, 1);
    printf("\nX\n");


    return 0;


}
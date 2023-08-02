#include "../RoCCcommon/csr.h"
#include "../RoCCcommon/rocc.h"
#include "AEAD_HW.h"

#include <stdio.h>

int main(void) {
    unsigned plain_len = 32;
    unsigned asso_len = 32; /// CReo que asignaste a memoria
    unsigned plain_len_int = plain_len / 4;
    plain_len_int = (plain_len % 4 == 0) ? plain_len_int : plain_len_int + 2;

    static unsigned plain_text[500] = {0x11121314, 0x25262728, 0x393a3b3c, 0x0d0e0f00,
                                       0x41424344, 0x55565758, 0x696a6b6c, 0x7d7e7f70};
    static unsigned asso_text[500] = {0x91929394, 0xa5a6a7a8, 0xb9babbbc, 0xcdcecfc0,
                                      0xd1d2d3d4, 0xe5e6e7e8, 0xf9fafbfc, 0x8d8e8f80};
    static unsigned cipher_text[500 + 4] = {0};
    static unsigned Nonce[4] = {0x76777777, 0xeeeeeeee, 0xffffffff, 0x33333332};
    static unsigned dec_text[500 + 4] = {0};
    static unsigned Key[4] = {0x11111111, 0x22222222, 0x33333333, 0x44444445};

    static unsigned *tag_addr;


    // printf("Init AEAD \n");
    printf("Init Hola2\n");
    printf("Ad addr = %08x\n", asso_text);
    printf("Pl addr = %08x\n", plain_text);
    printf("Ct addr = %08x\n", cipher_text);
    printf("Ke addr = %08x\n", Key);
    printf("Np addr = %08x\n", Nonce);
    unsigned start, end, HWcycles;
    int rd = 0;
    // RoCC
    start = rdcycle();
    write_csr(mstatus, MSTATUS_XS); // Always initialize the CSR such that the accelerator is recognized

    AEAD_ENC(asso_text, asso_len, plain_text, plain_len, cipher_text, Nonce, Key);

    end = rdcycle();
    HWcycles = end - start;
    //  printf("Total time = %d cycles\n",HWcycles);
    printC(cipher_text, plain_len_int, 1, 1);
    printf("\nX\n");


    AEAD_ENC(asso_text, asso_len, plain_text, plain_len, cipher_text, Nonce, Key);
    printC(cipher_text, plain_len_int, 1, 1);
    printf("\nX\n");
    plain_len = 1000;
    asso_len = 1000;
    plain_len_int = plain_len / 4;
    plain_len_int = (plain_len % 4 == 0) ? plain_len_int : plain_len_int + 2;
    tag_addr = cipher_text + plain_len_int;




    AEAD_ENC(asso_text, asso_len, plain_text, plain_len, cipher_text, Nonce, Key);
    printC(cipher_text, plain_len_int, 1, 0);
    printf("\nX\n");
    printf("Tag \n");
    printC(tag_addr, 4, 0, 0);

    unsigned rd2 = 0;
    rd2 = AEAD_DEC(asso_text, asso_len, cipher_text, plain_len, dec_text, Nonce, Key, tag_addr);
    printC(dec_text, plain_len_int, 0, 0);
    printf("\n%08x\n", rd2);

}
#include "../AsconHW/AEAD_HW.h"
#include "../Asconref/aead.h"
#include <stdio.h>
#include "../RoCCcommon/csr.h"

int main(void) {
    u32 plain_len =  1000;

    u32 plain_len_int = plain_len / 8;
    plain_len_int = (plain_len % 8 == 0) ? plain_len_int*2 : plain_len_int*2 +2;

    static u32 plain_text[500] = {0x11121314, 0x25262728, 0x393a3b3c, 0x0d0e0f00,
                                       0x41424344, 0x55565758, 0x696a6b6c, 0x7d7e7f70};
    static u32 hash[10] = {0};



    printf("Init Ascon Dec \n");
    printf("Pl addr = %08x\n", plain_text);
    printf("hash addr = %08x\n", hash);
    printf("Bytes %d\n", plain_len);
    unsigned start, end;
    unsigned rd = 0 ;
   start = rdcycle();
   rd = rd + 1;
   rd = rd +2;
   rd = rd + 5;
   rd = rd +7;
    end = rdcycle();
    printf("simple op  SW = %d cycles\n",end-start);

    start = rdcycle();
    hash [10] = rd;
    end = rdcycle();
    printf("simple write  SW = %d cycles\n",end-start);

    start = rdcycle();
    rd = plain_text[10];
    end = rdcycle();
    printf("simple load   SW = %d cycles\n",end-start);



    printf("Hash SW: \n");
    start = rdcycle();
    crypto_hash(plain_text,plain_len,hash,0);
    end = rdcycle();
    printf("Total time SW = %d cycles\n",end-start);
    printC(hash, 8, 1, 1);
    printf("\nX\n");

    start = rdcycle();
    crypto_hash(plain_text,plain_len,hash,0);
    end = rdcycle();
    printf("Total time SW = %d cycles\n",end-start);
    start = rdcycle();
    crypto_hash(plain_text,plain_len,hash,0);
    end = rdcycle();
    printf("Total time SW = %d cycles\n",end-start);

    start = rdcycle();
    crypto_hash(plain_text,plain_len,hash,0);
    end = rdcycle();
    printf("Total time SW = %d cycles\n",end-start);


    start = rdcycle();
    crypto_hash(plain_text,plain_len,hash,0);
    end = rdcycle();
    printf("Total time SW = %d cycles\n",end-start);

    start = rdcycle();
    crypto_hash(plain_text,plain_len,hash,0);
    end = rdcycle();
    printf("Total time SW = %d cycles\n",end-start);


    return 0;


}
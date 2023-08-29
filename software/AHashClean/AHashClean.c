
#include "aead.h"
#include "printf.h"
#include "csr.h"

int main(void) {
    u32 plain_len =  1000;

    static u32 plain_text[500] = {0x11121314, 0x25262728, 0x393a3b3c, 0x0d0e0f00,
                                       0x41424344, 0x55565758, 0x696a6b6c, 0x7d7e7f70};
    static  u32 performance[100] = {0};
    static u32 hash[100] = {0};
    u32 rd = 0;

    unsigned start, end;
  /* start = rdcycle();
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
    printf("simple load   SW = %d cycles\n",end-start);*/
  for(int i= 0 ; i < 100 ; i ++){
     start = rdcycle();
    crypto_hash(plain_text,plain_len,hash,0);
    /*rd = plain_text[i] + 1;

   rd = rd +2;
   rd = rd + 5;
   hash[i] = rd;*/
    end = rdcycle();
    performance[i] = end-start;

  }
  printf_("SW Hash \n");
  for(int i = 0 ; i < 100 ; i ++){
      printf_("%d:   %u\n", i, performance[i]);
  }


    return 0;


}
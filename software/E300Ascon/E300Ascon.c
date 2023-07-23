#include "../RoCCcommon/csr.h"
#include "../RoCCcommon/rocc.h"
#include "AEAD_HW.h"
#include "aead.h"
#include "printf.h"
//#include "stdio.h"
#include "word.h"

int main(void) {

    static unsigned plain_text [8]={0x11121314, 0x25262728, 0x393a3b3c, 0x0d0e0f00,
                                        0x41424344, 0x55565758, 0x696a6b6c, 0x7d7e7f70};

    static unsigned asso_text [8]={0x91929394, 0xa5a6a7a8, 0xb9babbbc, 0xcdcecfc0,
                                   0xd1d2d3d4, 0xe5e6e7e8, 0xf9fafbfc, 0x8d8e8f80};
    static unsigned cipher_text [8]= {0};
    static unsigned dumm_array [8]= {0};
    static unsigned cipher_text_sw [12]= {0};

    static unsigned key[4] ={0};
    static unsigned npub[4] ={0};
    unsigned plain_len = 10;
    unsigned asso_len = 10; /// CReo que asignaste a memoria
    unsigned long long int c_len = plain_len;
    unsigned long long int p_len = plain_len;
    unsigned long long int a_len = asso_len;
    unsigned plain_len_int = plain_len / 4 ;
    plain_len_int = (plain_len % 4 == 0 )? plain_len_int :plain_len_int+1;


    printf("Init AEAD \n");
    unsigned start, end, HWcycles;
    int rd = 0;
    // RoCC
    start = rdcycle();
    write_csr(mstatus, MSTATUS_XS); // Always initialize the CSR such that the accelerator is recognized

    //rd = AEAD_E_Set_P( plain_text, plain_len);
    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0,rd, plain_text, plain_len, Enc_Set_P );
    asm volatile("fence" ::: "memory");
    printf("Set Plain text finish length : %d \n", rd);

    //rd = AEAD_E_Set_AD(plain_text, plain_len );
    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0, rd,asso_text, asso_len, Enc_Set_AD );
    asm volatile("fence" ::: "memory");
    printf("Set Associated Data finish length: %d \n", rd);

    // rd = AEAD_E_Set_C_Tag(cipher_text,dumm_array);
    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0,rd, cipher_text, dumm_array, Enc_Set_C_Tag );
    asm volatile("fence" ::: "memory");
    printf("Set Tag and C finish : %d \n", rd);

    // rd = AEAD_E_Set_Nonce(dumm_array );
    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0,rd, dumm_array, Enc_Set_Nonce );
    asm volatile("fence" ::: "memory");
    printf("Set Nonce finish : %d \n", rd);

    // rd = AEAD_E_Set_Key(rd);
    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0,rd,  rd, Enc_Set_Key );
    asm volatile("fence" ::: "memory");
    printf("Set Key  finish : %d \n", rd);

    //rd = AEAD_E_Set_Init();
    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0,rd, rd,  Enc_Init );
    asm volatile("fence" ::: "memory");
    printf("Finish AEAD : %x \n", rd);

    end = rdcycle();
    HWcycles = end - start;
    printf("Total time = %d cycles\n",HWcycles);
    printf("Hardware \n");
    for(int i = 0; i < plain_len_int; i ++){
       if(i%2==0 ){
            printf("\n");
        }
        printf("%x ",cipher_text[i]);
    }


    crypto_aead_encrypt((unsigned char *)cipher_text_sw,&c_len,(unsigned char*)plain_text,p_len, (unsigned char*)asso_text,a_len,(unsigned char*)npub,(unsigned char*)key);

    printf("\n");
    printf("Software");
    for(int i = 0; i < plain_len_int + 4; i ++){
        if(i%2==0 ){
            printf("\n");
        }
        printf("%x ",cipher_text_sw[i]);
    }


    return 0;
}

/*
int main(void) {
    static unsigned plain_text []={0x1234, 0x5678, 0x2389, 0x2342};
    static unsigned cipher_text []= {0x0, 0x0, 0x0 , 0x0};
    static unsigned dumm_array []= {0x0, 0x0, 0x0, 0x0};
    unsigned plain_len = 2;


    printf("Init AEAD \n");
    unsigned start, end, HWcycles;
    int rd = 0;
    // RoCC
    start = rdcycle();
    write_csr(mstatus, MSTATUS_XS); // Always initialize the CSR such that the accelerator is recognized

    //rd = AEAD_E_Set_P( plain_text, plain_len);
    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0,rd, plain_text, 0, Enc_Set_P );
    asm volatile("fence" ::: "memory");
    printf("Set Plain text finish : %d \n", rd);

    //rd = AEAD_E_Set_AD(plain_text, plain_len );
    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0, rd,plain_text, plain_len, Enc_Set_AD );
    asm volatile("fence" ::: "memory");
    printf("Set Associated Data finish : %d \n", rd);

    // rd = AEAD_E_Set_C_Tag(cipher_text,dumm_array);
    asm volatile("fence");
    ROCC_INSTRUCTION_DSS(0,rd, cipher_text, dumm_array, Enc_Set_C_Tag );
    asm volatile("fence" ::: "memory");
    printf("Set Tag and C finish : %d \n", rd);

    // rd = AEAD_E_Set_Nonce(dumm_array );
    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0,rd, dumm_array, Enc_Set_Nonce );
    asm volatile("fence" ::: "memory");
    printf("Set Nonce finish : %d \n", rd);

    // rd = AEAD_E_Set_Key(rd);
    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0,rd,  rd, Enc_Set_Key );
    asm volatile("fence" ::: "memory");
    printf("Set Key  finish : %d \n", rd);

    //rd = AEAD_E_Set_Init();
    asm volatile("fence");
    ROCC_INSTRUCTION_DS(0,rd, rd,  Enc_Init );
    asm volatile("fence" ::: "memory");
    printf("Finish AEAD : %x \n", rd);

    end = rdcycle();
    HWcycles = end - start;
    printf("Total time = %d cycles\n",HWcycles);
    for(int i = 0; i < plain_len *2; i ++){
       if(i%2==0 ){
            printf("\n");
        }
        printf("%x ",cipher_text[i]);

    }
    printf("\n");


    return 0;
}*/

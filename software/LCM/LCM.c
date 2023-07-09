//
// Created by albertojor on 7/05/23.
//

#include "../RoCCcommon/csr.h"
#include "../RoCCcommon/rocc.h"

#include<stdio.h>
#define SIZE 10

unsigned gcdCompute(unsigned a, unsigned b){
	unsigned temp;
	while(a != b){
		if(a>b){
			temp = b;
			b = a;
			a = temp;
		}
		b = b - a;
	}
	return a;
}



int main(void){
	unsigned   randNum1[SIZE] = {
            26985, 84546, 46198, 38570, 46417, 49941, 8138, 8827, 99324, 96819};
	unsigned randNum2[SIZE] = {
            2826, 77394, 39239, 46078, 43985, 43458, 34337, 66575, 76502, 17900};
	unsigned swLcmRes[SIZE] = {0};
	unsigned hwLcmRes[SIZE] = {0};
	unsigned start, end;
    printf("Hello s \n");
    start = rdcycle();
    printf("\n");
	for(int i=0; i<SIZE; i++){
        printf("%d \n",swLcmRes[i] );
		swLcmRes[i] = gcdCompute(randNum1[i], randNum2[i]);
        printf("%d , %d \n", swLcmRes[i], gcdCompute(randNum1[i], randNum2[i]));
	}
	end = rdcycle();
    printf("leyo \n");
	// printf("LCM compute:\n");
	// for(int i=0; i<SIZE; i++){
	// 	printf("(%lld, %lld) -> %lld\n", randNum1[i], randNum2[i], swLcmRes[i]);
	// }
    printf("start %d end %d \n",start, end);
	printf("SW average cycles used:  %d\n", (end-start)/SIZE);

	// RoCC
    write_csr(mstatus, MSTATUS_XS); // Always initialize the CSR such that the accelerator is recognized
    start = rdcycle();
	for(int i=0; i<SIZE; i++){
		asm volatile ("fence");
		ROCC_INSTRUCTION_DSS(0, hwLcmRes[i], randNum1[i], randNum2[i], 0);
		asm volatile ("fence" ::: "memory");
	}
	end = rdcycle();

	for(int i=0; i<SIZE; i++){

			printf("t %d and %d LCM: swLcmRes: %d, hwLcmRes: %d\n", randNum1[i], randNum2[i], swLcmRes[i], hwLcmRes[i]);

	}
    printf("start %d end %d \n",start, end);
	printf("HW average cycles used:  %d\n", (end-start)/SIZE);
	printf("test successed! \n");
	return 0;

}
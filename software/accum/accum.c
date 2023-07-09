#include "rocc.h"
#include <stdio.h>
#include "riscv_asm.h"
#include "encoding.h"


static inline void accum_write(int idx, unsigned int data)
{
	ROCC_INSTRUCTION_SS(0, data, idx, 0);
}

static inline unsigned int accum_read(int idx)
{
	unsigned int value;
	ROCC_INSTRUCTION_DSS(0, value, 0, idx, 1);
	return value;
}

static inline void accum_load(int idx, void *ptr)
{
	asm volatile ("fence");
	ROCC_INSTRUCTION_SS(0, (uintptr_t) ptr, idx, 2);
}

static inline void accum_add(int idx, unsigned int addend)
{	
	ROCC_INSTRUCTION_SS(0, addend, idx, 3);
}

unsigned int data = 0x3421L;

int main(void)
{	// MSTATUS_FS = FPU on , = MSTATUS_XS accelerator on, MSTATUS_VS = vector unit on 
	//write_csr(mstatus, MSTATUS_FS | MSTATUS_XS |MSTATUS_VS);
	write_csr(mstatus, MSTATUS_XS);

	unsigned int result;
	printf("Start...\n");

	accum_load(0, &data);
	printf("data addr %lx \n", data);
	printf("data value %l \n", &data);
	accum_add(0, 2);
	result = accum_read(0);
	printf("result :%l \n", result);

	if (result != data + 2)
		return 1;

	accum_write(0, 3);
	accum_add(0, 1);
	result = accum_read(0);
	printf("last result %l", result);
	if (result != 4)
		return 2;

	return 0;
}

/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */
/* ----------------------------------- */
/* ----------------------------------- */

#ifndef METAL_PLATFORM_H
#define METAL_PLATFORM_H

/* From clock@0 */
#define METAL_FIXED_CLOCK_0_CLOCK_FREQUENCY 16000000UL

/* From clock@2 */
#define METAL_FIXED_CLOCK_2_CLOCK_FREQUENCY 72000000UL

/* From clock@5 */
#define METAL_FIXED_CLOCK_5_CLOCK_FREQUENCY 32000000UL

#define METAL_FIXED_CLOCK

/* From clint@2000000 */
#define METAL_RISCV_CLINT0_2000000_BASE_ADDRESS 33554432UL
#define METAL_RISCV_CLINT0_0_BASE_ADDRESS 33554432UL
#define METAL_RISCV_CLINT0_2000000_SIZE 65536UL
#define METAL_RISCV_CLINT0_0_SIZE 65536UL

#define METAL_RISCV_CLINT0
#define METAL_RISCV_CLINT0_MSIP_BASE 0UL
#define METAL_RISCV_CLINT0_MTIMECMP_BASE 16384UL
#define METAL_RISCV_CLINT0_MTIME 49144UL

/* From interrupt_controller@c000000 */
#define METAL_RISCV_PLIC0_C000000_BASE_ADDRESS 201326592UL
#define METAL_RISCV_PLIC0_0_BASE_ADDRESS 201326592UL
#define METAL_RISCV_PLIC0_C000000_SIZE 67108864UL
#define METAL_RISCV_PLIC0_0_SIZE 67108864UL
#define METAL_RISCV_PLIC0_C000000_RISCV_MAX_PRIORITY 7UL
#define METAL_RISCV_PLIC0_0_RISCV_MAX_PRIORITY 7UL
#define METAL_RISCV_PLIC0_C000000_RISCV_NDEV 36UL
#define METAL_RISCV_PLIC0_0_RISCV_NDEV 36UL

#define METAL_RISCV_PLIC0
#define METAL_RISCV_PLIC0_PRIORITY_BASE 0UL
#define METAL_RISCV_PLIC0_PENDING_BASE 4096UL
#define METAL_RISCV_PLIC0_ENABLE_BASE 8192UL
#define METAL_RISCV_PLIC0_ENABLE_PER_HART 128UL
#define METAL_RISCV_PLIC0_CONTEXT_BASE 2097152UL
#define METAL_RISCV_PLIC0_CONTEXT_PER_HART 4096UL
#define METAL_RISCV_PLIC0_CONTEXT_THRESHOLD 0UL
#define METAL_RISCV_PLIC0_CONTEXT_CLAIM 4UL

/* From aon@10000000 */
#define METAL_SIFIVE_AON0_10000000_BASE_ADDRESS 268435456UL
#define METAL_SIFIVE_AON0_0_BASE_ADDRESS 268435456UL
#define METAL_SIFIVE_AON0_10000000_SIZE 32768UL
#define METAL_SIFIVE_AON0_0_SIZE 32768UL

#define METAL_SIFIVE_AON0
#define METAL_SIFIVE_AON0_WDOGCFG 0UL
#define METAL_SIFIVE_AON0_WDOGCOUNT 8UL
#define METAL_SIFIVE_AON0_WDOGS 16UL
#define METAL_SIFIVE_AON0_WDOGFEED 24UL
#define METAL_SIFIVE_AON0_WDOGKEY 28UL
#define METAL_SIFIVE_AON0_WDOGCMP 32UL
#define METAL_SIFIVE_AON0_RTCCFG 64UL
#define METAL_SIFIVE_AON0_RTCLO 72UL
#define METAL_SIFIVE_AON0_RTCHI 72UL
#define METAL_SIFIVE_AON0_RTCS 80UL
#define METAL_SIFIVE_AON0_RTCCMP 96UL
#define METAL_SIFIVE_AON0_LFROSCCFG 112UL
#define METAL_SIFIVE_AON0_BACKUP0 128UL
#define METAL_SIFIVE_AON0_BACKUP1 132UL
#define METAL_SIFIVE_AON0_BACKUP2 136UL
#define METAL_SIFIVE_AON0_BACKUP3 140UL
#define METAL_SIFIVE_AON0_BACKUP4 144UL
#define METAL_SIFIVE_AON0_BACKUP5 148UL
#define METAL_SIFIVE_AON0_BACKUP6 152UL
#define METAL_SIFIVE_AON0_BACKUP7 152UL
#define METAL_SIFIVE_AON0_BACKUP8 160UL
#define METAL_SIFIVE_AON0_BACKUP9 164UL
#define METAL_SIFIVE_AON0_BACKUP10 168UL
#define METAL_SIFIVE_AON0_BACKUP11 172UL
#define METAL_SIFIVE_AON0_BACKUP12 176UL
#define METAL_SIFIVE_AON0_BACKUP13 180UL
#define METAL_SIFIVE_AON0_BACKUP14 184UL
#define METAL_SIFIVE_AON0_BACKUP15 188UL
#define METAL_SIFIVE_AON0_BACKUP16 192UL
#define METAL_SIFIVE_AON0_BACKUP17 196UL
#define METAL_SIFIVE_AON0_BACKUP18 200UL
#define METAL_SIFIVE_AON0_BACKUP19 204UL
#define METAL_SIFIVE_AON0_BACKUP20 208UL
#define METAL_SIFIVE_AON0_BACKUP21 212UL
#define METAL_SIFIVE_AON0_BACKUP22 216UL
#define METAL_SIFIVE_AON0_BACKUP23 220UL
#define METAL_SIFIVE_AON0_BACKUP24 224UL
#define METAL_SIFIVE_AON0_BACKUP25 228UL
#define METAL_SIFIVE_AON0_BACKUP26 232UL
#define METAL_SIFIVE_AON0_BACKUP27 236UL
#define METAL_SIFIVE_AON0_BACKUP28 240UL
#define METAL_SIFIVE_AON0_BACKUP29 244UL
#define METAL_SIFIVE_AON0_BACKUP30 248UL
#define METAL_SIFIVE_AON0_BACKUP31 252UL
#define METAL_SIFIVE_AON0_PMU_WAKEUP_BASE 256UL
#define METAL_SIFIVE_AON0_PWM_SLEEP_BASE 288UL
#define METAL_SIFIVE_AON0_PMUIE 320UL
#define METAL_SIFIVE_AON0_PMUCAUSE 324UL
#define METAL_SIFIVE_AON0_PMUSLEEP 328UL
#define METAL_SIFIVE_AON0_PMUKEY 332UL

/* From bus_error_unit@4000000 */
#define METAL_SIFIVE_BUSERROR0_4000000_BASE_ADDRESS 67108864UL
#define METAL_SIFIVE_BUSERROR0_0_BASE_ADDRESS 67108864UL
#define METAL_SIFIVE_BUSERROR0_4000000_SIZE 4096UL
#define METAL_SIFIVE_BUSERROR0_0_SIZE 4096UL

#define METAL_SIFIVE_BUSERROR0
#define METAL_SIFIVE_BUSERROR0_CAUSE 0UL
#define METAL_SIFIVE_BUSERROR0_VALUE 8UL
#define METAL_SIFIVE_BUSERROR0_ENABLE 16UL
#define METAL_SIFIVE_BUSERROR0_PLATFORM_INTERRUPT 24UL
#define METAL_SIFIVE_BUSERROR0_ACCRUED 32UL
#define METAL_SIFIVE_BUSERROR0_LOCAL_INTERRUPT 40UL

/* From error_device@3000 */
#define METAL_SIFIVE_ERROR0_3000_BASE_ADDRESS 12288UL
#define METAL_SIFIVE_ERROR0_0_BASE_ADDRESS 12288UL
#define METAL_SIFIVE_ERROR0_3000_SIZE 4096UL
#define METAL_SIFIVE_ERROR0_0_SIZE 4096UL

#define METAL_SIFIVE_ERROR0

/* From clock@3 */

#define METAL_SIFIVE_FE310_G000_HFROSC

/* From clock@1 */

#define METAL_SIFIVE_FE310_G000_HFXOSC

/* From clock@6 */

#define METAL_SIFIVE_FE310_G000_LFROSC

/* From prci@10008000 */
#define METAL_SIFIVE_FE310_G000_PRCI_10008000_BASE_ADDRESS 268468224UL
#define METAL_SIFIVE_FE310_G000_PRCI_0_BASE_ADDRESS 268468224UL
#define METAL_SIFIVE_FE310_G000_PRCI_10008000_SIZE 32768UL
#define METAL_SIFIVE_FE310_G000_PRCI_0_SIZE 32768UL

#define METAL_SIFIVE_FE310_G000_PRCI
#define METAL_SIFIVE_FE310_G000_PRCI_HFROSCCFG 0UL
#define METAL_SIFIVE_FE310_G000_PRCI_HFXOSCCFG 4UL
#define METAL_SIFIVE_FE310_G000_PRCI_PLLCFG 8UL
#define METAL_SIFIVE_FE310_G000_PRCI_PLLOUTDIV 12UL

/* From clock@4 */
#define METAL_SIFIVE_FE310_G000_PLL_4_CLOCK_FREQUENCY 16000000UL

#define METAL_SIFIVE_FE310_G000_PLL

/* From gpio@10012000 */
#define METAL_SIFIVE_GPIO0_10012000_BASE_ADDRESS 268509184UL
#define METAL_SIFIVE_GPIO0_0_BASE_ADDRESS 268509184UL
#define METAL_SIFIVE_GPIO0_10012000_SIZE 4096UL
#define METAL_SIFIVE_GPIO0_0_SIZE 4096UL

#define METAL_SIFIVE_GPIO0
#define METAL_SIFIVE_GPIO0_VALUE 0UL
#define METAL_SIFIVE_GPIO0_INPUT_EN 4UL
#define METAL_SIFIVE_GPIO0_OUTPUT_EN 8UL
#define METAL_SIFIVE_GPIO0_PORT 12UL
#define METAL_SIFIVE_GPIO0_PUE 16UL
#define METAL_SIFIVE_GPIO0_DS 20UL
#define METAL_SIFIVE_GPIO0_RISE_IE 24UL
#define METAL_SIFIVE_GPIO0_RISE_IP 28UL
#define METAL_SIFIVE_GPIO0_FALL_IE 32UL
#define METAL_SIFIVE_GPIO0_FALL_IP 36UL
#define METAL_SIFIVE_GPIO0_HIGH_IE 40UL
#define METAL_SIFIVE_GPIO0_HIGH_IP 44UL
#define METAL_SIFIVE_GPIO0_LOW_IE 48UL
#define METAL_SIFIVE_GPIO0_LOW_IP 52UL
#define METAL_SIFIVE_GPIO0_IOF_EN 56UL
#define METAL_SIFIVE_GPIO0_IOF_SEL 60UL
#define METAL_SIFIVE_GPIO0_OUT_XOR 64UL

/* From led@0 */

/* From led@1 */

/* From led@2 */

#define METAL_SIFIVE_GPIO_LEDS

/* From local_external_interrupts_0 */

#define METAL_SIFIVE_LOCAL_EXTERNAL_INTERRUPTS0

/* From pwm@10015000 */
#define METAL_SIFIVE_PWM0_10015000_BASE_ADDRESS 268521472UL
#define METAL_SIFIVE_PWM0_0_BASE_ADDRESS 268521472UL
#define METAL_SIFIVE_PWM0_10015000_SIZE 4096UL
#define METAL_SIFIVE_PWM0_0_SIZE 4096UL

#define METAL_SIFIVE_PWM0
#define METAL_SIFIVE_PWM0_PWMCFG 0UL
#define METAL_SIFIVE_PWM0_PWMCOUNT 8UL
#define METAL_SIFIVE_PWM0_PWMS 16UL
#define METAL_SIFIVE_PWM0_PWMCMP0 32UL
#define METAL_SIFIVE_PWM0_PWMCMP1 36UL
#define METAL_SIFIVE_PWM0_PWMCMP2 40UL
#define METAL_SIFIVE_PWM0_PWMCMP3 44UL

/* From remapper@3000000 */
#define METAL_SIFIVE_REMAPPER2_3000000_BASE_ADDRESS 50331648UL
#define METAL_SIFIVE_REMAPPER2_0_BASE_ADDRESS 50331648UL
#define METAL_SIFIVE_REMAPPER2_3000000_SIZE 4096UL
#define METAL_SIFIVE_REMAPPER2_0_SIZE 4096UL

#define METAL_SIFIVE_REMAPPER2
#define METAL_SIFIVE_REMAPPER2_CFG 0UL
#define METAL_SIFIVE_REMAPPER2_VALID_BASE 4UL
#define METAL_SIFIVE_REMAPPER2_FLUSH 32UL
#define METAL_SIFIVE_REMAPPER2_VERSION 500UL
#define METAL_SIFIVE_REMAPPER2_ENTRIES 504UL
#define METAL_SIFIVE_REMAPPER2_KEY 508UL
#define METAL_SIFIVE_REMAPPER2_FROM_BASE 512UL

/* From aon@10000000 */
#define METAL_SIFIVE_AON0_10000000_BASE_ADDRESS 268435456UL
#define METAL_SIFIVE_AON0_0_BASE_ADDRESS 268435456UL
#define METAL_SIFIVE_AON0_10000000_SIZE 32768UL
#define METAL_SIFIVE_AON0_0_SIZE 32768UL

#define METAL_SIFIVE_RTC0
#define METAL_SIFIVE_RTC0_RTCCFG 64UL
#define METAL_SIFIVE_RTC0_RTCCOUNTLO 72UL
#define METAL_SIFIVE_RTC0_RTCCOUNTHI 76UL
#define METAL_SIFIVE_RTC0_RTCS 80UL
#define METAL_SIFIVE_RTC0_RTCCMP0 96UL

/* From spi@10014000 */
#define METAL_SIFIVE_SPI0_10014000_BASE_ADDRESS 268517376UL
#define METAL_SIFIVE_SPI0_0_BASE_ADDRESS 268517376UL
#define METAL_SIFIVE_SPI0_10014000_SIZE 4096UL
#define METAL_SIFIVE_SPI0_0_SIZE 4096UL

#define METAL_SIFIVE_SPI0
#define METAL_SIFIVE_SPI0_SCKDIV 0UL
#define METAL_SIFIVE_SPI0_SCKMODE 4UL
#define METAL_SIFIVE_SPI0_CSID 16UL
#define METAL_SIFIVE_SPI0_CSDEF 20UL
#define METAL_SIFIVE_SPI0_CSMODE 24UL
#define METAL_SIFIVE_SPI0_DELAY0 40UL
#define METAL_SIFIVE_SPI0_DELAY1 44UL
#define METAL_SIFIVE_SPI0_FMT 64UL
#define METAL_SIFIVE_SPI0_TXDATA 72UL
#define METAL_SIFIVE_SPI0_RXDATA 76UL
#define METAL_SIFIVE_SPI0_TXMARK 80UL
#define METAL_SIFIVE_SPI0_RXMARK 84UL
#define METAL_SIFIVE_SPI0_FCTRL 96UL
#define METAL_SIFIVE_SPI0_FFMT 100UL
#define METAL_SIFIVE_SPI0_IE 112UL
#define METAL_SIFIVE_SPI0_IP 116UL

/* From test@100000 */
#define METAL_SIFIVE_TEST0_100000_BASE_ADDRESS 1048576UL
#define METAL_SIFIVE_TEST0_0_BASE_ADDRESS 1048576UL
#define METAL_SIFIVE_TEST0_100000_SIZE 4096UL
#define METAL_SIFIVE_TEST0_0_SIZE 4096UL

#define METAL_SIFIVE_TEST0
#define METAL_SIFIVE_TEST0_FINISHER_OFFSET 0UL

/* From serial@10013000 */
#define METAL_SIFIVE_UART0_10013000_BASE_ADDRESS 268513280UL
#define METAL_SIFIVE_UART0_0_BASE_ADDRESS 268513280UL
#define METAL_SIFIVE_UART0_10013000_SIZE 4096UL
#define METAL_SIFIVE_UART0_0_SIZE 4096UL

#define METAL_SIFIVE_UART0
#define METAL_SIFIVE_UART0_TXDATA 0UL
#define METAL_SIFIVE_UART0_RXDATA 4UL
#define METAL_SIFIVE_UART0_TXCTRL 8UL
#define METAL_SIFIVE_UART0_RXCTRL 12UL
#define METAL_SIFIVE_UART0_IE 16UL
#define METAL_SIFIVE_UART0_IP 20UL
#define METAL_SIFIVE_UART0_DIV 24UL

/* From aon@10000000 */
#define METAL_SIFIVE_AON0_10000000_BASE_ADDRESS 268435456UL
#define METAL_SIFIVE_AON0_0_BASE_ADDRESS 268435456UL
#define METAL_SIFIVE_AON0_10000000_SIZE 32768UL
#define METAL_SIFIVE_AON0_0_SIZE 32768UL

#define METAL_SIFIVE_WDOG0
#define METAL_SIFIVE_WDOG0_MAGIC_KEY 5370206UL
#define METAL_SIFIVE_WDOG0_MAGIC_FOOD 218755085UL
#define METAL_SIFIVE_WDOG0_WDOGCFG 0UL
#define METAL_SIFIVE_WDOG0_WDOGCOUNT 8UL
#define METAL_SIFIVE_WDOG0_WDOGS 16UL
#define METAL_SIFIVE_WDOG0_WDOGFEED 24UL
#define METAL_SIFIVE_WDOG0_WDOGKEY 28UL
#define METAL_SIFIVE_WDOG0_WDOGCMP 32UL

#endif /* METAL_PLATFORM_H*/

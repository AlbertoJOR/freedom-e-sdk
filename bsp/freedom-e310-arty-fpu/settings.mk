# Copyright 2019 SiFive, Inc #
# SPDX-License-Identifier: Apache-2.0 #
# ----------------------------------- #
# ----------------------------------- #

RISCV_ARCH=rv64imafdc
RISCV_ABI=lp64d  #ABI especifies that l= long and p = pointer are 64 bil and fpu hold 64 bit double
RISCV_CMODEL=medany
RISCV_SERIES=sifive-3-series

TARGET_TAGS=fpga openocd
TARGET_DHRY_ITERS=20000000
TARGET_CORE_ITERS=5000

cmake_minimum_required(VERSION 3.15)

set(ASCON_COMMON_INCLUDES include)

add_library(ascon_common STATIC
    ${ASCON_COMMON_INCLUDES}/_internal/common.h
    ${ASCON_COMMON_INCLUDES}/_internal/state.h
        round_constants.c
        interleaving.c
)

set(ASCON_COMMON_INCLUDES ${ASCON_COMMON_INCLUDES} PARENT_SCOPE)

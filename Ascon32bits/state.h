//
// Created by albertojor on 31/07/23.
//

#ifndef FREEDOM_E_SDK_STATE_H
#define FREEDOM_E_SDK_STATE_H

#include <stdint.h>
#include <stdio.h>

typedef uint32_t u32;
typedef struct {
    u32 xh[5];
    u32 xl[5];
} ascon_state_t;

typedef struct {
    u32 xh;
    u32 xl;
} u64;



#endif //FREEDOM_E_SDK_STATE_H

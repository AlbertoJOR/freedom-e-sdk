#ifndef ROUND_H_
#define ROUND_H_
#define PADH(m_len) ((m_len > 3) ? (0) : (0x80000000 >> ((m_len)*8)))
#define PADL(m_len) ((m_len > 3) ? ((m_len == 8) ? 0 : (0x80000000 >> (((m_len)-4)*8))) : (0))
#define TRUNH(m_len, hi) ((m_len > 4 ) ? ((hi)) : ((m_len == 0) ? 0: ((hi) &  (0xFFFFFFFF << ((4 - m_len) *8)))) )
#define TRUNL(m_len, lo) (( m_len > 4 ) ? ( (lo) &  (0xFFFFFFFF << ((8-m_len) * 8))): (0))
#define CLEARH(m_len, hi) ((m_len > 4 ) ? ((0)) : ((m_len == 0) ? hi: ((hi) & ~ (0xFFFFFFFF << ((4 - m_len) *8)))) )
#define CLEARL(m_len, lo) (( m_len > 4 ) ? ( (lo) &  ~ (0xFFFFFFFF << ((8-m_len) * 8))): (lo))

#define RORH(n, yh, yl) ((n>31) ? ((yh) << 64 - (n) | (yl) >> (n) - 32) : ((yl) << 32-(n) | (yh) >> (n)))
#define RORL(n, yh, yl) ((n>31) ? ((yl) << 64 - (n) | (yh) >> (n) - 32) : ((yh) << 32-(n) | (yl) >> (n)))
#include "state.h"

static inline u64 ROR32(u32 highPart, u32 lowPart, int rotation) {

    rotation = rotation % 64; // Ensure rotation is in the range [0, 63]
    u32 High = highPart;
    u32 Low = lowPart;
    u64 res;
    res.xh = highPart;
    res.xl = lowPart;

    if (rotation != 0) {
        if (rotation == 32) {
            res.xh = Low;
            res.xl = High;
            return res;
        }
        // Perform the right rotation using bitwise operations
        u32 auxHigh = (High >> (rotation % 32)) | (Low << (32 - (rotation % 32)));
        u32 auxLow = (Low >> (rotation % 32)) | (High << (32 - (rotation % 32)));

        // For rotation >= 32, swap the high and low parts
        if (rotation > 32) {
            u32 temp = auxHigh;
            auxHigh = auxLow;
            auxLow = temp;
        }
        res.xh= auxHigh;
        res.xl = auxLow;

    }
    return res;

}

static inline void ROUND(ascon_state_t *s, u32 C) {
    ascon_state_t t;
    // addition of round constant
    s->xl[2] ^=C;
    // printstate(" round constant", s);
    // substitution layer

    s->xh[0] ^= s->xh[4];
    s->xl[0] ^= s->xl[4];

    s->xh[4] ^= s->xh[3];
    s->xl[4] ^= s->xl[3];

    s->xh[2] ^= s->xh[1];
    s->xl[2] ^= s->xl[1];
    // start of keccak s-box
    t.xh[0] = s->xh[0] ^ (~s->xh[1] & s->xh[2]);
    t.xl[0] = s->xl[0] ^ (~s->xl[1] & s->xl[2]);

    t.xh[1] = s->xh[1] ^ (~s->xh[2] & s->xh[3]);
    t.xl[1] = s->xl[1] ^ (~s->xl[2] & s->xl[3]);

    t.xh[2] = s->xh[2] ^ (~s->xh[3] & s->xh[4]);
    t.xl[2] = s->xl[2] ^ (~s->xl[3] & s->xl[4]);

    t.xh[3] = s->xh[3] ^ (~s->xh[4] & s->xh[0]);
    t.xl[3] = s->xl[3] ^ (~s->xl[4] & s->xl[0]);

    t.xh[4] = s->xh[4] ^ (~s->xh[0] & s->xh[1]);
    t.xl[4] = s->xl[4] ^ (~s->xl[0] & s->xl[1]);
    // end of keccak s-box
    t.xh[1] ^= t.xh[0];
    t.xh[0] ^= t.xh[4];
    t.xh[3] ^= t.xh[2];
    t.xh[2] = ~t.xh[2];
    t.xl[1] ^= t.xl[0];
    t.xl[0] ^= t.xl[4];
    t.xl[3] ^= t.xl[2];
    t.xl[2] = ~t.xl[2];
    // printstate(" substitution layer", &t);
    u64  ror1;
    u64  ror2;
    //linear diffusion layer

    s->xh[0] = t.xh[0] ^ RORH(19,t.xh[0],t.xl[0]) ^ RORH(28,t.xh[0], t.xl[0]);
    s->xl[0] = t.xl[0] ^ RORL(19,t.xh[0],t.xl[0]) ^ RORL(28,t.xh[0], t.xl[0]);

    s->xh[1] = t.xh[1] ^ RORH(61,t.xh[1],t.xl[1]) ^ RORH(39,t.xh[1], t.xl[1]);
    s->xl[1] = t.xl[1] ^ RORL(61,t.xh[1],t.xl[1]) ^ RORL(39,t.xh[1], t.xl[1]);

    s->xh[2] = t.xh[2] ^ RORH(1,t.xh[2],t.xl[2]) ^ RORH(6,t.xh[2], t.xl[2]);
    s->xl[2] = t.xl[2] ^ RORL(1,t.xh[2],t.xl[2]) ^ RORL(6,t.xh[2], t.xl[2]);

    s->xh[3] = t.xh[3] ^ RORH(10,t.xh[3],t.xl[3]) ^ RORH(17,t.xh[3], t.xl[3]);
    s->xl[3] = t.xl[3] ^ RORL(10,t.xh[3],t.xl[3]) ^ RORL(17,t.xh[3], t.xl[3]);

    s->xh[4] = t.xh[4] ^ RORH(7,t.xh[4],t.xl[4]) ^ RORH(41,t.xh[4], t.xl[4]);
    s->xl[4] = t.xl[4] ^ RORL(7,t.xh[4],t.xl[4]) ^ RORL(41,t.xh[4], t.xl[4]);

    //printstate(" round output", s);
}


static inline void P12(ascon_state_t* s) {
  ROUND(s, 0xf0);
  ROUND(s, 0xe1);
  ROUND(s, 0xd2);
  ROUND(s, 0xc3);
  ROUND(s, 0xb4);
  ROUND(s, 0xa5);
  ROUND(s, 0x96);
  ROUND(s, 0x87);
  ROUND(s, 0x78);
  ROUND(s, 0x69);
  ROUND(s, 0x5a);
  ROUND(s, 0x4b);
}

static inline void P8(ascon_state_t* s) {
  ROUND(s, 0xb4);
  ROUND(s, 0xa5);
  ROUND(s, 0x96);
  ROUND(s, 0x87);
  ROUND(s, 0x78);
  ROUND(s, 0x69);
  ROUND(s, 0x5a);
  ROUND(s, 0x4b);
}

static inline void P6(ascon_state_t* s) {
  ROUND(s, 0x96);
  ROUND(s, 0x87);
  ROUND(s, 0x78);
  ROUND(s, 0x69);
  ROUND(s, 0x5a);
  ROUND(s, 0x4b);
}

#endif /* ROUND_H_ */

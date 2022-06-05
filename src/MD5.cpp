#include "src/MD5.h"

u_int32_t MD5 :: ROL(u_int32_t x, int y) {
    return (x << y) | (x >> (32 - y));
}

u_int32_t MD5 :: F(u_int32_t x, u_int32_t y, u_int32_t z) {
    return (x & y) | ((~x) & z);
}

u_int32_t MD5 :: G(u_int32_t x, u_int32_t y, u_int32_t z) {
    return (x & z) | (y & (~z));
}

u_int32_t MD5 :: H(u_int32_t x, u_int32_t y, u_int32_t z) {
    return x ^ y ^ z;
}

u_int32_t MD5 :: I(u_int32_t x, u_int32_t y, u_int32_t z) {
    return y ^ (x | (~z));
}

ByteArray MD5 :: calculateMD5Code(ByteVector S) {
    u_int64_t len = S.getSize() * 8;
    S.pushBack(0x80);
    while ((S.getSize() * 8) % 512 != 448)
        S.pushBack(0);
    for (int index = 0; index < 8; index++)
        S.pushBack(len & 0xff), len >>= 8;
    Array<u_int32_t> tmp(64, 0);
    for (int index = 0; index < 64; index++)
        tmp[index] = floor(0x100000000ull * fabs(sin(index + 1)));
    u_int32_t a = 0x67452301u;
    u_int32_t b = 0xefcdab89u;
    u_int32_t c = 0x98badcfeu;
    u_int32_t d = 0x10325476u;
    for (int t = 0; t * 64 < S.getSize(); t++) {
        Array<u_int32_t> m(16, 0);
        for (int i = 0; i < 16; i++)
            for (int j = 3; j >= 0; j--)
                m[i] = (m[i] << 8) | S[t * 64 + i * 4 + j];
        u_int32_t tmpa = a;
        u_int32_t tmpb = b;
        u_int32_t tmpc = c;
        u_int32_t tmpd = d;
        for (int index = 0; index < 16; index++) {
            int i = index;
            int j = index;
            int s = 0;
            switch (index % 4) {
                case 0:
                    s = 7; break;
                case 1:
                    s = 12; break;
                case 2:
                    s = 17; break;
                case 3:
                    s = 22; break;
            }
            a = b + ROL((a + F(b, c, d) + m[i] + tmp[j]), s);
            unsigned t = d;
            d = c; c = b; b = a; a = t;
        }
        for (int index = 0; index < 16; index++) {
            int i = (1 + index * 5) % 16;
            int j = 16 + index;
            int s = 0;
            switch (index % 4) {
                case 0:
                    s = 5; break;
                case 1:
                    s = 9; break;
                case 2:
                    s = 14; break;
                case 3:
                    s = 20; break;
            }
            a = b + ROL((a + G(b, c, d) + m[i] + tmp[j]), s);
            unsigned t = d;
            d = c; c = b; b = a; a = t;
        }
        for (int index = 0; index < 16; index++) {
            int i = (5 + index * 3) % 16;
            int j = 32 + index;
            int s = 0;
            switch (index % 4) {
                case 0:
                    s = 4; break;
                case 1:
                    s = 11; break;
                case 2:
                    s = 16; break;
                case 3:
                    s = 23; break;
            }
            a = b + ROL((a + H(b, c, d) + m[i] + tmp[j]), s);
            unsigned t = d;
            d = c; c = b; b = a; a = t;
        }
        for (int index = 0; index < 16; index++) {
            int i = (index * 7) % 16;
            int j = 48 + index;
            int s = 0;
            switch (index % 4) {
                case 0:
                    s = 6; break;
                case 1:
                    s = 10; break;
                case 2:
                    s = 15; break;
                case 3:
                    s = 21; break;
            }
            a = b + ROL((a + I(b, c, d) + m[i] + tmp[j]), s);
            unsigned t = d;
            d = c; c = b; b = a; a = t;
        }
        a += tmpa; b += tmpb;
        c += tmpc; d += tmpd;
    }
    ByteArray res(16, 0);
    for (int index = 0; index < 4; index++) {
        res[index] = a & 0xff; a >>= 8;
        res[index + 4] = b & 0xff; b >>= 8;
        res[index + 8] = c & 0xff; c >>= 8;
        res[index + 12] = d & 0xff; d >>= 8;
    }
    return res;
}

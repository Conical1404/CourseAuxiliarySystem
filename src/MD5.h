#pragma once
#include <math.h>
#include <stdio.h>
#include "Array.h"
#include "Basic.h"
#include "Vector.h"

namespace MD5 {
    u_int32_t F(u_int32_t x, u_int32_t y, u_int32_t z);
    u_int32_t G(u_int32_t x, u_int32_t y, u_int32_t z);
    u_int32_t H(u_int32_t x, u_int32_t y, u_int32_t z);
    u_int32_t I(u_int32_t x, u_int32_t y, u_int32_t z);
    u_int32_t ROL(u_int32_t x, int y);
    ByteArray calculateMD5Code(ByteVector S);
}

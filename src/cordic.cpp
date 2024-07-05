#include "cordic.hpp"
#include "ik.hpp"
#include "vec.hpp"
#include <cmath>
#include <iostream>

namespace cordic {

struct ArctanTable {
    /// Number of x values that have precomputed arctan(2^(-x)) before being
    /// replaced by arctan(2^(-x)) = 2^(-x)
    static constexpr uint8_t LOOKUP_LEN = 5;

    /// Compute the inverse arctan of 2 raised to `-pow2`
    static inline bfp_t atan_inv_pow2(uint8_t pow2) {
        bfp_t LUT[LOOKUP_LEN] = {
            bfp_t::raw(0x0000c9),
            bfp_t::raw(0x000077),
            bfp_t::raw(0x00003f),
            bfp_t::raw(0x000020),
            bfp_t::raw(0x000010),
        };
        if(pow2 < LOOKUP_LEN) {
            return LUT[pow2];
        } else {
            return bfp_t(1) >> pow2;
        }
    }
};

static Vec2 rotate_vec(Vec2 v, uint8_t step, bool ccw) {
    Vec2 rot{-(v.y >> step), v.x >> step};
    if(!ccw) {
        rot.x = -rot.x;
        rot.y = -rot.y;
    }

    return v + rot;
}

static void cordic_vectoring_kernel_vec(Vec2& v) {
    bfp_t K = bfp_t::raw(0x00004e);
    for(uint8_t n = 0; n <= (bfp_t::FRACTION_SHIFT * 2) + 1; ++n) {
        v = rotate_vec(v, (n >> 1), v.y.is_negative());
    }
    v = v * K;
}

static bfp_t cordic_vectoring_kernel_angle(Vec2 v) {
    bfp_t beta = 0;
    for(uint8_t n = 0; n <= (bfp_t::FRACTION_SHIFT * 2) + 1; ++n) {
        uint8_t idx = n >> 1;
        bool ccw = v.y.is_negative();
        bfp_t atan = ArctanTable::atan_inv_pow2(idx);
        if(ccw) { atan = -atan; }
        beta = beta + atan;
        v = rotate_vec(v, idx, ccw);
    }

    return beta;
}

bfp_t norm(Vec2 v) {
    cordic_vectoring_kernel_vec(v);
    return v.x;
}



bfp_t angle_between(Vec2 from, Vec2 to) {
    bfp_t beta_from = cordic_vectoring_kernel_angle(from);
    bfp_t beta_to   = cordic_vectoring_kernel_angle(to);
    return beta_to - beta_from;
}

bfp_t angle_of(Vec2 v) {
    return cordic_vectoring_kernel_angle(v);
}


}

#include "ik.hpp"
#include "vec.hpp"
#include <cmath>
#include <iostream>

bfp_t r2d(bfp_t v) {
    return v * bfp_t{180} / bfp::PI;
}

int main(int const _argc, char const *argv[]) {
    static constexpr bfp_t
        ARM_SEGMENT_OFFSET{20},
        ARM_SEGMENT_BASE{35},
        ARM_SEGMENT_FORE{50},
        ARM_SEGMENT_HAND{30};


    Arm arm{ARM_SEGMENT_OFFSET, ARM_SEGMENT_BASE, ARM_SEGMENT_FORE, ARM_SEGMENT_HAND};

    auto res = arm.fabrik(bfp_t{20}, bfp_t{60}, bfp_t{30}); 
    std::cout << 
        "θ azimuth: " << (int32_t)r2d(res.AngleAzimuth) << '\n' <<
        "θ el. base: " << (int32_t)r2d(res.AngleElevationBase) << '\n' <<
        "θ arm elevation: " << (int32_t)r2d(res.AngleElevationArm) << '\n' <<
        "θ wrist elevation: "  << (int32_t)r2d(res.AngleElevationWrist) << '\n' <<
        "effector: (" << (int32_t)arm.effector().head.x << ", " << (int32_t)arm.effector().head.y << ')' << std::endl;

    for(unsigned i = 0; i < arm.SEGMENTS_LEN; ++i) {
        std::cout << "Joint " << i << " = (" <<
            (int32_t)arm._segments[i].head.x << ", " <<
            (int32_t)arm._segments[i].head.y << ")" << std::endl;
    }
}

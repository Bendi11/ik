#include "cordic.hpp"
#include "ik.hpp"
#include "vec.hpp"
#include <cmath>
#include <iostream>

bfp_t r2d(bfp_t v) {
    return v * bfp_t{180} / cordic::PI;
}

int main(int const _argc, char const *argv[]) {
    Arm arm{};

    auto res = arm.fabrik(bfp_t{50}, bfp_t{50}, bfp_t{20}); 
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

#include "cordic.hpp"
#include "ik.hpp"
#include "vec.hpp"
#include <iostream>

bfp_t r2d(bfp_t v) {
    return v * bfp_t{180} / cordic::PI;
}

int main(int const _argc, char const *argv[]) {
    Arm arm{};

    auto result = arm.fabrik(20, 2, 0);
    std::cout
        << "azimuth: " << r2d(result.AngleAzimuth) << '\n'
        << "elevation base: " << r2d(result.AngleElevationBase) << '\n'
        << "elevation arm: " << r2d(result.AngleElevationArm) << '\n'
        << "elevation wrist: " << r2d(result.AngleElevationWrist) << std::endl;
}

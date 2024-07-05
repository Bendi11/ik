#include "cordic.hpp"
#include "ik.hpp"
#include "vec.hpp"
#include <cmath>

bfp_t r2d(bfp_t v) {
    return v * bfp_t{180} / cordic::PI;
}

int main(int const _argc, char const *argv[]) {
    Arm arm{};
    
    for(int32_t x = -5000; x <= 5000; ++x) {
        for(int32_t y = -5000; y <= 5000; ++y) {
            for(int32_t z = -100; z <= 100; ++z) {
                auto result = arm.fabrik(x, y, z);
            }
        }
    }
}

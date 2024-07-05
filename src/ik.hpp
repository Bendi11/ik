#include <cmath>
#include <cstdint>

#include "vec.hpp"


struct Segment {
    Vec2 head;
    bfp_t len;

    inline Segment(Vec2 h, bfp_t l) : head{h}, len{l} {}
};


struct Arm {
public:
    struct FabrikResult {
        bfp_t AngleAzimuth;
        bfp_t AngleElevationBase;
        bfp_t AngleElevationArm;
        bfp_t AngleElevationWrist;
    };

    static inline constexpr const uint8_t SEGMENTS_LEN = 3;

    Arm();

    FabrikResult fabrik(bfp_t x, bfp_t y, bfp_t z);

    inline constexpr Segment const& effector(void) const { return _segments[SEGMENTS_LEN - 1]; }
private:
    Segment _segments[SEGMENTS_LEN];

    Vec2 reach(Vec2 from, Vec2 to, bfp_t len);

    static inline constexpr const bfp_t
        ARM_SEGMENT_OFFSET{20},
        ARM_SEGMENT_BASE{35},
        ARM_SEGMENT_FORE{50},
        ARM_SEGMENT_HAND{30};
};

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

    static constexpr const uint8_t SEGMENTS_LEN = 3;

    Arm(bfp_t offset, bfp_t base, bfp_t arm, bfp_t wrist);

    FabrikResult fabrik(bfp_t x, bfp_t y, bfp_t z);
    
    Segment _segments[SEGMENTS_LEN];
    bfp_t _offset;
    inline constexpr Segment const& effector(void) const { return _segments[SEGMENTS_LEN - 1]; }
private:

    Vec2 reach(Vec2 from, Vec2 to, bfp_t len);
};

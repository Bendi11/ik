#include "ik.hpp"
#include "cordic.hpp"
#include <cmath>

static constexpr bfp_t
        ARM_SEGMENT_OFFSET{20},
        ARM_SEGMENT_BASE{35},
        ARM_SEGMENT_FORE{50},
        ARM_SEGMENT_HAND{30};

Arm::Arm() : _segments{
    Segment(Vec2(0, ARM_SEGMENT_BASE), ARM_SEGMENT_BASE),
    Segment(Vec2(0, ARM_SEGMENT_BASE + ARM_SEGMENT_FORE), ARM_SEGMENT_FORE),
    Segment(Vec2(0, ARM_SEGMENT_BASE + ARM_SEGMENT_FORE + ARM_SEGMENT_HAND), ARM_SEGMENT_HAND),
} {}

Arm::FabrikResult Arm::fabrik(bfp_t x, bfp_t y, bfp_t z) {
    Vec2 target = Vec2(
        cordic::norm(Vec2{x, z}),
        y - ARM_SEGMENT_OFFSET
    );
    
    for(uint8_t i = SEGMENTS_LEN - 1; i > 0; --i) {
        Segment& tail = _segments[i - 1];
        Segment& head = _segments[i];
        head.head = target;
        target = reach(tail.head, target, head.len);
    }

    _segments[0].head = target;

    
    target = Vec2(0, 0);
    for(uint8_t i = 0; i < SEGMENTS_LEN; ++i) {
        Segment& seg = _segments[i];
        seg.head  = reach(seg.head, target, seg.len);
        target = seg.head;
    }

    Vec2 seg1 = _segments[1].head - _segments[0].head;
    Vec2 seg2 = _segments[2].head - _segments[1].head;

    auto az = cordic::angle_of(Vec2{z, -x});
    auto el_base = cordic::angle_of(Vec2{_segments[0].head.y, -_segments[0].head.x});
    auto el_arm  = cordic::angle_of(Vec2{seg1.y, -seg1.x});
    auto el_wrist = cordic::angle_of(Vec2{seg2.y, -seg2.x});

    el_wrist = el_wrist - el_arm;
    el_arm = el_arm - el_base;

    return FabrikResult {
        .AngleAzimuth = az,
        .AngleElevationBase = el_base,
        .AngleElevationArm = el_arm,
        .AngleElevationWrist = el_wrist,
    };
}

Vec2 Arm::reach(Vec2 from, Vec2 to, bfp_t len) {
    Vec2 diff = from - to;
    bfp_t norm = cordic::norm(diff);

    return to + (diff * len / norm);
}

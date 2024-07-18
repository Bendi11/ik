#pragma once

#include "vec.hpp"


namespace cordic {



bfp_t norm(Vec2 v);

bfp_t angle_between(Vec2 from, Vec2 to);

bfp_t angle_of(Vec2 v);

}

#pragma once
#include <limits>
namespace micromouse {
constexpr float nan = std::numeric_limits<float>::quiet_NaN();
constexpr float FIELD_SIZE = 0.168;

struct Position2D {
    float x_m{nan};
    float y_m{nan};
};

struct Quaternion {
    float x{nan};
    float y{nan};
    float z{nan};
    float w{nan};
};
}  // namespace micromouse
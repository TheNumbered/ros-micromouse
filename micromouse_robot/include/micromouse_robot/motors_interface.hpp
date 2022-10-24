#pragma once
#include "math_structs.hpp"
#include <string>

namespace micromouse {
class MotorsInterface {
   public:
    MotorsInterface()
        : linear_velocity_m_per_s_{std::numeric_limits<float>::quiet_NaN()}, angular_velocity_rad_per_s_{std::numeric_limits<float>::quiet_NaN()}, angle_rad_{std::numeric_limits<float>::quiet_NaN()}, position_{std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN()} {
    }

    virtual void set_velocity(float linear_velocity_m_per_s, float angular_velocity_rad_per_s) = 0;
    virtual float get_linear_velocity() = 0;
    virtual float get_angular_velocity() = 0;
    virtual float get_angle() = 0;
    virtual Quaternion get_quaternion() = 0;
    virtual Position2D get_position() = 0;

   protected:
    float linear_velocity_m_per_s_;
    float angular_velocity_rad_per_s_;
    float angle_rad_;
    Position2D position_;
    Quaternion quaternion_;
};
}  // namespace micromouse
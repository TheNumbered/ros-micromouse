#pragma once
#include "math_structs.hpp"
namespace micromouse {
class ImuInterface {
   public:
    ImuInterface() : angle_rad_{NAN} {};
    virtual float get_angle() = 0;
    virtual Quaternion get_quaternion() = 0;

   protected:
    float angle_rad_;
    Quaternion quaternion_;
};
}  // namespace micromouse
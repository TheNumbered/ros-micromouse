#pragma once
#include <limits>

namespace micromouse {
class ImuInterface {
   public:
    ImuInterface()
        : angle_rad_{std::numeric_limits<float>::quiet_NaN()} {}
    virtual float get_angle() = 0;

   protected:
    float angle_rad_;
};
}  // namespace micromouse
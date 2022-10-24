#pragma once
#include <string>
#include <limits>

namespace micromouse {
class RangeSensorInterface {
   public:
    RangeSensorInterface(const std::string &name)
        : name_{name}, range_{std::numeric_limits<double>::quiet_NaN()} {}
    virtual double get_range() = 0;

   protected:
    const std::string name_;
    double range_;
};
}  // namespace micromouse
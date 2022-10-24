#pragma once
#include <string>
#include "math_structs.hpp"
namespace micromouse {
class RangeSensorInterface {
   public:
    RangeSensorInterface(const std::string &name)
        : name_{name}, range_{nan} {}
    virtual float get_range() = 0;

   protected:
    const std::string name_;
    float range_;
};
}  // namespace micromouse
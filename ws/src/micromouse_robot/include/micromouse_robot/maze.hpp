#pragma once
#include <array>
#include <cmath>
namespace micromouse {
constexpr float FIELD_SIZE = 0.168;
constexpr float POST_SIZE = 0.012;

namespace directions {
constexpr float NORTH = 0.0;
constexpr float SOUTH = M_PI;
constexpr float WEST = M_PI / 2;
constexpr float EAST = -M_PI / 2;
}  // namespace directions

enum class Wall {
    unknown,
    empty,
    wall
};

struct Field {
    Wall north_wall;
    Wall south_wall;
    Wall east_wall;
    Wall west_wall;
};

class Maze {
   public:
    Field &operator()(std::size_t x, std::size_t y) {
        return fields_[x][y];
    }

    Field operator()(std::size_t x, std::size_t y) const {
        return fields_[x][y];
    }

   private:
    std::array<std::array<Field, 16>, 16> fields_;
};
}  // namespace micromouse
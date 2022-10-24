#pragma once
#include <cmath>
#include <functional>
#include <rclcpp/rclcpp.hpp>

#include "pid_controller.hpp"
#include "rclcpp_imu.hpp"
#include "rclcpp_motors.hpp"
#include "rclcpp_range_sensor.hpp"
#include "maze.hpp"

namespace micromouse {
constexpr float FLOAT_MINIMAL_ERROR = 0.008;
constexpr bool float_equal(float l, float r) {
    return std::fabs(l - r) < FLOAT_MINIMAL_ERROR;
}

class Robot {
   public:
    Robot(std::function<float()> get_time_stamp);
    void update();
    void go_dir(float dir);

   private:
    std::function<float()> get_time_stamp_;
    PidController align_controller_;
    PidController rotate_controller_;
    float robot_direction_;

    float command_linear_velocity_;
    float command_angular_velocity_;
    float command_angle_;

    bool is_rotating_;
    std::shared_ptr<RangeSensorInterface> range_left;
    std::shared_ptr<RangeSensorInterface> range_right;
    std::shared_ptr<RangeSensorInterface> range_front_left;
    std::shared_ptr<RangeSensorInterface> range_front_right;
    std::shared_ptr<ImuInterface> imu;
    std::shared_ptr<MotorsInterface> motors;

    float get_filtered_angle();
    float get_forward_range();
};
}  // namespace micromouse
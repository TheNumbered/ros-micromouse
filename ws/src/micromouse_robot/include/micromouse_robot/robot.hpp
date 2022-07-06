#pragma once
#include <rclcpp/rclcpp.hpp>
#include <functional>
// #include "imu.hpp"
#include "rclcpp_motors.hpp"
#include "pid_controller.hpp"
#include "rclcpp_range_sensor.hpp"

namespace micromouse {
class Robot{
   public:
    Robot(std::function<float()> get_time_stamp);
    void update();

   private:
    std::function<float()> get_time_stamp_;
    std::shared_ptr<RangeSensorInterface> range_left;
    std::shared_ptr<RangeSensorInterface> range_right;
    std::shared_ptr<RangeSensorInterface> range_front_left;
    std::shared_ptr<RangeSensorInterface> range_front_right;
    // std::shared_ptr<Imu> imu;

    std::shared_ptr<MotorsInterface> motors;

    PidController align_controller_;
};
}  // namespace micromouse
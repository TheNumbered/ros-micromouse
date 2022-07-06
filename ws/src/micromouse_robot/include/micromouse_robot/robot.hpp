#pragma once
#include <rclcpp/rclcpp.hpp>

// #include "imu.hpp"
#include "motors.hpp"
#include "pid_controller.hpp"
#include "rclcpp_range_sensor.hpp"

namespace micromouse {
class Robot: public rclcpp::Node {
   public:
    Robot();

   private:
    std::shared_ptr<RangeSensorInterface> range_left;
    std::shared_ptr<RangeSensorInterface> range_right;
    std::shared_ptr<RangeSensorInterface> range_front_left;
    std::shared_ptr<RangeSensorInterface> range_front_right;
    // std::shared_ptr<Imu> imu;

    std::shared_ptr<Motors> motors;
    rclcpp::TimerBase::SharedPtr timer_;

    PidController align_controller_;
    void update_();
};
}  // namespace micromouse
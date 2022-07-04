#pragma once
#include <rclcpp/rclcpp.hpp>
#include "motors.hpp"
#include "range_sensor.hpp"
#include "pid_controller.hpp"

namespace micromouse {
class Robot: public rclcpp::Node {
   public:
    Robot();

   private:
    std::shared_ptr<RangeSensor> range_left;
    std::shared_ptr<RangeSensor> range_right;
    std::shared_ptr<RangeSensor> range_front_left;
    std::shared_ptr<RangeSensor> range_front_right;

    std::shared_ptr<Motors> motors;
    rclcpp::TimerBase::SharedPtr timer_;

    PidController align_controller_;
    void update_();
};
}  // namespace micromouse
#pragma once
#include <limits>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/range.hpp>
#include <string>
#include <thread>

#include "range_sensor_interface.hpp"

namespace micromouse {
class RclcppRangeSensor : public RangeSensorInterface, public rclcpp::Node {
   public:
    RclcppRangeSensor(const std::string name);
    virtual double get_range() override final;

   private:
    rclcpp::Subscription<sensor_msgs::msg::Range>::SharedPtr range_sub_;
    void sensor_callback_(const sensor_msgs::msg::Range &msg);
};
}  // namespace micromouse
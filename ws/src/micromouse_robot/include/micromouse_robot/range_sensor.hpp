#pragma once
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/range.hpp>
#include <string>
#include <thread>
#include <limits>

namespace micromouse {
class RangeSensor: public rclcpp::Node {
   public:
    RangeSensor(const std::string name);
    double get_range();

   private:
    const std::string name_;
    double range_;
    rclcpp::Subscription<sensor_msgs::msg::Range>::SharedPtr range_sub_;

    void sensor_callback_(const sensor_msgs::msg::Range &msg);
};
}  // namespace micromouse
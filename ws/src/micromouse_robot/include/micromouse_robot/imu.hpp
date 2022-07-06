#pragma once
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/LinearMath/Quaternion.h>

#include <limits>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <string>
#include <thread>

namespace micromouse {
class Imu : public rclcpp::Node {
   public:
    Imu();
    double get_angle();

   private:
    double angle_;
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;

    void imu_callback_(const sensor_msgs::msg::Imu &msg);
};
}  // namespace micromouse
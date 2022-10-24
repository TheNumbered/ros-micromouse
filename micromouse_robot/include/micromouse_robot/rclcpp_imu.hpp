#pragma once
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/LinearMath/Quaternion.h>

#include <limits>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <string>
#include <thread>
#include "imu_interface.hpp"

namespace micromouse {
class RclcppImu : public ImuInterface, public rclcpp::Node {
   public:
    RclcppImu();
    virtual float get_angle() override final;
    virtual Quaternion get_quaternion() override final;

   private:
    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
    void imu_callback_(const sensor_msgs::msg::Imu &msg);
};
}  // namespace micromouse
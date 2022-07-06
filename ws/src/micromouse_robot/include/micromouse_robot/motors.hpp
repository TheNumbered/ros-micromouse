#pragma once
#include <geometry_msgs/msg/twist.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <limits>
#include <nav_msgs/msg/odometry.hpp>
#include <rclcpp/rclcpp.hpp>
#include <string>
#include <thread>

namespace micromouse {
class Motors : public rclcpp::Node {
   public:
    Motors();
    void set_vel(double vel_lin, double vel_ang);

   private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_;

    double vel_lin_;
    double vel_ang_;

    // void odom_callback_(const nav_msgs::msg::Odometry &msg);
};
}
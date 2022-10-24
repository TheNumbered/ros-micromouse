#pragma once
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/LinearMath/Quaternion.h>

#include <geometry_msgs/msg/twist.hpp>
#include <limits>
#include <nav_msgs/msg/odometry.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <string>
#include <thread>
#include "math_structs.hpp"
#include "motors_interface.hpp"

namespace micromouse {
class RclcppMotors : public MotorsInterface, public rclcpp::Node {
   public:
    RclcppMotors();
    virtual void set_velocity(float linear_velocity_m_per_s, float angular_velocity_rad_per_s) override final;
    virtual float get_linear_velocity() override final;
    virtual float get_angular_velocity() override final;
    virtual float get_angle() override final;
    virtual Position2D get_position() override final;
    virtual Quaternion get_quaternion() override final;

   private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;

    void odom_callback_(const nav_msgs::msg::Odometry &msg);
};
}  // namespace micromouse
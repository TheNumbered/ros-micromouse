#include "micromouse_robot/motors.hpp"

namespace micromouse {
Motors::Motors()
    : rclcpp::Node("micromouse_motors"),
      vel_lin_{std::numeric_limits<double>::quiet_NaN()},
      vel_ang_{std::numeric_limits<double>::quiet_NaN()}{
    cmd_vel_pub_ = create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
    // odom_sub_ = create_subscription<nav_msgs::msg::Odometry>("odom", 10, std::bind(&Motors::odom_callback_, this, _1));
}

void Motors::set_vel(double vel_lin, double vel_ang){
    auto message = geometry_msgs::msg::Twist();
    message.linear.x = vel_lin;
    message.angular.z = vel_ang;
    cmd_vel_pub_->publish(message);
}

// void Motors::odom_callback_(const nav_msgs::msg::Odometry &msg){

// }

}  // namespace micromouse
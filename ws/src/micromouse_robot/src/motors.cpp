#include "micromouse_robot/motors.hpp"

namespace micromouse {
Motors::Motors()
    : rclcpp::Node("micromouse_motors"),
      vel_lin_{std::numeric_limits<double>::quiet_NaN()},
      vel_ang_{std::numeric_limits<double>::quiet_NaN()}{
    cmd_vel_pub_ = create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
}

void Motors::set_vel(double vel_lin, double vel_ang){
    auto message = geometry_msgs::msg::Twist();
    message.linear.x = vel_lin;
    message.angular.z = vel_ang;
    cmd_vel_pub_->publish(message);
}

}  // namespace micromouse
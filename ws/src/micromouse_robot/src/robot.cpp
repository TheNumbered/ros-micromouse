#include "micromouse_robot/robot.hpp"

namespace micromouse {
Robot::Robot()
    : rclcpp::Node("micromouse_robot") {
    range_left = std::make_shared<RangeSensor>("range_sensor_left");
    range_right = std::make_shared<RangeSensor>("range_sensor_right");
    range_front = std::make_shared<RangeSensor>("range_sensor_front");
    using namespace std::chrono_literals;
    timer_ = this->create_wall_timer(100ms, std::bind(&Robot::update_, this));
}

void Robot::update_() {
    RCLCPP_INFO(get_logger(), "left: %f", range_left->get_range());
    RCLCPP_INFO(get_logger(), "front: %f", range_front->get_range());
    RCLCPP_INFO(get_logger(), "right: %f", range_right->get_range());

}
}  // namespace micromouse
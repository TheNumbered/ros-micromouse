#include "micromouse_robot/robot.hpp"

namespace micromouse {
Robot::Robot()
    : rclcpp::Node("micromouse_robot"), align_controller_(1.3, 0.0, 0.0) {
    range_left = std::make_shared<RangeSensor>("range_sensor_left");
    range_right = std::make_shared<RangeSensor>("range_sensor_right");
    range_front_left = std::make_shared<RangeSensor>("range_sensor_front_left");
    range_front_right = std::make_shared<RangeSensor>("range_sensor_front_right");
    motors = std::make_shared<Motors>();

    using namespace std::chrono_literals;
    timer_ = this->create_wall_timer(100ms, std::bind(&Robot::update_, this));
}

void Robot::update_() {
    // RCLCPP_INFO(get_logger(), "left: %f", range_left->get_range());
    // RCLCPP_INFO(get_logger(), "front: %f", range_front->get_range());
    // RCLCPP_INFO(get_logger(), "right: %f", range_right->get_range());

    if (range_front_left->get_range() > 0.16) {
        auto cmd_arg_vel = align_controller_.get_command(0.0, range_left->get_range() - range_right->get_range(), get_clock()->now().seconds());
        motors->set_vel(0.4, cmd_arg_vel);
    } else if (range_front_left->get_range() > 0.06) {
        auto cmd_arg_vel = align_controller_.get_command(0.0, range_front_left->get_range() - range_front_right->get_range(), get_clock()->now().seconds());
        motors->set_vel(0.1, cmd_arg_vel);
    }
    else{
        motors->set_vel(0.0, 0.0);

    }
}
}  // namespace micromouse
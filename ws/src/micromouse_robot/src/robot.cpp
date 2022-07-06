#include "micromouse_robot/robot.hpp"

namespace micromouse {

Robot::Robot(std::function<float()> get_time_stamp)
    : get_time_stamp_{get_time_stamp}
    , align_controller_(1.3, 0.0, 0.0) {
    range_left = std::make_shared<RclcppRangeSensor>("range_sensor_left");
    range_right = std::make_shared<RclcppRangeSensor>("range_sensor_right");
    range_front_left = std::make_shared<RclcppRangeSensor>("range_sensor_front_left");
    range_front_right = std::make_shared<RclcppRangeSensor>("range_sensor_front_right");

    // imu = std::make_shared<Imu>();

    motors = std::make_shared<RclcppMotors>();
}

void Robot::update() {
    // RCLCPP_INFO(get_logger(), "left: %f", range_left->get_range());
    // RCLCPP_INFO(get_logger(), "front: %f", range_front->get_range());

    if ((range_front_left->get_range() + range_front_right->get_range()) / 2 > 0.16) {
        auto cmd_arg_vel = align_controller_.get_command(0.0, range_left->get_range() - range_right->get_range(), get_time_stamp_());
        motors->set_velocity(0.7, cmd_arg_vel);
    } else if ((range_front_left->get_range() + range_front_right->get_range()) / 2 > 0.06) {
        auto cmd_arg_vel = align_controller_.get_command(0.0, range_front_left->get_range() - range_front_right->get_range(), get_time_stamp_());
        motors->set_velocity(0.3, cmd_arg_vel);
    } else {
        auto cmd_arg_vel = align_controller_.get_command(3.14, motors->get_angle(), get_time_stamp_());
        motors->set_velocity(0.0, cmd_arg_vel);
    }
}
}  // namespace micromouse
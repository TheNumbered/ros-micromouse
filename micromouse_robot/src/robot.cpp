#include "micromouse_robot/robot.hpp"

namespace micromouse {

Robot::Robot(std::function<float()> get_time_stamp)
    : get_time_stamp_{get_time_stamp}
    , align_controller_(1.3, 0.3, 0.0)
    , rotate_controller_(0.9, 0.8, 0.000000000000001)
    , robot_direction_{directions::NORTH}
    , command_linear_velocity_{0.0}
    , command_angular_velocity_{0.0}
    , command_angle_{0.0}
    , is_rotating_{false} {
    range_left = std::make_shared<RclcppRangeSensor>("range_sensor_left");
    range_right = std::make_shared<RclcppRangeSensor>("range_sensor_right");
    range_front_left = std::make_shared<RclcppRangeSensor>("range_sensor_front_left");
    range_front_right = std::make_shared<RclcppRangeSensor>("range_sensor_front_right");

    imu = std::make_shared<RclcppImu>();
    motors = std::make_shared<RclcppMotors>();
    std::srand(std::time(nullptr));
}

void Robot::update() {
    auto left_range = range_left->get_range();
    auto right_range = range_right->get_range();
    auto front_left_range = range_front_left->get_range();
    auto front_right_range = range_front_right->get_range();
    if (get_forward_range() < FIELD_SIZE / 2 and not is_rotating_) {
        if (left_range > FIELD_SIZE) {
            command_angle_ -= M_PI / 2;
        } else if (right_range > FIELD_SIZE) {
            command_angle_ += M_PI / 2;
        } else {
            command_angle_ += M_PI;
        }

        command_angle_ = command_angle_ > M_PI ? command_angle_ - 2 * M_PI : command_angle_;
        command_angle_ = command_angle_ < -1 * M_PI ? command_angle_ + 2 * M_PI : command_angle_;
        if (command_angle_)
            is_rotating_ = true;
    } else if (is_rotating_) {
        command_angular_velocity_ = rotate_controller_.get_command(command_angle_, get_filtered_angle(), get_time_stamp_());
        command_linear_velocity_ = 0.0;
    } else if (not is_rotating_) {
        command_linear_velocity_ = 0.5;

        if (left_range < FIELD_SIZE / 2 and right_range < FIELD_SIZE / 2) {
            command_angular_velocity_ = align_controller_.get_command(0.0, left_range - right_range, get_time_stamp_());
        } else if (left_range < FIELD_SIZE / 2) {
            command_angular_velocity_ = align_controller_.get_command(FIELD_SIZE / 4, left_range, get_time_stamp_());
        } else if (right_range < FIELD_SIZE / 2) {
            command_angular_velocity_ = -align_controller_.get_command(FIELD_SIZE / 4, right_range, get_time_stamp_());
        }
    }

    if (float_equal(get_filtered_angle(), command_angle_)) {
        is_rotating_ = false;
    }

    motors->set_velocity(command_linear_velocity_, command_angular_velocity_);
}

float Robot::get_filtered_angle() {
    return imu->get_angle();
}

float Robot::get_forward_range() {
    return (range_front_left->get_range() + range_front_right->get_range()) / 2;
}

}  // namespace micromouse
#include <rclcpp/rclcpp.hpp>

#include "micromouse_robot/robot.hpp"

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<micromouse::Robot>());
    rclcpp::shutdown();
    return 0;
}
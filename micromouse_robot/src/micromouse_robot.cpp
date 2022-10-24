#include <rclcpp/rclcpp.hpp>

#include "micromouse_robot/robot.hpp"

class MicromouseRobot : public rclcpp::Node {
   public:
    MicromouseRobot()
        : rclcpp::Node("micromous_robot"), robot([this]() -> double { return get_clock()->now().seconds(); }) {
        using namespace std::chrono_literals;
        timer_ = create_wall_timer(100ms, std::bind(&MicromouseRobot::callback, this));
    }
    micromouse::Robot robot;

   private:
    rclcpp::TimerBase::SharedPtr timer_;
    void callback(){
        robot.update();
    }
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MicromouseRobot>());
    rclcpp::shutdown();
    return 0;
}
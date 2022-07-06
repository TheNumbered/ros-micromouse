#include "micromouse_robot/rclcpp_range_sensor.hpp"
using std::placeholders::_1;
namespace micromouse {
RclcppRangeSensor::RclcppRangeSensor(const std::string name)
    : RangeSensorInterface(name), rclcpp::Node(name){
    RCLCPP_INFO(get_logger(), "Created range sensor: %s", name_.c_str());
    range_sub_ = this->create_subscription<sensor_msgs::msg::Range>(name + "/out", 10, std::bind(&RclcppRangeSensor::sensor_callback_, this, _1));
}

double RclcppRangeSensor::get_range() {
    rclcpp::WaitSet wait_set;
    wait_set.add_subscription(range_sub_);
    auto ret = wait_set.wait(std::chrono::microseconds(100));
    if (ret.kind() == rclcpp::WaitResultKind::Ready) {
        sensor_msgs::msg::Range msg;
        rclcpp::MessageInfo info;
        auto ret_take = range_sub_->take(msg, info);
        if (ret_take) {
            RCLCPP_DEBUG(this->get_logger(), "got message: %f", msg.range);
            range_ = msg.range;
        }
    }
    wait_set.remove_subscription(range_sub_);
    return range_;
}

void RclcppRangeSensor::sensor_callback_(const sensor_msgs::msg::Range &msg) {
    range_ = msg.range;
    RCLCPP_INFO(get_logger(), "Range: %f", msg.range);
}
}  // namespace micromouse
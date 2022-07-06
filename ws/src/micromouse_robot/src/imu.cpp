#include "micromouse_robot/imu.hpp"
using std::placeholders::_1;
namespace micromouse {
Imu::Imu()
    : rclcpp::Node("imu_listener"), angle_{std::numeric_limits<double>::quiet_NaN()} {

    imu_sub_ = create_subscription<sensor_msgs::msg::Imu>("imu", 10, std::bind(&Imu::imu_callback_, this, _1));
}

double Imu::get_angle() {
    rclcpp::WaitSet wait_set;
    wait_set.add_subscription(imu_sub_);
    auto ret = wait_set.wait(std::chrono::microseconds(100));
    if (ret.kind() == rclcpp::WaitResultKind::Ready) {
        sensor_msgs::msg::Imu msg;
        rclcpp::MessageInfo info;
        auto ret_take = imu_sub_->take(msg, info);
        if (ret_take) {
            tf2::Quaternion q(
                msg.orientation.x,
                msg.orientation.y,
                msg.orientation.z,
                msg.orientation.w);
            tf2::Matrix3x3 m(q);
            double roll, pitch, yaw;
            m.getRPY(roll, pitch, yaw);
            angle_ = yaw;
        }
    }
    wait_set.remove_subscription(imu_sub_);
    return angle_;
}

void Imu::imu_callback_(const sensor_msgs::msg::Imu &msg) {
    tf2::Quaternion q(
        msg.orientation.x,
        msg.orientation.y,
        msg.orientation.z,
        msg.orientation.w);
    tf2::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);
    angle_ = yaw;
}
}  // namespace micromouse
#include "micromouse_robot/rclcpp_motors.hpp"
using std::placeholders::_1;

namespace micromouse {
RclcppMotors::RclcppMotors()
    : MotorsInterface(), rclcpp::Node("micromouse_motors") {
    cmd_vel_pub_ = create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
    odom_sub_ = create_subscription<nav_msgs::msg::Odometry>("odom", 100, std::bind(&RclcppMotors::odom_callback_, this, _1));
}

void RclcppMotors::set_velocity(float linear_velocity_m_per_s, float angular_velocity_rad_per_s) {
    auto message = geometry_msgs::msg::Twist();
    message.linear.x = linear_velocity_m_per_s;
    message.angular.z = angular_velocity_rad_per_s;
    cmd_vel_pub_->publish(message);
}

float RclcppMotors::get_linear_velocity() {
    rclcpp::WaitSet wait_set;
    wait_set.add_subscription(odom_sub_);
    auto ret = wait_set.wait(std::chrono::microseconds(100));
    if (ret.kind() == rclcpp::WaitResultKind::Ready) {
        nav_msgs::msg::Odometry msg;
        rclcpp::MessageInfo info;
        auto ret_take = odom_sub_->take(msg, info);
        if (ret_take) {
            linear_velocity_m_per_s_ = static_cast<float>(msg.twist.twist.linear.x);
        }
    }
    wait_set.remove_subscription(odom_sub_);
    return linear_velocity_m_per_s_;
}

float RclcppMotors::get_angular_velocity() {
    rclcpp::WaitSet wait_set;
    wait_set.add_subscription(odom_sub_);
    auto ret = wait_set.wait(std::chrono::microseconds(100));
    if (ret.kind() == rclcpp::WaitResultKind::Ready) {
        nav_msgs::msg::Odometry msg;
        rclcpp::MessageInfo info;
        auto ret_take = odom_sub_->take(msg, info);
        if (ret_take) {
            angular_velocity_rad_per_s_ = static_cast<float>(msg.twist.twist.angular.z);
        }
    }
    wait_set.remove_subscription(odom_sub_);
    return angular_velocity_rad_per_s_;
}

float RclcppMotors::get_angle() {
    rclcpp::WaitSet wait_set;
    wait_set.add_subscription(odom_sub_);
    auto ret = wait_set.wait(std::chrono::microseconds(100));
    if (ret.kind() == rclcpp::WaitResultKind::Ready) {
        nav_msgs::msg::Odometry msg;
        rclcpp::MessageInfo info;
        auto ret_take = odom_sub_->take(msg, info);
        if (ret_take) {
            tf2::Quaternion q(
                msg.pose.pose.orientation.x,
                msg.pose.pose.orientation.y,
                msg.pose.pose.orientation.z,
                msg.pose.pose.orientation.w);
            tf2::Matrix3x3 m(q);
            double roll, pitch, yaw;
            m.getRPY(roll, pitch, yaw);
            angle_rad_ = yaw;
        }
    }
    wait_set.remove_subscription(odom_sub_);
    return angle_rad_;
}

Quaternion RclcppMotors::get_quaternion() {
    rclcpp::WaitSet wait_set;
    wait_set.add_subscription(odom_sub_);
    auto ret = wait_set.wait(std::chrono::microseconds(100));
    if (ret.kind() == rclcpp::WaitResultKind::Ready) {
        nav_msgs::msg::Odometry msg;
        rclcpp::MessageInfo info;
        auto ret_take = odom_sub_->take(msg, info);
        if (ret_take) {
            quaternion_ = Quaternion{static_cast<float>(msg.pose.pose.orientation.x),
                           static_cast<float>(msg.pose.pose.orientation.y),
                           static_cast<float>(msg.pose.pose.orientation.z),
                           static_cast<float>(msg.pose.pose.orientation.w)};
        }
    }
    wait_set.remove_subscription(odom_sub_);
    return quaternion_;
}

Position2D RclcppMotors::get_position() {
    rclcpp::WaitSet wait_set;
    wait_set.add_subscription(odom_sub_);
    auto ret = wait_set.wait(std::chrono::microseconds(100));
    if (ret.kind() == rclcpp::WaitResultKind::Ready) {
        nav_msgs::msg::Odometry msg;
        rclcpp::MessageInfo info;
        auto ret_take = odom_sub_->take(msg, info);
        if (ret_take) {
            position_ = {static_cast<float>(msg.pose.pose.position.x),
                         static_cast<float>(msg.pose.pose.position.y)};
        }
    }
    wait_set.remove_subscription(odom_sub_);
    return position_;
}

void RclcppMotors::odom_callback_(const nav_msgs::msg::Odometry &msg) {
    tf2::Quaternion q(
        msg.pose.pose.orientation.x,
        msg.pose.pose.orientation.y,
        msg.pose.pose.orientation.z,
        msg.pose.pose.orientation.w);
    tf2::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);
    angle_rad_ = yaw;
    position_ = {static_cast<float>(msg.pose.pose.position.x),
                 static_cast<float>(msg.pose.pose.position.y)};
}
}  // namespace micromouse
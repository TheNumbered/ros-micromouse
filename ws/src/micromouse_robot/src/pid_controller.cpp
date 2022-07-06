#include "micromouse_robot/pid_controller.hpp"

namespace micromouse {
PidController::PidController(double kp, double kd, double ki)
    : kp_{kp}, kd_{kd}, ki_{ki}, last_error_{0.0}, integral_{0.0}, last_time_{0.0} {
}
double PidController::get_command(double command, double state, double time) {
    auto dt = time - last_time_;
    auto error = command - state;

    auto divide = kd_ * (last_error_ - error) / dt;
    auto proportional = kp_ * error;
    integral_ = ki_ * (integral_ + dt * error);
    last_error_ = error;

    // Check if nan
    if(integral_ != integral_){
        integral_ = 0.0;
    }
    return divide + proportional + integral_;
}
}  // namespace micromouse
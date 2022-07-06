#include "micromouse_robot/pid_controller.hpp"

namespace micromouse {
PidController::PidController(float kp, float kd, float ki)
    : kp_{kp}, kd_{kd}, ki_{ki}, last_error_{0.0}, integral_{0.0}, last_time_{0.0} {
}
float PidController::get_command(float command, float state, float time) {
    auto dt = time - last_time_;
    auto error = command - state;

    auto divide = kd_ * (last_error_ - error) / dt;
    auto proportional = kp_ * error;
    integral_ =  integral_ + dt * error;
    last_error_ = error;

    // Check if nan
    if(integral_ != integral_){
        integral_ = 0.0;
    }
    auto val = divide + proportional + ki_ * integral_;
    if(val != val){
        val = 0.0;
    }
    return val;
}
}  // namespace micromouse
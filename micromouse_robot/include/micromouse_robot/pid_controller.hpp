#pragma once

namespace micromouse{
class PidController {
   public:
    PidController(float kp, float kd, float ki);
    float get_command(float command, float state, float time);

   private:
    float kp_;
    float kd_;
    float ki_;

    float last_error_;
    float integral_;
    float last_time_;
};
}  // namespace
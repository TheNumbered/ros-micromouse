#pragma once
namespace micromouse{
class PidController {
   public:
    PidController(double kp, double kd, double ki);
    double get_command(double command, double state, double time);

   private:
    double kp_;
    double kd_;
    double ki_;

    double last_error_;
    double integral_;
    double last_time_;
};
}  // namespace
#include "doosan_gcode.h"

namespace dgc
{
    void DoosanGCode::G0_()
    {
        std::cout << "G0" << std::endl;
        for (int i = 0; i < 3; i++){
            std::cout << new_XYZ_[i] << ' ';
        }
        std::cout << feedrate_;
        std::cout << std::endl;

        target_vel[0] = feedrate_;

        std::array<float, 6> target = {new_XYZ_[0] + 400, new_XYZ_[1] + 0, new_XYZ_[2] + 400, 180, 180, 180};
        robot->servol(target, target_vel, target_acc);
    }

    void DoosanGCode::G1_()
    {
        std::cout << "G1: " << std::endl;
        for (int i = 0; i < 3; i++){
            std::cout << new_XYZ_[i] << ' ';
        }
        std::cout << feedrate_;
        std::cout << std::endl;

        target_vel[0] = feedrate_;

        std::array<float, 6> target = {new_XYZ_[0] + 400, new_XYZ_[1] + 0, new_XYZ_[2] + 400, 180, 180, 180};
        robot->servol(target, target_vel, target_acc);
    }

    void DoosanGCode::G28_()
    {
        std::cout << "---" << std::endl;
        std::cout << "G28" << std::endl;
        std::cout << "---" << std::endl;

        std::array<float, 6> target = {400, 0, -100 + 400, 180, 180, 180};

        robot->movel(target, default_max_vel, default_max_acc);
    }

}

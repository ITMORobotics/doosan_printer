#include "doosan_gcode.h"

namespace dgc
{
    void DoosanGCode::G0_() // MoveL (Long path movement)
    {
        std::cout << "G0" << std::endl;
        for (int i = 0; i < 3; i++){
            std::cout << new_XYZ_[i] << ' ';
        }
        std::cout << feedrate_;
        std::cout << " MoveL" << std::endl;

        target_vel[0] = feedrate_;

        std::array<float, 6> target = table_frame;
        target[0] += new_XYZ_[0];
        target[1] += new_XYZ_[1];
        target[2] += new_XYZ_[2];

        robot->movel(target, target_vel, target_acc);
    }

    void DoosanGCode::G1_() // ServoL
    {
        std::cout << "G1: " << std::endl;
        for (int i = 0; i < 3; i++){
            std::cout << new_XYZ_[i] << ' ';
        }
        std::cout << feedrate_;
        std::cout << " ServoL" << std::endl;

        target_vel[0] = feedrate_;

        std::array<float, 6> target = table_frame;
        target[0] += new_XYZ_[0];
        target[1] += new_XYZ_[1];
        target[2] += new_XYZ_[2];

        robot->servol(target, target_vel, target_acc, 0.0);
    }

    void DoosanGCode::G28_() // MoveL (Long path movement)
    {
        std::cout << "---" << std::endl;
        std::cout << "G28" << std::endl;
        std::cout << "---" << std::endl;

        std::array<float, 6> target = table_frame;
        target[2] += 0.1;

        robot->movel(target, default_max_vel, default_max_acc);
    }

}

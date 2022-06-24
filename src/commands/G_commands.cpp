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

        std::array<float,2> delta_XYZ = {
            new_XYZ_[0] - last_XYZ_[0],
            new_XYZ_[1] - last_XYZ_[1]
        };
        float XYZ_vector_length = sqrt(
            delta_XYZ[0]*delta_XYZ[0] + delta_XYZ[1]*delta_XYZ[1]
        );

        target_vel[0] = delta_XYZ[0]*feedrate_*0.06/XYZ_vector_length;
        target_vel[1] = delta_XYZ[1]*feedrate_*0.06/XYZ_vector_length;

        std::cout << "Target velocity: " << target_vel[0] << ", " << target_vel[1] << std::endl;

        std::array<float, 6> target = table_frame;
        target[0] += new_XYZ_[0];
        target[1] += new_XYZ_[1];
        target[2] += new_XYZ_[2];


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


        std::array<float,2> delta_XYZ = {
            new_XYZ_[0] - last_XYZ_[0],
            new_XYZ_[1] - last_XYZ_[1]
        };
        float XYZ_vector_length = sqrt(
            delta_XYZ[0]*delta_XYZ[0] + delta_XYZ[1]*delta_XYZ[1]
        );

        target_vel[0] = delta_XYZ[0]*feedrate_*0.06/XYZ_vector_length;
        target_vel[1] = delta_XYZ[1]*feedrate_*0.06/XYZ_vector_length;

        std::cout << "Target velocity: " << target_vel[0] << ", " << target_vel[1] << std::endl;
        std::array<float, 6> target = table_frame;
        target[0] += new_XYZ_[0];
        target[1] += new_XYZ_[1];
        target[2] += new_XYZ_[2];

        robot->servol(target, target_vel, target_acc);
    }

    void DoosanGCode::G28_()
    {
        std::cout << "---" << std::endl;
        std::cout << "G28" << std::endl;
        std::cout << "---" << std::endl;

        std::array<float, 6> target = table_frame;
        target[2] += 0.1;

        robot->movel(target, default_max_vel, default_max_acc);
    }

}

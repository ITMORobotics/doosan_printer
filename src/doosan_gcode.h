#pragma once

#include <vector>
#include <array>
#include <cmath>
#include <string>
#include <fstream>
#include <streambuf>
#include <memory>
#include "parser.h"

#include <doosan_control.h>

namespace dgc
{

    class DoosanGCode
    {
        private:
            std::array<double, 3>   last_XYZ_; // X, Y, Z
            std::array<double, 3>   new_XYZ_;  // X, Y, Z
            std::array<float, 6>    target_pos;
            std::array<float, 2>    target_vel;
            std::array<float, 2>    target_acc; // mm/s^2

            // Table frame, home position
            std::array<float, 6>    table_frame;

            std::array<float, 2>    default_max_vel;
            std::array<float, 2>    default_max_acc; // mm/s^2

            char last_cmd_;         // which cmd: G or M
            uint16_t m_cmd_;        // number of cmd M like (M28)
            uint16_t g_cmd_;        // number of cmd G like (G1)
            uint16_t feedrate_;     // the amount to extrude between the starting point and ending point
            double extrude_;        // The feedrate per minute of the move between the starting point and ending point
            uint8_t cmd_;           // variable to known which parameters contain new line
            void chunkProcessing_(gpr::chunk chunk);

            DoosanRobot * robot;

            // ================= Commands ====================
            void command_execute_();
            void G0_();
            void G1_();
            void G28_();

            // ===============================================

        public:
            DoosanGCode();
            void parseLine(std::string gcode);
    };


}

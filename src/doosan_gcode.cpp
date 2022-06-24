#include "doosan_gcode.h"

#include <memory>

namespace dgc
{
    DoosanGCode::DoosanGCode()
    {
        std::cout << "DoosanGCode::DoosanGCode" << std::endl;
        robot = new DoosanRobot();
        if (!robot->init()) {
            std::cout << "[doosan_control] Error initializing robot" << std::endl;
        }

        // Move home
        robot->move_home();
        usleep(100000);

        // Joint movements
        std::array<float, NUM_JOINT> testJointTarget = {0, 0, 90, 0, 90, 0};
        float maxSpeed = 100;
        float maxAccel = 100;

        std::cout << "Move joint" << std::endl;
        if (!robot->movej(testJointTarget, maxSpeed, maxAccel)) {
            std::cout << "[movej] something wrong" << std::endl;
        }

        // robot->set_robot_mode(ROBOT_MODE_AUTONOMOUS);
        robot->set_robot_speed_mode(SPEED_NORMAL_MODE);

        default_max_vel = {500, 360};
        default_max_acc = {500, 360};

        target_vel = default_max_vel;
        target_acc = default_max_acc;

        last_XYZ_ = {0, 0, 0};
        new_XYZ_ = {0, 0, 0};
    };

    void DoosanGCode::parseLine(std::string gcode)
    {
        // Parse line using parse_gcode
        // There is only one line in gcode, so it is only one block
        gpr::block current_block = gpr::parse_gcode(gcode).get_block(0);
        int chunkSize = current_block.size();
        cmd_ = 0;

        for (int i = 0; i < chunkSize; ++i)
        {
            gpr::chunk chunk = current_block.get_chunk(i);

            switch(chunk.tp())
            {
                case gpr::CHUNK_TYPE_WORD_ADDRESS:
                    chunkProcessing_(chunk);
                    break;
                case gpr::CHUNK_TYPE_PERCENT:
                    std::cout << "CHUNK_TYPE_PERCENT" << std::endl;
                    break;
                case gpr::CHUNK_TYPE_WORD:
                    std::cout << "CHUNK_TYPE_WORD" << std::endl;
                    break;
            }
        }

        // run command
        command_execute_();
        // update XYZ state
        last_XYZ_ = new_XYZ_;
    }

    void DoosanGCode::command_execute_()
    {
        if (last_cmd_ == 'G')
        {
            switch (g_cmd_)
            {
                case 0:
                    G0_();
                    break;
                case 1:
                    G1_();
                    break;
                case 28:
                    G28_();
                    break;
            }
        }
        if (last_cmd_ == 'M')
        {

        }
    }

    void DoosanGCode::chunkProcessing_(gpr::chunk chunk)
    {
        // =============== address =============
        gpr::addr addr = chunk.get_address();
        // =============== word =============
        switch (chunk.get_word())
        {
            case 'G':
                last_cmd_ = 'G';
                g_cmd_ = addr.int_value();
                cmd_ |= 1 << 1;
                break;
            case 'M':
                last_cmd_ = 'M';
                m_cmd_ = addr.int_value();
                cmd_ |= 1 << 1;
                break;
            case 'X':
                new_XYZ_[0] = addr.tp() == gpr::ADDRESS_TYPE_DOUBLE ? addr.double_value() : addr.int_value();
                cmd_ |= 1 << 2;
                break;
            case 'Y':
                new_XYZ_[1] = addr.tp() == gpr::ADDRESS_TYPE_DOUBLE ? addr.double_value() : addr.int_value();
                cmd_ |= 1 << 3;
                break;
            case 'Z':
                new_XYZ_[2] = addr.tp() == gpr::ADDRESS_TYPE_DOUBLE ? addr.double_value() : addr.int_value();
                cmd_ |= 1 << 4;
                break;
            case 'E':
                extrude_ = addr.double_value();
                cmd_ |= 1 << 5;
                break;
            case 'F':
                feedrate_ = addr.double_value();
                cmd_ |= 1 << 6;
                break;
            default:break;
        }
    }
}

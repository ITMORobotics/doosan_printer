#include "parser.h"
#include "doosan_gcode.h"

#include <string>
#include <fstream>
#include <streambuf>

using namespace gpr;
using namespace std;

// This example program shows how to create your own blocks and print them out,
// and how to use the parser. To create a custom block and print it out just type:
//     ./parse-gcode
// at the command line
// To parse a G-code file type:
//     ./parse-gcode <path-to-gcode-file>
int main(int argc, char** argv)
{

    dgc::DoosanGCode dg;

    if (argc == 1) {

        std::string gcode = "G28 ;Home";
        dg.parseLine(gcode);

        gcode = "G1 Z15.0 F3000 ;Move the platform down 15mm";
        dg.parseLine(gcode);

        gcode = "G0 F3600 X43.256 Y45.828 Z0.3";
        dg.parseLine(gcode);

    } else {

        assert(argc == 2);

        string file = argv[1];
        std::ifstream t(file);

        std::string file_contents((std::istreambuf_iterator<char>(t)),
                std::istreambuf_iterator<char>());
        gpr::gcode_program p = parse_gcode(file_contents);

        for (std::vector<gpr::block>::iterator ptr = p.begin(); ptr < p.end(); ptr++) {
            // std::cout << ptr->to_string() << std::endl;
            dg.parseLine(ptr->to_string());
            usleep(10000);
        }

    }
}

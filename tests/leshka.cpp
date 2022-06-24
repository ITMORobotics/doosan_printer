#include "parser.h"

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
int main(int argc, char** argv) {
    if (argc == 1) {
        cout << "We are going to create a new block programatically ";
        cout << "and print it out:" << endl;

        chunk G1 = make_word_int('G', 1);
        chunk X1pt7 = make_word_double('X', 1.7);
        chunk YN1 = make_word_double('Y', -1.0);
        chunk comment = make_comment('(', ')', "This is a silly comment");

        block artificial_block(false, {G1, X1pt7, YN1, comment});
        // The call to set_text is only relevant for debugging. It sets the block
        // member variable block_text to a string representation of the block so
        // that you can see a compact representation of the block during debugging
        artificial_block.set_debug_text();

        cout << artificial_block << endl;
    } else {
        unsigned int log_out = 0;
        assert(argc == 2);

        string file = argv[1];

        std::ifstream t(file);

        std::string file_contents((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
        gcode_program p = parse_gcode(file_contents);

        for (size_t i = 0; i < 15; ++i) {
            cout << "num blocks " << p.num_blocks() << endl;
            cout << "block " << i << " " << p.get_block(i) << endl;
            cout << "block type " << p.get_block(i).get_chunk(0).tp() << endl; // CHUNK_TYPE_COMMENT
            cout << "---" << endl;
            // cout << p << endl;
        }

        size_t i = 11;
        cout << "num blocks " << p.num_blocks() << endl;
        cout << "block " << i << " " << p.get_block(i) << endl;
        cout << "chunk size " << p.get_block(i).size() << endl;
        cout << "chunk 0 " << p.get_block(i).get_chunk(0).get_address().int_value() << endl;
        cout << "chunk 1 word " << p.get_block(i).get_chunk(0).get_word() << endl;
        cout << "block type " << p.get_block(i).get_chunk(0).tp() << endl;
        cout << "---" << endl;

        i = 32;
        cout << "num blocks " << p.num_blocks() << endl;
        cout << "block " << i << " " << p.get_block(i) << endl;
        cout << "chunk size " << p.get_block(i).size() << endl;
        cout << "chunk 0 " << p.get_block(i).get_chunk(0) << endl;
        cout << "block type " << p.get_block(i).get_chunk(0).tp() << endl;


    }
}

#include "parser.h"
#include "doosan_gcode.h"

#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

const int max_length = 1024;
dgc::DoosanGCode * dg;

void session(tcp::socket sock)
{
    try
    {
        for (;;)
        {
            char data[max_length];

            boost::system::error_code error;
            size_t length = sock.read_some(boost::asio::buffer(data), error);
            if (error == boost::asio::error::eof)
            break; // Connection closed cleanly by peer.
            else if (error)
            throw boost::system::system_error(error); // Some other error.

            std::cout << "received data: " << data << std::endl;
            dg->parseLine(std::string(data));
            boost::asio::write(sock, boost::asio::buffer(data, length));
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}

void server(boost::asio::io_context& io_context, std::string host, unsigned short port)
{
    tcp::acceptor a(io_context, tcp::endpoint(boost::asio::ip::address::from_string(host), port));
    for (;;)
    {
        std::thread(session, a.accept()).detach();
    }
}

int main(int argc, char** argv) {


    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: tcp_printer <ip> <port>\n";
            return 1;
        }

        dg = new dgc::DoosanGCode();

        boost::asio::io_context io_context;

        std::cout << "input data: " << std::string(argv[1]) << ", " << std::atoi(argv[2]) << std::endl;
        server(io_context, std::string(argv[1]), std::atoi(argv[2]));
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

#include <asio.hpp>
#include <iostream>
#include "server.hpp"

int main(int argc, char *argv[])
{
    try{
        asio::io_service        io_service;
        asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), 3000);
        my::server              server(io_service, endpoint);

        io_service.run();
    } catch (std::exception& e) {
        std::cerr << "exception: " << e.what() << "\n";
    }

    return 0;
}

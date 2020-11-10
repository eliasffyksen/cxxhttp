
#pragma once
#include "../pch.hpp"

namespace cxxhttp {
    class Server {
    public:
        Server(int port = 8080);
    private:
        int port, sockfd = 0, opt = 1;
        struct sockaddr_in address;
        socklen_t addrlen = sizeof(address);
    };
}
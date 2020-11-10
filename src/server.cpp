
#include "server.hpp"

using namespace cxxhttp;
using namespace std;

Server::Server(int port) : port(port) {
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 

    // Forcefully attaching socket to the port 8080 
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 

    // Forcefully attaching socket to the port 8080 
    if (bind(sockfd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 

    if (listen(sockfd, 100) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    }

    while (true) {
        int conn = accept(sockfd, (sockaddr *) &address, &addrlen);
        char buf[1024] = {0};
        read(conn, buf, 1024);
        string content = "Hello World, form C++! :)";
        string resp = "HTTP/1.1 200 OK\n";
        resp += "Connection: close\n";
        resp += "Content-Length: " + to_string(content.size()) + "\n";
        resp += "\n" + content;
        send(conn, resp.c_str(), resp.size(), 0);
    }
}
#include "Server.h"

int main() {
    int port;
    std::cout << "Enter server port number: ";
    std::cin >> port;
    Server *server=new Server(port);

    try {
        server->startListening();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

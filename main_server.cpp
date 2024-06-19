#include "inc/Server.h"

int main() {
    int port;
    std::cout << "Enter server port number: ";
    std::cin >> port;
    Server server(port);

    try {
        server.startListening();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

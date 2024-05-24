#include <iostream>
#include <thread>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>

void scan_port(const char* host, int port, std::vector<int>& open_ports) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        return;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    struct in_addr host_addr;
    if (inet_pton(AF_INET, host, &host_addr) != 1) {
        close(sock);
        return;
    }

    addr.sin_addr = host_addr;

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == 0) {
        open_ports.push_back(port);
    }

    close(sock);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <host> <start_port> <end_port>" << std::endl;
        return 1;
    }

    const char* host = argv[1];
    int start_port = std::stoi(argv[2]);
    int end_port = std::stoi(argv[3]);

    std::vector<std::thread> threads;
    std::vector<int> open_ports;

    auto start = std::chrono::high_resolution_clock::now();

    for (int port = start_port; port <= end_port; port++) {
        threads.emplace_back(scan_port, host, port, std::ref(open_ports));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    std::cout << "Open ports: ";
    for (int port : open_ports) {
        std::cout << port << " ";
    }
    std::cout << std::endl;

    int hours = duration / 3600;
    int minutes = (duration % 3600) / 60;
    int seconds = duration % 60;

    std::cout << "Port scanning completed in " << hours << " hours, " << minutes << " minutes, " << seconds << " seconds." << std::endl;

    return 0;
}


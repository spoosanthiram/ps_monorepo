#include "sandbox/uptime/charging_network.h"

#include <format>
#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << std::format("{} <input file>", argv[0]) << '\n';
        return 1;
    }

    std::ifstream input_stream{argv[1]};
    if (!input_stream) {
        std::cout << std::format("Couldn't open {} for reading", argv[1]) << '\n';
        return 1;
    }

    sandbox::uptime::ChargingNetwork network;
    network.read_input(input_stream);
    network.print_uptime();

    return 0;
}

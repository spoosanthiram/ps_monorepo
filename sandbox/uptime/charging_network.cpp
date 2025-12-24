#include "sandbox/uptime/charging_network.h"

#include <format>
#include <iostream>
#include <regex>

namespace sandbox::uptime {

void ChargingNetwork::read_input(std::ifstream& input_stream)
{
    std::string line;
    while (std::getline(input_stream, line)) {
        if (line == "[Stations]") {
            read_stations(input_stream);
        }
        else if (line == "[Charger Availability Reports]") {
            read_chargers(input_stream);
        }
    }
}

void ChargingNetwork::read_stations(std::ifstream& input_stream)
{
    const auto pattern = std::regex{R"(\s+)"};

    std::string line;
    while (std::getline(input_stream, line)) {
        if (line.empty()) { // Empty line signifies end of [Stations] section
            break;
        }
        auto it = std::sregex_token_iterator{line.begin(), line.end(), pattern, -1};
        const std::sregex_token_iterator end_it;

        const auto station_id = static_cast<uint32_t>(std::stoi(it->str()));
        auto retval = stations_.emplace(station_id, station_id);
        if (!retval.second) {
            std::cerr << std::format("Duplicate station: {}", station_id) << '\n';
            continue;
        }
        auto& station = retval.first->second;

        for (++it; it != end_it; ++it) {
            const auto charger_id = static_cast<uint32_t>(std::stoi(it->str()));
            station.add_charger(charger_id);
            charger_station_map_.emplace(charger_id, station.id());
        }
    }
}

void ChargingNetwork::read_chargers(std::ifstream& input_stream)
{
    const auto pattern = std::regex{R"((\d+)\s+(\d+)\s+(\d+)\s+(true|false))"};

    std::string line;
    std::smatch matches;
    while (std::getline(input_stream, line)) {
        if (std::regex_match(line, matches, pattern)) {
            const auto charger_id = std::stoi(matches[1].str());
            if (!charger_station_map_.contains(charger_id)) {
                std::cerr << std::format("Charger {} not part of any Stations", charger_id) << '\n';
                continue;
            }
            const auto station_id = charger_station_map_[charger_id];
            const auto start_time = std::stoul(matches[2].str());
            const auto end_time = std::stoul(matches[3].str());
            const auto is_up = matches[4].str() == "true" ? true : false;

            auto& station = stations_.at(station_id);
            station.update_charger_uptime(charger_id, start_time, end_time, is_up);
        }
    }
}

void ChargingNetwork::print_uptime() const
{
    for (auto& [id, station] : stations_) {
        station.print_uptime();
    }
}

} // namespace sandbox::uptime

#pragma once

#include "sandbox/uptime/station.h"

#include <fstream>
#include <map>
#include <unordered_map>

namespace sandbox::uptime {

class ChargingNetwork
{
public:
    void read_input(std::ifstream& input_stream);
    void print_uptime() const;

private:
    /// @brief Read [Stations] section
    void read_stations(std::ifstream& input_stream);

    /// @brief Read [Charger Availability Reports] section
    void read_chargers(std::ifstream& input_stream);

private:
    std::map<uint32_t, Station> stations_;
    std::unordered_map<uint32_t, uint32_t> charger_station_map_;
};

} // namespace sandbox::uptime

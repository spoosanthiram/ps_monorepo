#include "sandbox/uptime/station.h"

#include <format>
#include <iostream>

namespace sandbox::uptime {

void Station::update_charger_uptime(uint32_t charger_id, uint64_t start_time, uint64_t end_time, bool is_up)
{
    if (!chargers_.contains(charger_id)) {
        std::cerr << std::format("Charger {} not part of Station {}", charger_id, id_) << '\n';
        return;
    }
    auto& charger = chargers_[charger_id];
    charger.overall_start_time = std::min(charger.overall_start_time, start_time);
    charger.overall_end_time = std::max(charger.overall_end_time, end_time);
    if (is_up) {
        charger.up_time += (end_time - start_time);
    }
}

void Station::print_uptime() const
{
    uint64_t up_percent = 0;
    for (const auto& [id, charger] : chargers_) {
        up_percent += (charger.up_time * 100) / (charger.overall_end_time - charger.overall_start_time);
    }
    up_percent /= chargers_.size();
    std::cout << std::format("{} {}", id_, up_percent) << '\n';
}

} // namespace sandbox::uptime

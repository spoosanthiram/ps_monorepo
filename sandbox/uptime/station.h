#pragma once

#include <cstdint>
#include <limits>
#include <unordered_map>

namespace sandbox::uptime {

class Station
{
public:
    explicit Station(uint32_t id)
        : id_{id}
    {}

    uint32_t id() const { return id_; }

    /// @brief Add default Charger object to map for the charger_id
    void add_charger(uint32_t charger_id) { chargers_.emplace(charger_id, Charger{}); }

    /// @brief Update the overall_start_time, overall_end_time & up_time
    void update_charger_uptime(uint32_t charger_id, uint64_t start_time, uint64_t end_time, bool is_up);

    /// @brief
    void print_uptime() const;

private:
    struct Charger
    {
        uint64_t overall_start_time{std::numeric_limits<uint64_t>::max()};
        uint64_t overall_end_time{std::numeric_limits<uint64_t>::min()};
        uint64_t up_time{0};
    };

    uint32_t id_;
    std::unordered_map<uint32_t, Charger> chargers_;
};

} // namespace sandbox::uptime

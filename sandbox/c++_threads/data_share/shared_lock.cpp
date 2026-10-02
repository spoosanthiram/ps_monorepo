#include <chrono>
#include <format>
#include <iostream>
#include <map>
#include <mutex>
#include <random>
#include <shared_mutex>
#include <string>
#include <thread>

using namespace std::literals::chrono_literals;

struct DnsEntry
{
    std::string ip_address;
    std::chrono::time_point<std::chrono::system_clock> starting_tp;
};

class DnsCache
{
public:
    std::optional<const DnsEntry> find_entry(std::string_view domain) const;
    void update_or_add_entry(std::string_view domain, const DnsEntry& entry);

private:
    std::map<std::string, DnsEntry> entries_;
    mutable std::shared_mutex entries_mutex_;
};

std::optional<const DnsEntry> DnsCache::find_entry(std::string_view domain) const
{
    const auto t0 = std::chrono::system_clock::now();
    std::shared_lock lck{entries_mutex_};
    const auto it = entries_.find(domain.data());
    std::cout
        << std::format(
               "Querying domain: {} --- start time: {}...duration: {}",
               domain,
               t0,
               std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - t0).count())
        << '\n';
    return (it != entries_.end()) ? std::make_optional<const DnsEntry>(it->second) : std::optional<const DnsEntry>{};
}

void DnsCache::update_or_add_entry(std::string_view domain, const DnsEntry& entry)
{
    std::scoped_lock lck{entries_mutex_};
    entries_[domain.data()] = entry;
    std::this_thread::sleep_for(1s);
    std::cout << std::format("Adding domain: {}, start time: {}...end time: {}",
                             domain,
                             entry.starting_tp,
                             std::chrono::system_clock::now())
              << '\n';
}

DnsCache dns_cache;
std::atomic_bool find_entries_flag = true;

std::vector<std::string_view> domains{"sarvanz.com", "sarvanz.in", "sarvanz.xyz", "xyz.com"};

std::default_random_engine random_engine;

void add_entries()
{
    std::uniform_int_distribution<> add_entries_interval_dist{3, 6}; // to simulate rare operation: add entries

    DnsEntry entry;
    uint32_t ip_val = 1;
    for (const auto& domain : domains) {
        entry.ip_address = std::format("192.168.1.{}", ip_val);
        entry.starting_tp = std::chrono::system_clock::now();

        dns_cache.update_or_add_entry(domain, entry);

        ++ip_val;
        std::this_thread::sleep_for(std::chrono::seconds{add_entries_interval_dist(random_engine)});
    }
}

void find_entries()
{
    std::uniform_int_distribution<> find_entries_interval_dist{0, 1}; // to simulate frequent find entries

    while (find_entries_flag) {
        for (const auto& domain : domains) {
            const auto entry_opt = dns_cache.find_entry(domain);
            if (entry_opt) {
                const auto& entry = entry_opt.value();
                std::cout << std::format("{}: {}", domain, entry.ip_address) << '\n';
            }
            std::this_thread::sleep_for(std::chrono::seconds{find_entries_interval_dist(random_engine)});
        }
    }
}

int main()
{
    std::random_device rd{};
    random_engine.seed(rd());

    std::jthread add_entries_thread{add_entries};
    std::jthread find_entries_thread{find_entries};

    std::this_thread::sleep_for(30s);
    find_entries_flag = false;

    return 0;
}

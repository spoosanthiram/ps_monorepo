#include <chrono>
#include <format>
#include <iostream>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>

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
    std::shared_lock lck{entries_mutex_};
    const auto it = entries_.find(domain.data());
    return (it != entries_.end()) ? std::make_optional<const DnsEntry>(it->second) : std::optional<const DnsEntry>{};
}

void DnsCache::update_or_add_entry(std::string_view domain, const DnsEntry& entry)
{
    std::scoped_lock lck{entries_mutex_};
    entries_[domain.data()] = entry;
}

DnsCache dns_cache;
std::atomic_bool add_entries_flag = true;
std::atomic_bool find_entries_flag = true;

std::vector<std::string_view> domains{"sarvanz.com", "sarvanz.in", "sarvanz.xyz", "xyz.com"};

using namespace std::chrono_literals;

void add_entries()
{
    while (add_entries_flag) {
        DnsEntry entry;

        uint32_t ip_val = 1;
        for (const auto& domain : domains) {
            entry.ip_address = std::format("192.168.1.{}", ip_val);
            entry.starting_tp = std::chrono::system_clock::now();

            dns_cache.update_or_add_entry(domain, entry);
            std::this_thread::sleep_for(5s);

            ++ip_val;
        }
    }
}

void find_entries()
{
    while (find_entries_flag) {
        for (const auto& domain : domains) {
            const auto entry_opt = dns_cache.find_entry(domain);
            if (entry_opt) {
                const auto& entry = entry_opt.value();
                std::cout << std::format("{}: {}, {}", domain, entry.ip_address, entry.starting_tp) << '\n';
            }
            std::this_thread::sleep_for(1s);
        }
    }
}

int main()
{
    std::jthread add_entries_thread{add_entries};
    std::jthread find_entries_thread{find_entries};

    std::this_thread::sleep_for(30s);
    find_entries_flag = false;
    add_entries_flag = false;

    return 0;
}

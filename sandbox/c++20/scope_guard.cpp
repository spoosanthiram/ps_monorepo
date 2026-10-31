#include <functional>
#include <iostream>

template <typename Arg>
class ScopeGuard
{
public:
    explicit ScopeGuard(Arg&& func)
        : func_{std::forward<Arg>(func)}
        , active_{true}
    {}
    ~ScopeGuard()
    {
        if (active_) {
            func_();
        }
    }

    ScopeGuard(ScopeGuard&& other)
        : func_{other.func_}
        , active_{other.active_}
    {
        other.active_ = false;
    }

    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;
    ScopeGuard& operator=(ScopeGuard&&) = delete;

private:
    Arg func_;
    bool active_{false};
};

int main()
{
    auto x = std::make_unique<int>(4);
    ScopeGuard scope_guard{[y = *x]() { std::cout << "Good bye: " << y << "!!\n"; }};
    ScopeGuard guard2 = std::move(scope_guard);
    std::cout << "Hello!\n";

    return 0;
}
